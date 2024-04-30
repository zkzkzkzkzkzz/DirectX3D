#pragma once

#include <vector>
class CGameObject;
class CAsset;
#include <Magic_Enum/magic_enum_all.hpp>

string ToString(const wstring& _str);
wstring ToWString(const string& _str);
string ToString(const std::string_view& _sv);
wstring ToWString(const std::string_view& _sv);

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

	void DrawDebugCube(const Matrix& _WorldMat, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);
	void DrawDebugCube(Vec3 _vWorldPos, Vec3 _vWorldScale, Vec3 _vWorldRot, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);

	void DrawDebugSphere(Vec3 _vWorldPos, float _fRadius, Vec3 _Color, bool _bDepthTest, float _Duration = 0.f);

}


	
	class COLOR
	{
		// 유지보수 1/4 .Enum추가
		enum class DEFAULT_COLOR
		{
			WHITE,
			BLACK,
			RED,
			GREEN,
			BLUE,
			YELLOW,
			MAZENTA,
			END,
		};

		// 유지보수 2/4 . 컬러변수 추가
		static const Vec4 WHITE;
		static const Vec4 BLACK;
		static const Vec4 RED;
		static const Vec4 GREEN;
		static const Vec4 BLUE;
		static const Vec4 YELLOW;
		static const Vec4 MAZENTA;

	public:
		// 유지보수 3/4 . 컬러변수 맵핑
		static vector<std::pair<string, Vec4>> GetColors()
		{
			return
			{
				{ToString(magic_enum::enum_name(DEFAULT_COLOR::WHITE))	   , WHITE    }
				, {ToString(magic_enum::enum_name(DEFAULT_COLOR::BLACK))   , BLACK    }
				, {ToString(magic_enum::enum_name(DEFAULT_COLOR::RED))	   , RED      }
				, {ToString(magic_enum::enum_name(DEFAULT_COLOR::GREEN))   , GREEN    }
				, {ToString(magic_enum::enum_name(DEFAULT_COLOR::YELLOW))  , YELLOW   }
				, {ToString(magic_enum::enum_name(DEFAULT_COLOR::MAZENTA)) , MAZENTA  }
			};
		}
	};
}

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

