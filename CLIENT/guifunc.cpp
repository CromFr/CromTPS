#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>
#include "main.h"
#include "convert.h"
#include "guifunc.h"
#include "Buttons.h"

using namespace sf;

//Application :
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern RenderWindow oApp;

/*====> Liste des images ============*/
/*==*/ //Curseur
/*==*/ extern Image oCursor;
/*==*/    extern Sprite sprCursor;
/*==*/
/*==*/ //Ecrans
/*==*/ extern Image oWelcomeScreen;
/*==*/    extern Sprite sprWelcomeScreen;
/*==*/ extern Image oGameScreen;
/*==*/    extern Sprite sprGameScreen;
/*==*/ extern Image oInputBox;
/*==*/    extern Sprite sprInputBox;
/*==*/ extern Image oQuestionBox;
/*==*/    extern Sprite sprQuestionBox;
/*==*/ extern Image oButton0Inactive;
/*==*/    extern Sprite sprButton0Inactive;
/*==*/ extern Image oButton0Active;
/*==*/    extern Sprite sprButton0Active;
/*==*/ extern Image oButton0Pressed;
/*==*/    extern Sprite sprButton0Pressed;
/*==*/
/*==*/ extern sf::Image oWeaponBulletPistol;
/*==*/    extern sf::Sprite sprWeaponBulletPistol;
/*==*/ extern sf::Image oWeaponBulletRifle;
/*==*/    extern sf::Sprite sprWeaponBulletRifle;
/*==*/ extern sf::Image oWeaponBulletMinigun;
/*==*/    extern sf::Sprite sprWeaponBulletMinigun;
/*==*/ extern sf::Image oWeaponLaserPistol;
/*==*/    extern sf::Sprite sprWeaponLaserPistol;
/*==*/ extern sf::Image oWeaponLaserRifle;
/*==*/    extern sf::Sprite sprWeaponLaserRifle;
/*==*/ extern sf::Image oWeaponLaserMinigun;
/*==*/    extern sf::Sprite sprWeaponLaserMinigun;
/*==*/ extern sf::Image oWeaponGaussPistol;
/*==*/    extern sf::Sprite sprWeaponGaussPistol;
/*==*/ extern sf::Image oWeaponGaussRifle;
/*==*/    extern sf::Sprite sprWeaponGaussRifle;
/*==*/ extern sf::Image oWeaponGaussMinigun;
/*==*/    extern sf::Sprite sprWeaponGaussMinigun;
/*==*/ extern sf::Image oWeaponGaussDestructeur;
/*==*/    extern sf::Sprite sprWeaponGaussDestructeur;
/*==*/
/*==*/ //Eléments de World
/*==*/ extern Image oWorldNotSet;
/*==*/    extern Sprite sprWorldNotSet;
/*==*/ extern Image oWorldFloorRock;
/*==*/    extern Sprite sprWorldFloorRock;
/*==*/ extern Image oWorldCrateA;
/*==*/    extern Sprite sprWorldCrateA;
/*==*/ extern Image oWorldGap;
/*==*/    extern Sprite sprWorldGap;
/*==*/
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
/*==*/
/*==*/ //PCs
/*==*/ extern Image imgPlayer;
/*==*/    extern Sprite sprPlayerSkinDefault;
/*==*/    extern Sprite sprPlayerRed;
/*==*/    extern Sprite sprPlayerGreen;
/*==*/    extern Sprite sprPlayerBlue;
/*==*/
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


extern sf::Clock clkDateGame;

extern sf::Font GameFont;



//monde
extern int nWorld[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];
extern int nWorldSpe[WORLD_HEIGHT_CUBE][WORLD_WIDTH_CUBE];


void InitImagesAndSprites()
{


    //Curseur ================
    oCursor.LoadFromFile("data/img/cur.png");
        sprCursor.SetImage(oCursor);

    //Ecrans ===========
    oWelcomeScreen.LoadFromFile("data/img/welcomescreen.bmp");
        sprWelcomeScreen.SetImage(oWelcomeScreen);
    oGameScreen.LoadFromFile("data/img/gamescreen.bmp");
        sprGameScreen.SetImage(oGameScreen);
    oInputBox.LoadFromFile("data/img/menu/inputbox.bmp");
        sprInputBox.SetImage(oInputBox);
    oQuestionBox.LoadFromFile("data/img/menu/questionbox.bmp");
        sprQuestionBox.SetImage(oQuestionBox);
    oButton0Inactive.LoadFromFile("data/img/menu/button_inactive.jpg");
        sprButton0Inactive.SetImage(oButton0Inactive);
    oButton0Active.LoadFromFile("data/img/menu/button_active.jpg");
        sprButton0Active.SetImage(oButton0Active);
    oButton0Pressed.LoadFromFile("data/img/menu/button_pressed.jpg");
        sprButton0Pressed.SetImage(oButton0Pressed);

    oWeaponBulletPistol.LoadFromFile("data/img/item/bullet_pistol.png");
        sprWeaponBulletPistol.SetImage(oWeaponBulletPistol);
    oWeaponBulletRifle.LoadFromFile("data/img/item/bullet_rifle.png");
        sprWeaponBulletRifle.SetImage(oWeaponBulletRifle);
    oWeaponBulletMinigun.LoadFromFile("data/img/item/bullet_minigun.png");
        sprWeaponBulletMinigun.SetImage(oWeaponBulletMinigun);
    oWeaponLaserPistol.LoadFromFile("data/img/item/laser_pistol.png");
        sprWeaponLaserPistol.SetImage(oWeaponLaserPistol);
    oWeaponLaserRifle.LoadFromFile("data/img/item/laser_rifle.png");
        sprWeaponLaserRifle.SetImage(oWeaponLaserRifle);
    oWeaponLaserMinigun.LoadFromFile("data/img/item/laser_minigun.png");
        sprWeaponLaserMinigun.SetImage(oWeaponLaserMinigun);
    oWeaponGaussPistol.LoadFromFile("data/img/item/gauss_pistol.png");
        sprWeaponGaussPistol.SetImage(oWeaponGaussPistol);
    oWeaponGaussRifle.LoadFromFile("data/img/item/gauss_rifle.png");
        sprWeaponGaussRifle.SetImage(oWeaponGaussRifle);
    oWeaponGaussMinigun.LoadFromFile("data/img/item/gauss_minigun.png");
        sprWeaponGaussMinigun.SetImage(oWeaponGaussMinigun);
    oWeaponGaussDestructeur.LoadFromFile("data/img/item/gauss_destructeur.png");
        sprWeaponGaussDestructeur.SetImage(oWeaponGaussDestructeur);

    //World ==================
    //Special
    oWorldNotSet.LoadFromFile("data/img/world_notset.bmp");
        sprWorldNotSet.SetImage(oWorldNotSet);
    //Floors
    oWorldFloorRock.LoadFromFile("data/img/world_floor_rock.bmp");
        sprWorldFloorRock.SetImage(oWorldFloorRock);
    //Crates
    oWorldCrateA.LoadFromFile("data/img/world_crate_a.bmp");
        sprWorldCrateA.SetImage(oWorldCrateA);
    //Gap
    oWorldGap.LoadFromFile("data/img/world_gap.bmp");
        sprWorldGap.SetImage(oWorldGap);

    oWorldDelete.LoadFromFile("data/img/delete.png");
        sprWorldDelete.SetImage(oWorldDelete);
    oWorldFlagRed.LoadFromFile("data/img/redflag.png");
        sprWorldFlagRed.SetImage(oWorldFlagRed);
    oWorldFlagGreen.LoadFromFile("data/img/greenflag.png");
        sprWorldFlagGreen.SetImage(oWorldFlagGreen);
    oWorldFlagBlue.LoadFromFile("data/img/blueflag.png");
        sprWorldFlagBlue.SetImage(oWorldFlagBlue);
    oWorldSpawnRed.LoadFromFile("data/img/redspawn.png");
        sprWorldSpawnRed.SetImage(oWorldSpawnRed);
    oWorldSpawnGreen.LoadFromFile("data/img/greenspawn.png");
        sprWorldSpawnGreen.SetImage(oWorldSpawnGreen);
    oWorldSpawnBlue.LoadFromFile("data/img/bluespawn.png");
        sprWorldSpawnBlue.SetImage(oWorldSpawnBlue);

    //PCs =============
    imgPlayer.LoadFromFile("data/img/player.png");
        sprPlayerSkinDefault.SetImage(imgPlayer);
        sprPlayerSkinDefault.SetCenter(25, 25);
    /*
        sprPCRed.SetImage(oPC);
        sprPCRed.SetColor(sf::Color(255, 128, 128));
        sprPCRed.SetCenter(25, 25);

        sprPCBlue.SetImage(oPC);
        sprPCBlue.SetColor(sf::Color(128, 128, 255));
        sprPCBlue.SetCenter(25, 25);

        sprPCGreen.SetImage(oPC);
        sprPCGreen.SetColor(sf::Color(128, 255, 128));
        sprPCGreen.SetCenter(25, 25);*/

    //Effects ================
    oEffectRayBullet.LoadFromFile("data/img/ray_bullet.png");
        sprEffectRayBullet.SetImage(oEffectRayBullet);
    oEffectRayBulletImpact.LoadFromFile("data/img/ray_bullet_impact.png");
        sprEffectRayBulletImpact.SetImage(oEffectRayBulletImpact);
    oEffectRayLaser.LoadFromFile("data/img/ray_laser.png");
        sprEffectRayLaser.SetImage(oEffectRayLaser);
    oEffectRayLaserImpact.LoadFromFile("data/img/ray_laser_impact.png");
        sprEffectRayLaserImpact.SetImage(oEffectRayLaserImpact);
    oEffectRayGauss.LoadFromFile("data/img/ray_gauss.png");
        sprEffectRayGauss.SetImage(oEffectRayGauss);
    oEffectRayGaussImpact.LoadFromFile("data/img/ray_gauss_impact.png");
        sprEffectRayGaussImpact.SetImage(oEffectRayGaussImpact);
    oEffectExplosion.LoadFromFile("data/img/explosion.png");
        sprEffectExplosion.SetImage(oEffectExplosion);
    oEffectPostExplosion.LoadFromFile("data/img/postexplosion.png");
        sprEffectPostExplosion.SetImage(oEffectPostExplosion);
    oEffectBlood1.LoadFromFile("data/img/blood1.png");
        sprEffectBlood1.SetImage(oEffectBlood1);
    oEffectBlood2.LoadFromFile("data/img/blood2.png");
        sprEffectBlood2.SetImage(oEffectBlood2);
}


void DrawScreen(int nScreen)
{
    switch(nScreen)
    {
        case 0:
            oApp.Draw(sprGameScreen);
            break;
        case 1:
            oApp.Draw(sprWelcomeScreen);
            break;

    }
}

void DrawWorld()
{
    int i, j;
    Vector2<float>::Vector2<float> vPosWindow;
    struct worldposblock vPosWorld;

    for(i=0 ; i<WORLD_HEIGHT_CUBE ; i++)
    {
        for(j=0 ; j<WORLD_WIDTH_CUBE ; j++)
        {
            vPosWorld.hrz = j; vPosWorld.ver = i;
            vPosWindow = CoordWorldBlocksToScreenPx(vPosWorld);

            switch(nWorld[i][j])
            {
                //=========================
                case WORLD_CUBE_FLOOR_ROCK:
                    sprWorldFloorRock.SetPosition(vPosWindow);
                    oApp.Draw(sprWorldFloorRock);
                    break;
                //=========================
                case WORLD_CUBE_CRATE_A:
                    sprWorldCrateA.SetPosition(vPosWindow);
                    oApp.Draw(sprWorldCrateA);
                    break;
                //=========================
                case WORLD_CUBE_GAP:
                    sprWorldGap.SetPosition(vPosWindow);
                    oApp.Draw(sprWorldGap);
                    break;
                //=========================
                case WORLD_CUBE_NOTSET:
                    sprWorldNotSet.SetPosition(vPosWindow);
                    oApp.Draw(sprWorldNotSet);
                    break;
            }

            switch(nWorldSpe[i][j])
            {
                //=========================
                case WORLD_SPEC_FLAG_RED:
                    sprWorldFlagRed.SetPosition(vPosWindow);
                    oApp.Draw(sprWorldFlagRed);
                    break;
                //=========================
                case WORLD_SPEC_FLAG_GREEN:
                    sprWorldFlagGreen.SetPosition(vPosWindow);
                    oApp.Draw(sprWorldFlagGreen);
                    break;
                //=========================
                case WORLD_SPEC_FLAG_BLUE:
                    sprWorldFlagBlue.SetPosition(vPosWindow);
                    oApp.Draw(sprWorldFlagBlue);
                    break;
                //=========================
                case WORLD_SPEC_SPAWN_RED:
                    sprWorldSpawnRed.SetPosition(vPosWindow);
                    oApp.Draw(sprWorldSpawnRed);
                    break;
                //=========================
                case WORLD_SPEC_SPAWN_GREEN:
                    sprWorldSpawnGreen.SetPosition(vPosWindow);
                    oApp.Draw(sprWorldSpawnGreen);
                    break;
                //=========================
                case WORLD_SPEC_SPAWN_BLUE:
                    sprWorldSpawnBlue.SetPosition(vPosWindow);
                    oApp.Draw(sprWorldSpawnBlue);
                    break;
            }
        }
    }
}


void DrawCursor(Vector2<float>::Vector2<float> vPosition)
{
    if(vPosition.x>0 && vPosition.x<SCREEN_WIDTH && vPosition.y>0 && vPosition.y<SCREEN_HEIGHT)
    {
        sprCursor.SetPosition(Vector2f(vPosition.x-(DIM_CURSOR_WIDTH/2), vPosition.y-(DIM_CURSOR_HEIGHT/2)));
        oApp.Draw(sprCursor);
    }
}


void DrawPCs(PC::PC* oPC)
{




    struct location lLocPC;
    lLocPC = oPC->GetLocation();

    Vector2<float>::Vector2<float> vPosAff;
    vPosAff = CoordWorldPxToScreenPx(lLocPC.pos);

    float fRotation = lLocPC.facing-sprPlayerSkinDefault.GetRotation();

    sprPlayerSkinDefault.Rotate(fRotation);
    sprPlayerSkinDefault.SetPosition(Vector2f(vPosAff.x, vPosAff.y));
    oApp.Draw(sprPlayerSkinDefault);
}


void DrawPlayerInfo(PC::PC* oPC)
{
    #define X_POSITION 800
    #define Y_POSITION 850

    float fDate = clkDateGame.GetElapsedTime();
    Item::Item* pItem = oPC->m_oInventaire.GetEquipedItem(EQUIPMENT_PART_WEAPON);
    Weapon* pWeapon = dynamic_cast<Weapon*>(pItem);

    int nCurrAmmo = pWeapon->Weapon_GetCurrAmmo();
    float fCoolDownDateEnd = oPC->m_fFireDelayDateEnd;
    float fReloadDateEnd = oPC->m_fReloadDelayDateEnd;

    std::stringstream sOut;
    sOut<<oPC->m_nHP;
    String oHP(sOut.str(), GameFont);
    oHP.SetColor(Color(255, 64, 64));
    oHP.SetPosition(X_POSITION, Y_POSITION);

    std::stringstream sOut2;
    sOut2<<nCurrAmmo;
    String oAmmo(sOut2.str(), GameFont);
    oAmmo.SetColor(Color(172, 172, 172));
    oAmmo.SetPosition(X_POSITION+60, Y_POSITION);

    Shape oFiringDelayLine;
    if(fCoolDownDateEnd>fDate)
    {
        //Draw de la ligne
        int nLineLengh=(fCoolDownDateEnd-fDate)*300;
        oFiringDelayLine = Shape::Line(X_POSITION+100, Y_POSITION+10, X_POSITION+100+nLineLengh, Y_POSITION+10, 7, Color(255, 60, 0));
    }

    Shape oReloadDelayLine;
    if(fReloadDateEnd>fDate)
    {
        //Draw de la ligne
        int nLineLengh=(fReloadDateEnd-fDate)*50;
        oReloadDelayLine = Shape::Line(X_POSITION+100, Y_POSITION+23, X_POSITION+100+nLineLengh, Y_POSITION+23, 12, Color(255, 255, 0));
    }


    oApp.Draw(oHP);
    oApp.Draw(oAmmo);
    oApp.Draw(oFiringDelayLine);
    oApp.Draw(oReloadDelayLine);
}



std::string InputBox(const char* cPrezText, bool bEscape)
{
    sprInputBox.SetPosition(Vector2f((SCREEN_WIDTH-DIM_SCREEN_ENTRYBOX_WIDTH)/2, (SCREEN_HEIGHT-DIM_SCREEN_ENTRYBOX_HEIGHT)/2));


    std::string sInput = ("");
    String sAffichage("", GameFont),
           sTitre(cPrezText, GameFont);

    sAffichage.SetColor(Color(0, 0, 0));

    sTitre.SetPosition((SCREEN_WIDTH-sTitre.GetRect().GetWidth())/2, (SCREEN_HEIGHT-sTitre.GetRect().GetHeight())/2-110);
    sTitre.SetColor(Color(0, 0, 0));


    bool bQuit=false;
    Event eEvent;
    while(!bQuit)
    {
        while(oApp.GetEvent(eEvent))
        {
            switch(eEvent.Type)
            {

                case Event::KeyPressed:
                    switch(eEvent.Key.Code)
                    {
                        case Key::A:
                            if(eEvent.Key.Shift)    sInput+='A';
                            else                    sInput+='a';
                            break;
                        case Key::B:
                            if(eEvent.Key.Shift)    sInput+='B';
                            else                    sInput+='b';
                            break;
                        case Key::C:
                            if(eEvent.Key.Shift)    sInput+='C';
                            else                    sInput+='c';
                            break;
                        case Key::D:
                            if(eEvent.Key.Shift)    sInput+='D';
                            else                    sInput+='d';
                            break;
                        case Key::E:
                            if(eEvent.Key.Shift)    sInput+='E';
                            else                    sInput+='e';
                            break;
                        case Key::F:
                            if(eEvent.Key.Shift)    sInput+='F';
                            else                    sInput+='f';
                            break;
                        case Key::G:
                            if(eEvent.Key.Shift)    sInput+='G';
                            else                    sInput+='g';
                            break;
                        case Key::H:
                            if(eEvent.Key.Shift)    sInput+='H';
                            else                    sInput+='h';
                            break;
                        case Key::I:
                            if(eEvent.Key.Shift)    sInput+='I';
                            else                    sInput+='i';
                            break;
                        case Key::J:
                            if(eEvent.Key.Shift)    sInput+='J';
                            else                    sInput+='j';
                            break;
                        case Key::K:
                            if(eEvent.Key.Shift)    sInput+='K';
                            else                    sInput+='k';
                            break;
                        case Key::L:
                            if(eEvent.Key.Shift)    sInput+='L';
                            else                    sInput+='l';
                            break;
                        case Key::M:
                            if(eEvent.Key.Shift)    sInput+='M';
                            else                    sInput+='m';
                            break;
                        case Key::N:
                            if(eEvent.Key.Shift)    sInput+='N';
                            else                    sInput+='n';
                            break;
                        case Key::O:
                            if(eEvent.Key.Shift)    sInput+='O';
                            else                    sInput+='o';
                            break;
                        case Key::P:
                            if(eEvent.Key.Shift)    sInput+='P';
                            else                    sInput+='p';
                            break;
                        case Key::Q:
                            if(eEvent.Key.Shift)    sInput+='Q';
                            else                    sInput+='q';
                            break;
                        case Key::R:
                            if(eEvent.Key.Shift)    sInput+='R';
                            else                    sInput+='r';
                            break;
                        case Key::S:
                            if(eEvent.Key.Shift)    sInput+='S';
                            else                    sInput+='s';
                            break;
                        case Key::T:
                            if(eEvent.Key.Shift)    sInput+='T';
                            else                    sInput+='t';
                            break;
                        case Key::U:
                            if(eEvent.Key.Shift)    sInput+='U';
                            else                    sInput+='u';
                            break;
                        case Key::V:
                            if(eEvent.Key.Shift)    sInput+='V';
                            else                    sInput+='v';
                            break;
                        case Key::W:
                            if(eEvent.Key.Shift)    sInput+='W';
                            else                    sInput+='w';
                            break;
                        case Key::X:
                            if(eEvent.Key.Shift)    sInput+='X';
                            else                    sInput+='x';
                            break;
                        case Key::Y:
                            if(eEvent.Key.Shift)    sInput+='Y';
                            else                    sInput+='y';
                            break;
                        case Key::Z:
                            if(eEvent.Key.Shift)    sInput+='Z';
                            else                    sInput+='z';
                            break;

                        case Key::Num0:
                            if(eEvent.Key.Shift)    sInput+='0';
                            break;
                        case Key::Num1:
                            if(eEvent.Key.Shift)    sInput+='1';
                            else                    sInput+='&';
                            break;
                        case Key::Num2:
                            if(eEvent.Key.Shift)    sInput+='2';
                            break;
                        case Key::Num3:
                            if(eEvent.Key.Shift)    sInput+='3';
                            break;
                        case Key::Num4:
                            if(eEvent.Key.Shift)    sInput+='4';
                            break;
                        case Key::Num5:
                            if(eEvent.Key.Shift)    sInput+='5';
                            else                    sInput+='(';
                            break;
                        case Key::Num6:
                            if(eEvent.Key.Shift)    sInput+='6';
                            else                    sInput+='-';
                            break;
                        case Key::Num7:
                            if(eEvent.Key.Shift)    sInput+='7';
                            break;
                        case Key::Num8:
                            if(eEvent.Key.Shift)    sInput+='8';
                            else                    sInput+='_';
                            break;
                        case Key::Num9:
                            if(eEvent.Key.Shift)    sInput+='9';
                            break;

                        case Key::Numpad0:
                                                    sInput+='0';
                            break;
                        case Key::Numpad1:
                                                    sInput+='1';
                            break;
                        case Key::Numpad2:
                                                    sInput+='2';
                            break;
                        case Key::Numpad3:
                                                    sInput+='3';
                            break;
                        case Key::Numpad4:
                                                    sInput+='4';
                            break;
                        case Key::Numpad5:
                                                    sInput+='5';
                            break;
                        case Key::Numpad6:
                                                    sInput+='6';
                            break;
                        case Key::Numpad7:
                                                    sInput+='7';
                            break;
                        case Key::Numpad8:
                                                    sInput+='8';
                            break;
                        case Key::Numpad9:
                                                    sInput+='9';
                            break;

                        case Key::LBracket:
                                                    sInput+='[';
                            break;
                        case Key::RBracket:
                                                    sInput+=']';
                            break;
                        case Key::SemiColon:
                                                    sInput+=';';
                            break;
                        case Key::Comma:
                                                    sInput+=',';
                            break;
                        case Key::Period:
                                                    sInput+='.';
                            break;
                        case Key::Quote:
                                                    sInput+='\'';
                            break;
                        case Key::Slash:
                                                    sInput+='/';
                            break;
                        case Key::Tilde:
                                                    sInput+='~';
                            break;
                        case Key::Equal:
                                                    sInput+='=';
                            break;
                        case Key::Add:
                                                    sInput+='+';
                            break;
                        case Key::Dash:
                                                    sInput+='-';
                            break;
                        case Key::Multiply:
                                                    sInput+='*';
                            break;
                        case Key::Divide:
                                                    sInput+='/';
                            break;
                        case Key::BackSlash:
                                                    sInput+='\\';
                            break;
                        case Key::Space:
                                                    sInput+=' ';
                            break;


                        case Key::Back:
                            if(sInput.length()>0)
                                sInput.erase(sInput.length()-1,1);
                            break;
                        case Key::Return:
                            return sInput;
                            break;
                        case Key::Escape:
                            if(bEscape)return "-1";
                            break;
                        default:
                            break;

                    }
                    break;

                default:
                    break;
            }
        }
        oApp.Clear();

        //Draw de la boite
        oApp.Draw(sprInputBox);

        oApp.Draw(sTitre);

        sAffichage.SetText(sInput.c_str());
        sAffichage.SetPosition(Vector2f( (SCREEN_WIDTH-sAffichage.GetRect().GetWidth())/2, (SCREEN_HEIGHT-sAffichage.GetRect().GetHeight())/2+60));
        oApp.Draw(sAffichage);

        oApp.Display();

    }
    return "";
}




///Noircit l'écran et pose la question cQuestion a l'utilisateur, qui peut répondre oui/non
///Renvoie -1 si échap, 0 si non, 1 si oui
int QuestionBox(const char* cQuestion, bool bEscape, const char* cYes, bool bNo, const char* cNo)
{
    String sTitre(cQuestion, GameFont);
    sTitre.SetPosition((SCREEN_WIDTH-sTitre.GetRect().GetWidth())/2, (SCREEN_HEIGHT-DIM_SCREEN_ENTRYBOX_HEIGHT-sTitre.GetRect().GetHeight())/2+70);
    sTitre.SetColor(Color(255, 255, 255));

    ButtonHandler::ButtonHandler Buttons;
    if(bNo)//Si il y a deux boutons
    {
        Buttons.AddButton(SCREEN_WIDTH/2-150, 600, cNo, 1);
        Buttons.AddButton(SCREEN_WIDTH/2+150, 600, cYes, 2);
    }
    else
    {
        Buttons.AddButton(SCREEN_WIDTH/2, 600, cYes, 2);
    }


    bool bQuit=false;
    int nButtonPressed=0;
    Event eEvent;
    Vector2<float>::Vector2<float> vPosMouse;
    while(!bQuit)
    {
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
                        case Key::Return:
                            return true;
                            break;
                        case Key::Escape:
                            return -1;
                            break;
                        default:
                            break;
                    }
                    break;

                case Event::Closed:
                    oApp.Close();
                    return -1;
                    break;

                default:
                    break;
            }

            nButtonPressed = Buttons.OnEvent(eEvent);

        }


        switch(nButtonPressed)
        {
            case 1://Non
                return 0;
                break;
            case 2://oui
                return 1;
                break;
        }

        oApp.Clear();

        oApp.Draw(sTitre);
        Buttons.DrawButtons();

        DrawCursor(vPosMouse);

        oApp.Display();

    }
    return false;
}



