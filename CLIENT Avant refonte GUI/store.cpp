#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>


#include <SFML/Graphics.hpp>
#include "main.h"
#include "convert.h"
#include "guifunc.h"

#include "Items.h"
#include "Buttons.h"

#include "store.h"

using namespace sf;

//Application :
extern RenderWindow oApp;



void Store(PC::PC* oPC)
{
    ButtonHandler::ButtonHandler Buttons;

    Buttons.AddButton(DIM_WINDOW_WIDTH/2, 400, "Armes", 1);
    Buttons.AddButton(DIM_WINDOW_WIDTH/2, 500, "Armures", 2);
    Buttons.AddButton(DIM_WINDOW_WIDTH/2, 600, "Blocs", 3);
    Buttons.AddButton(DIM_WINDOW_WIDTH/2, 700, "Divers", 4);

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
                            return;
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

            nButtonPressed = Buttons.OnEvent(eEvent);
        }

        if(nButtonPressed == 1)
        {//Armes
            while(oApp.GetEvent(eEvent));
            Store_Weapons(oPC);
        }
        if(nButtonPressed == 2)
        {//Armures
            while(oApp.GetEvent(eEvent))
            {

            }
            std::cout<<"Armures"<<std::endl;
        }
        if(nButtonPressed == 3)
        {//Blocs
            while(oApp.GetEvent(eEvent))
            {

            }
            std::cout<<"Blocs"<<std::endl;
        }
        if(nButtonPressed == 4)
        {//Divers
            while(oApp.GetEvent(eEvent))
            {

            }
            std::cout<<"Divers"<<std::endl;
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
    return;
}




void Store_Weapons(PC::PC* oPC)
{
    ButtonHandler::ButtonHandler Buttons;

    Buttons.AddButton(DIM_WINDOW_WIDTH/4, 200, "", 1, 101);
    Buttons.AddButton(DIM_WINDOW_WIDTH/4, 350, "", 2, 102);
    Buttons.AddButton(DIM_WINDOW_WIDTH/4, 500, "", 3, 103);

    Buttons.AddButton(DIM_WINDOW_WIDTH/2, 200, "", 4, 111);
    Buttons.AddButton(DIM_WINDOW_WIDTH/2, 350, "", 5, 112);
    Buttons.AddButton(DIM_WINDOW_WIDTH/2, 500, "", 6, 113);

    Buttons.AddButton(3*DIM_WINDOW_WIDTH/4, 200, "", 7, 121);
    Buttons.AddButton(3*DIM_WINDOW_WIDTH/4, 350, "", 8, 122);
    Buttons.AddButton(3*DIM_WINDOW_WIDTH/4, 500, "", 9, 123);
    Buttons.AddButton(3*DIM_WINDOW_WIDTH/4, 650, "", 10, 124);

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
                            return;
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

            nButtonPressed = Buttons.OnEvent(eEvent);
        }
        switch(nButtonPressed)
        {
        case 1://bullet pistol
            while(oApp.GetEvent(eEvent));
            switch(QuestionBox("Voulez-vous vraiment acheter\ncet objet?"))
            {
                case -1: case 0: break;
                case 1: oPC->BuyItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_BULLET_PISTOL)); break;
            }
            break;
        case 2://bullet rifle
            while(oApp.GetEvent(eEvent));
            switch(QuestionBox("Voulez-vous vraiment acheter\ncet objet?"))
            {
                case -1: case 0: break;
                case 1: oPC->BuyItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_BULLET_RIFLE)); break;
            }
            break;
        case 3://bullet minigun
            while(oApp.GetEvent(eEvent));
            switch(QuestionBox("Voulez-vous vraiment acheter\ncet objet?"))
            {
                case -1: case 0: break;
                case 1: oPC->BuyItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_BULLET_MINIGUN)); break;
            }
            break;
        case 4://laser pistol
            while(oApp.GetEvent(eEvent));
            switch(QuestionBox("Voulez-vous vraiment acheter\ncet objet?"))
            {
                case -1: case 0: break;
                case 1: oPC->BuyItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_LASER_PISTOL)); break;
            }
            break;
        case 5://laser rifle
            while(oApp.GetEvent(eEvent));
            switch(QuestionBox("Voulez-vous vraiment acheter\ncet objet?"))
            {
                case -1: case 0: break;
                case 1: oPC->BuyItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_LASER_RIFLE)); break;
            }
            break;
        case 6://laser minigun
            while(oApp.GetEvent(eEvent));
            switch(QuestionBox("Voulez-vous vraiment acheter\ncet objet?"))
            {
                case -1: case 0: break;
                case 1: oPC->BuyItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_LASER_MINIGUN)); break;
            }
            break;
        case 7://gauss pistol
            while(oApp.GetEvent(eEvent));
            switch(QuestionBox("Voulez-vous vraiment acheter\ncet objet?"))
            {
                case -1: case 0: break;
                case 1: oPC->BuyItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_GAUSS_PISTOL)); break;
            }
            break;
        case 8://gauss rifle
            while(oApp.GetEvent(eEvent));
            switch(QuestionBox("Voulez-vous vraiment acheter\ncet objet?"))
            {
                case -1: case 0: break;
                case 1: oPC->BuyItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_GAUSS_RIFLE)); break;
            }
            break;
        case 9://gauss minigun
            while(oApp.GetEvent(eEvent));
            switch(QuestionBox("Voulez-vous vraiment acheter\ncet objet?"))
            {
                case -1: case 0: break;
                case 1: oPC->BuyItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_GAUSS_MINIGUN)); break;
            }
            break;
        case 10://gauss destructeur
            while(oApp.GetEvent(eEvent));
            switch(QuestionBox("Voulez-vous vraiment acheter\ncet objet?"))
            {
                case -1: case 0: break;
                case 1: oPC->BuyItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_GAUSS_DESTRUCTEUR)); break;
            }
            break;
        }
        if(nButtonPressed!=0)while(oApp.GetEvent(eEvent));


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
    return;
}
