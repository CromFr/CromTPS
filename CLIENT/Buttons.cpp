#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Buttons.h"


extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern sf::RenderWindow oApp;

/*==*/ extern sf::Image oButton0Inactive;
/*==*/    extern sf::Sprite sprButton0Inactive;
/*==*/ extern sf::Image oButton0Active;
/*==*/    extern sf::Sprite sprButton0Active;
/*==*/ extern sf::Image oButton0Pressed;
/*==*/    extern sf::Sprite sprButton0Pressed;
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

extern sf::Font GameFont;

//=====================================================================
//=====================================================================
Button::Button(int nPosX, int nPosY, std::string sText, int nID, int nSkin)
{
    using namespace sf;

    Button::sprDefault=0;
    Button::sprOnMouseOver=0;
    Button::sprOnClick=0;

    switch(nSkin)// <------------------- Liste des skins
    {
        case 0://Skin 0
            Button::sprDefault=&sprButton0Inactive;         Button::sprOnMouseOver=&sprButton0Active;           Button::sprOnClick=&sprButton0Pressed;
            break;
        case 101:
            Button::sprDefault=&sprWeaponBulletPistol;      Button::sprOnMouseOver=&sprWeaponBulletPistol;      Button::sprOnClick=&sprWeaponBulletPistol;
            break;
        case 102:
            Button::sprDefault=&sprWeaponBulletRifle;       Button::sprOnMouseOver=&sprWeaponBulletRifle;       Button::sprOnClick=&sprWeaponBulletRifle;
            break;
        case 103:
            Button::sprDefault=&sprWeaponBulletMinigun;     Button::sprOnMouseOver=&sprWeaponBulletMinigun;     Button::sprOnClick=&sprWeaponBulletMinigun;
            break;
        case 111:
            Button::sprDefault=&sprWeaponLaserPistol;       Button::sprOnMouseOver=&sprWeaponLaserPistol;       Button::sprOnClick=&sprWeaponLaserPistol;
            break;
        case 112:
            Button::sprDefault=&sprWeaponLaserRifle;        Button::sprOnMouseOver=&sprWeaponLaserRifle;        Button::sprOnClick=&sprWeaponLaserRifle;
            break;
        case 113:
            Button::sprDefault=&sprWeaponLaserMinigun;      Button::sprOnMouseOver=&sprWeaponLaserMinigun;      Button::sprOnClick=&sprWeaponLaserMinigun;
            break;
        case 121:
            Button::sprDefault=&sprWeaponGaussPistol;       Button::sprOnMouseOver=&sprWeaponGaussPistol;       Button::sprOnClick=&sprWeaponGaussPistol;
            break;
        case 122:
            Button::sprDefault=&sprWeaponGaussRifle;        Button::sprOnMouseOver=&sprWeaponGaussRifle;        Button::sprOnClick=&sprWeaponGaussRifle;
            break;
        case 123:
            Button::sprDefault=&sprWeaponGaussMinigun;      Button::sprOnMouseOver=&sprWeaponGaussMinigun;      Button::sprOnClick=&sprWeaponGaussMinigun;
            break;
        case 124:
            Button::sprDefault=&sprWeaponGaussDestructeur;  Button::sprOnMouseOver=&sprWeaponGaussDestructeur;  Button::sprOnClick=&sprWeaponGaussDestructeur;
            break;

        //...liste des skins

        default:
            Button::sprDefault=&sprButton0Inactive;
            Button::sprOnMouseOver=&sprButton0Active;
            Button::sprOnClick=&sprButton0Pressed;
            break;
    }

    Button::m_nID = nID;
    Button::m_nPosX = nPosX;
    Button::m_nPosY = nPosY;

    int ButtonWidth = sprDefault->GetSize().x;
    int ButtonHeight = sprDefault->GetSize().y;
    Button::m_sText.SetText(sText.c_str());
    Button::m_sText.SetFont(GameFont);
    Button::m_sText.SetColor(Color(0, 0, 0));
    Button::m_sText.SetPosition(nPosX+(ButtonWidth-m_sText.GetRect().GetWidth())/2, nPosY+(ButtonHeight-m_sText.GetRect().GetHeight())/2-5);

    Button::m_nMode = 0;
}
//=====================================================================
void Button::SetMode(int nMode)
{
    Button::m_nMode=nMode;
}
//=====================================================================
void Button::DrawButton()
{
    sf::Sprite* sprButton=0;
    switch(Button::m_nMode)
    {
        case 0:
            sprButton=Button::sprDefault;
            break;
        case 1:
            sprButton=Button::sprOnMouseOver;
            break;
        case 2:
            sprButton=Button::sprOnClick;
            break;
    }

    if(sprButton!=0)
    {
        sprButton->SetPosition(m_nPosX, m_nPosY);
        oApp.Draw(*sprButton);
    }

    oApp.Draw(Button::m_sText);
}
//=====================================================================
int Button::GetID()const
{
    return Button::m_nID;
}
//=====================================================================
int Button::GetXMin()const
{
    return Button::m_nPosX;
}
//=====================================================================
int Button::GetXMax()const
{
    return Button::m_nPosX+_BUTTON_WIDTH;
}
//=====================================================================
int Button::GetYMin()const
{
    return Button::m_nPosY;
}
//=====================================================================
int Button::GetYMax()const
{
    return Button::m_nPosY+_BUTTON_HEIGHT;
}
//=====================================================================
//=====================================================================
ButtonHandler::ButtonHandler()
{

}
//=====================================================================
ButtonHandler::~ButtonHandler()
{
    while(ButtonHandler::m_pListeButton.size()>0)
    {
        delete ButtonHandler::m_pListeButton[ButtonHandler::m_pListeButton.size()-1];
        ButtonHandler::m_pListeButton.pop_back();
    }
}
//=====================================================================
int ButtonHandler::OnEvent(sf::Event eEvent)
{
    using namespace sf;

    int nSize=ButtonHandler::m_pListeButton.size();
    sf::Vector2<float>::Vector2<float> vPosMouse;
    Button::Button* pClickedButton=0;

    switch(eEvent.Type)
    {
        case Event::MouseMoved:
            vPosMouse = Vector2f(eEvent.MouseMove.X, eEvent.MouseMove.Y);

            for(int n(0) ; n<nSize ; n++)
            {
                if(GetIsOnButton(vPosMouse, ButtonHandler::m_pListeButton[n]))//Si la souris survole le bouton
                    ButtonHandler::m_pListeButton[n]->SetMode(1);//SetActive
                else//Si la souris est ailleurs
                    ButtonHandler::m_pListeButton[n]->SetMode(0);//SetInactive
            }
            break;

        case Event::MouseButtonPressed:
            if(eEvent.MouseButton.Button == Mouse::Left)
            {
                vPosMouse.x=eEvent.MouseButton.X;
                vPosMouse.y=eEvent.MouseButton.Y;
                for(int n(0) ; n<nSize ; n++)
                {
                    if(GetIsOnButton(vPosMouse, ButtonHandler::m_pListeButton[n]))//Si la souris a cliqué sur un bouton
                    {
                        ButtonHandler::m_pListeButton[n]->SetMode(2);//SetPressed
                    }
                    else//Si la souris est ailleurs
                        ButtonHandler::m_pListeButton[n]->SetMode(0);//SetInactive
                }
            }
            break;
        case Event::MouseButtonReleased:
            if(eEvent.MouseButton.Button == Mouse::Left)
            {
                vPosMouse.x=eEvent.MouseButton.X;
                vPosMouse.y=eEvent.MouseButton.Y;
                for(int n(0) ; n<nSize ; n++)
                {
                    if(GetIsOnButton(vPosMouse, ButtonHandler::m_pListeButton[n]))//Si la souris a cliqué sur un bouton
                    {
                        ButtonHandler::m_pListeButton[n]->SetMode(1);//SetPressed
                        pClickedButton=ButtonHandler::m_pListeButton[n];//On note ce bouton qui a été cliqué
                    }
                    else//Si la souris est ailleurs
                        ButtonHandler::m_pListeButton[n]->SetMode(0);//SetInactive
                }

                //On retourne l'ID du bouton, si on a bien cliqué sur un bouton
                if(pClickedButton!=0)
                    return pClickedButton->GetID();
            }
            break;
        default:
            break;
    }

    return 0;
}
//=====================================================================
void ButtonHandler::DrawButtons() const
{
    int nSize=ButtonHandler::m_pListeButton.size();
    for(int n(0) ; n<nSize ; n++)
    {
        if(ButtonHandler::m_pListeButton[n] != 0)
            ButtonHandler::m_pListeButton[n]->DrawButton();
    }
}
//=====================================================================
void ButtonHandler::AddButton(int nPosCenterX, int nPosCenterY, std::string sText, int nID, int nSkin)
{
    Button::Button* pButton=0;
    pButton = new Button::Button(nPosCenterX-_BUTTON_WIDTH/2, nPosCenterY-_BUTTON_HEIGHT/2, sText, nID, nSkin);

    ButtonHandler::m_pListeButton.push_back(pButton);
}
//=====================================================================
void ButtonHandler::AddButtonPercent(float fPosCenterXPercent, float fPosCenterYPercent, std::string sText, int nID, int nOffsetX, int nOffsetY, int nSkin)
{
    Button::Button* pButton=0;
    pButton = new Button::Button(nOffsetX+SCREEN_WIDTH*(fPosCenterXPercent/100)-_BUTTON_WIDTH/2, nOffsetY+SCREEN_HEIGHT*(fPosCenterYPercent/100)-_BUTTON_HEIGHT/2, sText, nID, nSkin);

    ButtonHandler::m_pListeButton.push_back(pButton);
}
//=====================================================================
bool ButtonHandler::GetIsOnButton(sf::Vector2<float>::Vector2<float> vMouse, Button::Button* pButton)
{
    if(vMouse.x>pButton->GetXMin() && vMouse.x<pButton->GetXMax()
       && vMouse.y>pButton->GetYMin() && vMouse.y<pButton->GetYMax())
       return true;
    return false;
}

