﻿#include "pch.h"
#include "CCollider2D.h"

#include "CTransform.h"
#include "CScript.h"

CCollider2D::CCollider2D()
	: CComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_CollisionCount(0)
	, m_bAbsolute(false)
	, m_Type(COLLIDER2D_TYPE::RECT)
	, m_bDebug(false)
{
}

CCollider2D::CCollider2D(const CCollider2D& _OriginCollider2D)
	: CComponent(_OriginCollider2D)
	, m_vOffsetPos(_OriginCollider2D.m_vOffsetPos)
	, m_vOffsetScale(_OriginCollider2D.m_vOffsetScale)
	, m_CollisionCount(0)
	, m_bAbsolute(_OriginCollider2D.m_bAbsolute)
	, m_Type(_OriginCollider2D.m_Type)
	, m_bDebug(_OriginCollider2D.m_bDebug)
{
}

CCollider2D::~CCollider2D()
{
}

void CCollider2D::finaltick()
{
	// 충돌체의 로컬 행렬 계산
	m_matColWorld = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
	m_matColWorld *= XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);

	// 충돌체에 적용시킬 GameObject 의 월드행렬
	const Matrix& matObjWorld = Transform()->GetWorldMat();

	// GameObject 의 Scale 에 영향을 받지 않으려는 경우
	if (m_bAbsolute)
	{
		Vec3 vWorldScale = Transform()->GetWorldScale();
		Matrix matScaleInv = XMMatrixScaling(vWorldScale.x, vWorldScale.y, vWorldScale.z);
		matScaleInv = XMMatrixInverse(nullptr, matScaleInv);

		// Object 의 Scale 의 역행렬을 사이에 배치해서 무효화 시킴
		m_matColWorld = m_matColWorld * matScaleInv *  matObjWorld;
	}
	else
	{
		m_matColWorld *= matObjWorld;
	}	
	
	if (m_bDebug)
	{
		// 충돌중이면 Red, 충돌하고 있지 않으면 Green
		if (0 == m_CollisionCount)
		{
			if (m_Type == COLLIDER2D_TYPE::RECT)
			{
				GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(0.f, 1.f, 0.f), false);
			}
			else
			{
				Vec3 vPos = GetOwner()->Transform()->GetWorldPos();
				Vec2 vRadius = GetOwner()->Collider2D()->GetOffsetScale();
				GamePlayStatic::DrawDebugCircle(vPos, vRadius.x, Vec3(0.f, 1.f, 0.f), false);
			}
		}
		else
		{
			if (m_Type == COLLIDER2D_TYPE::RECT)
			{
				GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(1.f, 0.f, 0.f), false);
			}
			else
			{
				Vec3 vPos = GetOwner()->Transform()->GetWorldPos();
				Vec2 vRadius = GetOwner()->Collider2D()->GetOffsetScale();
				GamePlayStatic::DrawDebugCircle(vPos, vRadius.x, Vec3(1.f, 0.f, 0.f), false);
			}
		}
	}
}

void CCollider2D::BeginOverlap(CCollider2D* _OtherCollider)
{
	++m_CollisionCount;

	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->BeginOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}

void CCollider2D::Overlap(CCollider2D* _OtherCollider)
{
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->Overlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}

void CCollider2D::EndOverlap(CCollider2D* _OtherCollider)
{
	--m_CollisionCount;

	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->EndOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}

void CCollider2D::SaveToFile(FILE* _File)
{
	fwrite(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fwrite(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fwrite(&m_bAbsolute, sizeof(bool), 1, _File);
	fwrite(&m_Type, sizeof(UINT), 1, _File);	
}

#define TagOffsetPos "[OffsetPos]"
#define TagOffsetScale "[OffsetScale]"
#define TagAbsolute "[Absolute]"
#define TagColliderType "[ColliderType]"

void CCollider2D::SaveToFile(ofstream& fout)
{
	fout << TagOffsetPos << endl;
	fout << m_vOffsetPos << endl;

	fout << TagOffsetScale << endl;
	fout << m_vOffsetScale << endl;

	fout << TagAbsolute << endl;
	fout << m_bAbsolute << endl;

	fout << TagColliderType << endl;
	auto type = magic_enum::enum_name(m_Type);
	fout << ToString(type) << endl;
}

void CCollider2D::LoadFromFile(FILE* _File)
{
	fread(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fread(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fread(&m_bAbsolute, sizeof(bool), 1, _File);
	fread(&m_Type, sizeof(UINT), 1, _File);
}

void CCollider2D::LoadFromFile(ifstream& fin)
{
	string tag, str;
	Utils::GetLineUntilString(fin, TagOffsetPos);
	fin >> m_vOffsetPos;

	Utils::GetLineUntilString(fin, TagOffsetScale);
	fin >> m_vOffsetScale;

	Utils::GetLineUntilString(fin, TagAbsolute);
	fin >> m_bAbsolute;

	Utils::GetLineUntilString(fin, TagColliderType);
	getline(fin, str);

	m_Type = magic_enum::enum_cast<COLLIDER2D_TYPE>(str).value();
}
