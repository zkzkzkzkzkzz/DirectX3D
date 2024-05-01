#pragma once
#include "CEntity.h"

class CMRT :
    public CEntity
{
private:
    Ptr<CTexture>   m_arrRTTex[8];
    Ptr<CTexture>   m_DSTex;

public:
    void Create(Ptr<CTexture>* _pArrTex, int _RTCount, Ptr<CTexture> _DSTex);
    void OMSet();

    CLONE_DISABLE(CMRT);
public:
    CMRT();
    ~CMRT();
};

