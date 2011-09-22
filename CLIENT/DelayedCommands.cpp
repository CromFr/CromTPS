
#include "DelayedCommands.hpp"

extern sf::Clock clkDateGame;


DelayedCommands::DelayedCommands(bool bExecute)
{
    DelayedCommands::m_bExecute=bExecute;


}

DelayedCommands::~DelayedCommands()
{



}


void DelayedCommands::ExecuteCommands()
{
    if(DelayedCommands::m_bExecute)
    {
        int nSize = DelayedCommands::m_pCommandsList.size();
        float fDate = clkDateGame.GetElapsedTime();

        int n;
        for(n=0 ; n<nSize ; n++)
        {
            if(DelayedCommands::m_fDatesList[n]>=fDate && DelayedCommands::m_pCommandsList[n]!=0)
            {
                //Executer et supprimer
                //void* fonction = DelayedCommands::m_pCommandsList[n];
                //(DelayedCommands::m_pCommandsList[n])();
                //*DelayedCommands::m_pCommandsList[n]();
            }
        }
    }
}


void DelayedCommands::StopCommands()
{
    while(DelayedCommands::m_pCommandsList.size()>0)
        DelayedCommands::m_pCommandsList.pop_back();

    while(DelayedCommands::m_fDatesList.size()>0)
        DelayedCommands::m_fDatesList.pop_back();
}

void DelayedCommands::PauseCommands(bool bRestart)
{
    DelayedCommands::m_bExecute=bRestart;
}

void DelayedCommands::AddCommand(float fDelay, void *Function)
{
    int nSize = DelayedCommands::m_pCommandsList.size();
    float fDate = clkDateGame.GetElapsedTime();

    int nEmplacement =-1;

    int n;
    for(n=0 ; n<nSize ; n++)
    {
        if(DelayedCommands::m_pCommandsList[n]==0 || DelayedCommands::m_fDatesList[n]>=fDate)
        {
            nEmplacement=n;
            break;
        }
    }

    //Cas d'un emplacement trouvé
    if(nEmplacement>=0)
    {
        DelayedCommands::m_pCommandsList[n]=(Function);
        DelayedCommands::m_fDatesList[n]=fDate+fDelay;
    }
    else//cas d'une liste pleine, on ouvre une case supplémentaire
    {
        //DelayedCommands::m_pCommandsList.push_back(Function);
        DelayedCommands::m_fDatesList.push_back(fDate+fDelay);

    }
}


