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

struct itTemplate MakeItemTemplate(int nType, int nTypeType, int nTypeTypeType=0);

///On ne peut pas créer un item avec cette classe, car elle est abstraite
class Item
{
    public:
    Item();

    virtual Item* GetObject();

    bool GetIsItemValid() const;
    struct itTemplate GetTemplate() const;
    std::string GetName() const;
    void Display() const;


    protected:
    int m_nType;
    int m_nTypeType;
    int m_nTypeTypeType;
    int m_nPrice;
    std::string m_sName;

    private:

};

class Weapon : public Item
{
    public:
    Weapon(int nType);//A la création, préciser le typetype

    virtual Weapon* GetObject();

    int Weapon_Fire();//retourne 1 si il faut recharger
    void Weapon_Reload();//retourne 1 si il faut recharger
    void Weapon_PlaySound(int nSoundType) const;//0:tir, 1:Impact
    float Weapon_GetReusableDateAfterEvent(int nEvent) const;//0:Event de tir, 1 de reload
    int Weapon_GetDamageType() const;
    int Weapon_GetDamageAmount() const;//Calcul aléatoire
    int Weapon_GetCurrAmmo() const;
    int Weapon_GetRange() const;

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

    virtual Armor* GetObject();

    int Armor_GetReduction(int nDamageType) const;

    private:
    int m_nReductionVsBullet;
    int m_nReductionVsLaser;
    int m_nReductionVsGauss;
};


class Potion : public Item
{
    public:
    Potion(int nType);//A la création, préciser le typetype

    virtual Potion* GetObject();

    int Potion_GetHpHeal() const;//Calcul aléatoire

    private:
    int m_nBaseHpHeal;
    int m_nRandomHpHeal;
};


///Abstrait !
class PlaceableItem : public Item
{
    public:
    PlaceableItem();


    private:
    int m_nPlaceableType;

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



#endif // ITEMS_H_INCLUDED
