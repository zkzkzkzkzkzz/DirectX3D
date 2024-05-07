#include "pch.h"
#include "CRenderMgrScript.h"

#include <Engine/CRenderMgr.h>

#define RENDERMGR CRenderMgr::GetInst()

LerpFloatFuncPtr lerpFloatFunc = RoRMath::Lerp;
TestPram CRenderMgrScript::m_TestParam = {};

CRenderMgrScript::CRenderMgrScript()
	: CScript((UINT)SCRIPT_TYPE::RENDERMGRSCRIPT)
{
	AppendScriptFunction("LerpFloat", SCRIPT_PARAM::FUNC_STATIC, "Lerp", &CRenderMgrScript::LerpTest);

	AppendScriptParam("From", SCRIPT_PARAM::FLOAT, &m_TestParam.T1);
	AppendScriptParam("To", SCRIPT_PARAM::FLOAT, &m_TestParam.T2);
	AppendScriptParam("Alpha", SCRIPT_PARAM::FLOAT, &m_TestParam.T3);
	AppendScriptParam("Res", SCRIPT_PARAM::FLOAT, &m_TestParam.result);
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

