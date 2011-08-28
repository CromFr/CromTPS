#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

//Dépendance a l'object Inventory
#include "Inventory.h"

struct location
{
    struct worldpospx pos;
    float facing;
};


class PC
{
    public:
    PC(int nTeam);
    ~PC();

    ///Renvoie la location du joueur (position en px et facing)
    struct location GetLocation()const;

    ///Renvoie la vitesse actuelle du joueur // TODO (crom#1#): moteur physique à faire
    float GetSpeed()const;

    ///Renvoie le nb d'HP que le joueur dispose
    int GetHP() const;

    ///true si le joueur est mort
    bool GetIsDead() const;

    ///Renvoie la team dont le joueur fait partie
    int GetTeam() const;

    ///Renvoie le skin du joueur
    int GetSkin() const;


    //===================================================
    //Combat
    ///Le joueur tire à la position indiquée.
    ///Gère les collisions avec le world, mais pas avec les players
    void FireAtPosition(struct worldpospx pPos);

    ///Inflige des dg au perso et renvoie true si fatals
    ///Si true => Set de la date de respawn // TODO (crom#1#): à faire
    bool TakeDamages(int nAmount, int nDamageType);

    ///Soigne le perso de nAmount points de vie
    void Heal(int nAmount);

    ///Change l'equipe dont fait partie le joueur
    void ChangeTeam(int nNewTeam);

    ///Si le joueur est mort, cette fonction le fait réapparaitre
    void Respawn();

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


    ///Déplace le joueur de x pixels dans la direction donnée, en fonction du temps de frame // TODO (crom#1#): collisions à terminer
    bool MoveToDirection(int nDirection, float fMod=1.0);

    void DecreaseSpeed();

    ///Change le facing (rotation) du joueur (unité : degré)
    void SetFacing(float fFacing);

    ///Renvoie l'argent dont dispose le joueur
    int GetMoney() const;

    //===================================================
    private:


    int m_nTeam;
    int m_nSkin;
    int m_nHP;

    float m_fFacing;
    struct worldpospx m_pPosition;
    sf::Vector2<float>::Vector2<float> m_vSpeed;// pixel/sec

    int m_nMoney;

    float m_fFireDelayDateEnd;
    float m_fReloadDelayDateEnd;
    float m_fRespawnDelayDateEnd;

    Inventory m_oInventaire;

    void PlayWeaponFireSound();
    void PlayWeaponImpactSound();

    friend void DrawPlayerInfo(PC::PC* oPC);

};




class PlayerHandler
{
    public://===================================================
    ///Dessine tous les joueurs sur la map
    void DrawPlayers();

    ///Ajoute le personnage du joueur
    void AddControlledPlayer();

    ///ajoute un joueur non controlé au jeu
    void AddNonControlledPlayer(int nTeam, char* nIP);

    ///renvoie le pc qui est controlé
    PC::PC* GetControlledPC();

    ///renvoie le nombre de joueurs en jeu
    int GetNumberOfPlayers();

    ///Supprime un joueur de la partie
    void DeletePlayer();


    private://===================================================
    ///Fait pointer sprPlayer vers le skin associé
    void ApplySkin(int nSkin, sf::Sprite* sprPlayer);

    ///Colorise le sprite en fonction de l'équipe
    void ApplyTeamColor(int nTeam, sf::Sprite* sprPlayer);

    ///Positionne et tourne le sprite
    void ApplyLocation(struct location lPlayer, sf::Sprite* sprPlayer);

    PC::PC m_oPC;
    //std::vector<NPC::NPC> m_ListeNPC;


};



#endif // CHARACTER_H_INCLUDED
