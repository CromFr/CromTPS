#include <iostream>
#include <cstdlib>

#include <vector>//Pour les tableaux dynamiques
#include <string>
#include <ctime>

#include "main.h"
#include "Player.h"

#include "Vfx.h"
#include "convert.h"
#include "utils.h"
#include "world.h"
#include "threads.h"




extern sf::Uint16 nWorld[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];
extern sf::Uint16 nWorldSpe[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];
extern Vfx oVfx;
extern sf::RenderWindow oApp;

extern sf::Clock clkDateGame;

//----------------------------------------------------------------------------------------------------------------------------------------------------
Player::Player(std::string sPlayerName, int nSkin, int nTeam, sf::IPAddress IP):m_oInventaire()
{
    Player::bValid=true;

    Player::m_sPlayerName=sPlayerName;

    Player::m_nTeam=nTeam;
    Player::m_nSkin=nSkin;
    Player::m_IPAddress=IP;

    Player::m_nHP=0;

    Player::m_nMoney=200;
    Player::m_fSpeed=0.0;// pixel/sec
    Player::m_fAccel=0.0;// pixel/sec

    Player::m_fFireDelayDateEnd=0.0;
    Player::m_fReloadDelayDateEnd=0.0;
    Player::m_fRespawnDelayDateEnd=clkDateGame.GetElapsedTime()+2.0;


    Player::m_IPAddress = IP;
    Player::m_bThreadStopper = new bool;
    *Player::m_bThreadStopper=false;

    sf::Thread thServerInfo(&PlayerDiscuss, this);
    thServerInfo.Launch();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
Player::~Player()
{
    *Player::m_bThreadStopper=true;
}


//====================================================================================================================================================
//==POSITIONS & DEPLACEMENTS======POSITIONS & DEPLACEMENTS======POSITIONS & DEPLACEMENTS======POSITIONS & DEPLACEMENTS======POSITIONS & DEPLACEMENTS==
//====================================================================================================================================================
struct location Player::GetLocation()const
{
    struct location Loc;
    Loc.pos = Player::m_pPosition;
    Loc.facing = Player::m_fFacing;
    return Loc;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Player::MoveToDirection(int nDirection)
{
    struct worldpospx pNewPosition;
    pNewPosition.hrz=Player::m_pPosition.hrz;
    pNewPosition.ver=Player::m_pPosition.ver;

    float fFrameTime = 0.1;//oApp.GetFrameTime();
    switch(nDirection)
    {
        case DIRECTION_NORTH:
            pNewPosition.ver = Player::m_pPosition.ver-VITESSE_CHARACTER_PX_S*fFrameTime-1;
            if(!GetIsCollisionPJWithWorld(pNewPosition))
                Player::m_pPosition.ver -= VITESSE_CHARACTER_PX_S*fFrameTime-1;
            break;
        case DIRECTION_EAST:
            pNewPosition.hrz = Player::m_pPosition.hrz+VITESSE_CHARACTER_PX_S*fFrameTime;
            if(!GetIsCollisionPJWithWorld(pNewPosition))
                Player::m_pPosition.hrz += VITESSE_CHARACTER_PX_S*fFrameTime;
            break;
        case DIRECTION_SOUTH:
            pNewPosition.ver = Player::m_pPosition.ver+VITESSE_CHARACTER_PX_S*fFrameTime;
            if(!GetIsCollisionPJWithWorld(pNewPosition))
                Player::m_pPosition.ver += VITESSE_CHARACTER_PX_S*fFrameTime;
            break;
        case DIRECTION_WEST:
            pNewPosition.hrz = Player::m_pPosition.hrz-VITESSE_CHARACTER_PX_S*fFrameTime-1;
            if(!GetIsCollisionPJWithWorld(pNewPosition))
                Player::m_pPosition.hrz -= VITESSE_CHARACTER_PX_S*fFrameTime-1;
            break;
    }
    return true;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void Player::SetFacing(float fFacing)
{
    Player::m_fFacing = fFacing;
}


//====================================================================================================================================================
//=COMBAT===COMBAT===COMBAT===COMBAT===COMBAT===COMBAT===COMBAT===COMBAT===COMBAT===COMBAT===COMBAT===COMBAT===COMBAT===COMBAT===COMBAT===COMBAT======
//====================================================================================================================================================
void Player::FireAtPosition(struct worldpospx pPosVisee)
{
    float fDate = clkDateGame.GetElapsedTime();
    if(Player::m_fFireDelayDateEnd>fDate)//Si le joueur a tiré il y a peu de temps, on lui interdit de tirer
        return;

    if(Player::m_fReloadDelayDateEnd>fDate)//si le joueur doit recharger
        return;

    Item::Item* pWeapon = Player::m_oInventaire.GetEquipedItem(EQUIPMENT_PART_WEAPON);
    if(pWeapon == 0)return;

    int nRange = pWeapon->Weapon_GetRange();
    int nDamageType = pWeapon->Weapon_GetDamageType();

    //Determination du coeff de la droite
    float fDeltaVer = (pPosVisee.ver - Player::m_pPosition.ver),
          fDeltaHrz = (pPosVisee.hrz - Player::m_pPosition.hrz);

    //Détermination de l'angle avec l'horizontale
    float fAngle = atan(fDeltaVer/fDeltaHrz);

    bool bImpact = true;

    float fCoeff;
    int nSens, nDelta;
    struct worldpospx vPosPoint;
    struct worldposblock vPosPointBlocs;
    struct worldpospx vPosDepRay;
    bool bDepRayIsSet=false;
    float fDistance;

    if( (fAngle>(-PI/4) && fAngle<(PI/4)))
    {
        fCoeff = fDeltaVer/fDeltaHrz;

        //Set du sens d'évolution de la droite
        if((pPosVisee.hrz - Player::m_pPosition.hrz)>0)
            nSens=1;
        else if((pPosVisee.hrz - Player::m_pPosition.hrz)<0)
            nSens=-1;
        else
            return;

        vPosPoint.hrz=0;
        vPosDepRay.hrz=0; vPosDepRay.ver=0;
        //Verif point par point de la droite. Le point en cours est localisé par vPosPoint dans world
        for(nDelta=12*nSens ; 1 ; nDelta+=nSens)
        {
            //Calcul de la future position
            vPosPoint.hrz = Player::m_pPosition.hrz+nDelta-(VFX_RAY_DIM_PX/2);
            vPosPoint.ver = Player::m_pPosition.ver+fCoeff*nDelta-(VFX_RAY_DIM_PX/2);

            vPosPointBlocs = CoordWorldPxToWorldBlocks(vPosPoint);

            fDistance = GetDistanceBetween(Player::m_pPosition.hrz, Player::m_pPosition.ver, vPosPoint.hrz, vPosPoint.ver);

            //On note le départ du ray
            if(!bDepRayIsSet && fDistance>20)
            {
                vPosDepRay = vPosPoint;
                bDepRayIsSet=true;
            }

            //Stoppe si le rayon est bloqué par un élément de world ou épuisé
            if(GetIsBlockingVision(nWorld[vPosPointBlocs.ver][vPosPointBlocs.hrz])//Si le bloc bloque le rayon
               || 0)//Si rencontre un PJ
            {
                break;
            }
            else if(fDistance>nRange//Si le point a dépassé la portée max de l'arme
                    || vPosPoint.hrz<0 || vPosPoint.hrz>WORLD_WIDTH_PX || vPosPoint.ver<0 || vPosPoint.ver>WORLD_HEIGHT_PX)//Ou en dehors du world
            {
                bImpact=0;
                break;
            }
        }
    }
    else
    {
        fCoeff = fDeltaHrz/fDeltaVer;

        //Set du sens d'évolution de la droite
        if((Player::m_pPosition.ver - pPosVisee.ver)>0)
            nSens=-1;
        else if((Player::m_pPosition.ver - pPosVisee.ver)<0)
            nSens=1;
        else
            return;

        vPosPoint.ver=0;
        vPosDepRay.hrz=0; vPosDepRay.ver=0;
        //Verif point par point de la droite. Le point en cours est localisé par vPosPoint dans world
        for(nDelta=12*nSens ; 1 ; nDelta+=nSens)
        {
            //Calcul de la future position
            vPosPoint.ver = Player::m_pPosition.ver+nDelta-(VFX_RAY_DIM_PX/2);
            vPosPoint.hrz = Player::m_pPosition.hrz+fCoeff*nDelta-(VFX_RAY_DIM_PX/2);

            vPosPointBlocs = CoordWorldPxToWorldBlocks(vPosPoint);

            fDistance = GetDistanceBetween(Player::m_pPosition.hrz, Player::m_pPosition.ver, vPosPoint.hrz, vPosPoint.ver);

            //On note le départ du ray
            if(!bDepRayIsSet && fDistance>20)
            {
                vPosDepRay = vPosPoint;
                bDepRayIsSet=true;
            }

            //Stoppe si le rayon est bloqué par un élément de world ou épuisé
            if(GetIsBlockingVision(nWorld[vPosPointBlocs.ver][vPosPointBlocs.hrz])//Si le bloc bloque le rayon
               || 0)
            {
                break;
            }
            else if(fDistance>nRange//Si le point a dépassé la portée max de l'arme
                    || vPosPoint.hrz<0 || vPosPoint.hrz>WORLD_WIDTH_PX || vPosPoint.ver<0 || vPosPoint.ver>WORLD_HEIGHT_PX)//Ou en dehors du world
            {
                bImpact=0;
                break;
            }
        }
    }

    //Repercussions sur l'arme
    if(pWeapon->Weapon_Fire())//Si il faut recharger
    {
        Player::m_fReloadDelayDateEnd = pWeapon->Weapon_GetReusableDateAfterEvent(1);
        pWeapon->Weapon_Reload();
    }
    else//Cooldown du tir
    {
        Player::m_fFireDelayDateEnd = pWeapon->Weapon_GetReusableDateAfterEvent(0);
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Player::TakeDamages(int nAmount, int nDamageType)
{
    int nDmgFinal;
    float fDate = clkDateGame.GetElapsedTime();

    Item::Item* pArmor = Player::m_oInventaire.GetEquipedItem(EQUIPMENT_PART_ARMOR);
    if(pArmor == 0)return true;

    float fArmorReduction = 1-(pArmor->Armor_GetReduction(nDamageType))/100;

    nDmgFinal = nAmount*fArmorReduction;

    if(Player::m_nHP-nDmgFinal <= 0)
    {
        Player::m_nHP = 0;
        Player::m_fRespawnDelayDateEnd = fDate+RESPAWN_DELAY;
        return true;
    }
    else
    {
        Player::m_nHP -= nDmgFinal;
        return false;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void Player::Heal(int nAmount)
{
    if(Player::m_nHP+nAmount > 100)
    {
        Player::m_nHP = 100;
    }
    else
    {
        Player::m_nHP += nAmount;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
int Player::GetHP() const
{
    return Player::m_nHP;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Player::GetIsDead() const
{
    if(Player::m_nHP<=0)
        return true;
    return false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void Respawn()
{
    // NOTE (crom#1#): Respawn\teste si la date avant respawn est écoulée, si oui, on ressucite le joueur et on le place au point de spawn
}



//====================================================================================================================================================
//===EQUIPES====EQUIPES=====EQUIPES=====EQUIPES=====EQUIPES=====EQUIPES=====EQUIPES=====EQUIPES=====EQUIPES=====EQUIPES=====EQUIPES=====EQUIPES=======
//====================================================================================================================================================
int Player::GetTeam() const
{
    return Player::m_nTeam;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void Player::ChangeTeam(int nNewTeam)
{
    float fDate = clkDateGame.GetElapsedTime();

    Player::m_nHP=0;
    Player::m_fRespawnDelayDateEnd = fDate+RESPAWN_DELAY;

    Player::m_nTeam = nNewTeam;
}



//====================================================================================================================================================
//===INVENTAIRE====INVENTAIRE====INVENTAIRE====INVENTAIRE====INVENTAIRE====INVENTAIRE====INVENTAIRE====INVENTAIRE====INVENTAIRE====INVENTAIRE=========
//====================================================================================================================================================
Inventory::Inventory* Player::GetInventory()
{
    return &(Player::m_oInventaire);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Player::UsePotion(int nPotionType)
{
    struct itTemplate Template = MakeItemTemplate(ITEM_TYPE_POTION, nPotionType);
    Item::Item* pPotion = Player::m_oInventaire.GetFirstItem(Template);

    //Si l'objet à equipper est bien dans l'inventaire
    if(Player::m_oInventaire.GetItemStack(Template)>0)
    {
        int nAmount = pPotion->Potion_GetHpHeal();

        Player::Heal(nAmount);
        Player::m_oInventaire.DelItem(pPotion);
        return true;
    }
    else
    {
        std::cout << "L'item n'est pas dans l'inventaire !"<<std::endl;
        return false;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool UseBomb(struct worldposblock pPos ,int nBombType)
{
    // NOTE (crom#1#): UseBomb\Completer
    return false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Player::BuyItem(struct itTemplate Template)
{

    int nPrice;
    switch(Template.type)
    {
        case ITEM_TYPE_WEAPON:
            nPrice = Get2daInt("weapon_rules.2da", Template.typetype, _2DA_WEAPON_PRICE);
            break;
        case ITEM_TYPE_ARMOR:
            nPrice = Get2daInt("armor_rules.2da", Template.typetype, _2DA_ARMOR_PRICE);
            break;
        case ITEM_TYPE_POTION:
            nPrice = Get2daInt("potion_rules.2da", Template.typetype, _2DA_POTION_PRICE);
            break;
        case ITEM_TYPE_PLACEABLEITEM:
            switch(Template.typetype)
            {
                case PLACEABLEITEM_EXPLOSIVE:// TODO (crom#1#): Explosive : Completer
                    //...
                    break;
            }
            break;
    }
    //Si le personnage en a les moyens
    if(Player::m_nMoney>=nPrice)
    {
        Player::m_nMoney -= nPrice;//Déduction de l'argent
        Player::m_oInventaire.AddItem(Template);//Don de l'objet
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void Player::SellItem(Item::Item* pItemToSell)
{
    int nRefund;
    struct itTemplate Template = pItemToSell->GetTemplate();

    switch(Template.type)
    {
        case ITEM_TYPE_WEAPON:
            nRefund = Get2daInt("weapon_rules.2da", Template.typetype, _2DA_WEAPON_PRICE);
            break;
        case ITEM_TYPE_ARMOR:
            nRefund = Get2daInt("armor_rules.2da", Template.typetype, _2DA_ARMOR_PRICE);
            break;
        case ITEM_TYPE_POTION:
            nRefund = Get2daInt("potion_rules.2da", Template.typetype, _2DA_POTION_PRICE);
            break;
        case ITEM_TYPE_PLACEABLEITEM:
            switch(Template.typetype)
            {
                case PLACEABLEITEM_EXPLOSIVE:// TODO (crom#1#): Explosive : Completer
                    //...
                    break;
            }
            break;
    }
    nRefund /= SELL_DECREASE;

    if(Player::m_oInventaire.GetItemRowInInventory(pItemToSell)!=-1)//On vérifie si il possède bien l'item
    {
        Player::m_nMoney += nRefund;//Don de l'argent
        Player::m_oInventaire.DelItem(pItemToSell);//Suppression de l'item
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
int Player::GetMoney() const
{
    return Player::m_nMoney;
}


//====================================================================================================================================================
//===GESTION====GESTION====GESTION====GESTION====GESTION====GESTION====GESTION====GESTION====GESTION====GESTION====GESTION====GESTION====GESTION======
//====================================================================================================================================================
void Player::SetInvalid()
{
    Player::bValid=false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
bool Player::GetIsValid()
{
    return Player::bValid;
}


//====================================================================================================================================================
//====================================================================================================================================================
//====================================================================================================================================================
//====================================================================================================================================================
//====================================================================================================================================================
//====================================================================================================================================================
//====================================================================================================================================================
//====================================================================================================================================================


void PlayerHandler::AddPlayer(std::string sPlayerName, int nSkin, int nTeam, sf::IPAddress IP)
{
    Player::Player PlayerToAdd(sPlayerName, nSkin, nTeam, IP);

    int n, nRow=-1;
    int nSize = PlayerHandler::m_ListePlayer.size();
    for(n=0 ; n<nSize ; n++)
    {
        if(!PlayerHandler::m_ListePlayer[n].GetIsValid())
        {
            nRow=n;
            break;
        }
    }
    if(nRow!=-1)
    {
        PlayerHandler::m_ListePlayer[nRow] = PlayerToAdd;
    }
    else
    {
        PlayerHandler::m_ListePlayer.push_back(PlayerToAdd);
    }

}






















