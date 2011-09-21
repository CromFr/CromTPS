#include "DelayedCommands.hpp"

extern sf::Clock clkDateGame;


DelayedCommands::DelayedCommands()
{



}

DelayedCommands::~DelayedCommands()
{



}


void DelayedCommands::ExecuteCommands()
{
    int nSize = 5;//DelayedCommands::m_pCommandsList.size();
    float fDate = clkDateGame.GetElapsedTime();

    int n;
    for(n=0 ; n<nSize ; n++)
    {
        if(DelayedCommands::m_pDatesList[n] >= fDate && DelayedCommands::m_pCommandsList[n]!=0)
        {
            //Executer et supprimer
            //void* fonction = DelayedCommands::m_pCommandsList[n];
            (DelayedCommands::m_pCommandsList[n])();
            //*DelayedCommands::m_pCommandsList[n]();
        }


    }



}
