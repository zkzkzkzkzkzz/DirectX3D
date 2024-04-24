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

	return 0;
}