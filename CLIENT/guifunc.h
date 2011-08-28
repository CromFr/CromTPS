#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

//Depend de SFML
//Dépend de main.h : Structures de positions & ctes
//Dépend de convert.h

#include "Player.h"

void InitImagesAndSprites();

///Dessine le screen n°nScreen
/// 0=Game, 1=welcome
void DrawScreen(int nScreen=0);

void DrawWorld();
void DrawCursor(sf::Vector2<float>::Vector2<float> vPosition);
void DrawPCs(PC::PC* oPC);//Ne dessine qu'un character (oPC)
void DrawPlayerInfo(PC::PC* oPC);
std::string InputBox(const char* cPrezText, bool bEscape=false);//-1 si echap, sinon la chaine entrée
int QuestionBox(const char* cQuestion, bool bEscape=false, const char* cYes="Oui", bool bNo=true, const char* cNo="Non");//0 si non, 1si oui, -1 si escape

#endif // UI_H_INCLUDED
