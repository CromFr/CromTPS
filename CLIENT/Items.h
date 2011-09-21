#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "main.h"
#include "utils.h"

#define _ITEMS_WEAPON_SOUNDTYPE_FIRE 0
#define _ITEMS_WEAPON_SOUNDTYPE_IMPACT 1
#define _ITEMS_WEAPON_SOUNDTYPE_RELOAD 2

#define _ITEMS_WEAPON_EVENT_FIRE 0
#define _ITEMS_WEAPON_EVENT_RELOAD 1

struct itTemplate
{
        int type;
        int typetype;
        int typetypetype;
};
bool operator==(itTemplate const& a, itTemplate const& b);

struct itTemplate MakeItemTemplate(int nType=-1, int nTypeType=-1, int nTypeTypeType=-1);

///On ne peut pas créer un item avec cette classe, car elle est abstraite
class Item
{
    public:
    Item();

    ///True si l'item a été configuré normalement
    ///False si l'item est inexistant ou mal configuré
    virtual bool GetIsItemValid() const;

    ///Retourne le template associé à l'item
    struct itTemplate GetTemplate() const;

    ///Retourne le nom de l'item
    std::string GetName() const;

    /// (DEBUG) Affiche les infos sur l'item dans la console
    void Display() const;


    protected:
    itTemplate m_Template;
    int m_nPrice;
    std::string m_sName;

};

class Weapon : public Item
{
    public:
    Weapon(int nType);//A la création, préciser le typetype

    ///Applique les repercussions d'un tir sur l'arme (diminution des munitions). Retourne 1 si il faut recharger
    int Fire();

    ///Recharge l'arme
    void Reload();
    ///Joue le son de tir=0/impact=1/rechargement=2 de l'arme.
    void PlaySound(int nSoundType) const;
    // TODO (crom#1#): Son impact & rechargement a faire

    ///Renvoie la date a laquelle l'arme sera de nouveau utilisable après un event de tir=0/rechargement=1
    float GetReusableDateAfterEvent(int nEvent) const;

    //Accesseurs
    int GetDamageType() const;
    int GetDamageAmount() const;//Calcul aléatoire
    int GetCurrAmmo() const;
    int GetRange() const;
    //

    private:
    int m_nDamageType;//Types de dg infligés
    int m_nDamage;//Dégats infligés
    int m_nStock;//Capacité du chargeur
    int m_nCurrAmmo;//Balles restantes dans le chargeur
    float m_fFireDelay;//temps entre 2 tirs en sec
    float m_fReloadDelay;//Temps de rechargement en sec
    int m_nRange;
    sf::Sound* m_sndFire;
    sf::Sound* m_sndImpact;
    sf::Sound* m_sndReload;
};

class Armor : public Item
{
    public:
    Armor(int nType);//A la création, préciser le typetype

    ///Renvoie les dégâts restant après appliquation de la reduction de l'armure
    /// nDamageType : type des dégâts (DAMAGE_TYPE_*)
    /// nAmount : Quantité de dégâts reçus
    int ReduceDamages(int nDamageType, int nAmount)const;

    private:
    int m_nReductionVsBullet;
    int m_nReductionVsLaser;
    int m_nReductionVsGauss;

    //Renvoie un pourcentage (0-100) à /100 et multiplier par dg
    int GetReduction(int nDamageType) const;
};


///Abstrait !
class PlaceableItem : public Item
{
    public:
    PlaceableItem();


    protected:
    int m_nPlaceableType;
    int m_nSkin;

};

class Explosive : public PlaceableItem
{
    public:
    Explosive(int nType);

    private:
    int m_nExplosiveType;
    int m_nDamage;
    int m_nRange;
    float m_fTimeOut;

};



///Renvoie un pointeur sur le weapon associé via un cast. Renvoie 0 si ce n'est pas un weapon
Weapon::Weapon* GetWeapon(Item::Item* pItem);
///idem pour armor
Armor::Armor* GetArmor(Item::Item* pItem);



#endif // ITEMS_H_INCLUDED
