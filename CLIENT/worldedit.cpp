#include <iostream>
#include <cstdlib>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "main.h"
#include "convert.h"
#include "world.h"
#include "guifunc.h"

extern int nWorld[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];
extern int nWorldSpe[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];

using namespace sf;

extern RenderWindow oApp;
/*==*/ //Eléments de World
/*==*/ extern Image oWorldNotSet;
/*==*/    extern Sprite sprWorldNotSet;
/*==*/ extern Image oWorldFloorRock;
/*==*/    extern Sprite sprWorldFloorRock;
/*==*/ extern Image oWorldCrateA;
/*==*/    extern Sprite sprWorldCrateA;
/*==*/ extern Image oWorldGap;
/*==*/    extern Sprite sprWorldGap;

/*==*/ extern Image oWorldDelete;
/*==*/    extern Sprite sprWorldDelete;
/*==*/ extern Image oWorldFlagRed;
/*==*/    extern Sprite sprWorldFlagRed;
/*==*/ extern Image oWorldFlagGreen;
/*==*/    extern Sprite sprWorldFlagGreen;
/*==*/ extern Image oWorldFlagBlue;
/*==*/    extern Sprite sprWorldFlagBlue;
/*==*/ extern Image oWorldSpawnRed;
/*==*/    extern Sprite sprWorldSpawnRed;
/*==*/ extern Image oWorldSpawnGreen;
/*==*/    extern Sprite sprWorldSpawnGreen;
/*==*/ extern Image oWorldSpawnBlue;
/*==*/    extern Sprite sprWorldSpawnBlue;


void LoadEmptyMap()
{
    int i, j;
    for(i=0 ; i<WORLD_WIDTH_CUBE ; i++)
    {
        for(j=0 ; j<WORLD_HEIGHT_CUBE ; j++)
        {
            nWorld[j][i]=0;
            nWorldSpe[j][i]=0;
        }
    }
}

int ChangeCubeType(int nCubeType)
{
    int nReturn=0;
    switch(nCubeType)
    {
        case WORLD_CUBE_FLOOR_ROCK:
            nReturn = WORLD_CUBE_CRATE_A;
            break;
        case WORLD_CUBE_CRATE_A:
            nReturn = WORLD_CUBE_GAP;
            break;
        case WORLD_CUBE_GAP:
            nReturn = WORLD_CUBE_FLOOR_ROCK;
            break;
    }
    return nReturn;
}
int ChangeSpecialType(int nSpecialType)
{
    int nReturn=0;
    switch(nSpecialType)
    {
        case WORLD_SPEC_NA:
            nReturn = WORLD_SPEC_FLAG_RED;
            break;
        case WORLD_SPEC_FLAG_RED:
            nReturn = WORLD_SPEC_FLAG_GREEN;
            break;
        case WORLD_SPEC_FLAG_GREEN:
            nReturn = WORLD_SPEC_FLAG_BLUE;
            break;
        case WORLD_SPEC_FLAG_BLUE:
            nReturn = WORLD_SPEC_SPAWN_RED;
            break;
        case WORLD_SPEC_SPAWN_RED:
            nReturn = WORLD_SPEC_SPAWN_GREEN;
            break;
        case WORLD_SPEC_SPAWN_GREEN:
            nReturn = WORLD_SPEC_SPAWN_BLUE;
            break;
        case WORLD_SPEC_SPAWN_BLUE:
            nReturn = WORLD_SPEC_NA;
            break;
    }
    return nReturn;
}



void PlotType(int nPlotingType, int nCubeType, int nSpecialType, struct worldposblock pPosBlock)
{
    if(nPlotingType==0)
    {
        nWorld[pPosBlock.ver][pPosBlock.hrz] = nCubeType;
    }
    else
    {
        nWorldSpe[pPosBlock.ver][pPosBlock.hrz] = nSpecialType;
    }

}


void DisplayType(int nPlotingType, int nCubeType, int nSpecialType)
{
    Sprite *sprSprite;

    if(nPlotingType==0)
    {
        switch(nCubeType)
        {
            case WORLD_CUBE_NOTSET:
                sprSprite=&sprWorldNotSet;
                break;
            case WORLD_CUBE_FLOOR_ROCK:
                sprSprite=&sprWorldFloorRock;
                break;
            case WORLD_CUBE_CRATE_A:
                sprSprite=&sprWorldCrateA;
                break;
            case WORLD_CUBE_GAP:
                sprSprite=&sprWorldGap;
                break;
        }
    }
    else
    {
        switch(nSpecialType)
        {
            case WORLD_SPEC_NA:
                sprSprite=&sprWorldDelete;break;
            case WORLD_SPEC_FLAG_RED:
                sprSprite=&sprWorldFlagRed;break;
            case WORLD_SPEC_FLAG_GREEN:
                sprSprite=&sprWorldFlagGreen;break;
            case WORLD_SPEC_FLAG_BLUE:
                sprSprite=&sprWorldFlagBlue;break;
            case WORLD_SPEC_SPAWN_RED:
                sprSprite=&sprWorldSpawnRed;break;
            case WORLD_SPEC_SPAWN_GREEN:
                sprSprite=&sprWorldSpawnGreen;break;
            case WORLD_SPEC_SPAWN_BLUE:
                sprSprite=&sprWorldSpawnBlue;break;
        }
    }
    sprSprite->SetPosition(Vector2f(10, 840));
    oApp.Draw(*sprSprite);
}

void SaveMap(std::string sMapName)
{
    std::string sPath("map/");
    std::string sExtension(".map");

    std::ofstream stMap((sPath+sMapName+sExtension).c_str());

    if(stMap)
    {
        int i, j;
        for(i=0 ; i<WORLD_HEIGHT_CUBE ; i++)
        {
            for(j=0 ; j<WORLD_WIDTH_CUBE ; j++)
            {
                stMap<<nWorld[i][j]<<" "<<nWorldSpe[i][j]<<" ";
            }
        stMap<<"\n";
        }
    }
    else
    {
        std::cout<<"Erreur SaveMap : Probleme a l'ouverture/creation du fichier"<<std::endl;
    }
}





void WorldEdit()
{
    std::string sMapName;

    bool bChoosen=false;
    do
    {
        switch(QuestionBox("Voulez vous ouvrir une map\nou en creer une nouvelle?", true, "Nouvelle", true, "Ouvrir"))
        {
            case -1:return;break;
            case 0://Ouvrir
                sMapName = InputBox("Quelle map charger?", true);
                if(sMapName=="-1")break;

                while(!LoadMap(sMapName))
                {
                    sMapName = InputBox("Echec du chargement\nQuelle map charger?", true);
                    if(sMapName=="-1")break;
                }
                bChoosen=true;
                break;
            case 1://Nouvelle
                LoadEmptyMap();
                bChoosen=true;
                break;
        }
    }while(!bChoosen);

    Event eEvent;
    Vector2<float>::Vector2<float> vPosMouse;

    //0->Cubes, 1->Special
    int nPlotingType = 0;
    int nCubeType=WORLD_CUBE_FLOOR_ROCK;
    int nSpecialType=WORLD_SPEC_FLAG_RED;

    while(oApp.IsOpened())
    {
        //Gestion des evènements
        while(oApp.GetEvent(eEvent))
        {

            switch(eEvent.Type)
            {
                case Event::MouseMoved:
                    vPosMouse = Vector2f(eEvent.MouseMove.X, eEvent.MouseMove.Y);
                    break;

                case Event::MouseButtonPressed:
                    if(eEvent.MouseButton.Button == Mouse::Right)
                    {
                        if(nPlotingType==1)
                        {
                            nSpecialType = ChangeSpecialType(nSpecialType);
                        }
                        else
                        {
                            nCubeType = ChangeCubeType(nCubeType);
                        }

                    }
                    break;

                case Event::KeyPressed:
                    switch(eEvent.Key.Code)
                    {
                        case Key::Escape:
                            if(QuestionBox("Attention !\nVous allez quitter l'editeur\nsans sauvegarder la\nmap en cours", true, "Quitter", true, "Annuler")==1)
                                return;
                            break;

                        case Key::Tab:
                            if(nPlotingType==0)
                                nPlotingType=1;
                            else
                                nPlotingType=0;
                            break;

                        case Key::Return:
                            sMapName = InputBox("Quel nom donner à la map?");
                            if(sMapName!="" && sMapName!="-1")
                            {
                                std::cout<<"MapName="<<sMapName.c_str()<<std::endl;
                                SaveMap(sMapName);
                                return;
                            }
                            break;
                        default:
                            break;
                    }
                    break;


                case Event::Closed:
                    oApp.Close();
                    return;
                    break;

                default:
                    break;
            }
        }

        const Input &input = oApp.GetInput();

        if(input.IsMouseButtonDown(Mouse::Left))
        {
            Vector2<float>::Vector2<float> vPosAff;
                vPosAff.x=input.GetMouseX();
                vPosAff.y=input.GetMouseY();
            if(GetIsCoordScreenPxInWorld(vPosAff))
                PlotType(nPlotingType, nCubeType, nSpecialType, CoordScreenPxToWorldBlocks(vPosAff));
        }

        //Nettoyage de l'écran
        oApp.Clear();

        //Draw du world & Screen
        DrawScreen();
        DrawWorld();
        DisplayType(nPlotingType, nCubeType, nSpecialType);

        //Draw du curseur
        DrawCursor(vPosMouse);

        //Affichage
        oApp.Display();
    }



    return;

}













