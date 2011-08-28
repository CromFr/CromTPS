#ifndef SERVERLIST_H_INCLUDED
#define SERVERLIST_H_INCLUDED


struct server
{
    std::string sServerName;
    std::string sMapName;
    sf::Uint16 nGameType;
    sf::Uint16 nTeamNb;
    sf::Uint16 nPlayersConnected;
    sf::Uint16 nUnsecuredPort;
    sf::Uint16 nSecuredPort;
    bool bRedTeam, bGreenTeam, bBlueTeam;
};

void ServerList();


#endif // SERVERLIST_H_INCLUDED
