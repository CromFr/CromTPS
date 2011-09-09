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
#include "serverlist.h"
#include "Gif.h"


#include "version.h"

//
//                ||||||||||||
//                |  \    /  |
//        ╭-╮    ||  O    O  ||    ╭-╮
//        | |     |    ||    |     | |
//        | |     \   ____   /     | |
//     _╭-| |-╮_   \________/   _╭-| |-╮_
//    | | | | | |     |   |    | | | | | |
//     \        |              |        /
//      \      /                \      /
//
// ...fuck you i'm the best !




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

//=======================================
struct GifTemplate* giftplTest=0;
struct GifTemplate* giftplExplosion=0;

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

void Game();

int SCREEN_WIDTH=1200;//1200;//800;
int SCREEN_HEIGHT=900;//900;//600;
RenderWindow oApp(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "CROMGame", Style::Titlebar | Style::Close | Style::Resize);


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
    LoadAllGifs();

    //Chargement des sons
    InitSound();

    //Police
    GameFont.LoadFromFile("data/font/mk5style.ttf");

    oApp.ShowMouseCursor(false);


    std::cout<<"Complete !"<<std::endl;
    //==================================================================


    GifHandler::GifHandler oGifHandler;// TODO (crom#1#): a suppr
    oGifHandler.AddGif(giftplTest, Vector2f(300, 300));
    oGifHandler.AddGif(giftplExplosion, Vector2f(600, 300));


    ButtonHandler::ButtonHandler Buttons;
    Buttons.AddButtonPercent(50, 30, "Jouer", 1);
    Buttons.AddButtonPercent(50, 50, "Editeur", 2);
    Buttons.AddButtonPercent(50, 70, "Liste Servers", 3);

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
            ServerList();
        }

        //Nettoyage de l'écran
        oApp.Clear();

        //Draw du Screen
        DrawScreen(1);

        Buttons.DrawButtons();

        //Draw du curseur
        DrawCursor(vPosMouse);


        //Draw des Gifs
        oGifHandler.Draw();



        //Affichage
        oApp.Display();
    }


    UnloadAllGifs();
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
    Item::Item* pItem = pInventaire->AddItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_LASER_RIFLE));
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

        bool bZ = input.IsKeyDown(Key::Z);
        bool bD = input.IsKeyDown(Key::D);
        bool bS = input.IsKeyDown(Key::S);
        bool bQ = input.IsKeyDown(Key::Q);

        float fMod = 1;
        if((bZ&&bD)
           || (bD&&bS)
           || (bS&&bQ)
           || (bQ&&bZ))
           fMod=0.707;//(racine de 2/2)

        if(bZ)
        {
            oPC.MoveToDirection(DIRECTION_NORTH, fMod);
        }
        if(bD)
        {
            oPC.MoveToDirection(DIRECTION_EAST, fMod);
        }
        if(bS)
        {
            oPC.MoveToDirection(DIRECTION_SOUTH, fMod);
        }
        if(bQ)
        {
            oPC.MoveToDirection(DIRECTION_WEST, fMod);
        }
        if(!(bZ||bQ||bS||bD))
            oPC.MoveToDirection(0);

        oPC.DecreaseSpeed();


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


