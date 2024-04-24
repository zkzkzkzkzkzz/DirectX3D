#include "pch.h"
#include "CTimeMgrScript.h"

#include <Engine/CTimeMgr.h>



#define TIMEMGR CTimeMgr::GetInst()

CTimeMgrScript::CTimeMgrScript()
	: CScript(TIMEMGRSCRIPT)
	, m_DTLock(false)
	, m_DTScale(1.f)
{

}

CTimeMgrScript::~CTimeMgrScript()
{
}

void CTimeMgrScript::begin()
{
	AddScriptParam(SCRIPT_PARAM::INT, "[bool] DeltaTime Lock", &m_DTLock);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "[float] DeltaTime Scale", &m_DTScale);
}

void CTimeMgrScript::tick()
{
	// 만약 ScriptParam에 함수를 호출하는 델리게이트 형식의 버튼이 있다면 매 틱마다 함수를 호출하지 않아도 될 것 같다.
	TIMEMGR->LockDeltaTime(m_DTLock);
	TIMEMGR->SetDTScale(m_DTScale);
}

void CTimeMgrScript::SaveToFile(FILE* _File)
{
}

void CTimeMgrScript::LoadFromFile(FILE* _File)
{
}

#undef TIMEMGR