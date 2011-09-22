#ifndef DELAYEDCOMMANDS_HPP_INCLUDED
#define DELAYEDCOMMANDS_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>

typedef void (*Command)();

class DelayedCommands
{
    public:
    DelayedCommands(bool bExecute=true);
    ~DelayedCommands();


    ///A mettre dans un thread/boucle infinie pour éxécuter les commandes stockées
    void ExecuteCommands();

    ///Vide la liste des commandes
    void StopCommands();

    ///Met en pause/redémarre les commandes
    /// bRestart : false=>met en pause, true=>Redémarre après une pause
    ///Note : la pause est gérée à l'interieur de la class, ainsi executer ExecuteCommands() pendant une pause ne fera rien;
    void PauseCommands(bool bRestart=false);

    ///Ajoute une commande à retarder
    void AddCommand(float fDelay, void *Function);

    private:
    bool m_bExecute;
    std::vector<float> m_fDatesList;
    std::vector<Command> m_pCommandsList;

    //void* m_pCommandsList[100];
};

DelayedCommands::DelayedCommands CommandsDelayer;

void DelayCommand(float fDelay, void* Function);



#endif // DELAYEDCOMMANDS_HPP_INCLUDED
