#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED


//2da ============================================================
//weapon_rules.2da :
#define _2DA_WEAPON_PRICE 1
#define _2DA_WEAPON_NAME 2
#define _2DA_WEAPON_DAMAGE_TYPE 3
#define _2DA_WEAPON_DAMAGE 4
#define _2DA_WEAPON_STOCK 5
#define _2DA_WEAPON_FIRE_DELAY 6
#define _2DA_WEAPON_RELOAD_DELAY 7
#define _2DA_WEAPON_RANGE 8
#define _2DA_WEAPON_FIRE_SOUND 9
#define _2DA_WEAPON_IMPACT_SOUND 10
//armor_rules.2da :
#define _2DA_ARMOR_PRICE 1
#define _2DA_ARMOR_NAME 2
#define _2DA_ARMOR_RD_VS_BULLETS 3
#define _2DA_ARMOR_RD_VS_LASER 4
#define _2DA_ARMOR_RD_VS_GAUSS 5
//potion_rules.2da :
#define _2DA_POTION_PRICE 1
#define _2DA_POTION_NAME 2
#define _2DA_POTION_HPHEAL_BASE 3
#define _2DA_POTION_HPHEAL_RANDOM 4
//explosive_rules.2da :
#define _2DA_PLACEABLEITEM_EXPLOSIVE_PRICE 1
#define _2DA_PLACEABLEITEM_EXPLOSIVE_NAME 2
#define _2DA_PLACEABLEITEM_EXPLOSIVE_DAMAGE 3
#define _2DA_PLACEABLEITEM_EXPLOSIVE_RANGE 4
#define _2DA_PLACEABLEITEM_EXPLOSIVE_TIMEOUT 5

int Get2daInt(const std::string s2DAName, int nLineToGo, int nColonneToGo);
float Get2daFloat(const std::string s2DAName, int nLineToGo, int nColonneToGo);
std::string Get2daString(const std::string s2DAName, int nLineToGo, int nColonneToGo);

//======================================================================================

float GetDistanceBetween(int pPosAx, int pPosAy, int pPosBx, int pPosBy);


#endif // UTILS_H_INCLUDED
