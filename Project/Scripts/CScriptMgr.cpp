#include "pch.h"
#include "CScriptMgr.h"

#include "CBackgroundScript.h"
#include "CMissileScript.h"
#include "CPlayerScript.h"
#include "CMonsterScript.h"
#include "CTimeMgrScript.h"
#include "CRenderMgrScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CTimeMgrScript");
	_vec.push_back(L"CRenderMgrScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBackgroundScript" == _strScriptName)
		return new CBackgroundScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CTimeMgrScript" == _strScriptName)
		return new CTimeMgrScript;
	if (L"CRenderMgrScript" == _strScriptName)
		return new CRenderMgrScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return new CBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::TIMEMGRSCRIPT:
		return new CTimeMgrScript;
		break;
	case (UINT)SCRIPT_TYPE::RENDERMGRSCRIPT:
		return new CRenderMgrScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return L"CBackgroundScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::TIMEMGRSCRIPT:
		return L"CTimeMgrScript";
		break;

	case SCRIPT_TYPE::RENDERMGRSCRIPT:
		return L"CRenderMgrScript";
		break;

	}
	return nullptr;
}