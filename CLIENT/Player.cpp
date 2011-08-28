#include <iostream>
#include <cstdlib>

#include <vector>//Pour les tableaux dynamiques
#include <string>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "main.h"
#include "Player.h"

#include "Vfx.h"
#include "convert.h"
#include "guifunc.h"
#include "utils.h"
#include "world.h"


extern int nWorld[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];
extern int nWorldSpe[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];
extern Vfx oVfx;
extern sf::RenderWindow oApp;

extern sf::Clock clkDateGame;


//====================================================================================================================================================
struct location PC::GetLocation()const
{
    struct location Loc;
    Loc.pos = PC::m_pPosition;
    Loc.facing = PC::m_fFacing;
    return Loc;
}
//====================================================================================================================================================
float PC::GetSpeed()const
{
    return 0.0;
}
//====================================================================================================================================================
int PC::GetHP() const
{
    return PC::m_nHP;
}

//====================================================================================================================================================
bool PC::GetIsDead() const
{
    if(PC::m_nHP<=0)
        return true;
    return false;
}
//====================================================================================================================================================
int PC::GetTeam() const
{
    return PC::m_nTeam;
}
//====================================================================================================================================================
int PC::GetSkin() const
{
    return PC::m_nSkin;
}




















//====================================================================================================================================================
PC::PC(int nTeam):m_oInventaire()
{
    PC::m_nTeam=nTeam;
    PC::m_nHP=0;
    PC::m_nMoney=0;
    PC::m_vSpeed=sf::Vector2f(0, 0);// pixel/sec
    PC::m_fFacing=0;
    PC::m_pPosition.hrz = 75;
    PC::m_pPosition.ver = 75;

    PC::m_fFireDelayDateEnd=0.0;
    PC::m_fReloadDelayDateEnd=0.0;

    PC::m_oInventaire.Display();
}
//====================================================================================================================================================
PC::~PC()
{

}

//====================================================================================================================================================
void PC::FireAtPosition(struct worldpospx pPosVisee)
{
    float fDate = clkDateGame.GetElapsedTime();
    if(PC::m_fFireDelayDateEnd>fDate)//Si le joueur a tiré il y a peu de temps, on lui interdit de tirer
        return;

    if(PC::m_fReloadDelayDateEnd>fDate)//si le joueur doit recharger
        return;

    Item::Item* pWeapon = PC::m_oInventaire.GetEquipedItem(EQUIPMENT_PART_WEAPON);
    if(pWeapon == 0)return;

    int nRange = pWeapon->Weapon_GetRange();
    int nDamageType = pWeapon->Weapon_GetDamageType();

    //Determination du coeff de la droite
    float fDeltaVer = (pPosVisee.ver - PC::m_pPosition.ver),
          fDeltaHrz = (pPosVisee.hrz - PC::m_pPosition.hrz);

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
        if((pPosVisee.hrz - PC::m_pPosition.hrz)>0)
            nSens=1;
        else if((pPosVisee.hrz - PC::m_pPosition.hrz)<0)
            nSens=-1;
        else
            return;

        vPosPoint.hrz=0;
        vPosDepRay.hrz=0; vPosDepRay.ver=0;
        //Verif point par point de la droite. Le point en cours est localisé par vPosPoint dans world
        for(nDelta=12*nSens ; 1 ; nDelta+=nSens)
        {
            //Calcul de la future position
            vPosPoint.hrz = PC::m_pPosition.hrz+nDelta-(VFX_RAY_DIM_PX/2);
            vPosPoint.ver = PC::m_pPosition.ver+fCoeff*nDelta-(VFX_RAY_DIM_PX/2);

            vPosPointBlocs = CoordWorldPxToWorldBlocks(vPosPoint);

            fDistance = GetDistanceBetween(PC::m_pPosition.hrz, PC::m_pPosition.ver, vPosPoint.hrz, vPosPoint.ver);

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
        if((PC::m_pPosition.ver - pPosVisee.ver)>0)
            nSens=-1;
        else if((PC::m_pPosition.ver - pPosVisee.ver)<0)
            nSens=1;
        else
            return;

        vPosPoint.ver=0;
        vPosDepRay.hrz=0; vPosDepRay.ver=0;
        //Verif point par point de la droite. Le point en cours est localisé par vPosPoint dans world
        for(nDelta=12*nSens ; 1 ; nDelta+=nSens)
        {
            //Calcul de la future position
            vPosPoint.ver = PC::m_pPosition.ver+nDelta-(VFX_RAY_DIM_PX/2);
            vPosPoint.hrz = PC::m_pPosition.hrz+fCoeff*nDelta-(VFX_RAY_DIM_PX/2);

            vPosPointBlocs = CoordWorldPxToWorldBlocks(vPosPoint);

            fDistance = GetDistanceBetween(PC::m_pPosition.hrz, PC::m_pPosition.ver, vPosPoint.hrz, vPosPoint.ver);

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
        PC::m_fReloadDelayDateEnd = pWeapon->Weapon_GetReusableDateAfterEvent(1);
        pWeapon->Weapon_Reload();
    }
    else//Cooldown du tir
    {
        PC::m_fFireDelayDateEnd = pWeapon->Weapon_GetReusableDateAfterEvent(0);
    }
    //On joue le son
    pWeapon->Weapon_PlaySound(0);
    //On ajoute le ray
    if(!bDepRayIsSet)
    {
        vPosDepRay=vPosPoint;
    }
    oVfx.AddRay(nDamageType, vPosDepRay, vPosPoint, bImpact);
}


//====================================================================================================================================================
bool PC::TakeDamages(int nAmount, int nDamageType)
{
    int nDmgFinal;
    float fDate = clkDateGame.GetElapsedTime();

    Item::Item* pArmor = PC::m_oInventaire.GetEquipedItem(EQUIPMENT_PART_ARMOR);
    if(pArmor == 0)return true;

    float fArmorReduction = 1-(pArmor->Armor_GetReduction(nDamageType))/100;

    nDmgFinal = nAmount*fArmorReduction;

    if(PC::m_nHP-nDmgFinal <= 0)
    {
        PC::m_nHP = 0;
        PC::m_fRespawnDelayDateEnd = fDate+RESPAWN_DELAY;
        return true;
    }
    else
    {
        PC::m_nHP -= nDmgFinal;
        return false;
    }
}


//====================================================================================================================================================
void PC::Heal(int nAmount)
{
    if(PC::m_nHP+nAmount > 100)
    {
        PC::m_nHP = 100;
    }
    else
    {
        PC::m_nHP += nAmount;
    }
}
//====================================================================================================================================================
void PC::ChangeTeam(int nNewTeam)
{
    float fDate = clkDateGame.GetElapsedTime();

    PC::m_nHP=0;
    PC::m_fRespawnDelayDateEnd = fDate+RESPAWN_DELAY;

    PC::m_nTeam = nNewTeam;
}
//====================================================================================================================================================
Inventory::Inventory* PC::GetInventory()
{
    return &(PC::m_oInventaire);
}
//====================================================================================================================================================
bool PC::UsePotion(int nPotionType)
{
    struct itTemplate Template = MakeItemTemplate(ITEM_TYPE_POTION, nPotionType);
    Item::Item* pPotion = PC::m_oInventaire.GetFirstItem(Template);

    //Si l'objet à equipper est bien dans l'inventaire
    if(PC::m_oInventaire.GetItemStack(Template)>0)
    {
        int nAmount = pPotion->Potion_GetHpHeal();

        PC::Heal(nAmount);
        PC::m_oInventaire.DelItem(pPotion);
        return true;
    }
    else
    {
        std::cout << "L'item n'est pas dans l'inventaire !"<<std::endl;
        return false;
    }


}
//====================================================================================================================================================
bool PC::BuyItem(struct itTemplate Template)
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
    if(PC::m_nMoney>=nPrice)
    {
        PC::m_nMoney -= nPrice;//Déduction de l'argent
        PC::m_oInventaire.AddItem(Template);//Don de l'objet
        return true;
    }
    return false;
}

//====================================================================================================================================================
void PC::SellItem(Item::Item* pItemToSell)
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

    if(PC::m_oInventaire.GetItemRowInInventory(pItemToSell)!=-1)//On vérifie si il possède bien l'item
    {
        PC::m_nMoney += nRefund;//Don de l'argent
        PC::m_oInventaire.DelItem(pItemToSell);//Suppression de l'item
    }
}

extern sf::View oView;
//====================================================================================================================================================
bool PC::MoveToDirection(int nDirection, float fMod)
{
    struct worldpospx pNewPosition;
    pNewPosition.hrz=PC::m_pPosition.hrz;
    pNewPosition.ver=PC::m_pPosition.ver;
    float fFrameTime = oApp.GetFrameTime();

    #define SPEEDMAX 400.0
    #define SPEEDINC 2000.0

    switch(nDirection)
    {
        case DIRECTION_NORTH:
            //Empêche de dépasser la vitesse max
            if(PC::m_vSpeed.x*PC::m_vSpeed.x+PC::m_vSpeed.y*PC::m_vSpeed.y<SPEEDMAX*SPEEDMAX)
            {
                PC::m_vSpeed.y-=SPEEDINC*fFrameTime*fMod;
            }
            break;
        case DIRECTION_EAST:
            if(PC::m_vSpeed.x*PC::m_vSpeed.x+PC::m_vSpeed.y*PC::m_vSpeed.y<SPEEDMAX*SPEEDMAX)
            {
                PC::m_vSpeed.x+=SPEEDINC*fFrameTime*fMod;
            }
            break;
        case DIRECTION_SOUTH:
            if(PC::m_vSpeed.x*PC::m_vSpeed.x+PC::m_vSpeed.y*PC::m_vSpeed.y<SPEEDMAX*SPEEDMAX)
            {
                PC::m_vSpeed.y+=SPEEDINC*fFrameTime*fMod;
            }
            break;
        case DIRECTION_WEST:
            if(PC::m_vSpeed.x*PC::m_vSpeed.x+PC::m_vSpeed.y*PC::m_vSpeed.y<SPEEDMAX*SPEEDMAX)
            {
                PC::m_vSpeed.x-=SPEEDINC*fFrameTime*fMod;
            }
            break;
    }

    pNewPosition.hrz = PC::m_pPosition.hrz+PC::m_vSpeed.x*fFrameTime*fMod;
    pNewPosition.ver = PC::m_pPosition.ver+PC::m_vSpeed.y*fFrameTime*fMod;
    if(!GetIsCollisionPJWithWorld(pNewPosition))
    {
        PC::m_pPosition.hrz += PC::m_vSpeed.x*fFrameTime*fMod;
        PC::m_pPosition.ver += PC::m_vSpeed.y*fFrameTime*fMod;
    }
    else//En cas de collision
    {

        struct worldpospx pPosBlock = CoordWorldBlocksToWorldPx(CoordWorldPxToWorldBlocks(pNewPosition), true);
        int nDeltaX = PC::m_pPosition.hrz - pPosBlock.hrz;
        int nDeltaY = PC::m_pPosition.ver - pPosBlock.ver;

        if(nDeltaX<0 && abs(nDeltaX)>abs(nDeltaY))
        {//Partie à gauche
            PC::m_vSpeed.y=0.0;
            pNewPosition.hrz = pPosBlock.hrz-25;// pos-demi coté d'un bloc
        }
        if(nDeltaX>0 && abs(nDeltaX)>abs(nDeltaY))
        {//Partie à droite
            PC::m_vSpeed.y=0.0;
            pNewPosition.hrz = pPosBlock.hrz+25;// pos-demi coté d'un bloc
        }
        if(nDeltaY<0 && abs(nDeltaX)<abs(nDeltaY))
        {//Partie en haut
            PC::m_vSpeed.x=0.0;
            pNewPosition.ver = pPosBlock.ver-25;// pos-demi coté d'un bloc
        }
        if(nDeltaY>0 && abs(nDeltaX)<abs(nDeltaY))
        {//Partie en bas
            PC::m_vSpeed.x=0.0;
            pNewPosition.ver = pPosBlock.ver+25;// pos-demi coté d'un bloc
        }

        PC::m_pPosition = pNewPosition;

    }
    return true;
}
//====================================================================================================================================================
void PC::DecreaseSpeed()
{
    #define SPEEDDEC 500.0

    float fFrameTime = oApp.GetFrameTime();
    if(PC::m_vSpeed.x>0)
    {
        if(PC::m_vSpeed.x>=SPEEDDEC*fFrameTime)
            PC::m_vSpeed.x-=SPEEDDEC*fFrameTime;
        else
            PC::m_vSpeed.x=0;
    }
    else if(PC::m_vSpeed.x<0)
    {
        if(PC::m_vSpeed.x<=-SPEEDDEC*fFrameTime)
            PC::m_vSpeed.x+=SPEEDDEC*fFrameTime;
        else
            PC::m_vSpeed.x=0;
    }
    if(PC::m_vSpeed.y>0)
    {
        if(PC::m_vSpeed.y>=SPEEDDEC*fFrameTime)
            PC::m_vSpeed.y-=SPEEDDEC*fFrameTime;
        else
            PC::m_vSpeed.y=0;
    }
    else if(PC::m_vSpeed.y<0)
    {
        if(PC::m_vSpeed.y<=-SPEEDDEC*fFrameTime)
            PC::m_vSpeed.y+=SPEEDDEC*fFrameTime;
        else
            PC::m_vSpeed.y=0;
    }
}

//====================================================================================================================================================
int PC::GetMoney() const
{
    return PC::m_nMoney;
}

//====================================================================================================================================================
void PC::SetFacing(float fFacing)
{
    PC::m_fFacing = fFacing;
}







/*==*/ extern sf::Image imgPlayer;
/*==*/    extern sf::Sprite sprPlayerSkinDefault;



void PlayerHandler::DrawPlayers()
{
    struct location lPlayer = PlayerHandler::m_oPC.GetLocation();
    bool bDead = PlayerHandler::m_oPC.GetIsDead();
    int nTeam = PlayerHandler::m_oPC.GetTeam();
    int nSkin = PlayerHandler::m_oPC.GetSkin();

    sf::Sprite* sprPC=0;
    ApplySkin(nSkin, sprPC);
    ApplyTeamColor(nTeam, sprPC);
    ApplyLocation(lPlayer, sprPC);
    oApp.Draw(*sprPC);

/*
    sf::Sprite* sprNPC=0;
    int nSize = PlayerHandler::m_ListeNPC.size();
    int i;
    for(i=0 ; i<nSize  ; i++)
    {
        lPlayer = PlayerHandler::m_ListeNPC[i].GetLocation();
        bDead = PlayerHandler::m_ListeNPC[i].GetIsDead();
        nTeam = PlayerHandler::m_ListeNPC[i].GetTeam();
        nSkin = PlayerHandler::m_ListeNPC[i].GetSkin();

        sprNPC=0;
        ApplySkin(nSkin, sprNPC);
        ApplyTeamColor(nTeam, sprNPC);
        ApplyLocation(lPlayer, sprNPC);
        oApp.Draw(*sprNPC);
    }*/
}




void PlayerHandler::ApplySkin(int nSkin, sf::Sprite* sprPlayer)
{
    switch(nSkin)// <-------------------------------Liste des skins player
    {
        default:
            sprPlayer=&sprPlayerSkinDefault;
            break;
    }
}
void PlayerHandler::ApplyTeamColor(int nTeam, sf::Sprite* sprPlayer)
{
    switch(nTeam)
    {
        case TEAM_NOTEAM:
            break;
        case TEAM_RED:
            sprPlayer->SetColor(sf::Color(255, 128, 128));
            break;
        case TEAM_GREEN:
            sprPlayer->SetColor(sf::Color(128, 255, 128));
            break;
        case TEAM_BLUE:
            sprPlayer->SetColor(sf::Color(128, 128, 255));
            break;
    }
}
void PlayerHandler::ApplyLocation(struct location lPlayer, sf::Sprite* sprPlayer)
{
    sprPlayer->Rotate(lPlayer.facing-sprPlayer->GetRotation());

    sf::Vector2<float>::Vector2<float> vPosAff = CoordWorldPxToScreenPx(lPlayer.pos);
    sprPlayer->SetPosition(sf::Vector2f(vPosAff.x, vPosAff.y));
}


























