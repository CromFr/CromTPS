#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include "main.h"
#include "convert.h"

#include "Gif.h"


extern sf::RenderWindow oApp;
extern sf::Clock clkDateGame;


extern struct GifTemplate* giftplTest;
extern struct GifTemplate* giftplExplosion;

void LoadAllGifs()
{
    giftplTest = LoadGif("test");
    giftplExplosion = LoadGif("explosion");




}
void UnloadAllGifs()
{
    delete giftplTest;
    delete giftplExplosion;

}




struct GifTemplate* LoadGif(std::string sName)
{
    struct GifTemplate* giftplReturn = new struct GifTemplate;

    std::ifstream stConfigFile(("data/gif/"+sName+".cfg").c_str());

    std::string sExtension = "";
    int nFrames;
    float fFrameTime=1.0;//Valeur par défaut


    stConfigFile>>sExtension;
      //std::cout<<"Ext:"<<sExtension;

    stConfigFile>>giftplReturn->boucler;
      //std::cout<<" | loop:"<<giftplReturn->boucler;

    stConfigFile>>giftplReturn->smooth;

    stConfigFile>>nFrames;
      //std::cout<<"| frames:"<<nFrames<<std::endl;


    int n;
    for(n=0 ; n<nFrames ; n++)
    {
        struct GifFrame temp;
        giftplReturn->frames.push_back(temp);

        std::ostringstream oss;
        oss<<"data/gif/"<<sName<<n<<"."<<sExtension;

        //std::cout<<"Loading "<<oss.str()<<" in row n°"<<n<<std::endl;

        giftplReturn->frames[n].img.LoadFromFile(oss.str());

        stConfigFile>>fFrameTime;
        giftplReturn->frames[n].time = fFrameTime;
        fFrameTime=1.0;//Valeur par défaut

    }
    for(n=0 ; n<nFrames ; n++)
    {
        std::ostringstream oss;
        oss<<"data/gif/"<<sName<<n<<"."<<sExtension;

        giftplReturn->frames[n].spr.SetImage(giftplReturn->frames[n].img);
        giftplReturn->frames[n].spr.SetCenter(giftplReturn->frames[n].spr.GetSize().x/2, giftplReturn->frames[n].spr.GetSize().y/2);
    }


    stConfigFile.close();


    return giftplReturn;
}


//=================================================================================================================================================
//=================================================================================================================================================


Gif::Gif(struct GifTemplate *Template, sf::Vector2<float>::Vector2<float> pPosition, float fFacing)
{
    Gif::m_Template = Template;

    int n;
    int nFrames = Template->frames.size();

    //Pour la frame 0 : date de fin = sa durée
    Gif::m_fRelativesDates.push_back(Template->frames[0].time);

    //Pour les frames suivantes :
    for(n=1 ; n<nFrames ; n++)
    {
        //                                  date de fin de la frame précédente +        sa duree
        Gif::m_fRelativesDates.push_back(      Gif::m_fRelativesDates[n-1]     + Template->frames[n].time);
    }

    Gif::m_fDateFirstFrame = clkDateGame.GetElapsedTime();

    Gif::m_pPosition.x = pPosition.x;
    Gif::m_pPosition.y = pPosition.y;

    Gif::m_fFacing = fFacing;

    Gif::m_bActive=true;

}
//=================================================================================================================================================
bool Gif::Draw()
{
    if(Gif::m_bActive)
    {
        int nID;
        sf::Sprite* sprFrame = Gif::GetCurrentFrameSprite(&nID);

        //Si aucune date n'a été trouvée (la durée du gif est dépassée et il n'y a rien à afficher)
        if(sprFrame == 0)
        {
            Gif::m_bActive=false;
            return false;
        }
        else//Si une frame a été trouvée, on l'affiche
        {
            if(!Gif::m_Template->smooth)
            {
                //Déplacement du sprite à l'endroit voulu
                sprFrame->SetPosition(Gif::m_pPosition);

                //Rotation du Sprite
                float fRotation = Gif::m_fFacing-sprFrame->GetRotation();
                if(fRotation!=0.0)
                    sprFrame->Rotate(fRotation);

                //Draw de la frame !
                oApp.Draw(*sprFrame);
            }
            else
            {
                sf::Sprite* sprFrame2 = Gif::GetNextFrameSprite(nID);

                //Déplacement du sprite à l'endroit voulu
                sprFrame->SetPosition(Gif::m_pPosition);
                if(sprFrame2!=0)
                    sprFrame2->SetPosition(Gif::m_pPosition);

                //Rotation du Sprite
                float fRotation = Gif::m_fFacing-sprFrame->GetRotation();
                if(fRotation!=0.0)
                    sprFrame->Rotate(fRotation);

                if(sprFrame2!=0)
                {
                    fRotation = Gif::m_fFacing-sprFrame2->GetRotation();
                    if(fRotation!=0.0)
                        sprFrame2->Rotate(fRotation);
                }

                Gif::SmoothFrames(sprFrame, sprFrame2, nID);

                oApp.Draw(*sprFrame);
                if(sprFrame2!=0)
                    oApp.Draw(*sprFrame2);


            }

            return true;
        }
    }



    return false;
}
//=================================================================================================================================================
sf::Sprite *Gif::GetCurrentFrameSprite(int* nSetID) const
{

    int nIDFrame = GetCurrentFrameID();

    if(nSetID!=0)
        *nSetID = nIDFrame;


    if(nIDFrame == -1)
        return 0;

    //Suppression de toute transparence
    Gif::m_Template->frames[nIDFrame].spr.SetColor(sf::Color(255, 255, 255, 255));

    return &Gif::m_Template->frames[nIDFrame].spr;
}





//=================================================================================================================================================
void Gif::SetPosition(sf::Vector2<float>::Vector2<float> pNewPosition)
{
    Gif::m_pPosition.x = pNewPosition.x;
    Gif::m_pPosition.y = pNewPosition.y;
}

void Gif::SetFacing(float fNewFacing)
{
    Gif::m_fFacing = fNewFacing;
}
//=================================================================================================================================================
sf::Vector2<float>::Vector2<float> Gif::GetPosition()const
{
    return Gif::m_pPosition;
}
//=================================================================================================================================================
float Gif::GetFacing()const
{
    return Gif::m_fFacing;
}
//=================================================================================================================================================
bool Gif::GetIsActive()const
{
    return Gif::m_bActive;
}




//=================================================================================================================================================
float Gif::GetRelativeDate()const
{
    float fDate = clkDateGame.GetElapsedTime();

    float fRelativeDate;

    //Si le gif s'affiche en boucle
    if(Gif::m_Template->boucler)
    {
        //                 Date depuis le début du gif   %   la duree du gif (date relative de la derniere frame)
        //fRelativeDate = (fDate - Gif::m_fDateFirstFrame) % Gif::m_fRelativesDates[Gif::m_fRelativesDates.size()-1];

        fRelativeDate = (fDate - Gif::m_fDateFirstFrame);
        float fGifTime = Gif::m_fRelativesDates[Gif::m_fRelativesDates.size()-1];
        while(fRelativeDate >= fGifTime)
        {//fRelativeDate Modulo fGifTime
            fRelativeDate-=fGifTime;
        }
    }
    else
    {
        fRelativeDate = (fDate - Gif::m_fDateFirstFrame);
    }

    return fRelativeDate;
}
//=================================================================================================================================================
int Gif::GetCurrentFrameID()const
{
    //Calcul de la frame à afficher
    int nFrames = Gif::m_Template->frames.size();

    float fRelativeDate = Gif::GetRelativeDate();

    int n;
    int nIDFrame=-1;
    for(n=0 ; true ; n++)
    {
        if(n == nFrames)//Traitement de l'arrivée en fin de tableau (la durée du gif est dépassée et il n'y a rien à afficher)
            break;

        if(n!=0)
        {
            if(Gif::m_fRelativesDates[n-1]<fRelativeDate && fRelativeDate<Gif::m_fRelativesDates[n])
                nIDFrame = n;
        }
        else
        {
            if(0<fRelativeDate && fRelativeDate<Gif::m_fRelativesDates[n])
                nIDFrame = n;
        }
    }
    return nIDFrame;
}
//=================================================================================================================================================
sf::Sprite *Gif::GetNextFrameSprite(int nCurID)
{
    int nIDFrame;
    if(nCurID!=-1)
        nIDFrame = nCurID;
    else
        nIDFrame = GetCurrentFrameID();

    if(nIDFrame == -1)
        return 0;

    nIDFrame++;
    if(nIDFrame>=Gif::m_Template->frames.size())
    {
        if(Gif::m_Template->boucler)
            nIDFrame=0;
        else
            return 0;
    }

    return &Gif::m_Template->frames[nIDFrame].spr;
}
//=================================================================================================================================================
void Gif::SmoothFrames(sf::Sprite *sprFrame0, sf::Sprite *sprFrame1, int nIDFrame)
{
    float fRelativeDate = Gif::GetRelativeDate();

    //Application de la transparence
    float fPercent = (Gif::m_fRelativesDates[nIDFrame]-fRelativeDate)/(Gif::m_fRelativesDates[nIDFrame]-Gif::m_fRelativesDates[nIDFrame-1]);

    if(sprFrame0!=0)
        sprFrame0->SetColor(sf::Color(255, 255, 255, 255*fPercent));
    if(sprFrame1!=0)
        sprFrame1->SetColor(sf::Color(255, 255, 255, 255*(1-fPercent)));
}



//=================================================================================================================================================
//=================================================================================================================================================
//=================================================================================================================================================
//=================================================================================================================================================


GifHandler::~GifHandler()
{
    GifHandler::Clear();
}

//=================================================================================================================================================
void GifHandler::Draw()
{
        int nSize = GifHandler::m_pGifList.size();

        for(int n(0) ; n<nSize ; n++)
        {
            if(GifHandler::m_pGifList[n]!=0)
            {
                if(!GifHandler::m_pGifList[n]->Draw())
                {
                    delete GifHandler::m_pGifList[n];
                    GifHandler::m_pGifList[n]=0;
                }
            }
        }
}
//=================================================================================================================================================
void GifHandler::AddGif(struct GifTemplate *Template, sf::Vector2<float>::Vector2<float> pPosition, float fFacing)
{
    int nSize = GifHandler::m_pGifList.size();
    int nEmplacement = -1;

    for(int n(0) ; n<nSize ; n++)
    {
        if(GifHandler::m_pGifList[n]==0)
        {
            nEmplacement=n;
            break;
        }
    }

    Gif* pGifToAdd = new Gif(Template, pPosition, fFacing);

    //Si aucune case inactive n'a été trouvée dans le tableau
    if(nEmplacement==-1)
    {
        //On rajoute une ligne
        GifHandler::m_pGifList.push_back(pGifToAdd);
    }
    //Si une case a été trouvée
    else
    {
        GifHandler::m_pGifList[nEmplacement] = pGifToAdd;
    }


}
//=================================================================================================================================================
void GifHandler::Clear()
{
    int nSize = GifHandler::m_pGifList.size();

    for(int n(0) ; n<nSize ; n++)
    {
        delete GifHandler::m_pGifList[n];
        GifHandler::m_pGifList[n]=0;
    }
    while(GifHandler::m_pGifList.size()>0)
    {
        GifHandler::m_pGifList.pop_back();
    }
}
