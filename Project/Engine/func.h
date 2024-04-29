#pragma once


class CGameObject;
class CAsset;

namespace GamePlayStatic
{
	void SpawnGameObject(CGameObject* _Target, int _LayerIdx);
	void DestroyGameObject(CGameObject* _Target);

	void AddAsset(CAsset* _Asset);

	void DrawDebugRect(const Matrix& _WorldMat, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);
	void DrawDebugRect(Vec3 _vWorldPos, Vec3 _vWorldScale, Vec3 _vWorldRot, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);
		
	void DrawDebugCircle(const Matrix& _WorldMat, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);
	void DrawDebugCircle(Vec3 _vWorldPos, float _fRadius, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);
	
	void DrawDebugCross(Vec3 _vWorldPos, float _fScale, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);

	void Play2DSound(const wstring& _SoundPath, int _Loop, float _Volume, bool _Overlap = true);
	void Play2DBGM(const wstring& _SoundPath, float _Volume);

	//void DrawDebugCube();
	//void DrawDebugSphere();
}

namespace Utils
{
	/// <summary>
	/// 경로의 모든 파일의 확장자를 포함한 파일 이름을 추출해줍니다. 하위 폴더도 포함됩니다.
	/// </summary>
	void LoadAllFileNames(const wstring& _path, vector<string>& vec);

	/// <summary>
	/// 경로의 모든 파일의 경로를 추출해줍니다. 하위폴더도 포함됩니다.
	/// </summary>
	void LoadAllFilePaths(const wstring& _path, vector<string>& vec);
	/// <summary>
	/// 경로를 갖고 있는 파일들을 경로를 제외하고 추출해줍니다. 해당 경로를 갖고있지 않는다면 제외시킵니다.
	/// </summary>
	void SlicePath(const wstring& _path, vector<string>& vec);
}

string ToString(const wstring& _str);
wstring ToWString(const string& _str);
string ToString(const std::string_view& _sv);
wstring ToWString(const std::string_view& _sv);

void SaveWString(const wstring& _str, FILE* _File);
void LoadWString(wstring& _str, FILE* _FILE);


template<typename T>
class Ptr;

#include "CAssetMgr.h"

template<typename T>
void SaveAssetRef(Ptr<T> _Asset, FILE* _File)
{
	bool bAssetExist = false;
	_Asset == nullptr ? bAssetExist = false : bAssetExist = true;
	
	fwrite(&bAssetExist, sizeof(bool), 1, _File);

	if (bAssetExist)
	{
		SaveWString(_Asset->GetKey(), _File);
		SaveWString(_Asset->GetRelativePath(), _File);
	}
}

template<typename T>
void SaveAssetRef(Ptr<T> _Asset, ofstream& fout)
{
	fout << "[Asset Exist]" << endl;
	bool bAssetExist = false;
	_Asset == nullptr ? bAssetExist = false : bAssetExist = true;

	fout << bAssetExist << endl;

	if (bAssetExist)
	{
		fout << "[Key]" << endl;
		fout << ToString(_Asset->GetKey()) << endl;
		fout << "[Path]" << endl;
		fout << ToString(_Asset->GetRelativePath()) << endl;
	}
}

template<typename T>
void LoadAssetRef(Ptr<T>& _Asset, FILE* _File)
{	
	bool bAssetExist = false;
	fread(&bAssetExist, sizeof(bool), 1, _File);

	if (bAssetExist)
	{
		wstring strKey, strRelativePath;

		LoadWString(strKey, _File);
		LoadWString(strRelativePath, _File);

		_Asset = CAssetMgr::GetInst()->Load<T>(strKey, strRelativePath);
	}
}

template<typename T>
void LoadAssetRef(Ptr<T>& _Asset, ifstream& fin)
{
	string tag, str;

	bool exist;
	getline(fin, tag); // [Asset Exist]
	fin >> exist;
	getline(fin, str); // 공백 처리

	if (exist) 
	{
		string key, path;
		getline(fin, tag); // [Key]
		getline(fin, key);

		getline(fin, tag); // [Path]
		getline(fin, path);

		_Asset = CAssetMgr::GetInst()->Load<T>(key, path);
	}
}

template<typename T, UINT SIZE>
void Delete_Array(T* (&Arr)[SIZE])
{
	for (int i = i = 0; i < SIZE; ++i)
	{
		if (nullptr != Arr[i])
		{
			delete Arr[i];
			Arr[i] = nullptr;
		}
	}
}


template<typename T>
void Delete_Vec(vector<T*>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}

	_vec.clear();
}

template<typename T1, typename T2>
void Delete_Map(map<T1, T2>& _map)
{
	for (const auto& pair : _map)
	{
		delete pair.second;
	}
	_map.clear();
}

