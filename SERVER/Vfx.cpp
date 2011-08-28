/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>*/
#include <iostream>
#include <cstdlib>
#include <vector>//Pour les tableaux dynamiques

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "main.h"//Struct position
#include "world.h"//Constantes WORLD_..
#include "convert.h"
#include "Vfx.h"

using namespace sf;

extern Clock clkDateGame;


/*Vfx::Vfx()
{

}
*/


void Vfx::AddRay(int nDamageType, struct worldpospx pRayStart, struct worldpospx pRayEnd, bool bImpact, float fTimeoutms)
{
    int nEmplacement = -1;
    int nTaille = Vfx::vfxRaysList.size();
    float fDate = clkDateGame.GetElapsedTime();

    //Determination du vfx à entrer
    struct vfxray vfxRayToAdd;
        vfxRayToAdd.type = nDamageType;
        vfxRayToAdd.dep = pRayStart;
        vfxRayToAdd.fin = pRayEnd;
        vfxRayToAdd.dateout = fDate+fTimeoutms;
        vfxRayToAdd.impact = bImpact;

    //Recherche d'une case inactive où on pourrait placer le ray
    int i;
    for(i=0 ; i<nTaille ; i++)
    {
        if(Vfx::vfxRaysList[i].dateout<fDate)
        {
            nEmplacement = i;
            break;
        }
    }

    //Si aucune case inactive n'a été trouvée dans le tableau
    if(nEmplacement==-1)
    {
        //On rajoute une ligne
        Vfx::vfxRaysList.push_back(vfxRayToAdd);
    }
    //Si une case a été trouvée
    else
    {
        Vfx::vfxRaysList[nEmplacement] = vfxRayToAdd;
    }
}

//=================================================================================================================================================
void Vfx::AddExlplosion(struct worldpospx pPosition, float fFadeTime, float fPostVfxFadeTime)
{
    int nEmplacement = -1;
    int nTaille = Vfx::vfxExplosionsList.size();
    float fDate = clkDateGame.GetElapsedTime();

    //Determination du vfx à entrer
    struct vfxexplosion vfxExplosionToAdd;
        vfxExplosionToAdd.pos = pPosition;
        vfxExplosionToAdd.fadetime = fFadeTime;
        vfxExplosionToAdd.dateout = fDate+fFadeTime;
        vfxExplosionToAdd.postvfxfadetime = fPostVfxFadeTime;
        vfxExplosionToAdd.postvfxdateout = fDate+fPostVfxFadeTime;

    //Recherche d'une case inactive où on pourrait placer le ray
    int i;
    for(i=0 ; i<nTaille ; i++)
    {
        if(Vfx::vfxExplosionsList[i].postvfxdateout < fDate)
        {
            nEmplacement = i;
            break;
        }
    }

    //Si aucune case inactive n'a été trouvée dans le tableau
    if(nEmplacement==-1)
    {
        //On rajoute une ligne
        Vfx::vfxExplosionsList.push_back(vfxExplosionToAdd);
    }
    //Si une case a été trouvée
    else
    {
        Vfx::vfxExplosionsList[nEmplacement] = vfxExplosionToAdd;
    }

}

//=================================================================================================================================================
void Vfx::AddBlood(struct worldpospx pPosition, float fTimeout)
{
    int nEmplacement = -1;
    int nTaille = Vfx::vfxBloodsList.size();
    float fDate = clkDateGame.GetElapsedTime();

    //Determination du vfx à entrer
    struct vfxblood vfxBloodToAdd;
        vfxBloodToAdd.pos = pPosition;
        vfxBloodToAdd.type = rand()%2;
        vfxBloodToAdd.dateout = fDate+fTimeout;

    //Recherche d'une case inactive où on pourrait placer
    int i;
    for(i=0 ; i<nTaille ; i++)
    {
        if(Vfx::vfxBloodsList[i].dateout<fDate)
        {
            nEmplacement = i;
            break;
        }
    }

    //Si aucune case inactive n'a été trouvée dans le tableau
    if(nEmplacement==-1)
    {
        //On rajoute une ligne
        Vfx::vfxBloodsList.push_back(vfxBloodToAdd);
    }
    //Si une case a été trouvée
    else
    {
        Vfx::vfxBloodsList[nEmplacement] = vfxBloodToAdd;
    }
}

//=================================================================================================================================================
void Vfx::Clear(int nType)
{
    if(nType == VFX_TYPE_RAY || nType == VFX_TYPE_ALL)
    {
        while(Vfx::vfxRaysList.size()>0)
        {
            Vfx::vfxRaysList.pop_back();
        }
    }
    if(nType == VFX_TYPE_EXPLOSION || nType == VFX_TYPE_ALL)
    {
        while(Vfx::vfxExplosionsList.size()>0)
        {
            Vfx::vfxExplosionsList.pop_back();
        }
    }
    if(nType == VFX_TYPE_BLOOD || nType == VFX_TYPE_ALL)
    {
        while(Vfx::vfxBloodsList.size()>0)
        {
            Vfx::vfxBloodsList.pop_back();
        }
    }

}


