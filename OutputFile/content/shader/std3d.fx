#ifndef _STD3D
#define _STD3D

#include "value.fx"


static float3 g_LightPos = float3(0.f, 0.f, 0.f);
static float3 g_LightDir = float3(1.f, -1.f, 1.f);
static float3 g_LightColor = float3(1.f, 1.f, 1.f);
static float3 g_LightAmbient = float3(0.1f, 0.1f, 0.1f);
static float3 g_SpecularRatio = float3(0.3f, 0.3f, 0.3f);


struct VTX_IN
{
    float3 vPos : POSITION;
    float3 vUV  : TEXCOORD;    
    float3 vNormal : NORMAL;    
};


struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    float LightPow : FOG;
        
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
};


VTX_OUT VS_Std3D(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
            
    // 정점 안에 들어있는 Normal 방향을 월드로 이동시킨다.
    // 방향벡터는 상태행렬의 4행(이동정보) 에 영향받지 않아야 하기 때문에 
    // 동차좌표를 0 으로 설정해서 행렬을 적용시킨다.
    
    // 광원 연산은 PixelShader 에서, ViewSpace 상에서 진행
    // 정점 쉐이더에서는 정점의 ViewSpace 상에서의 Normal 과 Position 값을 PixelShader 로 전달
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    
    
    return output;
}


float4 PS_Std3D(VTX_OUT _in) : SV_Target
{
    float4 vOutColor = float4(0.f, 0.f, 0.f, 1.f);
        
    // 물체 색상
    float4 ObjectColor = float4(0.7f, 0.7f, 0.7f, 1.f);
    
    // 광원 연산이 ViewSpace 에서 진행되기로 했기 때문에,
    // 광원이 진입하는 방향도 View 공간 기준으로 변경함
    float3 vViewLightDir = normalize(mul(float4(g_LightDir, 0.f), g_matView).xyz);
   
    // ViewSpace 에서 광원의 방향과, 물체 표면의 법선를 이용해서 광원의 진입 세기(Diffuse) 를 구한다.
    float LightPow = saturate(dot(_in.vViewNormal, -vViewLightDir));
            
    // 빛이 표면에 진입해서 반사되는 방향을 구한다.
    float3 vReflect = vViewLightDir + 2 * dot(-vViewLightDir, _in.vViewNormal) * _in.vViewNormal;
    vReflect = normalize(vReflect);
    
    // 카메라가 물체를 향하는 방향
    float3 vEye = normalize(_in.vViewPos);
    
    // 시선벡터와 반사벡터 내적, 반사광의 세기
    float ReflectPow = saturate(dot(-vEye, vReflect));
    ReflectPow = pow(ReflectPow, 20.f);
    
    
    // 최종 색상 == 물체 색 x 광원의 색 x 표면의 광원 세기 
    //           + 물체 색 x 환경광 세기    
    //           + 빛의 색 x 빛의 반사광 감소비율 x 반사세기(카메라랑 반사벡터가 서로 마주보는 정도)
    vOutColor.xyz = ObjectColor.xyz * g_LightColor * LightPow
                    + ObjectColor.xyz * g_LightColor * g_LightAmbient
                    + g_LightColor * g_SpecularRatio * ReflectPow;
    
    return vOutColor;
}


// 3D 로 넘어오면서 CULL_BACK 모드를 사용한다.
// 시계방향으로 인덱스 접근순서가 설정된 면을 정면이라고 보고
// 반대 방향에서 볼때는 Culling 을 한다.







#endif