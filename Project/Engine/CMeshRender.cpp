﻿#include "pch.h"
#include "CMeshRender.h"

#include "CMesh.h"
#include "CGraphicsShader.h"

#include "CGameObject.h"
#include "CAnimator2D.h"
#include "CTransform.h"
#include "CMaterial.h"

#include "CRenderMgr.h"


CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}


void CMeshRender::UpdateData()
{
	if (nullptr != GetMaterial())
	{
		GetMaterial()->UpdateData();
	}

	Transform()->UpdateData();
}

void CMeshRender::finaltick()
{
	if (CRenderMgr::GetInst()->IsDebugPosition())
	{
		// Depth Test 추가
		GamePlayStatic::DrawDebugCross(Transform()->GetWorldPos(), 100.f, Vec3(0.f, 1.f, 0.f), false);
	}
}

void CMeshRender::render()
{
	if (nullptr == GetMesh() || nullptr == GetMaterial())
		return;

	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}
	else
	{
		Animator2D()->Clear();
	}

	UpdateData();

	GetMesh()->render();
}