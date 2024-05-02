#include "pch.h"
#include "Light3DUI.h"

#include <Engine\CLight3D.h>


Light3DUI::Light3DUI()
	: ComponentUI("Light3D", "##Light3D", COMPONENT_TYPE::LIGHT3D)
{
	SetSize(ImVec2(0.f, 430.f));
	SetComponentTitle("LIGHT3D");
}

Light3DUI::~Light3DUI()
{
}

void Light3DUI::render_update()
{
	ComponentUI::render_update();

	tLightInfo info = GetTargetObject()->Light3D()->GetLightInfo();

	static int LightType = (int)info.LightType;
	Vec3 vColor = info.vColor;
	Vec3 vAmbient = info.vAmbient;
	Vec3 vWorldDir = info.vWorldDir;
	float fRadius = info.fRadius;
	float fAngle = info.fAngle;



	ImGui::Text("Light Type");
	ImGui::SameLine(0, 20); ImGui::PushItemWidth(150);
	ImGui::Combo("##LightType", &LightType, "DIRECTIONAL\0POINT\0SPOT\0\0");

	if (0 == LightType)
	{
		ImGui::Text("Ambient");
		ImGui::SameLine(0, 41); ImGui::PushItemWidth(250);
		ImGui::ColorEdit3("##LightAmbient", vAmbient);
	}
	else if (1 == LightType)
	{
		ImGui::Text("Light Color");
		ImGui::SameLine(0, 13); ImGui::PushItemWidth(200);
		ImGui::ColorPicker3("##LightColor", vColor, ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);

		ImGui::Text("Radius");
		ImGui::SameLine(0, 48); ImGui::PushItemWidth(200);
		ImGui::DragFloat("##LightRadius", &fRadius);
	}
	else
	{
		ImGui::Text("Light Color");
		ImGui::SameLine(0, 13); ImGui::PushItemWidth(200);
		ImGui::ColorPicker3("##LightColor", vColor, ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);

		ImGui::Text("Radius");
		ImGui::SameLine(0, 48); ImGui::PushItemWidth(200);
		ImGui::DragFloat("##LightRadius", &fRadius);

		ImGui::Text("LightDir");
		ImGui::SameLine(0, 34); ImGui::PushItemWidth(200);
		ImGui::DragFloat3("##LightDir", vWorldDir);

		ImGui::Text("Angle");
		ImGui::SameLine(0, 55); ImGui::PushItemWidth(200);
		ImGui::SliderAngle("##LightAngle", &fAngle, 0.f, 360.f);
	}

	GetTargetObject()->Light3D()->SetLightType((LIGHT_TYPE)LightType);
	GetTargetObject()->Light3D()->SetLightColor(vColor);
	GetTargetObject()->Light3D()->SetAmbient(vAmbient);
	GetTargetObject()->Light3D()->SetRadius(fRadius);
	GetTargetObject()->Light3D()->SetAngle(fAngle);
}