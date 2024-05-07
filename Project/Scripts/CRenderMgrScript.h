#pragma once
#include <Engine/CScript.h>

typedef float(*LerpFloatFuncPtr)(float, float, float);

class CRenderMgrScript :
    public CScript
{
private:


public:
	virtual void begin() override;
	virtual void tick() override;

	virtual void SaveToFile(FILE* _File) override;
	virtual void LoadFromFile(FILE* _File) override;

public:
	CLONE_DISABLE(CRenderMgrScript);
	CRenderMgrScript();
	~CRenderMgrScript();
};
