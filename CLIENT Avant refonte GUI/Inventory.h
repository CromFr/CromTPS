#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED


#include "Items.h"

class Inventory
{
    public:
    ///Créé un inventaire par défaut (arme=pistolet, armure=ø...)
    Inventory();

    ///Supprime tous les items de l'inventaire, en supprimant les items puis reset des pointeurs
    ~Inventory();


    //===================================================

    ///Créé un item correspondant au template dans l'inventaire
    ///Renvoie l'adresse de l'item créé
    Item::Item* AddItem(struct itTemplate Template);

    ///Supprime nStack items correspondant au template et était dans l'inventaire
    void DelItemByTemplate(struct itTemplate Template, int nStack=1);

    ///Supprime UN item correspondant à l'adresse donnée.
    ///Regarde si l'item est dans l'inventaire avant de le supprimer
    void DelItem(Item::Item* pItem);

    ///Compte le nb d'items correspondant au template dans l'inventaire
    int GetItemStack(struct itTemplate Template) const;

    ///Renvoie la position de l'item dans l'inventaire, -1 si l'item n'a pas été trouvé
    int GetItemRowInInventory(const Item::Item* pItem)const;

    ///Equippe l'item si celui ci est equippable
    bool EquipItem(Item::Item* pItemToEquip);

    ///Renvoie l'adresse de l'item qui est equippé à tel endroit
    Item::Item* GetEquipedItem(int nEquipmentPart) const;

    ///Renvoie l'adresse du 1er item de l'inventaire correspondant au template
    Item::Item* GetFirstItem(struct itTemplate Template) const;

    ///Vide l'inventaire en supprimant les items à l'interieur
    void Empty();

    ///Liste sur la console la liste des items de l'inventaire
    void Display() const;

    ///Ouvre l'écran d'inventaire du joueur
    void OpenInventory();

    //===================================================
    private:

    ///Il faut IMPERATIVEMENT linker l'item à un inventaire, sinon il y a fuite de mémoire
    ///=====> LinkItem(CreateItem(struct itTemplate Template));
    Item::Item* CreateItem(struct itTemplate Template) const;

    ///Lie l'item à l'inventaire et place son pointeur dans la 1ere case vide.
    ///Attention : N'enlève pas les autres liens déja en place
    ///            A la suppr de l'inventaire, les items sont supprimés !
    void LinkItem(Item::Item* pItem);


    std::vector<Item::Item*> m_pItemList;

    Item::Item *m_pWeaponEquipped;
    Item::Item *m_pArmorEquipped;

};








#endif // INVENTORY_H_INCLUDED
