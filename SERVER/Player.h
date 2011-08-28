#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <SFML/Network.hpp>
//Dépendance a l'object Inventory
#include "Inventory.h"

struct location
{
    struct worldpospx pos;
    float facing;
};



class Player
{
    public:
    Player(std::string sPlayerName, int nSkin, int nTeam, sf::IPAddress IP);
    ~Player();

    //===================================================
    //Positions & déplacements-------------
    ///Renvoie la location du joueur (position en px et facing)
    struct location GetLocation()const;

    ///Déplace le joueur de x pixels dans la direction donnée, en fonction du temps de frame // TODO (crom#1#): collisions à terminer
    bool MoveToDirection(int nDirection);

    ///Change le facing (rotation) du joueur (unité : degré)
    void SetFacing(float fFacing);


    //Combat-----------------------------------
    ///Le joueur tire à la position indiquée.
    ///Gère les collisions avec le world, mais pas avec les players
    void FireAtPosition(struct worldpospx pPos);

    ///Inflige des dg au perso et renvoie true si fatals
    ///Si true => Set de la date de respawn // TODO (crom#1#): à faire
    bool TakeDamages(int nAmount, int nDamageType);

    ///Soigne le perso de nAmount points de vie
    void Heal(int nAmount);

    ///Renvoie le nb d'HP que le joueur dispose
    int GetHP() const;

    ///true si le joueur est mort
    bool GetIsDead() const;

    ///Si le joueur est mort, cette fonction le fait réapparaitre
    void Respawn();


    //Equipes-----------------------------------
    ///Renvoie la team dont le joueur fait partie
    int GetTeam() const;

    ///Change l'equipe dont fait partie le joueur
    void ChangeTeam(int nNewTeam);


    //Inventaire-----------------------------------
    ///Renvoie l'adresse de l'inventaire du joueur
    Inventory::Inventory* GetInventory();

    ///Supprime une potion de l'inventaire, et applique les effets au joueur
    ///Renvoie true si la potion a été bue
    bool UsePotion(int nPotionType);

    ///Pose une bombe à la position définie par le joueur
    bool UseBomb(struct worldposblock pPos ,int nBombType);

    ///Achète un item et le place dans l'inventaire du joueur
    ///renvoie true si le joueur a assez d'argent
    bool BuyItem(struct itTemplate Template);

    ///Vend un item et donne l'argent correspondant au joueur
    void SellItem(Item::Item* pItemToSell);

    ///Renvoie l'argent dont dispose le joueur
    int GetMoney() const;


    //Gestion-----------------------------------
    ///Passe le character en Invalid
    void SetInvalid();

    ///True si le player est valide
    bool GetIsValid();



    //===================================================
    private:
    bool bValid;

    std::string m_sPlayerName;
    int m_nTeam;
    int m_nSkin;

    int m_nHP;

    float m_fFacing;
    struct worldpospx m_pPosition;

    int m_nMoney;
    float m_fSpeed;// pixel/sec
    float m_fAccel;// pixel/sec

    float m_fFireDelayDateEnd;
    float m_fReloadDelayDateEnd;
    float m_fRespawnDelayDateEnd;

    Inventory m_oInventaire;

    sf::IPAddress m_IPAddress;
    bool* m_bThreadStopper;
    friend void PlayerDiscuss(void* UserData);
};



class PlayerHandler
{
    public://===================================================

    ///ajoute un joueur non controlé au jeu
    void AddPlayer(std::string sPlayerName, int nSkin, int nTeam, sf::IPAddress IP);

    ///renvoie le nombre de joueurs en jeu
    int GetNumberOfPlayers();

    ///Supprime un joueur de la partie
    void DeletePlayer();

    ///Renvoie l'action que désire éxécuter le joueur
    void DoAction(sf::Packet PacketReceived);

    ///Récupère & traite les infos envoyées par les joueurs
    void AskAndDoAction();

    private://===================================================
    ///Fait pointer sprPlayer vers le skin associé
    void ApplySkin(int nSkin, sf::Sprite* sprPlayer);

    ///Colorise le sprite en fonction de l'équipe
    void ApplyTeamColor(int nTeam, sf::Sprite* sprPlayer);

    ///Positionne et tourne le sprite
    void ApplyLocation(struct location lPlayer, sf::Sprite* sprPlayer);

    std::vector<Player::Player> m_ListePlayer;

};



#endif // CHARACTER_H_INCLUDED
