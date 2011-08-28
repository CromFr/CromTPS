#include <iostream>
#include <cstdlib>

#include <string>
#include <sstream>
#include <cmath>
#include <vector>//Pour les tableaux dynamiques
#include <fstream>//Manips de fichiers
#include <ctime> //temps, random

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "main.h"
#include "guifunc.h"
#include "world.h"
#include "Vfx.h"
#include "convert.h"
#include "worldedit.h"
#include "utils.h"
#include "Player.h"
#include "sound.h"
#include "store.h"
#include "Buttons.h"
#include "Inventory.h"


#include "version.h"





int nWorld[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE] = {{0}};
int nWorldSpe[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE] = {{0}};



using namespace sf;

//===================================================================================================================
//Images ============================================================================================================
Image oCursor;
    Sprite sprCursor;

Image oWelcomeScreen;
    Sprite sprWelcomeScreen;
Image oGameScreen;
    Sprite sprGameScreen;
Image oInputBox;
    Sprite sprInputBox;
Image oQuestionBox;
    Sprite sprQuestionBox;
Image oButton0Inactive;
    Sprite sprButton0Inactive;
Image oButton0Active;
    Sprite sprButton0Active;
Image oButton0Pressed;
    Sprite sprButton0Pressed;

//Images d'Armes
Image oWeaponBulletPistol;
    Sprite sprWeaponBulletPistol;
Image oWeaponBulletRifle;
    Sprite sprWeaponBulletRifle;
Image oWeaponBulletMinigun;
    Sprite sprWeaponBulletMinigun;
Image oWeaponLaserPistol;
    Sprite sprWeaponLaserPistol;
Image oWeaponLaserRifle;
    Sprite sprWeaponLaserRifle;
Image oWeaponLaserMinigun;
    Sprite sprWeaponLaserMinigun;
Image oWeaponGaussPistol;
    Sprite sprWeaponGaussPistol;
Image oWeaponGaussRifle;
    Sprite sprWeaponGaussRifle;
Image oWeaponGaussMinigun;
    Sprite sprWeaponGaussMinigun;
Image oWeaponGaussDestructeur;
    Sprite sprWeaponGaussDestructeur;

//Elements du world
Image oWorldNotSet;
    Sprite sprWorldNotSet;
Image oWorldFloorRock;
    Sprite sprWorldFloorRock;
Image oWorldCrateA;
    Sprite sprWorldCrateA;
Image oWorldGap;
    Sprite sprWorldGap;
Image oWorldDelete;
    Sprite sprWorldDelete;
Image oWorldFlagRed;
    Sprite sprWorldFlagRed;
Image oWorldFlagGreen;
    Sprite sprWorldFlagGreen;
Image oWorldFlagBlue;
    Sprite sprWorldFlagBlue;
Image oWorldSpawnRed;
    Sprite sprWorldSpawnRed;
Image oWorldSpawnGreen;
    Sprite sprWorldSpawnGreen;
Image oWorldSpawnBlue;
    Sprite sprWorldSpawnBlue;

Image imgPlayer;
    Sprite sprPlayerSkinDefault;
    Sprite sprPlayerRed;
    Sprite sprPlayerGreen;
    Sprite sprPlayerBlue;

Image oEffectRayBullet;
    Sprite sprEffectRayBullet;
Image oEffectRayBulletImpact;
    Sprite sprEffectRayBulletImpact;
Image oEffectRayLaser;
    Sprite sprEffectRayLaser;
Image oEffectRayLaserImpact;
    Sprite sprEffectRayLaserImpact;
Image oEffectRayGauss;
    Sprite sprEffectRayGauss;
Image oEffectRayGaussImpact;
    Sprite sprEffectRayGaussImpact;
Image oEffectExplosion;
    Sprite sprEffectExplosion;
Image oEffectPostExplosion;
    Sprite sprEffectPostExplosion;
Image oEffectBlood1;
    Sprite sprEffectBlood1;
Image oEffectBlood2;
    Sprite sprEffectBlood2;

//===================================================================================================================
//Sounds ============================================================================================================
//Bullet
SoundBuffer bufBulletPistol;
    Sound sndBulletPistol;
SoundBuffer bufBulletRifle;
    Sound sndBulletRifle;
SoundBuffer bufBulletMinigun;
    Sound sndBulletMinigun;
//Laser
SoundBuffer bufLaserPistol;
    Sound sndLaserPistol;
SoundBuffer bufLaserRifle;
    Sound sndLaserRifle;
SoundBuffer bufLaserMinigun;
    Sound sndLaserMinigun;
//Gauss
SoundBuffer bufGaussPistol;
    Sound sndGaussPistol;
SoundBuffer bufGaussRifle;
    Sound sndGaussRifle;
SoundBuffer bufGaussMinigun;
    Sound sndGaussMinigun;
SoundBuffer bufGaussDestructeur;
    Sound sndGaussDestructeur;
//===================================================================================================================
//===================================================================================================================
//Temps
Clock clkDateGame;
//===================================================================================================================
//===================================================================================================================
Vfx::Vfx oVfx;
//===================================================================================================================
//===================================================================================================================
Font GameFont;
//===================================================================================================================
//===================================================================================================================
RenderWindow oApp(VideoMode(1200, 900, 32), "CROMGame", Style::Titlebar | Style::Close);




void Game();



int main()
{
    std::cout<<"CROMGame version : "<<RC_FILEVERSION_STRING<<std::endl;


    //Chargement des images ===========================================
    std::cout<<"Loading...";

    //oApp.SetFramerateLimit(60);
    oApp.UseVerticalSync(true);

    Clock clkDateFrame;
    clkDateGame.Reset();

    //Init du random
    srand(time(NULL));

    //Chargement des images
    InitImagesAndSprites();

    //Chargement des sons
    InitSound();

    //Police
    GameFont.LoadFromFile("data/font/mk5style.ttf");


    std::cout<<"Complete !"<<std::endl;
    //==================================================================


    ButtonHandler::ButtonHandler Buttons;
    Buttons.AddButton(DIM_WINDOW_WIDTH/2, 400, "Jouer", 1);
    Buttons.AddButton(DIM_WINDOW_WIDTH/2, 500, "Editeur", 2);
    Buttons.AddButton(DIM_WINDOW_WIDTH/2, 600, "TestStore", 3);

    int nButtonPressed=0;

    Event eEvent;
    Vector2<float>::Vector2<float> vPosMouse;

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

                case Event::KeyPressed:
                    switch(eEvent.Key.Code)
                    {
                        case Key::Escape:
                            return 0;
                            break;
                        default:
                            break;
                    }
                    break;

                case Event::Closed:
                    oApp.Close();
                    return 0;
                    break;

                default:
                    break;
            }

            nButtonPressed = Buttons.OnEvent(eEvent);
        }

        if(nButtonPressed == 1)
        {//Jouer
            while(oApp.GetEvent(eEvent))
            {

            }
            Game();
        }
        if(nButtonPressed == 2)
        {//Editeur
            while(oApp.GetEvent(eEvent))
            {

            }
        WorldEdit();
        }
        if(nButtonPressed == 3)//Tests
        {//Editeur
            while(oApp.GetEvent(eEvent))
            {

            }
            //Store(&oPC);
        }

        //Nettoyage de l'écran
        oApp.Clear();

        //Draw du Screen
        DrawScreen(1);

        Buttons.DrawButtons();

        //Draw du curseur
        DrawCursor(vPosMouse);

        //Affichage
        oApp.Display();
    }
    return 0;









}













void Game()
{


    //int nFrames=0;
    //float fMoyenne=0;

    //WorldEdit();
    //Store();

    std::string sMapName;
    sMapName = InputBox("Quelle map charger?");
    while(!LoadMap(sMapName))
    {
        sMapName = InputBox("Echec du chargement\nQuelle map charger?");
    }


    struct worldposblock Position;Position.ver=1; Position.hrz=1;
    PC::PC oPC(1);

    Inventory::Inventory* pInventaire = oPC.GetInventory();
    Item::Item* pItem = pInventaire->AddItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_GAUSS_DESTRUCTEUR));
    pInventaire->EquipItem(pItem);

    pInventaire->AddItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_GAUSS_DESTRUCTEUR));
    pInventaire->AddItem(MakeItemTemplate(ITEM_TYPE_ARMOR, ARMOR_TYPE_BULLETS));
    pInventaire->AddItem(MakeItemTemplate(ITEM_TYPE_POTION, POTION_TYPE_MED));
    pInventaire->AddItem(MakeItemTemplate(ITEM_TYPE_POTION, POTION_TYPE_MED));
    pInventaire->AddItem(MakeItemTemplate(ITEM_TYPE_POTION, POTION_TYPE_MED));
    pInventaire->AddItem(MakeItemTemplate(ITEM_TYPE_POTION, POTION_TYPE_MED));
    pInventaire->AddItem(MakeItemTemplate(ITEM_TYPE_POTION, POTION_TYPE_MED));
    pInventaire->AddItem(MakeItemTemplate(ITEM_TYPE_POTION, POTION_TYPE_MED));
    pInventaire->AddItem(MakeItemTemplate(ITEM_TYPE_POTION, POTION_TYPE_MED));





    Event eEvent;
    Vector2<float>::Vector2<float> vPosMouse;

    struct worldpospx pPosPC, pPosMouse;
    float fDeltaVer, fDeltaHrz, fFacing;

    while(oApp.IsOpened())
    {
        //clkDateFrame.Reset();

        //Gestion des evènements
        while(oApp.GetEvent(eEvent))
        {

            switch(eEvent.Type)
            {
                case Event::MouseMoved:
                    vPosMouse = Vector2f(eEvent.MouseMove.X, eEvent.MouseMove.Y);
                    break;

                case Event::MouseButtonPressed:
                    if(eEvent.MouseButton.Button == Mouse::Left)
                    {
                        Vector2<float>::Vector2<float> vPosAff;
                            vPosAff.x=eEvent.MouseButton.X;
                            vPosAff.y=eEvent.MouseButton.Y;

                        oPC.FireAtPosition(CoordScreenPxToWorldPx(vPosAff));
                    }
                    break;

                case Event::KeyPressed:
                    switch(eEvent.Key.Code)
                    {
                        case Key::Escape:
                            oApp.Close();
                            return;
                            break;

                        case Key::B:
                            Store(&oPC);
                            break;

                        case Key::I:
                            //oPC.GetInventory()->OpenInventory();
                            break;


                        case Key::X:
                            oPC.TakeDamages(10, 1);
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

        if(input.IsKeyDown(Key::Z))
        {
            oPC.MoveToDirection(DIRECTION_NORTH);
        }
        if(input.IsKeyDown(Key::D))
        {
            oPC.MoveToDirection(DIRECTION_EAST);
        }
        if(input.IsKeyDown(Key::S))
        {
            oPC.MoveToDirection(DIRECTION_SOUTH);
        }
        if(input.IsKeyDown(Key::Q))
        {
            oPC.MoveToDirection(DIRECTION_WEST);
        }


        //Calcul du facing

        pPosMouse = CoordScreenPxToWorldPx(vPosMouse);
        pPosPC = oPC.GetLocation().pos;
        if(pPosPC.hrz != pPosMouse.hrz || pPosPC.ver != pPosMouse.ver)
        {
            fDeltaVer = (pPosMouse.ver - pPosPC.ver);
            fDeltaHrz = (pPosMouse.hrz - pPosPC.hrz);
            if(fDeltaHrz<0)
                fFacing = -atan(fDeltaVer/fDeltaHrz)-PI;
            else
                fFacing = -atan(fDeltaVer/fDeltaHrz);
            oPC.SetFacing(fFacing*(180/PI));
        }


        //Nettoyage de l'écran
        oApp.Clear();

        //Draw du world & Screen
        DrawScreen();
        DrawWorld();

        DrawPlayerInfo(&oPC);

        //Draw du personnage
        DrawPCs(&oPC);

        //Draw des effets spéciaux
        oVfx.Draw();

        //Draw du curseur
        DrawCursor(vPosMouse);

//        String text;
//        nFrames++;
//
//        float fFPS = 1/oApp.GetFrameTime();
//        fMoyenne = (fMoyenne*(nFrames-1)+oApp.GetFrameTime())/nFrames;
//
//        std::ostringstream oss;
//        oss << fFPS << " FPS | MOY="<<1/fMoyenne;
//        text.SetText(oss.str());
//
//        text.SetPosition(Vector2f(25, 850));
//        oApp.Draw(text);


        //Affichage
        oApp.Display();

    }

    return;
}


