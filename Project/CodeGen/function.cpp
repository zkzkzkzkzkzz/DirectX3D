#include "pch.h"
#include "function.h"

#include "PathMgr.h"

vector<wstring> g_vecScriptNames;

void ScriptNameInput()
{
	wstring solPath = CPathMgr::GetSolutionPath();
	wstring filterPath = solPath + L"Scripts\\Scripts.vcxproj.filters";

	wifstream fin;
	fin.open(filterPath);
	wstring line;
	wstring header;
	bool isheader = false;
	while (getline(fin, line))
	{
		if (line.find(L".cpp") != string::npos) {
			isheader = false;
			continue;
		}

		if (line.find(L".h") != string::npos) {
			int start = line.find(L"\"");
			int end = line.find(L".");

			header = line.substr(start + 1, end - start - 1);
			isheader = true;
		}

		if (line.find(L"<Filter>Scripts") != string::npos) {
			if (isheader) {
				g_vecScriptNames.push_back(header);
			}
		}
	}
}

void MakeScriptMgrHeader()
{
	wstring solPath = CPathMgr::GetSolutionPath();
	wstring Path = solPath + L"Scripts\\CScriptMgr.h";
	wfstream fout;
	fout.open(Path, ofstream::out | ofstream::trunc);
	if (!fout.is_open()) return;


	fout << L"#pragma once" << endl << endl;
	fout << L"#include <vector>" << endl;
	fout << L"#include <string>" << endl << endl;

	fout << L"enum class SCRIPT_TYPE" << endl << L"{" << endl;

	for (UINT i = 0; i < g_vecScriptNames.size(); ++i)
	{
		wstring strScriptUpperName = L"";
		for (UINT j = 1; j < g_vecScriptNames[i].size(); ++j)
		{
			strScriptUpperName += toupper(g_vecScriptNames[i][j]);
		}

		fout << L"\t" << strScriptUpperName << L"," << endl;
	}
	fout << L"\tEND," << endl;
	fout << L"};" << endl << endl;

	fout << L"using namespace std;" << endl << endl;
	fout << L"class CScript;" << endl << endl;
	fout << L"class CScriptMgr" << endl << L"{" << endl;
	fout << L"public: " << endl;
	fout << L"\tstatic void GetScriptInfo(vector<wstring>& _vec);" << endl;
	fout << L"\tstatic CScript* GetScript(const wstring& _strScriptName);" << endl;
	fout << L"\tstatic CScript* GetScript(UINT _iScriptType);" << endl;
	fout << L"\tstatic const wchar_t* GetScriptName(CScript* _pScript);" << endl << L"};" << endl;
}

void MakeScriptMgrCPP()
{
}
