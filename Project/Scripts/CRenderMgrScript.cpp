#include "pch.h"
#include "CRenderMgrScript.h"

#include <Engine/CRenderMgr.h>

#define RENDERMGR CRenderMgr::GetInst()

LerpFloatFuncPtr lerpFloatFunc = RoRMath::Lerp;

CRenderMgrScript::CRenderMgrScript()
	: CScript((UINT)SCRIPT_TYPE::RENDERMGRSCRIPT)
{
	TAppendScriptParam("LerpFloat", SCRIPT_PARAM::FUNC_LERP, FUNC_PARAM::FLOAT, &lerpFloatFunc, 1.0f, 2.0f, 0.5f);
}

CRenderMgrScript::~CRenderMgrScript()
{
}


void CRenderMgrScript::begin()
{
	AppendScriptParam("Clear Color", SCRIPT_PARAM::COLOR, &(RENDERMGR->m_vClearColor));
}

void CRenderMgrScript::tick()
{
}

void CRenderMgrScript::SaveToFile(FILE* _File)
{
}

void CRenderMgrScript::LoadFromFile(FILE* _File)
{
}

