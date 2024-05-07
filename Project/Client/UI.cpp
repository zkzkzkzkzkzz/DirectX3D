#include "pch.h"
#include "UI.h"


UI::UI(const string& _strName, const string& _strID)
	: m_strName(_strName)
	, m_strID(_strID)
	, m_bActive(true)
	, m_Parent(nullptr)
	, m_bModal(false)
{
}

UI::~UI()
{
	Delete_Vec(m_vecChildUI);
}

void UI::tick()
{

}

void UI::render()
{
	if (!m_bActive)
		return;

	bool Active = m_bActive;

	if (nullptr == GetParentUI())
	{
		// Modal
		if (!m_bModal)
		{
			ImGui::Begin(string(m_strName + m_strID).c_str(), &Active, ImGuiWindowFlags_AlwaysAutoResize);

			// 활성화, 비활성화 전환이 발생한 경우에는 Activate or Deactivate 를 호출시킨다.
			if (Active != m_bActive)
			{
				m_bActive = Active;

				if (m_bActive)
					Activate();
				else
					Deactivate();
			}

			render_update();

			for (size_t i = 0; i < m_vecChildUI.size(); ++i)
			{
				m_vecChildUI[i]->render();
			}

			ImGui::End();
		}

		// Modal
		else
		{
			ImGui::OpenPopup(string(m_strName + m_strID).c_str());
			if (ImGui::BeginPopupModal(string(m_strName + m_strID).c_str(), &Active))
			{
				render_update();

				for (size_t i = 0; i < m_vecChildUI.size(); ++i)
				{
					m_vecChildUI[i]->render();
				}

				ImGui::EndPopup();
			}

			else
			{
				// 활성화, 비활성화 전환이 발생한 경우에는 Activate or Deactivate 를 호출시킨다.
				if (Active != m_bActive)
				{
					m_bActive = Active;

					if (m_bActive)
						Activate();
					else
						Deactivate();
				}
			}
		}		
	}

	// Child UI 인 경우
	else
	{
		ImGui::BeginChild(string(m_strName + m_strID).c_str(), ImVec2(0,0), ImGuiChildFlags_AutoResizeY);

		render_update();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->render();
		}

		ImGui::EndChild();
	}
}

bool UI::ColorSelector(const char* _label, Vec4* _col)
{
	auto items = GamePlayStatic::COLOR::GetColors();
	static int selectedidx = 0;

	if (0 != items.size())
	{
		if (!(selectedidx < items.size()))
		{
			selectedidx = 0;
		}
		ImGui::SetNextItemWidth(150);
		if (ImGui::BeginCombo("##comboColorPreset", items[selectedidx].first.c_str())) {
			for (int i = 0; i < items.size(); i++) {
				const bool isSelected = (selectedidx == i);
				if (ImGui::Selectable(items[i].first.c_str(), isSelected)) {
					*_col = items[i].second;
					selectedidx = i;
				}

				// 항목 선택 시 자동으로 스크롤
				if (isSelected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

	}

	if (ImGui::ColorEdit4(_label, *_col))
	{
		return true;
	}
}