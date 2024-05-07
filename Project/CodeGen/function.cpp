﻿#include "pch.h"
#include "function.h"

#include "PathMgr.h"
#include <filesystem>

vector<wstring> g_vecScriptNames;
vector<string> g_vecFileNames;

vector<string> g_vecLevelNames;
vector<string> g_vecFxNames;
vector<string> g_vecSndNames;
vector<string> g_vecTexNames;
vector<string> g_vecMtrlNames;
vector<string> g_vecPrefNames;
vector<string> g_vecAnimNames;
vector<string> g_vecTxtNames;
#include <iostream>

void ScriptNameInput()
{
	wstring solPath = CPathMgr::GetSolutionPath();
	wstring filterPath = solPath + L"Project\\Scripts\\Scripts.vcxproj.filters";


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
	wstring Path = solPath + L"Project\\Scripts\\CScriptMgr.h";	

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
	wstring solPath = CPathMgr::GetSolutionPath();
	wstring Path = solPath + L"Project\\Scripts\\CScriptMgr.cpp";
	wfstream fout;
	fout.open(Path, ofstream::out | ofstream::trunc);
	if (!fout.is_open()) return;

	// 헤더 입력
	fout << L"#include \"pch.h\"" << endl;
	fout << L"#include \"CScriptMgr.h\"" << endl << endl;

	for (UINT i = 0; i < g_vecScriptNames.size(); ++i)
	{
		fout << L"#include \"" << g_vecScriptNames[i] << L".h\"" << endl;
	}

	// 첫 번째 함수 작성
	fout << L"\nvoid CScriptMgr::GetScriptInfo(vector<wstring>& _vec)" << endl << "{" << endl;

	for (UINT i = 0; i < g_vecScriptNames.size(); ++i)
	{
		fout << L"\t_vec.push_back(L\"" << g_vecScriptNames[i] << L"\");" << endl;
	}
	fout << L"}" << endl << endl;

	// 두번째 함수 작성
	fout << L"CScript * CScriptMgr::GetScript(const wstring& _strScriptName)" << endl << "{" << endl;

	for (UINT i = 0; i < g_vecScriptNames.size(); ++i)
	{
		fout << L"\tif (L\"" << g_vecScriptNames[i] << L"\" == _strScriptName)" << endl;
		fout << L"\t\treturn new " << g_vecScriptNames[i] << L";" << endl;
	}
	fout << L"\treturn nullptr;" << endl << "}" << endl << endl;

	// 세번째 함수
	fout << L"CScript * CScriptMgr::GetScript(UINT _iScriptType)" << endl << "{" << endl;

	fout << L"\tswitch (_iScriptType)" << endl << "\t{" << endl;
	for (UINT i = 0; i < g_vecScriptNames.size(); ++i)
	{
		wstring strScriptUpperName = L"";
		for (UINT j = 1; j < g_vecScriptNames[i].size(); ++j)
		{
			strScriptUpperName += toupper(g_vecScriptNames[i][j]);
		}
		fout << L"\tcase (UINT)SCRIPT_TYPE::" << strScriptUpperName << L":" << endl;
		fout << L"\t\treturn new " << g_vecScriptNames[i] << L";" << endl;
		fout << L"\t\tbreak;" << endl;
	}
	fout << L"\t}\n\treturn nullptr;" << endl << "}" << endl << endl;

	// 네번째 함수
	fout << L"const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)" << endl << "{" << endl;
	fout << L"\tswitch ((SCRIPT_TYPE)_pScript->GetScriptType())" << endl << "\t{" << endl;
	for (UINT i = 0; i < g_vecScriptNames.size(); ++i)
	{
		fout << L"\tcase SCRIPT_TYPE::";

		wstring strScriptUpperName = L"";
		for (UINT j = 1; j < g_vecScriptNames[i].size(); ++j)
		{
			strScriptUpperName += toupper(g_vecScriptNames[i][j]);
		}
		fout << strScriptUpperName;
		fout << L":" << endl << "\t\treturn " << L"L\"" << g_vecScriptNames[i];
		fout << L"\";" << endl << "\t\tbreak;" << endl << endl;
	}
	fout << L"\t}" << endl << "\treturn nullptr;" << endl << "}";
}

void GetAllContents()
{
	wstring solPath = CPathMgr::GetSolutionPath();
	wstring path = solPath + L"OutputFile\\content";
	FindAllFiles(path);

}

void FindAllFiles(const wstring& path)
{
	namespace fs = filesystem;
	wstring solPath = CPathMgr::GetSolutionPath();
	wstring subpath = solPath + L"..\\OutputFile\\content";
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.is_directory()) {
			int a = 0;
			
			FindAllFiles(entry.path().wstring());
		}
		else {
			string str = entry.path().string();
			str = str.substr(str.find("content") +8);
			g_vecFileNames.push_back(str);

			SortExtention(str, entry.path().extension().string());

		}
	}
}

void SortExtention(const string& path, const string& extention)
{
	if (extention == ".lv") {
		g_vecLevelNames.push_back(path);
	}
	else if (extention == ".fx") {
		g_vecFxNames.push_back(path);
	}
	else if (extention == ".wav" || extention == ".ogg") {
		g_vecSndNames.push_back(path);
	}
	else if (extention == ".png" || extention == ".bmp" || extention == ".jpg" || extention == ".tga" || extention == ".dds") {
		g_vecTexNames.push_back(path);
	}
	else if (extention == ".mtrl") {
		g_vecMtrlNames.push_back(path);
	}
	else if (extention == ".pref") {
		g_vecPrefNames.push_back(path);
	}
	else if (extention == ".anim") {
		g_vecAnimNames.push_back(path);
	}
	else if (extention == ".txt") {
		g_vecTxtNames.push_back(path);
	}
	else {
		MessageBox(nullptr, wstring(extention.begin(), extention.end()).c_str(), L"없는 자료형", 0);
	}

	return;
}

void MakeStrHeader(const string& path, const string& symbol, const vector<string>& vec)
{
	wstring solPath = CPathMgr::GetSolutionPath();
	string Path = string(solPath.begin(), solPath.end()) + path;

	fstream fout;

	fout.open(Path, ofstream::out | ofstream::trunc);
	if (!fout.is_open()) return;

	fout << "#pragma once" << endl << endl;
	for (int i = 0; i < vec.size(); i++) {
		std::string path = vec[i];
		std::string filename = path.substr(path.find_last_of('\\') + 1);
		std::string basename = filename.substr(0, filename.find_last_of('.'));

		fout << "#define ";
		fout << symbol;
		fout << basename;
		fout << " L\"";
		for (int j = 0; j < vec[i].size(); j++) {
			if (vec[i][j] == '\\') {
				fout << "\\\\";
			}
			else {
				fout << vec[i][j];
			}
		}
		fout << "\"";
		fout << endl;
	}
}

void MakeStrHeaderFX()
{
	wstring solPath = CPathMgr::GetSolutionPath();
	string Path = string(solPath.begin(), solPath.end()) + "Scripts\\strFx.h";
	fstream fout;
	fout.open(Path, ofstream::out | ofstream::trunc);
	if (!fout.is_open()) return;

	fout << "#pragma once" << endl << endl;
	for (int i = 0; i < g_vecFxNames.size(); i++) {
		std::string path = g_vecFxNames[i];
		std::string filename = path.substr(path.find_last_of('\\') + 1);
		std::string basename = filename.substr(0, filename.find_last_of('.'));

		fout << "#define FX";
		fout << basename;
		fout << " L\"";
		for (int j = 0; j < g_vecFxNames[i].size(); j++) {
			if (g_vecFxNames[i][j] == '\\') {
				fout << "\\\\";
			}
			else {
				fout << g_vecFxNames[i][j];
			}
		}
		//fout << g_vecFxNames[i];
		fout << "\"";
		fout << endl;
	}
}