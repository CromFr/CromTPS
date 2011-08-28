#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

int LoadMap(std::string sMapName);
bool GetIsBlockingVision(int nType);
bool GetIsBlockingWalk(int nType);

bool GetIsCollisionBallWithWorld(struct worldpospx pBall, float fRadius);
bool GetIsCollisionPointWithBall(struct worldpospx pPosPoint, struct worldpospx pPosBall, float fRadius);
bool GetIsCollisionPJWithWorld(struct worldpospx pPosPX);

bool GetIsCoordScreenPxInWorld(sf::Vector2<float>::Vector2<float> vPos);

#endif // WORLD_H_INCLUDED
