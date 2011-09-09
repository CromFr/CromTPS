#include <stdlib.h>
#include <stdio.h>
#include <vector>//Pour les tableaux dynamiques

#include "main.h"
#include "Inventory.h"
#include "Buttons.h"
#include "guifunc.h"


Inventory::Inventory()
{
    //Mise à 0 des pointeurs d'equippement
    Inventory::m_pWeaponEquipped=0;
    Inventory::m_pArmorEquipped=0;

    //Puis du sac
    int nSize = Inventory::m_pItemList.size();
    for(int n(0) ; n<nSize ; n++)
        Inventory::m_pItemList[n]=0;


    //Création & equippement des items par défaut
    Item::Item* pItem = Inventory::AddItem(MakeItemTemplate(ITEM_TYPE_WEAPON, WEAPON_TYPE_BULLET_PISTOL));
    Inventory::EquipItem(pItem);

    pItem = Inventory::AddItem(MakeItemTemplate(ITEM_TYPE_ARMOR, ARMOR_TYPE_NAKED));
    Inventory::EquipItem(pItem);
}
//====================================================================================================================================
Inventory::~Inventory()
{
    //Suppression des items équipés
    if(m_pWeaponEquipped!=0)
    {
        delete Inventory::m_pWeaponEquipped;
        Inventory::m_pWeaponEquipped=0;
    }
    if(m_pArmorEquipped!=0)
    {
        delete Inventory::m_pArmorEquipped;
        Inventory::m_pArmorEquipped=0;
    }

    //Suppression des items dans le sac
    int nSize = Inventory::m_pItemList.size();
    for(int n(0) ; n<nSize ; n++)
    {
        if(Inventory::m_pItemList[n]!=0)//Si la case est liée à un item
        {
            //Suppr de l'item associé
            delete Inventory::m_pItemList[n];
            //Mise à 0 du pointeur
            Inventory::m_pItemList[n]=0;
        }
    }
}
//====================================================================================================================================
Item::Item* Inventory::AddItem(struct itTemplate Template)
{
    Item::Item* pItem=0;

    pItem = Inventory::CreateItem(Template);
    Inventory::LinkItem(pItem);

    return pItem;
}
//====================================================================================================================================
//Possibilité de mettre nStack=-1 pour enlever tous les objets de l'inventaire correspondant au type indiqué
void Inventory::DelItemByTemplate(struct itTemplate Template, int nStack)
{
    int n;
    int nItemsTaken=0;
    int nSize = Inventory::m_pItemList.size();

    struct itTemplate CurrTemplate;

    for(n=0 ; nItemsTaken!=nStack && n<nSize ; n++)
    {
        CurrTemplate = Inventory::m_pItemList[n]->GetTemplate();

        if(CurrTemplate == Template)
        {
            delete Inventory::m_pItemList[n];//On suppr l'item
            Inventory::m_pItemList[n] = 0;//On remet le pointeur à 0
            nItemsTaken++;
        }
    }
}
//====================================================================================================================================
void Inventory::DelItem(Item::Item* pItem)
{
    int nRow, nSize = Inventory::m_pItemList.size();
    for(nRow=0 ; 1 ; nRow++)
    {
        if(!(nRow<nSize))//Déportation de la condition du for
        {
            nRow=-1;//On sait ainsi que l'item n'est pas dans cet inventaire
            break;
        }

        //On regarde toutes les adresses dans le tableau, si une correspond à pItem, on note le row
        if(Inventory::m_pItemList[nRow] == pItem)
            break;
    }

    if(nRow!=-1)
    {
        delete pItem;//On suppr l'item
        Inventory::m_pItemList[nRow] = 0;//On remet le pointeur à 0
    }
}
//====================================================================================================================================
int Inventory::GetItemStack(struct itTemplate Template) const
{
    int n;
    int nCount=0;
    int nSize = Inventory::m_pItemList.size();

    struct itTemplate CurrTemplate;

    for(n=0 ; n<nSize ; n++)
    {

        if(CurrTemplate == Template)
        {
            nCount++;
        }
    }
    return nCount;
}
//====================================================================================================================================
int Inventory::GetItemRowInInventory(const Item::Item* pItem)const
{
    int n;
    int nSize = Inventory::m_pItemList.size();

    for(n=0 ; n<nSize ; n++)
    {
        if(Inventory::m_pItemList[n] == pItem)
        {
            return n;
        }
    }
    return -1;
}
//====================================================================================================================================
bool Inventory::EquipItem(Item::Item* pItemToEquip)//true si objet correctement équippé
{
    int nRowItemToEquip = Inventory::GetItemRowInInventory(pItemToEquip);

    if(nRowItemToEquip == -1//Si l'item n'est pas dans l'inventaire
       || pItemToEquip==0)//Si l'item à equipper n'existe pas
    {
        return false;//On stoppe le programme
    }
    else//Si l'item est dans l'inventaire
    {
        //On l'equippe
        struct itTemplate Template = pItemToEquip->GetTemplate();
        switch(Template.type)
        {
            case ITEM_TYPE_WEAPON:
                //On désequippe l'item déja en place :
                //On lie l'item à désequipper à l'inventaire (il y a deux liens)
                Inventory::LinkItem(Inventory::GetEquipedItem(EQUIPMENT_PART_WEAPON));
                //  et on suppr le lien avec le corps (plus qu'un lien)
                Inventory::m_pWeaponEquipped = 0;

                //Puis on équippe l'item en question
                //On lie l'item à equipper au corps (il y a deux liens)
                Inventory::m_pWeaponEquipped = pItemToEquip;
                //   et on suppr le lien avec l'inventaire (plus qu'un lien)
                Inventory::m_pItemList[nRowItemToEquip] = 0;
                return true;
            case ITEM_TYPE_ARMOR:
                //On désequippe l'item déja en place :
                //On lie l'item à désequipper à l'inventaire (il y a deux liens)
                Inventory::LinkItem(Inventory::GetEquipedItem(EQUIPMENT_PART_ARMOR));
                //  et on suppr le lien avec le corps (plus qu'un lien)
                Inventory::m_pArmorEquipped = 0;

                //Puis on équippe l'item en question
                //On lie l'item à equipper au corps (il y a deux liens)
                Inventory::m_pArmorEquipped = pItemToEquip;
                //   et on suppr le lien avec l'inventaire (plus qu'un lien)
                Inventory::m_pItemList[nRowItemToEquip] = 0;
                return true;
        }
    }
    return false;
}
//====================================================================================================================================
Item::Item* Inventory::GetEquipedItem(int nEquipmentPart) const
{
    if(nEquipmentPart == EQUIPMENT_PART_WEAPON)
        return Inventory::m_pWeaponEquipped;
    return Inventory::m_pArmorEquipped;
}
//====================================================================================================================================
Item::Item* Inventory::GetFirstItem(struct itTemplate Template) const
{
    int nSize = Inventory::m_pItemList.size();
    for(int n(0) ; n<nSize ; n++)
    {
        if(Inventory::m_pItemList[n]->GetTemplate() == Template)
        {
            return Inventory::m_pItemList[n];
        }
    }
    return 0;
}
//====================================================================================================================================
void Inventory::Empty()
{
    int n;
    int nSize = Inventory::m_pItemList.size();

    //Suppression des items de la liste
    for(n=0 ; n<nSize ; n++)
    {
        if(Inventory::m_pItemList[n]!=0)
        {
            delete Inventory::m_pItemList[n];//On suppr l'item
            Inventory::m_pItemList[n] = 0;//On remet le pointeur à 0
            //Inventory::DelItem(Inventory::m_pItemList[n]);
        }
    }
    //Réduction de la liste des items
    while(Inventory::m_pItemList.size()>0)
    {
        Inventory::m_pItemList.pop_back();
    }

    //Suppression des items équippés
    if(Inventory::m_pWeaponEquipped!=0)
    {
        delete Inventory::m_pWeaponEquipped;
        Inventory::m_pWeaponEquipped = 0;
    }
    if(Inventory::m_pArmorEquipped!=0)
    {
        delete Inventory::m_pArmorEquipped;
        Inventory::m_pArmorEquipped = 0;
    }

}
//====================================================================================================================================
void Inventory::Display()const
{
    int n;
    int nSize = Inventory::m_pItemList.size();

    std::cout<<"======= Corps ====================="<<std::endl;
    std::cout<<"Arme :"<<std::endl;
    std::cout<<"Adresse="<<Inventory::m_pWeaponEquipped<<std::endl;
    if(Inventory::m_pWeaponEquipped!=0)
        Inventory::m_pWeaponEquipped->Display();
    std::cout<<"--------------------------------"<<std::endl;
    std::cout<<"Armure :"<<std::endl;
    std::cout<<"Adresse="<<Inventory::m_pArmorEquipped<<std::endl;
    if(Inventory::m_pArmorEquipped!=0)
        Inventory::m_pArmorEquipped->Display();

    std::cout<<"======= Sac ======================="<<std::endl;
    for(n=0 ; n<nSize ; n++)
    {
        std::cout<<"Adresse="<<Inventory::m_pItemList[n]<<std::endl;
        if(Inventory::m_pItemList[n]!=0)
            Inventory::m_pItemList[n]->Display();
        std::cout<<"--------------------------------"<<std::endl;
    }
    std::cout<<"==================================="<<std::endl;
}

//====================================================================================================================================
//====================================================================================================================================
//====================================================================================================================================
Item::Item* Inventory::CreateItem(struct itTemplate Template) const
{
    //On créé l'objet et place son adresse dans pItem
    Item::Item* pItem=0;
    switch(Template.type)
    {
        case ITEM_TYPE_WEAPON:
            pItem = new Weapon::Weapon(Template.typetype);
            break;
        case ITEM_TYPE_ARMOR:
            pItem = new Armor::Armor(Template.typetype);
            break;
        case ITEM_TYPE_POTION:
            pItem = new Potion::Potion(Template.typetype);
            break;
        case ITEM_TYPE_PLACEABLEITEM:
            switch(Template.typetype)
            {
                case PLACEABLEITEM_EXPLOSIVE:// TODO (crom#1#): Explosive : Completer
                    //pItem = new Explosive::Explosive(Template.typetypetype);
                    break;
                //...
            }
            break;
        //...
    }
    return pItem;
}
//====================================================================================================================================
void Inventory::LinkItem(Item::Item* pItem)
{
    int n, nEmplacement=-1;
    int nSize = Inventory::m_pItemList.size();

    //Recherche d'un emplacement pour mettre l'adresse de l'item
    for(n=0 ; n<nSize ; n++)
    {
        if(Inventory::m_pItemList[n] == 0)//Si le pointeur n'est pas définit
        {
            nEmplacement = n;
            break;
        }
    }

    //Si aucun emplacement n'a été trouvé
    if(nEmplacement==-1)
    {
        //On rajoute une ligne
        Inventory::m_pItemList.push_back(pItem);
    }
    //Si une case a été trouvée
    else
    {
        Inventory::m_pItemList[nEmplacement] = pItem;
    }

}






