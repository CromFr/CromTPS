#include <SFML/Graphics.hpp>

#include "main.h"


//Renvoie la coord en cubes correspondant à l'endroit indiqué par vCoordScreen
struct worldposblock CoordScreenPxToWorldBlocks(sf::Vector2<float>::Vector2<float> vCoordScreen)
{
    struct worldposblock vCoordWorldBlock;
    vCoordWorldBlock.hrz = (vCoordScreen.x-COORD_OFFSET_WORLD_X)/WORLD_CUBE_PX;
    vCoordWorldBlock.ver = (vCoordScreen.y-COORD_OFFSET_WORLD_Y)/WORLD_CUBE_PX;
    return vCoordWorldBlock;
}


//Renvoie la coord en PX par rapport à oWindow d'un cube (coin haut gauche)
sf::Vector2<float>::Vector2<float> CoordWorldBlocksToScreenPx(struct worldposblock CoordWorldBlock, bool bCenter)
{
    int nCenter=0;
    if(bCenter)nCenter=WORLD_WIDTH_CUBE/2;

    float x = CoordWorldBlock.hrz*WORLD_CUBE_PX+COORD_OFFSET_WORLD_X +nCenter;
    float y = CoordWorldBlock.ver*WORLD_CUBE_PX+COORD_OFFSET_WORLD_Y +nCenter;
    return sf::Vector2f(x, y);

}

//Renvoie la coord en px dans le world par rapport à un pixel dans la fenêtre
struct worldpospx CoordScreenPxToWorldPx(sf::Vector2<float>::Vector2<float> vCoordScreenPx)
{
    struct worldpospx vCoordWorld;
    vCoordWorld.hrz = vCoordScreenPx.x-COORD_OFFSET_WORLD_X;
    vCoordWorld.ver = vCoordScreenPx.y-COORD_OFFSET_WORLD_Y;
    return vCoordWorld;

}

sf::Vector2<float>::Vector2<float> CoordWorldPxToScreenPx(struct worldpospx CoordWorldPx)
{
    float x = CoordWorldPx.hrz+COORD_OFFSET_WORLD_X;
    float y = CoordWorldPx.ver+COORD_OFFSET_WORLD_Y;
    return sf::Vector2f(x, y);

}


struct worldposblock CoordWorldPxToWorldBlocks(struct worldpospx vCoordWorldPx)
{
    struct worldposblock vCoordWorldBlock;
    vCoordWorldBlock.hrz = (vCoordWorldPx.hrz)/WORLD_CUBE_PX;
    vCoordWorldBlock.ver = (vCoordWorldPx.ver)/WORLD_CUBE_PX;
    return vCoordWorldBlock;
}

struct worldpospx CoordWorldBlocksToWorldPx(struct worldposblock CoordWorldBlock, bool bCenter)
{
    struct worldpospx vCoordWorldPx;
    int nCenter=0;
    if(bCenter)nCenter=WORLD_WIDTH_CUBE/2;

    vCoordWorldPx.hrz = CoordWorldBlock.hrz*WORLD_CUBE_PX+COORD_OFFSET_WORLD_X +nCenter;
    vCoordWorldPx.ver = CoordWorldBlock.ver*WORLD_CUBE_PX+COORD_OFFSET_WORLD_Y +nCenter;
    return vCoordWorldPx;

}

















