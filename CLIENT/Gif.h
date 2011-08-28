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
    Gif(struct GifTemplate *Template, sf::Vector2<float>::Vector2<float> pPosition, bool bAddToHandler=true);
    Gif(struct GifTemplate *Template, sf::Vector2<float>::Vector2<float> pPosition, float fFacing, bool bAddToHandler=true);

    ///Renvoie 0 si le gif est terminé et n'a pas été affiché (si il n'est pas bouclé)
    bool Draw() const;

    ///Renvoie un pointeur vers le sprite correspondant à la frame actuelle
    /// Le pointeur est nul si l'animation est terminee
    sf::Sprite *GetCurrentFrameSprite() const;

    void SetPosition(sf::Vector2<float>::Vector2<float> pNewPosition);
    void SetFacing(float fNewFacing);

    sf::Vector2<float>::Vector2<float> GetPosition()const;
    float GetFacing()const;


    private:
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

};


class GifHandler
{
    public:
    GifHandler();


    private:


};


#endif // GIF_H_INCLUDED
