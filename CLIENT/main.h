#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define PI 3.14159265

#define VARIABLE_TYPE_STRING = 1;
#define VARIABLE_TYPE_INT = 2;
#define VARIABLE_TYPE_FLOAT = 3;

#define RESPAWN_DELAY 5.0

//VFX ============================================================
#define VFX_TYPE_INVALID 0
#define VFX_TYPE_ALL 1
#define VFX_TYPE_RAY 2
#define VFX_TYPE_EXPLOSION 3
#define VFX_TYPE_BLOOD 4

#define VFX_RAY_DIM_PX 3
#define VFX_RAY_IMPACT_DIM_PX 30

//ACTIONS ========================================================
#define ACTION_WAITING 0
#define ACTION_WALKING 1
#define ACTION_FIRING 2
#define ACTION_FIRING_WAIT 3
#define ACTION_RELOADING 4
#define ACTION_PLANTING_BOMB 10

//Equipes=========================================================
#define TEAM_NOTEAM 0
#define TEAM_RED 1
#define TEAM_GREEN 2
#define TEAM_BLUE 3

//ITEMS ==========================================================
#define ITEM_TYPE_UNDEFINED 0
#define ITEM_TYPE_ALL 1
#define ITEM_TYPE_WEAPON 2
    #define WEAPON_TYPE_UNDEFINED 0
    #define WEAPON_TYPE_BULLET_PISTOL 1
    #define WEAPON_TYPE_BULLET_RIFLE 2
    #define WEAPON_TYPE_BULLET_MINIGUN 3
    #define WEAPON_TYPE_LASER_PISTOL 11
    #define WEAPON_TYPE_LASER_RIFLE 12
    #define WEAPON_TYPE_LASER_MINIGUN 13
    #define WEAPON_TYPE_GAUSS_PISTOL 21
    #define WEAPON_TYPE_GAUSS_RIFLE 22
    #define WEAPON_TYPE_GAUSS_MINIGUN 23
    #define WEAPON_TYPE_GAUSS_DESTRUCTEUR 24
#define ITEM_TYPE_ARMOR 3
    #define ARMOR_TYPE_UNDEFINED 0
    #define ARMOR_TYPE_NAKED 1
    #define ARMOR_TYPE_LOW 2
    #define ARMOR_TYPE_MED 3
    #define ARMOR_TYPE_HIGH 4
    #define ARMOR_TYPE_BULLETS 10
    #define ARMOR_TYPE_LASER 11
    #define ARMOR_TYPE_GAUSS 12
#define ITEM_TYPE_POTION 4
    #define POTION_TYPE_UNDEFINED 0
    #define POTION_TYPE_BAD 1
    #define POTION_TYPE_MED 2
    #define POTION_TYPE_HIGH 3
#define ITEM_TYPE_PLACEABLEITEM 5
    #define PLACEABLEITEM_UNDEFINED 0
    #define PLACEABLEITEM_EXPLOSIVE 1
        #define EXPLOSIVE_TYPE_UNDEFINED 0
        #define EXPLOSIVE_TYPE_WORST 1
        #define EXPLOSIVE_TYPE_BAD 2
        #define EXPLOSIVE_TYPE_MED 3
        #define EXPLOSIVE_TYPE_HIGH 4
    #define PLACEABLEITEM_BLOC 1

#define EQUIPMENT_PART_WEAPON 2
#define EQUIPMENT_PART_ARMOR 3


//DAMAGES ========================================================
#define DAMAGE_TYPE_UNDEFINED 0
#define DAMAGE_TYPE_BULLET 1
#define DAMAGE_TYPE_LASER 2
#define DAMAGE_TYPE_GAUSS 3

#define DAMAGE_COLOR_BULLET_R 125
#define DAMAGE_COLOR_BULLET_G 125
#define DAMAGE_COLOR_BULLET_B 125
#define DAMAGE_COLOR_LASER_R 255
#define DAMAGE_COLOR_LASER_G 0
#define DAMAGE_COLOR_LASER_B 0
#define DAMAGE_COLOR_GAUS_R 0
#define DAMAGE_COLOR_GAUS_G 162
#define DAMAGE_COLOR_GAUS_B 255

//Réduction du prix de vente :
#define SELL_DECREASE 4


/*Correspondances world/screen ===================================
O---> X, Width, arg2
|
v
Y, Height, arg1
*/
#define WORLD_CUBE_NOTSET 0
#define WORLD_CUBE_FLOOR_ROCK 10
#define WORLD_CUBE_CRATE_A 20
#define WORLD_CUBE_GAP 30

#define WORLD_SPEC_NA 0
#define WORLD_SPEC_FLAG_RED 10
#define WORLD_SPEC_FLAG_GREEN 11
#define WORLD_SPEC_FLAG_BLUE 12
#define WORLD_SPEC_SPAWN_RED 20
#define WORLD_SPEC_SPAWN_GREEN 21
#define WORLD_SPEC_SPAWN_BLUE 22

#define COORD_OFFSET_WORLD_X 25
#define COORD_OFFSET_WORLD_Y 25

#define WORLD_WIDTH_PX 1150
#define WORLD_WIDTH_CUBE 23

#define WORLD_HEIGHT_PX 800
#define WORLD_HEIGHT_CUBE 16

#define WORLD_CUBE_PX 50

//Directions
#define DIRECTION_UNDEFINED 0
#define DIRECTION_NORTH 1
#define DIRECTION_EAST 2
#define DIRECTION_SOUTH 3
#define DIRECTION_WEST 4

//Vitesses de déplacement
#define VITESSE_CHARACTER_PX_S 300

//Taille de la fenetre:
//#define DIM_WINDOW_WIDTH 1200
//#define DIM_WINDOW_HEIGHT 900

//Tailles des images
#define DIM_CURSOR_WIDTH 40
    #define DIM_CURSOR_HEIGHT DIM_CURSOR_WIDTH

#define DIM_CHARACTER_WIDTH 50
#define DIM_CHARACTER_HEIGHT DIM_CHARACTER_WIDTH

#define DIM_EFFECT_RAY_WIDTH 3
    #define DIM_EFFECT_RAY_HEIGHT DIM_EFFECT_RAY_WIDTH
#define DIM_EFFECT_RAY_IMPACT_WIDTH 30
    #define DIM_EFFECT_RAY_IMPACT_HEIGHT DIM_EFFECT_RAY_IMPACT_WIDTH

#define DIM_EFFECT_EXPLOSION_WIDTH 150
    #define DIM_EFFECT_EXPLOSION_HEIGHT DIM_EFFECT_EXPLOSION_WIDTH
#define DIM_EFFECT_POSTEXPLOSION_WIDTH 100
    #define DIM_EFFECT_POSTEXPLOSION_HEIGHT DIM_EFFECT_POSTEXPLOSION_WIDTH

#define DIM_EFFECT_BLOOD_1_WIDTH 150
    #define DIM_EFFECT_BLOOD_1_HEIGHT DIM_EFFECT_BLOOD_1_WIDTH
#define DIM_EFFECT_BLOOD_2_WIDTH 100
    #define DIM_EFFECT_BLOOD_2_HEIGHT DIM_EFFECT_BLOOD_2_WIDTH


#define DIM_SCREEN_ENTRYBOX_WIDTH 400
    #define DIM_SCREEN_ENTRYBOX_HEIGHT 300


struct worldpospx
{
    float ver;
    float hrz;
};

struct worldposblock
{
    int ver;
    int hrz;
};




#endif // MAIN_H_INCLUDED
