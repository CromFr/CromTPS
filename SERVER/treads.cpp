

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "threads.h"
#include "Player.h"

extern PlayerHandler::PlayerHandler oPlayerHandler;

extern bool bStopThreads;
extern bool bAttenteSynchro;

extern std::string sServerName;
extern std::string sMapName;
extern sf::Uint16 nGameType;
extern sf::Uint16 nTeamNb;
extern sf::Uint16 nPlayersConnected;
extern sf::Uint16 nUnsecuredPort;
extern sf::Uint16 nSecuredPort;

extern bool bRedTeam;
extern bool bGreenTeam;
extern bool bBlueTeam;

extern sf::Uint16 nWorld[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];
extern sf::Uint16 nWorldSpe[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];



void ServerInformation(void* UserData)
{

    std::cout<<"Thread ServerInformation lancé"<<std::endl;

    sf::SocketTCP TCPServer;
    sf::SocketTCP TCPClient;

    sf::IPAddress IPClient;

    sf::Packet PacketToSend;
    sf::Packet PacketReceived;

    if(!TCPServer.Listen(4000))//Le server écoute le port 4000
    {
        std::cout<<"Error ServerInformation : 0"<<std::endl;
        return;
    }
    while(!bStopThreads)
    {
        //Attente qu'un client se connecte
        if (TCPServer.Accept(TCPClient, &IPClient) != sf::Socket::Done)
        {
            std::cout<<"Error ServerInformation : 1"<<std::endl;
            return;
        }

        PacketToSend.Clear();
        PacketReceived.Clear();

        TCPClient.Receive(PacketReceived);
        int nChoix;
        PacketReceived>>nChoix;

        if(nChoix==1)//Envoi des informations
        {
            std::cout<<"Un client demande les info"<<std::endl;

                        //Infos visibles-----------------------------------------------|Pour entrer sur le server ------------------------------------
            PacketToSend<<sServerName<<sMapName<<nGameType<<nTeamNb<<nPlayersConnected<<nUnsecuredPort<<nSecuredPort<<bRedTeam<<bGreenTeam<<bBlueTeam;
            TCPClient.Send(PacketToSend);
        }
        if(nChoix==2)//Connexion au server
        {
            std::cout<<"Un client entre sur le server:"<<std::endl;

            std::string sPlayerName;
            int nSkin;
            int nTeam;
            PacketReceived>>sPlayerName>>nSkin>>nTeam;

            oPlayerHandler.AddPlayer(sPlayerName, nSkin, nTeam, IPClient);

            std::cout<<"Pseudo:"<<sPlayerName<<"  IP:"<<IPClient<<"  Skin="<<nSkin<<"  Team="<<nTeam<<std::endl;
        }
        TCPClient.Close();
    }

    std::cout<<"Fin du thread 'ServerInformations'"<<std::endl;
}


void PlayerDiscuss(void* UserData)
{
    std::cout<<"Thread PlayerDiscuss associé au joueur lancé"<<std::endl;


    Player::Player* oPlayer = static_cast<Player::Player*>(UserData);


    sf::SocketTCP TCPServer;
    sf::SocketTCP TCPClient;

    sf::Packet PacketToSend;
    sf::Packet PacketReceived;

    if(!TCPServer.Listen(nSecuredPort))//Le server écoute le port TCP
    {
        std::cout<<"Error PlayerDiscuss : 0"<<std::endl;
        return;
    }

    //Le player doit accepter la connexion TCP
    if (TCPClient.Connect(nSecuredPort, oPlayer->m_IPAddress) != sf::Socket::Done)//oPlayer->m_IPAddress
    {
        std::cout<<"Error PlayerDiscuss 1"<<std::endl;
        return;
    }

    while(!*(oPlayer->m_bThreadStopper))
    {
        //Attente de la synchro du main
        while(bAttenteSynchro & !bStopThreads)
            sf::Sleep(0.01);

        if(bStopThreads)break;


        //Envoi du paquet qui dira au joueur qu'il doit envoyer son paquet action/question
        bool i=1;
        PacketToSend.Clear();
        PacketToSend<<i;
        TCPClient.Send(PacketToSend);

        PacketReceived.Clear();
        TCPClient.Receive(PacketReceived);


        sf::Uint16 nActionType;
        PacketReceived>>nActionType;
        switch(nActionType)
        {
            case ACTION_MOVE:
                std::cout<<"Demande de mouvement"<<std::endl;
                sf::Uint16 nDirection;
                PacketReceived>>nDirection;
                break;


            //Achat d'un item ========================================================================
            case 0:
                std::cout<<"Demande d'achat"<<std::endl;
                sf::Uint16 nItemType;
                sf::Uint16 nItemTypeType;
                sf::Uint16 nItemTypeTypeType;
                PacketReceived>>nItemType>>nItemTypeType>>nItemTypeTypeType;
                struct itTemplate Template;
                    Template.type=nItemType;
                    Template.typetype=nItemTypeType;
                    Template.typetypetype=nItemTypeTypeType;

                //Don de l'objet si assez d'argent
                bool bHasBought=oPlayer->BuyItem(Template);

                std::cout<<"Demande traitée"<<std::endl;
                PacketToSend.Clear();
                PacketToSend<<bHasBought;
                TCPClient.Send(PacketToSend);
                break;

            //========================================================================================



        }
        while(!bAttenteSynchro & !bStopThreads)
            sf::Sleep(0.01);

    }
    delete oPlayer->m_bThreadStopper;
}


