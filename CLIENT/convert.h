#ifndef CONVERT_H_INCLUDED
#define CONVERT_H_INCLUDED

//Dépend de FSML : Type Vector2
//Dépend de main.h : constantes

//Renvoie la coord en cubes correspondant à l'endroit indiqué par vCoordScreen
struct worldposblock CoordScreenPxToWorldBlocks(sf::Vector2<float>::Vector2<float> vCoordScreen);

//Renvoie la coord en PX par rapport à oWindow d'un cube (coin haut gauche)
sf::Vector2<float>::Vector2<float> CoordWorldBlocksToScreenPx(struct worldposblock CoordWorldBlock, bool bCenter=0);

//Renvoie la coord en px dans le world par rapport à un pixel dans la fenêtre
struct worldpospx CoordScreenPxToWorldPx(sf::Vector2<float>::Vector2<float> vCoordScreenPx);

sf::Vector2<float>::Vector2<float> CoordWorldPxToScreenPx(struct worldpospx CoordWorldPx);

struct worldposblock CoordWorldPxToWorldBlocks(struct worldpospx vCoordWorldPx);

struct worldpospx CoordWorldBlocksToWorldPx(struct worldposblock CoordWorldBlock, bool bCenter=0);

#endif // CONVERT_H_INCLUDED
