#ifndef _STD3D
#define _STD3D

#include "value.fx"


static float3 g_LightPos = float3(0.f, 0.f, 0.f);
static float3 g_LightDir = float3(1.f, 0.f, 0.f);
static float3 g_LightColor = float3(1.f, 1.f, 1.f);
static float3 g_LightAmbient = float3(0.1f, 0.1f, 0.1f);


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
};


VTX_OUT VS_Std3D(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
            
    // 정점 안에 들어있는 Normal 방향을 월드로 이동시킨다.
    // 방향벡터는 상태행렬의 4행(이동정보) 에 영향받지 않아야 하기 때문에 
    // 동차좌표를 0 으로 설정해서 행렬을 적용시킨다.
    float3 vWorldNormal = mul(float4(_in.vNormal, 0.f), g_matWorld);    
    float3 vLightDir = normalize(g_LightDir);
    
    // 광원의 방향과, 표면에서의 정점의 Normal 방향을 내적시켜서
    // 광원의 세기값을 구한다.
    output.LightPow = dot(vWorldNormal, -vLightDir);
    
    return output;
}


float4 PS_Std3D(VTX_OUT _in) : SV_Target
{
    float4 vOutColor = float4(0.f, 0.f, 0.f, 1.f);
         
    // 물체 색상
    float4 ObjectColor = float4(1.f, 0.f, 1.f, 1.f);
    
    // 최종 색상 == 물체 색 x 광원의 색 x 표면의 광원 세기 
    //           + 물체 색 x 환경광 세기
    vOutColor.xyz = ObjectColor.xyz * g_LightColor * _in.LightPow
                  + ObjectColor.xyz * g_LightAmbient;
    
    return vOutColor;
}


// 3D 로 넘어오면서 CULL_BACK 모드를 사용한다.
// 시계방향으로 인덱스 접근순서가 설정된 면을 정면이라고 보고
// 반대 방향에서 볼때는 Culling 을 한다.







#endif