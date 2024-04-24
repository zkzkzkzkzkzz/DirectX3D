#pragma once

#include <fstream>
using std::ofstream;

extern vector<wstring> g_vecScriptNames;


void ScriptNameInput();
void MakeScriptMgrHeader();
void MakeScriptMgrCPP();

void MakeStrHeaderFX();