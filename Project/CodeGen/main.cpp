#include "pch.h"
#include "PathMgr.h"

#include "function.h"
vector<wstring> g_vecName;

int main()
{
	CPathMgr::init();

	// 스크립트 매니저 생성
	ScriptNameInput();
	MakeScriptMgrHeader();
	MakeScriptMgrCPP();

	GetAllContents();

	MakeStrHeader("Project\\Scripts\\strLevel.h", "LEVEL", g_vecLevelNames);
	MakeStrHeader("Project\\Scripts\\strFx.h", "FX", g_vecFxNames);
	MakeStrHeader("Project\\Scripts\\strSnd.h", "SND", g_vecSndNames);
	MakeStrHeader("Project\\Scripts\\strTex.h", "TEX", g_vecTexNames);
	MakeStrHeader("Project\\Scripts\\strMtrl.h", "MTRL", g_vecMtrlNames);
	MakeStrHeader("Project\\Scripts\\strPref.h", "PREF", g_vecPrefNames);
	MakeStrHeader("Project\\Scripts\\strAnim.h", "ANIM", g_vecAnimNames);
	MakeStrHeader("Project\\Scripts\\strTxt.h", "TXT", g_vecTxtNames);

	return 0;
}