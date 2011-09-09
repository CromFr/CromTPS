#include <iostream>
#include <cstdlib>

#include <cmath>
#include <string>
#include <fstream>//Manips de fichiers
#include <SFML/Graphics.hpp>

#include "main.h"
#include "utils.h"



int Get2daInt(const std::string s2DAName, int nLineToGo, int nColonneToGo)
{
    using namespace std;

    //cout<<"Recherche dans le 2da"<<endl;
    ifstream st2DA(("data/"+s2DAName).c_str());

    if(!st2DA)
    {
        cout <<"Erreur Get2da('"<<s2DAName<<"',"<<nLineToGo<<","<<nColonneToGo<<") : Le fichier n'a pas pu etre ouvert"<<endl;
        return 0;
    }

    char cFirstChar, cChar;
    int nCurrent;
    int nLineDetected=-1, nColonneDetected=0;


    //Ignorer les commentaires de début de fichier
    st2DA.get(cFirstChar);
    while(nLineDetected!=nLineToGo)
    {
        if(cFirstChar == '#')
        {
            //Déplace le curseur a la fin de la ligne
            do
            {
                st2DA.get(cChar);
            }
            while(cChar!='\n');

            //On note le prochain char
            st2DA.get(cFirstChar);

            st2DA.seekg(-1, ios::cur);
            continue;
        }

        //Déplace le curseur a la fin de la ligne
        do
        {
            st2DA.get(cChar);
        }
        while(cChar!='\n');

        st2DA>>nLineDetected;//On note le prochain int

        //Si on a dépassé la ligne cherchée, c'est qu'elle n'existe pas
        if(nLineDetected>nLineToGo)
        {
            cout <<"Erreur Get2da('"<<s2DAName<<"',"<<nLineToGo<<","<<nColonneToGo<<") : La ligne n'existe pas"<<endl;
            return 0;
        }
    }

    //On se situe à la bonne ligne, juste après le chiffre de la ligne
    while(nColonneDetected<100)
    {
        //On passe tous les espaces
        while(st2DA.peek()==' ')
            st2DA. seekg(1, ios::cur);

        nColonneDetected++;

        //Si la colonne sur laquelle on arrive NE correspond PAS à celle voulue
        if(nColonneDetected != nColonneToGo)
        {
            //On ignore la chaine de caractère
            while(st2DA.peek()!=' ')
                st2DA. seekg(1, ios::cur);
        }
        //... correspond
        else
        {
            //On retourne la val trouvee
            st2DA>>nCurrent;
            return nCurrent;
        }
    }

    cout <<"Erreur Get2da('"<<s2DAName<<"',"<<nLineToGo<<","<<nColonneToGo<<") : La colonne n'existe pas"<<endl;
    return 0;
}



float Get2daFloat(const std::string s2DAName, int nLineToGo, int nColonneToGo)
{
    using namespace std;

    //cout<<"Recherche dans le 2da"<<endl;
    ifstream st2DA(("data/"+s2DAName).c_str());

    if(!st2DA)
    {
        cout <<"Erreur Get2da('"<<s2DAName<<"',"<<nLineToGo<<","<<nColonneToGo<<") : Le fichier n'a pas pu etre ouvert"<<endl;
        return 0.0;
    }

    char cFirstChar, cChar;
    float fCurrent;
    int nLineDetected=-1, nColonneDetected=0;


    //Ignorer les commentaires de début de fichier
    st2DA.get(cFirstChar);
    while(nLineDetected!=nLineToGo)
    {
        if(cFirstChar == '#')
        {
            //Déplace le curseur a la fin de la ligne
            do
            {
                st2DA.get(cChar);
            }
            while(cChar!='\n');

            //On note le prochain char
            st2DA.get(cFirstChar);

            st2DA.seekg(-1, ios::cur);
            continue;
        }

        //Déplace le curseur a la fin de la ligne
        do
        {
            st2DA.get(cChar);
        }
        while(cChar!='\n');

        st2DA>>nLineDetected;//On note le prochain int

        //Si on a dépassé la ligne cherchée, c'est qu'elle n'existe pas
        if(nLineDetected>nLineToGo)
        {
            cout <<"Erreur Get2da('"<<s2DAName<<"',"<<nLineToGo<<","<<nColonneToGo<<") : La ligne n'existe pas"<<endl;
            return 0.0;
        }
    }

    //On se situe à la bonne ligne, juste après le chiffre de la ligne
    while(nColonneDetected<100)
    {
        //On passe tous les espaces
        while(st2DA.peek()==' ')
            st2DA. seekg(1, ios::cur);

        nColonneDetected++;

        //Si la colonne sur laquelle on arrive NE correspond PAS à celle voulue
        if(nColonneDetected != nColonneToGo)
        {
            //On ignore la chaine de caractère
            while(st2DA.peek()!=' ')
                st2DA. seekg(1, ios::cur);
        }
        //... correspond
        else
        {
            //On retourne la val trouvee
            st2DA>>fCurrent;
            return fCurrent;
        }
    }

    cout <<"Erreur Get2da('"<<s2DAName<<"',"<<nLineToGo<<","<<nColonneToGo<<") : La colonne n'existe pas"<<endl;
    return 0.0;
}

std::string Get2daString(const std::string s2DAName, int nLineToGo, int nColonneToGo)
{
    using namespace std;

    //cout<<"Recherche dans le 2da"<<endl;
    ifstream st2DA(("data/"+s2DAName).c_str());

    if(!st2DA)
    {
        cout <<"Erreur Get2da('"<<s2DAName<<"',"<<nLineToGo<<","<<nColonneToGo<<") : Le fichier n'a pas pu etre ouvert"<<endl;
        return "ERROR";
    }

    char cFirstChar, cChar;
    std::string sCurrent;
    int nLineDetected=-1, nColonneDetected=0;


    //Ignorer les commentaires de début de fichier
    st2DA.get(cFirstChar);
    while(nLineDetected!=nLineToGo)
    {
        if(cFirstChar == '#')
        {
            //Déplace le curseur a la fin de la ligne
            do
            {
                st2DA.get(cChar);
            }
            while(cChar!='\n');

            //On note le prochain char
            st2DA.get(cFirstChar);

            st2DA.seekg(-1, ios::cur);
            continue;
        }

        //Déplace le curseur a la fin de la ligne
        do
        {
            st2DA.get(cChar);
        }
        while(cChar!='\n');

        st2DA>>nLineDetected;//On note le prochain int

        //Si on a dépassé la ligne cherchée, c'est qu'elle n'existe pas
        if(nLineDetected>nLineToGo)
        {
            cout <<"Erreur Get2da('"<<s2DAName<<"',"<<nLineToGo<<","<<nColonneToGo<<") : La ligne n'existe pas"<<endl;
            return "ERROR";
        }
    }

    //On se situe à la bonne ligne, juste après le chiffre de la ligne
    while(nColonneDetected<100)
    {
        //On passe tous les espaces
        while(st2DA.peek()==' ')
            st2DA. seekg(1, ios::cur);

        nColonneDetected++;

        //Si la colonne sur laquelle on arrive NE correspond PAS à celle voulue
        if(nColonneDetected != nColonneToGo)
        {
            //On ignore la chaine de caractère
            while(st2DA.peek()!=' ')
                st2DA. seekg(1, ios::cur);
        }
        //... correspond
        else
        {
            //On retourne la val trouvee
            st2DA>>sCurrent;
            return sCurrent;
        }
    }

    cout <<"Erreur Get2da('"<<s2DAName<<"',"<<nLineToGo<<","<<nColonneToGo<<") : La colonne n'existe pas"<<endl;
    return "ERROR";
}


float GetDistanceBetween(int pPosAx, int pPosAy, int pPosBx, int pPosBy)
{
    int nDeltaHrz = fabs(pPosAx - pPosBx);
    int nDeltaVer = fabs(pPosAy - pPosBy);
    return sqrt(nDeltaHrz*nDeltaHrz + nDeltaVer*nDeltaVer);
}














