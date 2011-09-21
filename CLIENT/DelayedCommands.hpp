#ifndef DELAYEDCOMMANDS_HPP_INCLUDED
#define DELAYEDCOMMANDS_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>

class DelayedCommands
{
    public:
    DelayedCommands();
    ~DelayedCommands();


    ///A mettre dans un thread/boucle infinie pour éxécuter les commandes stockées
    void ExecuteCommands();

    ///Vide la liste des commandes
    /// bExecute : true=>les commandes sont executees immédiatement puis sont supprimees, false=>Rien n'est éxécuté et tout est supprimé
    void StopCommands(bool bExecute=false);

    ///Met en pause/redémarre les commandes
    /// bRestart : false=>met en pause, true=>Redémarre après une pause
    ///Note : la pause est gérée à l'interieur de la class, ainsi executer ExecuteCommands() pendant une pause ne fera rien;
    void PauseCommands(bool bRestart=false);

    ///Ajoute une commande à retarder
    void AddCommand(float fDelay, void* Function);

    private:
    bool m_bExecute;
    std::vector<float> m_pDatesList;
    //std::vector<void> *m_pCommandsList();

    void* m_pCommandsList[100];
};

DelayedCommands::DelayedCommands CommandsDelayer;

void DelayCommand(float fDelay, void* Function);



#endif // DELAYEDCOMMANDS_HPP_INCLUDED
