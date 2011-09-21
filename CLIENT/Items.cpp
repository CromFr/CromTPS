
#include "Items.h"

//Weapons ================================================
//Fire
//Bullet
extern sf::SoundBuffer bufBulletPistol;
    extern sf::Sound sndBulletPistol;
extern sf::SoundBuffer bufBulletRifle;
    extern sf::Sound sndBulletRifle;
extern sf::SoundBuffer bufBulletMinigun;
    extern sf::Sound sndBulletMinigun;
//Laser
extern sf::SoundBuffer bufLaserPistol;
    extern sf::Sound sndLaserPistol;
extern sf::SoundBuffer bufLaserRifle;
    extern sf::Sound sndLaserRifle;
extern sf::SoundBuffer bufLaserMinigun;
    extern sf::Sound sndLaserMinigun;
//Gauss
extern sf::SoundBuffer bufGaussPistol;
    extern sf::Sound sndGaussPistol;
extern sf::SoundBuffer bufGaussRifle;
    extern sf::Sound sndGaussRifle;
extern sf::SoundBuffer bufGaussMinigun;
    extern sf::Sound sndGaussMinigun;
extern sf::SoundBuffer bufGaussDestructeur;
    extern sf::Sound sndGaussDestructeur;

extern sf::Clock clkDateGame;




bool operator==(itTemplate const& a, itTemplate const& b)
{
    if(a.type == b.type && a.typetype == b.typetype && a.typetypetype == b.typetypetype)
        return true;
    return false;
}

struct itTemplate MakeItemTemplate(int nType, int nTypeType, int nTypeTypeType)
{
    struct itTemplate Template;
    Template.type = nType;
    Template.typetype = nTypeType;
    Template.typetypetype = nTypeTypeType;
    return Template;
}








//============================================================================================================================================
//============================================================================================================================================
Item::Item()
{
    Item::m_Template=MakeItemTemplate(-1,-1,-1);
    Item::m_nPrice=-1;
    Item::m_sName="INVALID_ITEM";

}
//=====================================================
bool Item::GetIsItemValid() const
{
    if(Item::m_Template.type!=-1)
        return true;
    return false;
}
//=====================================================
struct itTemplate Item::GetTemplate() const
{
    return Item::m_Template;
}
//=====================================================
std::string Item::GetName() const
{
    return Item::m_sName;
}
//=====================================================
void Item::Display() const
{
    using namespace std;

    cout<<"m_nType="<<Item::m_Template.type<<endl;
    cout<<"m_nTypeType="<<Item::m_Template.typetype<<endl;
    cout<<"m_nTypeTypeType="<<Item::m_Template.typetypetype<<endl;
    cout<<"m_nPrice="<<Item::m_nPrice<<endl;
    cout<<"m_sName="<<Item::m_sName<<endl;
}

//============================================================================================================================================
//============================================================================================================================================
//============================================================================================================================================

Weapon::Weapon(int nType)
{
    Item::m_Template = MakeItemTemplate(ITEM_TYPE_WEAPON, nType);
    Item::m_nPrice = Get2daInt("weapon_rules.2da", nType, _2DA_WEAPON_PRICE);
    Item::m_sName = Get2daString("weapon_rules.2da", nType, _2DA_WEAPON_NAME);

    Weapon::m_nDamageType = Get2daInt("weapon_rules.2da", nType, _2DA_WEAPON_DAMAGE_TYPE);
    Weapon::m_nDamage = Get2daInt("weapon_rules.2da", nType, _2DA_WEAPON_DAMAGE);
    Weapon::m_nStock = Get2daInt("weapon_rules.2da", nType, _2DA_WEAPON_STOCK);
    Weapon::m_nCurrAmmo = Weapon::m_nStock;
    Weapon::m_fFireDelay = Get2daFloat("weapon_rules.2da", nType, _2DA_WEAPON_FIRE_DELAY);
    Weapon::m_fReloadDelay = Get2daFloat("weapon_rules.2da", nType, _2DA_WEAPON_RELOAD_DELAY);
    Weapon::m_nRange = Get2daInt("weapon_rules.2da", nType, _2DA_WEAPON_RANGE);

    Weapon::m_sndFire = 0;
    switch(nType)
    {
        case WEAPON_TYPE_BULLET_PISTOL:         Weapon::m_sndFire = &sndBulletPistol;      break;
        case WEAPON_TYPE_BULLET_RIFLE:          Weapon::m_sndFire = &sndBulletRifle;       break;
        case WEAPON_TYPE_BULLET_MINIGUN:        Weapon::m_sndFire = &sndBulletMinigun;     break;
        case WEAPON_TYPE_LASER_PISTOL:          Weapon::m_sndFire = &sndLaserPistol;       break;
        case WEAPON_TYPE_LASER_RIFLE:           Weapon::m_sndFire = &sndLaserRifle;        break;
        case WEAPON_TYPE_LASER_MINIGUN:         Weapon::m_sndFire = &sndLaserMinigun;      break;
        case WEAPON_TYPE_GAUSS_PISTOL:          Weapon::m_sndFire = &sndGaussPistol;       break;
        case WEAPON_TYPE_GAUSS_RIFLE:           Weapon::m_sndFire = &sndGaussRifle;        break;
        case WEAPON_TYPE_GAUSS_MINIGUN:         Weapon::m_sndFire = &sndGaussMinigun;      break;
        case WEAPON_TYPE_GAUSS_DESTRUCTEUR:     Weapon::m_sndFire = &sndGaussDestructeur;  break;
    }

    // TODO (crom#1#): Associer l'adresse du son d'impact à l'arme
    //Weapon::m_sndImpactSound = new sf::Sound;
    Weapon::m_sndImpact=0;


    Weapon::m_sndReload=0;
}
//=====================================================
int Weapon::Fire()
{
    Weapon::m_nCurrAmmo--;
    if(m_nCurrAmmo <= 0)
        return 1;
    return 0;
}
//=====================================================
void Weapon::Reload()
{
    Weapon::m_nCurrAmmo = Weapon::m_nStock;
}
//=====================================================
void Weapon::PlaySound(int nSoundType) const
{
    switch(nSoundType)
    {
        case _ITEMS_WEAPON_SOUNDTYPE_FIRE:
            //Son de tir
            Weapon::m_sndFire->Play();
            break;
        case _ITEMS_WEAPON_SOUNDTYPE_IMPACT:
            //Son de tir
            Weapon::m_sndImpact->Play();// TODO (crom#1#): Gestion des sons d'impact
            break;
        case _ITEMS_WEAPON_SOUNDTYPE_RELOAD:
            //Son de tir
            Weapon::m_sndReload->Play();// TODO (crom#1#): Gestion des sons de reload
            break;
    }
}
//=====================================================
float Weapon::GetReusableDateAfterEvent(int nEvent) const
{
    if(nEvent == _ITEMS_WEAPON_EVENT_FIRE)
    {
        return clkDateGame.GetElapsedTime()+Weapon::m_fFireDelay;
    }
    else if(nEvent == _ITEMS_WEAPON_EVENT_RELOAD)
    {
        return clkDateGame.GetElapsedTime()+Weapon::m_fReloadDelay;
    }
    return clkDateGame.GetElapsedTime();
}
//=====================================================
int Weapon::GetDamageType() const
{
    return Weapon::m_nDamageType;
}
//=====================================================
int Weapon::GetDamageAmount() const
{
    int nRandWidth = Weapon::m_nDamage*0.20;//20% d'aléatoire
    return Weapon::m_nDamage-nRandWidth/2+rand()%nRandWidth;
}
//=====================================================
int Weapon::GetCurrAmmo()const
{
    return Weapon::m_nCurrAmmo;
}
//=====================================================
int Weapon::GetRange() const
{
    return Weapon::m_nRange;
}
//============================================================================================================================================
//============================================================================================================================================
Armor::Armor(int nType)
{
    Item::m_Template = MakeItemTemplate(ITEM_TYPE_ARMOR, nType);
    Item::m_nPrice = Get2daInt("armor_rules.2da", nType, _2DA_ARMOR_PRICE);
    Item::m_sName = Get2daString("armor_rules.2da", nType, _2DA_ARMOR_NAME);

    Armor::m_nReductionVsBullet = Get2daInt("armor_rules.2da", nType, _2DA_ARMOR_RD_VS_BULLETS);
    Armor::m_nReductionVsLaser = Get2daInt("armor_rules.2da", nType, _2DA_ARMOR_RD_VS_LASER);
    Armor::m_nReductionVsGauss = Get2daInt("armor_rules.2da", nType, _2DA_ARMOR_RD_VS_GAUSS);
}
//=====================================================
int Armor::ReduceDamages(int nDamageType, int nAmount)const
{
    //Pourcentage de réduction
    float fArmorReduction = 1-(GetReduction(nDamageType))/100;

    return nAmount*fArmorReduction;
}
//=====================================================
int Armor::GetReduction(int nDamageType) const
{
    switch(nDamageType)
    {
        case DAMAGE_TYPE_BULLET:
            return Armor::m_nReductionVsBullet;
        case DAMAGE_TYPE_LASER:
            return Armor::m_nReductionVsLaser;
        case DAMAGE_TYPE_GAUSS:
            return Armor::m_nReductionVsGauss;
    }
    return 0;
}
//============================================================================================================================================
//============================================================================================================================================
PlaceableItem::PlaceableItem()
{

}
//============================================================================================================================================
//============================================================================================================================================
Explosive::Explosive(int nType)
{
    Item::m_Template = MakeItemTemplate(ITEM_TYPE_PLACEABLEITEM, PLACEABLEITEM_EXPLOSIVE, nType);

    Item::m_nPrice = Get2daInt("explosive_rules.2da", nType, _2DA_PLACEABLEITEM_EXPLOSIVE_PRICE);
    Item::m_sName = Get2daString("explosive_rules.2da", nType, _2DA_PLACEABLEITEM_EXPLOSIVE_NAME);

    Explosive::m_nExplosiveType = nType;
    Explosive::m_nDamage = Get2daInt("explosive_rules.2da", nType, _2DA_PLACEABLEITEM_EXPLOSIVE_DAMAGE);
    Explosive::m_nRange = Get2daInt("explosive_rules.2da", nType, _2DA_PLACEABLEITEM_EXPLOSIVE_RANGE);
    Explosive::m_fTimeOut = Get2daFloat("explosive_rules.2da", nType, _2DA_PLACEABLEITEM_EXPLOSIVE_TIMEOUT);
}























//=====================================================
Weapon::Weapon* GetWeapon(Item::Item* pItem)
{
    if(pItem->GetTemplate().type==ITEM_TYPE_WEAPON)
        return dynamic_cast<Weapon*>(pItem);
    return 0;
}
//=====================================================
Armor::Armor* GetArmor(Item::Item* pItem)
{
    if(pItem->GetTemplate().type==ITEM_TYPE_ARMOR)
        return dynamic_cast<Armor*>(pItem);
    return 0;
}




