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
void Vfx::Draw(int nType)
{
    int n, nTaille;
    float fDate = clkDateGame.GetElapsedTime();

    if(nType == VFX_TYPE_RAY || nType == VFX_TYPE_ALL)
    {
        //BLIT DES RAYS
        nTaille = Vfx::vfxRaysList.size();

        for(n=0 ; n<nTaille ; n++)
        {
            //Si la date ou le ray doit être désactivé n'est pas encore arrivée
            if(Vfx::vfxRaysList[n].dateout >= fDate)
            {
                Vfx::BlitRay(Vfx::vfxRaysList[n].dep, Vfx::vfxRaysList[n].fin, Vfx::vfxRaysList[n].impact, Vfx::vfxRaysList[n].type);
            }
        }
    }
    if(nType == VFX_TYPE_EXPLOSION || nType == VFX_TYPE_ALL)
    {
        //BLIT DES EXPLOSIONS
        nTaille = Vfx::vfxExplosionsList.size();

        bool bExplosion, bPostEffects;
        int nAlphaExplosion, nAlphaPostEffect;

        for(n=0 ; n<nTaille ; n++)
        {
            //Si la date ou le ray doit être désactivé n'est pas encore arrivée
            if(Vfx::vfxExplosionsList[n].postvfxdateout >= fDate)
            {
                //Doit on afficher une explosion?
                if(Vfx::vfxExplosionsList[n].dateout >= fDate)//TimeOut de l'explosion pas encore arrivé
                {
                    bExplosion=1;
                    float f = (Vfx::vfxExplosionsList[n].dateout-fDate)/(Vfx::vfxExplosionsList[n].fadetime);
                    nAlphaExplosion = (f)*255;
                }
                else
                {
                    bExplosion=0;
                    nAlphaExplosion=0;
                }

                //Doit on afficher un posteffect?
                if(Vfx::vfxExplosionsList[n].postvfxdateout >= fDate)//TimeOut de l'explosion pas encore arrivé
                {
                    bPostEffects=1;
                    nAlphaPostEffect = ((Vfx::vfxExplosionsList[n].postvfxdateout-fDate)/(Vfx::vfxExplosionsList[n].postvfxfadetime))*255;
                }
                else
                {
                    bPostEffects=0;
                    nAlphaPostEffect=0;
                }


                Vfx::BlitExplosion(Vfx::vfxExplosionsList[n].pos, bExplosion, nAlphaExplosion, bPostEffects, nAlphaPostEffect);
            }
        }
    }
    if(nType == VFX_TYPE_BLOOD || nType == VFX_TYPE_ALL)
    {
        //BLIT DES TACHES DE SANG
        nTaille = Vfx::vfxBloodsList.size();

        for(n=0 ; n<nTaille ; n++)
        {
        if(Vfx::vfxBloodsList[n].dateout >= fDate)
            {
                Vfx::BlitBlood(Vfx::vfxBloodsList[n].pos, Vfx::vfxBloodsList[n].type);
            }
        }
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
















//======================================================================================================================================================================================
//Private ==============================================================================================================================================================================


//Application :
extern RenderWindow oApp;

/*====> Liste des images ============*/
/*==*/ //VFX
/*==*/ extern Image oEffectRayBullet;
/*==*/    extern Sprite sprEffectRayBullet;
/*==*/ extern Image oEffectRayBulletImpact;
/*==*/    extern Sprite sprEffectRayBulletImpact;
/*==*/ extern Image oEffectRayLaser;
/*==*/    extern Sprite sprEffectRayLaser;
/*==*/ extern Image oEffectRayLaserImpact;
/*==*/    extern Sprite sprEffectRayLaserImpact;
/*==*/ extern Image oEffectRayGauss;
/*==*/    extern Sprite sprEffectRayGauss;
/*==*/ extern Image oEffectRayGaussImpact;
/*==*/    extern Sprite sprEffectRayGaussImpact;
/*==*/ extern Image oEffectExplosion;
/*==*/    extern Sprite sprEffectExplosion;
/*==*/ extern Image oEffectPostExplosion;
/*==*/    extern Sprite sprEffectPostExplosion;
/*==*/ extern Image oEffectBlood1;
/*==*/    extern Sprite sprEffectBlood1;
/*==*/ extern Image oEffectBlood2;
/*==*/    extern Sprite sprEffectBlood2;


void Vfx::BlitRay(struct worldpospx pPosDepart, struct worldpospx pPosArrivee, bool bImpact, int nDamageType)
{
    Sprite sprImpact;
    Color rgbColor;

    struct worldpospx vPosPoint;
    Vector2<float>::Vector2<float> pPosDepartScreen, pPosArriveeScreen;

    switch(nDamageType)
    {
        case DAMAGE_TYPE_BULLET: rgbColor = Color(DAMAGE_COLOR_BULLET_R, DAMAGE_COLOR_BULLET_G, DAMAGE_COLOR_BULLET_B);
                                 sprImpact.SetImage(oEffectRayBulletImpact);
                                 break;
        case DAMAGE_TYPE_LASER: rgbColor = Color(DAMAGE_COLOR_LASER_R, DAMAGE_COLOR_LASER_G, DAMAGE_COLOR_LASER_B);
                                sprImpact.SetImage(oEffectRayLaserImpact);
                                break;
        case DAMAGE_TYPE_GAUSS: rgbColor = Color(DAMAGE_COLOR_GAUS_R, DAMAGE_COLOR_GAUS_G, DAMAGE_COLOR_GAUS_B);
                                sprImpact.SetImage(oEffectRayGaussImpact);
                                break;
    }

    pPosDepartScreen = CoordWorldPxToScreenPx(pPosDepart);
    pPosArriveeScreen = CoordWorldPxToScreenPx(pPosArrivee);

    oApp.Draw(Shape::Line(pPosDepartScreen.x, pPosDepartScreen.y, pPosArriveeScreen.x, pPosArriveeScreen.y, 1, rgbColor));

    if(bImpact)
    {
        vPosPoint.hrz = pPosArrivee.hrz - (DIM_EFFECT_RAY_IMPACT_WIDTH/2);
        vPosPoint.ver = pPosArrivee.ver - (DIM_EFFECT_RAY_IMPACT_HEIGHT/2);
        sprImpact.SetPosition(CoordWorldPxToScreenPx(vPosPoint));
        oApp.Draw(sprImpact);
    }

}

void Vfx::BlitExplosion(struct worldpospx pPosition, bool bExplosion, int nAlphaExplosion, bool bPostEffect, int nAlphaPostEffect)
{
    struct worldpospx vPosPoint;

    if(bPostEffect)
    {
        vPosPoint.hrz = pPosition.hrz - (DIM_EFFECT_POSTEXPLOSION_WIDTH/2);
        vPosPoint.ver = pPosition.ver - (DIM_EFFECT_POSTEXPLOSION_HEIGHT/2);

        sprEffectPostExplosion.SetColor(Color(255, 255, 255, nAlphaPostEffect));
        sprEffectPostExplosion.SetPosition(CoordWorldPxToScreenPx(vPosPoint));
        oApp.Draw(sprEffectPostExplosion);
    }

    if(bExplosion||1)
    {
        vPosPoint.hrz = pPosition.hrz - (DIM_EFFECT_EXPLOSION_WIDTH/2);
        vPosPoint.ver = pPosition.ver - (DIM_EFFECT_EXPLOSION_HEIGHT/2);

        sprEffectExplosion.SetColor(Color(255, 255, 255, nAlphaExplosion));
        sprEffectExplosion.SetPosition(CoordWorldPxToScreenPx(vPosPoint));
        oApp.Draw(sprEffectExplosion);
    }
}



void Vfx::BlitBlood(struct worldpospx pPosition, int nType)
{
    struct worldpospx vPosPoint;
    Sprite sprBloodFile;
    int nHeight, nWidth;

    switch(nType)
    {
    case 0:
        sprBloodFile = sprEffectBlood1;
        nWidth = DIM_EFFECT_BLOOD_1_WIDTH;
        nHeight = DIM_EFFECT_BLOOD_1_HEIGHT;
        break;
    case 1:
        sprBloodFile = sprEffectBlood2;
        nWidth = DIM_EFFECT_BLOOD_2_WIDTH;
        nHeight = DIM_EFFECT_BLOOD_2_HEIGHT;
        break;
    }

    vPosPoint.hrz = pPosition.hrz - (nWidth/2);
    vPosPoint.ver = pPosition.ver - (nHeight/2);

    sprBloodFile.SetPosition(CoordWorldPxToScreenPx(vPosPoint));
    oApp.Draw(sprBloodFile);
}





