﻿#include "pch.h"
#include "CKeyMgr.h"
#include "CEngine.h"

int g_KeySync[KEY::KEY_END] =
{
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

	VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4,
	VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7,  VK_NUMPAD8, VK_NUMPAD9,	

	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 
	'Z', 'X', 'C', 'V', 'B', 'N', 'M', 

	VK_TAB, VK_LSHIFT, VK_LMENU, VK_LCONTROL, VK_SPACE,
	VK_ESCAPE, VK_RETURN, VK_BACK, VK_DELETE,
	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN, 
	VK_LBUTTON, VK_RBUTTON,
};


CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	// Capaticy 를 미리 확보
	m_vecKeyData.reserve(KEY::KEY_END);

	// 데이터 개수를 늘림
	//m_vecKeyData.resize(KEY::KEY_END);

	for (UINT i = 0; i < KEY_END; ++i)
	{
		m_vecKeyData.push_back(FKeyData{(KEY)i, NONE, false});	
	}
}

void CKeyMgr::tick()
{
	// GetFocus()는 현재 포커싱 되어있는 윈도우를 반환한다.
	// 메인 윈도우와 비교해서 메인 윈도우가 포커싱 되어있는지 판단한다.

	//if (GetFocus() == nullptr)
	//{
	//	m_FocusState = FOCUS_STATE::NONE;
	//}
	//else if (GetFocus() == CEngine::GetInst()->GetMainWind())
	//{
	//	m_FocusState = FOCUS_STATE::MAIN;
	//}
	//else
	//{
	//	m_FocusState = FOCUS_STATE::OTHER;
	//}

	// FOCUS_STATE 가져오기
	m_FocusState = m_FocusCallback();


	// 1. 포커싱 되어있는 창이 없을 경우
	if (FOCUS_STATE::NONE == m_FocusState)
	{
		for (size_t i = 0; i < m_vecKeyData.size(); ++i)
		{
			switch (m_vecKeyData[i].eState)
			{
			case TAP:
				m_vecKeyData[i].eState = PRESSED;
				break;
			case PRESSED:
				m_vecKeyData[i].eState = RELEASED;
				break;
			case RELEASED:
				m_vecKeyData[i].eState = NONE;
				break;
			}
		}
	}
	// 2. 포커싱 되어있는 창이 있을 경우
	else
	{
		for (size_t i = 0; i < m_vecKeyData.size(); ++i)
		{
			if (GetAsyncKeyState(g_KeySync[m_vecKeyData[i].eKey]) & 0x8001)
			{
				// 이번 프레임에 해당 키가 눌려있다.
				if (m_vecKeyData[i].bPressed)
				{
					// 이전에도 눌려있었다 ==> 계속 눌림 상태
					m_vecKeyData[i].eState = PRESSED;
				}
				else
				{
					// 이전에는 눌려있지 않았다 ==> 막 눌림 상태
					m_vecKeyData[i].eState = TAP;
				}

				m_vecKeyData[i].bPressed = true;
			}
			else
			{
				// 이번 프레임에 해당키는 안 눌려 있다
				if (m_vecKeyData[i].bPressed)
				{
					// 이전 프레임에는 눌려 있었다 ==> 막 뗌
					m_vecKeyData[i].eState = RELEASED;
				}
				else
				{
					m_vecKeyData[i].eState = NONE;
				}

				m_vecKeyData[i].bPressed = false;
			}
		}

		// 마우스 좌표 계산
		m_vMousePrevPos = m_vMousePos;

		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(CEngine::GetInst()->GetMainWind(), &pt);
		m_vMousePos = Vec2((float)pt.x, (float)pt.y);

		// 마우스 이동 방향
		m_vMouseDrag = m_vMousePos - m_vMousePrevPos;

	}
}