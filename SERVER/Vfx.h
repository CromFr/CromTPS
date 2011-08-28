#ifndef VFXHANDLER_H_INCLUDED
#define VFXHANDLER_H_INCLUDED

//VFX
#define VFX_TYPE_INVALID 0
#define VFX_TYPE_ALL 1
#define VFX_TYPE_RAY 2
#define VFX_TYPE_EXPLOSION 3
#define VFX_TYPE_BLOOD 4

#define VFX_RAY_DIM_PX 3
#define VFX_RAY_IMPACT_DIM_PX 30


struct vfxray
{
    int type;
    struct worldpospx dep;
    struct worldpospx fin;
    float dateout;
    bool impact;
};
struct vfxexplosion
{
    struct worldpospx pos;
    float fadetime;
    float dateout;
    float postvfxfadetime;
    float postvfxdateout;
};
struct vfxblood
{
    struct worldpospx pos;
    int type;
    float dateout;
};

class Vfx
{
    public:
    //Vfx();
    //~Vfx();

    //===================================================

    void AddRay(int nDamageType, struct worldpospx pRayStart, struct worldpospx pRayEnd, bool bImpact=true, float fTimeoutms=0.05);
    void AddExlplosion(struct worldpospx pPosition, float fFadeTime=1.5, float fPostVfxFadeTime=15.0);
    void AddBlood(struct worldpospx pPosition, float fTimeout=6.0);

    void Clear(int nType=VFX_TYPE_ALL);

    void Draw(int nType=VFX_TYPE_ALL);

    //===================================================
    private:
    void BlitRay(struct worldpospx pPosDepart, struct worldpospx pPosArrivee, bool bImpact, int nDamageType);
    void BlitExplosion(struct worldpospx pPosition, bool bExplosion, int nAlphaExplosion, bool bPostEffect, int nAlphaPostEffect);
    void BlitBlood(struct worldpospx pPosition, int nType);

    std::vector<struct vfxray> vfxRaysList;
    std::vector<struct vfxexplosion> vfxExplosionsList;
    std::vector<struct vfxblood> vfxBloodsList;
};

#endif // VFXHANDLER_H_INCLUDED
