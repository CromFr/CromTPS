#include <iostream>
#include <cstdlib>

#include <string>
#include <sstream>
#include <cmath>
#include <vector>//Pour les tableaux dynamiques
#include <fstream>//Manips de fichiers
#include <ctime> //temps, random


#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "guifunc.h"
#include "Buttons.h"

#include "serverlist.h"


extern sf::RenderWindow oApp;




void ServerList()
{
    using namespace sf;

    //Adresse du client
    sf::IPAddress LANClientAddress = sf::IPAddress::GetLocalAddress();
    //Adresse de Broadcast
    std::string sAddr = LANClientAddress.ToString();
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

    sf::SocketUDP UDPClient;

    sf::Packet PacketToSend;
    sf::Packet PacketReceived;
    unsigned short nPort = 4000;
    sf::Uint16 n=1;
    PacketToSend<<n;
    UDPClient.Send(PacketToSend, BroadcastAdress, nPort);

    if (!UDPClient.Bind(nPort))
    {
        std::cout<<"Error ServerList : 0"<<std::endl;
        return;
    }

    std::vector<struct server> ServerList;

    while(UDPClient.Receive(PacketReceived, BroadcastAdress, nPort) != sf::Socket::Done)
    {
        std::string sServerName="";
        std::string sMapName="";
        sf::Uint16 nGameType=0;
        sf::Uint16 nTeamNb=0;
        sf::Uint16 nPlayersConnected=0;
        sf::Uint16 nUnsecuredPort=0;
        sf::Uint16 nSecuredPort=0;
        bool bRedTeam=0, bGreenTeam=0, bBlueTeam=0;

        if(!(PacketReceived>>sServerName>>sMapName>>nGameType>>nTeamNb>>nPlayersConnected>>nUnsecuredPort>>nSecuredPort>>bRedTeam>>bGreenTeam>>bBlueTeam))
            std::cout<<"Erreur de lecture du packet"<<std::endl;

        struct server ServerToAdd;
            ServerToAdd.sServerName=sServerName;
            ServerToAdd.sMapName=sMapName;
            ServerToAdd.nGameType=nGameType;
            ServerToAdd.nTeamNb=nTeamNb;
            ServerToAdd.nPlayersConnected=nPlayersConnected;
            ServerToAdd.nUnsecuredPort=nUnsecuredPort;
            ServerToAdd.nSecuredPort=nSecuredPort;
            ServerToAdd.bRedTeam=bRedTeam;
            ServerToAdd.bGreenTeam=bGreenTeam;
            ServerToAdd.bBlueTeam=bBlueTeam;

        ServerList.push_back(ServerToAdd);

        PacketReceived.Clear();
    }

    int i;
    int nSizeServerList = ServerList.size();
    for(i=0 ; i<nSizeServerList ; i++)
    {
        std::cout<<"sServerName="<<ServerList[i].sServerName<<"\nsMapName="<<ServerList[i].sMapName<<"\nnGameType="<<ServerList[i].nGameType<<"\nnTeamNb="<<ServerList[i].nTeamNb<<"\nnPlayersConnected="<<ServerList[i].nPlayersConnected;
        std::cout<<"\nnUnsecuredPort="<<ServerList[i].nUnsecuredPort<<"\nnSecuredPort="<<ServerList[i].nSecuredPort<<"\nbRedTeam="<<ServerList[i].bRedTeam<<"\nbGreenTeam="<<ServerList[i].bGreenTeam<<"\nbBlueTeam="<<ServerList[i].bBlueTeam;
    }









    int nButtonPressed=0;

    sf::Event eEvent;
    Vector2<float>::Vector2<float> vPosMouse;

    while(oApp.IsOpened())
    {
        //Gestion des evènements
        while(oApp.GetEvent(eEvent))
        {

            switch(eEvent.Type)
            {
                case Event::MouseMoved:
                    vPosMouse = Vector2f(eEvent.MouseMove.X, eEvent.MouseMove.Y);
                    break;

                case Event::KeyPressed:
                    switch(eEvent.Key.Code)
                    {
                        case Key::Escape:
                            return;
                            break;
                        default:
                            break;
                    }
                    break;

                case Event::Closed:
                    oApp.Close();
                    return;
                    break;

                default:
                    break;
            }

        }

        //Nettoyage de l'écran
        oApp.Clear();

        //Draw du Screen
        DrawScreen(1);

        //Draw du curseur
        DrawCursor(vPosMouse);

        //Affichage
        oApp.Display();
    }
    return;


}
