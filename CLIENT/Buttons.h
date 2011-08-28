#ifndef BUTTONHANDLER_H_INCLUDED
#define BUTTONHANDLER_H_INCLUDED

#define _BUTTON_WIDTH 200
#define _BUTTON_HEIGHT 60

class Button
{
    public://=======================================
    ///Les skins sont définis ici !
    Button(int nPosX, int nPosY, std::string sText, int nID, int nSkin=0);

    ///Change le mode du bouton : 0=inactive, 1=active, 2=pressed
    void SetMode(int nMode);

    ///Dessine le bouton sur l'écran
    void DrawButton();

    ///Retourne l'ID du bouton
    int GetID()const;

    ///Délimitation du bouton
    ///Sa position étant (GetXMin, GetYMin)
    int GetXMin()const;
    int GetXMax()const;
    int GetYMin()const;
    int GetYMax()const;

    private://=======================================
    sf::Sprite* sprDefault;
    sf::Sprite* sprOnMouseOver;
    sf::Sprite* sprOnClick;

    int m_nID;
    int m_nPosX;
    int m_nPosY;

    sf::String m_sText;

    int m_nMode;
};

class ButtonHandler
{
    public://=======================================
    ButtonHandler();

    ///Supprime les boutons à la destruction
    ~ButtonHandler();

    ///Modifie l'état des boutons en fonction de l'event
    ///En cas de clic sur un bouton, retourne l'ID de celui ci
    int OnEvent(sf::Event eEvent);

    ///Ajoute un bouton à la liste
    ///l'ID doit etre superieure à 0 (strict)
    void AddButton(int nPosCenterX, int nPosCenterY, std::string sText, int nID, int nSkin=0);

    ///Dessine les boutons
    void DrawButtons() const;

    private://=======================================
    std::vector<Button::Button*> m_pListeButton;

    bool GetIsOnButton(sf::Vector2<float>::Vector2<float> vMouse, Button::Button* pButton);
};


#endif // BUTTONHANDLER_H_INCLUDED
