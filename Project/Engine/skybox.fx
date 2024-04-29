#ifndef _SKYBOX
#define _SKYBOX

#include "value.fx"
#include "func.fx"

struct VS_SKYBOX_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_SKYBOX_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

VS_SKYBOX_OUT VS_SkyBox(VS_SKYBOX_IN _in)
{
    VS_SKYBOX_OUT output = (VS_SKYBOX_OUT) 0.f;
        
    // 로컬 스페이스의 메쉬가 이미 카메라(View) 스페이스의 원점이 있는것으로 가정
    float3 vLocalPos = _in.vPos * 2.f;
    float3 vViewPos = mul(float4(vLocalPos, 0.f), g_matView);
    float4 vPosition = mul(float4(vViewPos, 1.f), g_matProj);
    vPosition.z = vPosition.w;
            
    output.vPosition = vPosition;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_SkyBox(VS_SKYBOX_OUT _in) : SV_Target
{
    float4 vOutColor = float4(0.2f, 0.2f, 1.f, 1.f);
    
    if (g_btex_0)
    {
        vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }
    
    return vOutColor;
}

#endif