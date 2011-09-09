#ifndef GIF_H_INCLUDED
#define GIF_H_INCLUDED



struct GifFrame
{
    sf::Image img;
    sf::Sprite spr;
    float time;
};

struct GifTemplate
{
    std::vector<GifFrame> frames;
    bool boucler;
    bool smooth;
};


///Pour chaque gif :
///Lit dans le fichier de config (sGifName.cfg) les proprietes du gif:
///  sExtensionDesImages|bBoucler|nFrames|fTpsFrame0|fTpsFrame1|fTpsFrame2...
///
///Les images doivent être nommées ainsi: sGifName+nFrameID+"."+sExtensionDesImages
void LoadAllGifs();
void UnloadAllGifs();

struct GifTemplate* LoadGif(std::string sName);




class Gif
{
    public:
    ///Constructeur
    ///Créé un gif animé qui commencera à la date d'éxécution
    Gif(struct GifTemplate *Template, sf::Vector2<float>::Vector2<float> pPosition, float fFacing=0);

    ///Renvoie 0 si le gif est terminé et n'a pas été affiché (si il n'est pas bouclé)
    ///Si le gif est terminé, ça le désactivera (m_bActive=0)
    bool Draw();

    ///Renvoie un pointeur vers le sprite correspondant à la frame actuelle
    /// Le pointeur est nul si l'animation est terminee
    /// Possibilité de mettre l'adresse d'un int pour récupèrer dedans l'ID de la frame
    sf::Sprite *GetCurrentFrameSprite(int* nSetID=0) const;



    void SetPosition(sf::Vector2<float>::Vector2<float> pNewPosition);
    void SetFacing(float fNewFacing);

    sf::Vector2<float>::Vector2<float> GetPosition()const;
    float GetFacing()const;

    bool GetIsActive()const;


    private:

    ///Renvoie la date relative du gif (Date depuis la dernière occurence de la frame 0)
    float GetRelativeDate()const;

    ///Renvoie l'ID de la frame actuelle
    int GetCurrentFrameID()const;

    ///Applique un effet de fondu entre les deux frames
    void SmoothFrames(sf::Sprite *sprFrame0, sf::Sprite *sprFrame1, int nIDFrame);

    ///Presque identique a GetCurrentFrameSprite
    /// Renvoie pointeur nul si pas de prochaine frame
    /// Note : Si nCurID n'est pas renseigné, relance du calcul pour trouver la frame actuelle
    sf::Sprite *GetNextFrameSprite(int nCurID=-1);



    ///Pointeur vers le template associé
    struct GifTemplate *m_Template;

    ///Dates de fins de frames calculées en cumulant tous les délais des images (indépendant de fDateFirstFrame)
    std::vector<float> m_fRelativesDates;

    ///Date de création du gif
    float m_fDateFirstFrame;

    ///Position sur l'écran du centre du gif
    sf::Vector2<float>::Vector2<float> m_pPosition;

    ///rotation du gif
    float m_fFacing;

    ///true si doit s'afficher, false si l'animation est terminée
    bool m_bActive;

};


class GifHandler
{
    public:
    ~GifHandler();

    ///Dessine tous les gifs en cours sur l'écran, et supprime ceux qui sont terminés
    void Draw();

    ///Ajoute un gif au gestionnaire
    void AddGif(struct GifTemplate *Template, sf::Vector2<float>::Vector2<float> pPosition, float fFacing=0);


    ///Supprime tous les gifs
    void Clear();


    private:
    std::vector<Gif*> m_pGifList;
};


#endif // GIF_H_INCLUDED
