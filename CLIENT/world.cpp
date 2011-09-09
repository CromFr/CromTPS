#include <iostream>
#include <cstdlib>
#include <fstream>

#include <SFML/Graphics.hpp>
#include "main.h"
#include "world.h"
#include "convert.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern int nWorld[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];
extern int nWorldSpe[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];

int LoadMap(std::string sMapName)
{
    int i, j;

    std::string sPath("map/");
    std::string sExtension(".map");

    std::ifstream stMap((sPath+sMapName+sExtension).c_str());
    if(!stMap)
    {
        std::cout<<"Erreur LoadMap : Map introuvable"<<std::endl;
        return false;
    }

    if(stMap)
    {
        for(i=0 ; i<WORLD_HEIGHT_CUBE ; i++)
        {
            for(j=0 ; j<WORLD_WIDTH_CUBE ; j++)
            {
                stMap>>nWorld[i][j];
                stMap>>nWorldSpe[i][j];
            }
        }
    }
    return true;
}


bool GetIsBlockingVision(int nType)
{
    if(//Liste des types qui bloquent la vision
          nType == WORLD_CUBE_CRATE_A
       || 0





       )
        return true;
    return false;
}


bool GetIsBlockingWalk(int nType)
{
    if(//Liste des types qui bloquent la vision
          nType == WORLD_CUBE_CRATE_A
       || nType == WORLD_CUBE_GAP





       )
        return true;
    return false;
}



bool GetIsCollisionBallWithWorld(struct worldpospx pBall, float fRadius)
{/*
    //Avec les blocs :
    struct worldposblock pBlock = CoordWorldPxToWorldBlocks(worldpospx+);

    racine de 2 / 2 * radius

    worldpospx

*/
return false;
}

bool GetIsCollisionPointWithBall(struct worldpospx pPosPoint, struct worldpospx pPosBall, float fRadius)
{
    int nDeltaHrz = pPosPoint.hrz - pPosBall.hrz;
    int nDeltaVer = pPosPoint.ver - pPosBall.ver;

    //           Distance calculée                 Minimale
    if(nDeltaHrz*nDeltaHrz+nDeltaVer*nDeltaVer < fRadius*fRadius)
    {
        return true;
    }
    return false;
}



bool GetIsCollisionPJWithWorld(struct worldpospx pPosPX)
{
    //Le pj est considéré comme un carré de coté 20
    struct worldpospx pPosTestPX;
    struct worldposblock pPosTestBlock;

    //Avec les cubes
    int n;
    for(n=0 ; n<4 ; n++)
    {
        switch(n)
        {
            case 0:
                pPosTestPX.hrz = pPosPX.hrz+10;
                pPosTestPX.ver = pPosPX.ver-10;
                break;
            case 1:
                pPosTestPX.hrz = pPosPX.hrz+10;
                pPosTestPX.ver = pPosPX.ver+10;
                break;
            case 2:
                pPosTestPX.hrz = pPosPX.hrz-10;
                pPosTestPX.ver = pPosPX.ver+10;
                break;
            case 3:
                pPosTestPX.hrz = pPosPX.hrz-10;
                pPosTestPX.ver = pPosPX.ver-10;
                break;
        }
        pPosTestBlock = CoordWorldPxToWorldBlocks(pPosTestPX);
        if(GetIsBlockingWalk(nWorld[pPosTestBlock.ver][pPosTestBlock.hrz]))
            return true;
    }

    //Avec les bords du screen
    if(pPosPX.hrz<0 || pPosPX.hrz>WORLD_WIDTH_PX || pPosPX.ver<0 || pPosPX.ver>WORLD_HEIGHT_PX)
        return true;

    return false;
}



bool GetIsCoordScreenPxInWorld(sf::Vector2<float>::Vector2<float> vPos)
{
    if(   vPos.x>COORD_OFFSET_WORLD_X && vPos.x<SCREEN_WIDTH-COORD_OFFSET_WORLD_X
       && vPos.y>COORD_OFFSET_WORLD_Y && vPos.y<SCREEN_HEIGHT-COORD_OFFSET_WORLD_Y)
       return true;
    return false;

}







