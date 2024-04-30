#include "pch.h"
#include "CRenderMgrScript.h"

#include <Engine/CRenderMgr.h>

#define RENDERMGR CRenderMgr::GetInst()

CRenderMgrScript::CRenderMgrScript()
	: CScript((UINT)SCRIPT_TYPE::RENDERMGRSCRIPT)
{
}

CRenderMgrScript::~CRenderMgrScript()
{
}


void CRenderMgrScript::begin()
{
	AddScriptParam(SCRIPT_PARAM::COLOR, "Clear Color", &(RENDERMGR->m_vClearColor) );
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

