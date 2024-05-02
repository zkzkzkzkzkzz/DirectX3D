#ifndef _MERGE
#define _MERGE

#include "value.fx"

// ===============
// Merge Shader
// MRT : SwapChain
// Mesh : RectMesh
#define ColorTargetTex      g_tex_0
#define ColorTargetCheck    g_btex_0
// ===============

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

VS_OUT VS_Merge(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPos * 2.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Merge(VS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    if (ColorTargetCheck)
    {
        vOutColor = ColorTargetTex.Sample(g_sam_0, _in.vUV);
        
    }
    
    return vOutColor;
}







#endif