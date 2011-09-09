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

extern struct GifTemplate* giftplTest;

extern sf::RenderWindow oApp;
extern sf::Clock clkDateGame;


void LoadAllGifs()
{
    giftplTest = LoadGif("test");




}

void UnloadAllGifs()
{
    delete giftplTest;

}




struct GifTemplate* LoadGif(std::string sName)
{
    struct GifTemplate* giftplReturn = new struct GifTemplate;

    std::ifstream stConfigFile(("data/gif/"+sName+".cfg").c_str());

    std::string sExtension = "";
    int nFrames;
    float fFrameTime=1.0;//Valeur par défaut


    stConfigFile>>sExtension;
      std::cout<<"Extension:"<<sExtension<<std::endl;

    stConfigFile>>giftplReturn->boucler;
      std::cout<<"Boucler:"<<giftplReturn->boucler<<std::endl;

    stConfigFile>>nFrames;
      std::cout<<"Frames:"<<nFrames<<std::endl;
/*
    int n;
    for(n=0 ; n<nFrames ; n++)
    {
        struct GifFrame temp;
        giftplReturn.frames.push_back(temp);

        std::ostringstream oss;
        oss<<"data/gif/"<<sName<<n<<"."<<sExtension;

        std::cout<<"Loading "<<oss.str()<<" in row n°"<<n<<std::endl;

        giftplReturn.frames[n].img.LoadFromFile(oss.str());//"data/gif/"+sName+n+"."+sExtension
        giftplReturn.frames[n].spr.SetImage(giftplReturn.frames[n].img);
        giftplReturn.frames[n].spr.SetCenter(giftplReturn.frames[n].spr.GetSize().x, giftplReturn.frames[n].spr.GetSize().y);

        stConfigFile>>fFrameTime;
        giftplReturn.frames[n].time = fFrameTime;
        fFrameTime=1.0;//Valeur par défaut

    }*/
    int n;
    for(n=0 ; n<nFrames ; n++)
    {
        struct GifFrame temp;
        giftplReturn->frames.push_back(temp);

        std::ostringstream oss;
        oss<<"data/gif/"<<sName<<n<<"."<<sExtension;

        std::cout<<"Loading "<<oss.str()<<" in row n°"<<n<<std::endl;

        giftplReturn->frames[n].img.LoadFromFile(oss.str());//"data/gif/"+sName+n+"."+sExtension

        stConfigFile>>fFrameTime;
        giftplReturn->frames[n].time = fFrameTime;
        fFrameTime=1.0;//Valeur par défaut

    }
    for(n=0 ; n<nFrames ; n++)
    {
        std::ostringstream oss;
        oss<<"data/gif/"<<sName<<n<<"."<<sExtension;

        giftplReturn->frames[n].spr.SetImage(giftplReturn->frames[n].img);
        giftplReturn->frames[n].spr.SetCenter(giftplReturn->frames[n].spr.GetSize().x, giftplReturn->frames[n].spr.GetSize().y);
    }



    stConfigFile.close();


    return giftplReturn;
}





Gif::Gif(struct GifTemplate *Template, sf::Vector2<float>::Vector2<float> pPosition, bool bAddToHandler)
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

}

Gif::Gif(struct GifTemplate *Template, sf::Vector2<float>::Vector2<float> pPosition, float fFacing, bool bAddToHandler)
{
    Gif::Gif(Template, pPosition, bAddToHandler);
    Gif::m_fFacing = fFacing;
}




bool Gif::Draw() const
{

    sf::Sprite* sprFrame = Gif::GetCurrentFrameSprite();

    //Si aucune date n'a été trouvée (la durée du gif est dépassée et il n'y a rien à afficher)
    if(sprFrame == 0)
    {
        return false;
    }
    else//Si une frame a été trouvée, on l'affiche
    {

        //Déplacement du sprite à l'endroit voulu
        sprFrame->SetPosition(Gif::m_pPosition);

        //Rotation du Sprite
        float fRotation = Gif::m_fFacing-sprFrame->GetRotation();
        sprFrame->Rotate(fRotation);


        //Draw de la frame !
        oApp.Draw(*sprFrame);
        return true;
    }




    return false;
}


sf::Sprite *Gif::GetCurrentFrameSprite() const
{

    //Calcul de la frame à afficher
    float fDate = clkDateGame.GetElapsedTime();
    int nFrames = Gif::m_Template->frames.size();

    float fRelativeDate;

    //Si le gif s'affiche en boucle
    if(Gif::m_Template->boucler)
    {
        //                 Date depuis le début du gif   %   la duree du gif (date relative de la derniere frame)
        //fRelativeDate = (fDate - Gif::m_fDateFirstFrame) % Gif::m_fRelativesDates[Gif::m_fRelativesDates.size()-1];

        fRelativeDate = (fDate - Gif::m_fDateFirstFrame);
        float fGifTime = Gif::m_fRelativesDates[Gif::m_fRelativesDates.size()-1];
        while(fRelativeDate >= fGifTime)
        {
            fRelativeDate-=fGifTime;
        }
    }
    else
    {
        fRelativeDate = (fDate - Gif::m_fDateFirstFrame);
    }

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

    if(nIDFrame == -1)
        return 0;

    return &Gif::m_Template->frames[nIDFrame].spr;
}


void Gif::SetPosition(sf::Vector2<float>::Vector2<float> pNewPosition)
{
    Gif::m_pPosition.x = pNewPosition.x;
    Gif::m_pPosition.y = pNewPosition.y;
}

void Gif::SetFacing(float fNewFacing)
{
    Gif::m_fFacing = fNewFacing;
}

sf::Vector2<float>::Vector2<float> Gif::GetPosition()const
{
    return Gif::m_pPosition;
}

float Gif::GetFacing()const
{
    return Gif::m_fFacing;
}





