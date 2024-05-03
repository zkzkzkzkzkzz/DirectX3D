#include "pch.h"
#include "CLight3D.h"

#include "CRenderMgr.h"
#include "CTransform.h"

CLight3D::CLight3D()
	: CComponent(COMPONENT_TYPE::LIGHT3D)
{
}

CLight3D::~CLight3D()
{
}


void CLight3D::finaltick()
{
	m_Info.vWorldDir = Transform()->GetWorldDir(DIR_TYPE::FRONT);
	m_Info.vWorldPos = Transform()->GetWorldPos();

	CRenderMgr::GetInst()->RegisterLight3D(this);

	// 현재 광원의 위치에 DebugRender 요청
	if (m_Info.LightType == (int)LIGHT_TYPE::POINT)
	{
		GamePlayStatic::DrawDebugSphere(m_Info.vWorldPos, m_Info.fRadius, Vec3(0.f, 1.f, 0.1f), true);
		//GamePlayStatic::DrawDebugCube(m_Info.vWorldPos, Vec3(m_Info.fRadius, m_Info.fRadius, m_Info.fRadius), Vec3(0.f, 0.f, 0.f),   Vec3(0.f, 1.f, 0.1f), true);
	}
}

void CLight3D::SetLightType(LIGHT_TYPE _type)
{
	m_Info.LightType = (int)_type;
}


void CLight3D::SaveToFile(FILE* _File)
{
	fwrite(&m_Info, sizeof(tLightInfo), 1, _File);
}

void CLight3D::SaveToFile(ofstream& fout)
{
	fout << m_Info << endl;
}

void CLight3D::LoadFromFile(FILE* _File)
{
	fread(&m_Info, sizeof(tLightInfo), 1, _File);
}

void CLight3D::LoadFromFile(ifstream& fin)
{
	fin >> m_Info;
}
