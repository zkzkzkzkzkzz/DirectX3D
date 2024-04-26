#include "pch.h"

ofstream& operator<<(ofstream& fout, const tLightInfo& info)
{
	fout << "[LightType]" << endl;
	auto str = magic_enum::enum_name((LIGHT_TYPE)info.LightType);
	fout << ToString(str) << endl;

	fout << "[LightColor]" << endl;
	fout << info.vColor << endl;

	fout << "[Specular]" << endl;
	fout << info.vSpecular << endl;

	fout << "[Ambient]" << endl;
	fout << info.vAmbient << endl;

	fout << "[WorldPos]" << endl;
	fout << info.vWorldPos << endl;

	fout << "[WorldDir]" << endl;
	fout << info.vWorldDir << endl;

	fout << "[Radius]" << endl;
	fout << info.fRadius << endl;

	fout << "[Angle]" << endl;
	fout << info.fAngle;

    return fout;
}
