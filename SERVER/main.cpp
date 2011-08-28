#include <iostream>
#include <cstdlib>

#include <string>
#include <sstream>
#include <cmath>
#include <vector>//Pour les tableaux dynamiques
#include <fstream>//Manips de fichiers
#include <ctime> //temps, random

#include <SFML/Network.hpp>

#include "main.h"
#include "world.h"
#include "Vfx.h"
#include "convert.h"
#include "utils.h"
#include "Player.h"

#include "threads.h"


#include "version.h"


sf::Uint16 nWorld[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE] = {{0}};
sf::Uint16 nWorldSpe[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE] = {{0}};

PlayerHandler::PlayerHandler oPlayerHandler;


bool bStopThreads=false;
bool bAttenteSynchro=false;

std::string sServerName="noname server";
std::string sMapName="noname_map";
sf::Uint16 nGameType=0;
sf::Uint16 nTeamNb=0;
sf::Uint16 nPlayersConnected=0;
sf::Uint16 nUnsecuredPort=0;//Port dédié à l'envoi UDP (rafraichissement des positions, effets...)
sf::Uint16 nSecuredPort=0;//Port dédié à l'envoi/réception TCP (Actions du joueur, questions du joueur...)

bool bRedTeam;
bool bGreenTeam;
bool bBlueTeam;



using namespace sf;
//===================================================================================================================
//===================================================================================================================
//Temps
Clock clkDateGame;
//===================================================================================================================
//===================================================================================================================
Vfx::Vfx oVfx;
//===================================================================================================================
//===================================================================================================================


int main()
{
    using namespace std;

    cout<<"=====================================SERVER====================================="<<endl;
    cout<<"CROMGame Server version : "<<RC_FILEVERSION_STRING<<endl;


    //Chargement des images ===========================================
    cout<<"Loading data...";

    sf::Clock clkDateFrame;
    clkDateGame.Reset();

    //Init du random
    srand(time(NULL));

    cout<<"Done"<<endl;
    //==================================================================

    bool bRedFlag;
    bool bGreenFlag;
    bool bBlueFlag;

    do
    {
        string sInput("");
        bool bSuccess=false;
        do
        {
            cout<<"================================================================================"<<endl;
            cout<<"Quelle map charger ?   ";

            cin>>sInput;

            bSuccess = LoadMap(sInput);
        }while(!bSuccess);

        sMapName=sInput;

        cout<<"Scan de la map pour déterminer le type de jeu..."<<endl;
        bRedTeam=false;
        bGreenTeam=false;
        bBlueTeam=false;
        bRedFlag=false;
        bGreenFlag=false;
        bBlueFlag=false;
        nGameType=0;

        int i, j;
        for(i=0 ; i<WORLD_HEIGHT_CUBE ; i++)
        {
            for(j=0 ; j<WORLD_WIDTH_CUBE ; j++)
            {
                switch(nWorldSpe[i][j])
                {
                    case WORLD_SPEC_FLAG_RED:       bRedFlag=true;  break;
                    case WORLD_SPEC_FLAG_GREEN:     bGreenFlag=true;  break;
                    case WORLD_SPEC_FLAG_BLUE:      bBlueFlag=true;  break;
                    case WORLD_SPEC_SPAWN_RED:      bRedTeam=true;  break;
                    case WORLD_SPEC_SPAWN_GREEN:    bGreenTeam=true;  break;
                    case WORLD_SPEC_SPAWN_BLUE:     bBlueTeam=true;  break;
                }
            }
        }

        nTeamNb = bRedTeam+bGreenTeam+bBlueTeam;
        switch(nTeamNb)
        {
            //---------------------------------
            case 0:
                nGameType = GAMETYPE_DM;
                break;
            case 1:
                nGameType=0;
                break;
            //---------------------------------
            case 2:
                if(  (bRedTeam && bRedFlag && bGreenTeam && bGreenFlag)
                   ||(bRedTeam && bRedFlag && bBlueTeam && bBlueFlag)
                   ||(bGreenTeam && bGreenFlag && bBlueTeam && bBlueFlag))
                    nGameType = GAMETYPE_CTF;
                else
                    nGameType = GAMETYPE_TDM;
                break;
            //---------------------------------
            case 3:
                if(bRedFlag && bGreenFlag && bBlueFlag)
                    nGameType = GAMETYPE_CTF;
                else
                    nGameType = GAMETYPE_TDM;
                break;
        }
        if(nGameType == 0)
        {
            cout<<"Erreur : map incomplete, impossible de continuer !"<<endl;
        }
    }while(nGameType==0);

    cout<<"Equipes : "<<nTeamNb<<" (";
    if(bRedTeam)cout<<" Rouge";
    if(bGreenTeam)cout<<" Vert";
    if(bBlueTeam)cout<<" Bleu";
    cout<<" )"<<endl;

    switch(nGameType)
    {
        case GAMETYPE_DM: cout<<"Mode de jeu : Match classique"<<endl; break;
        case GAMETYPE_TDM: cout<<"Mode de jeu : Match en equipe"<<endl; break;
        case GAMETYPE_CTF: cout<<"Mode de jeu : Capture de drapeau"<<endl; break;
    }

    //Parametres dans le serverconfig.cfg
    ifstream stServerConfig("serverconfig.cfg");
    if(!stServerConfig)
    {
        cout<<"serverconfig.cfg non trouvé !"<<endl;
        sf::Sleep(2.0);
        return 0;
    }

    std::string sVar;
    char cChar;
    do
    {
        stServerConfig>>sVar;
        if(sVar == "ServerName")
        {
            stServerConfig.seekg(1, ios::cur);
            getline(stServerConfig, sServerName);
            stServerConfig.seekg(-1, ios::cur);
        }
        else if(sVar == "SecuredPort")
        {
            stServerConfig>>nSecuredPort;
        }
        else if(sVar == "UnsecuredPort")
        {
            stServerConfig>>nUnsecuredPort;
        }
        else if(sVar == "Passworld")
        {

        }

        //Déplace le curseur a la fin de la ligne
        do
        {
            stServerConfig.get(cChar);
        }
        while(cChar!='\n' && !stServerConfig.eof());
    }while(!stServerConfig.eof());


    //Adresse du server
    sf::IPAddress LANServerAddress = sf::IPAddress::GetLocalAddress();
    //Adresse de Broadcast
    string sAddr = LANServerAddress.ToString();
    int nSize = sAddr.size();
    char cEnd = sAddr[nSize-1];
    while(cEnd!='.')
    {
        sAddr.erase(nSize-1, 1);
        nSize = sAddr.size();
        cEnd = sAddr[nSize-1];
    }
    sAddr+="255";
    sf::IPAddress BroadcastAdress(sAddr);


    cout<<"Lancement des threads..."<<endl;
    sf::Thread thServerInfo(&ServerInformation);
    thServerInfo.Launch();

    sf::Sleep(0.5);
    cout<<"================================================================================"<<endl;
    cout<<"Server infos :"<<endl;
    cout<<"LAN Address : "<<LANServerAddress.ToString()<<endl;
    cout<<"Server pret, les joueurs peuvent se connecter"<<endl;

    while(true)
    {
        cout<<"Attente synchro"<<endl;
        bAttenteSynchro = true;
        sf::Sleep(1.0);
        cout<<"Synchronise"<<endl;
        bAttenteSynchro = false;
        sf::Sleep(1.0);

        //Broadcast des infos
        //sf::SocketUDP Socket;

        //sf::Packet PacketToSend;
        //PacketToSend<<">>>>Test de Broadcast !!<<<<";

        //PacketToSend<<nWorld<<nWorldSpe;
        //Socket.Send(PacketToSend, BroadcastAdress, nUnsecuredPort);


    }




    bStopThreads = true;



    return 0;
}



























