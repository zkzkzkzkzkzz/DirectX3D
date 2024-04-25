#ifndef _FUNC
#define _FUNC

#include "struct.fx"
#include "value.fx"


void CalLight2D(float3 _WorldPos, int _LightIdx, inout tLightColor _output)
{
    // 빛을 적용시킬 광원의 정보
    tLightInfo info = g_Light2D[_LightIdx];    
    
    // Directional Light
    if (0 == info.LightType)
    {
        _output.vAmbient += info.Color.vAmbient;
    }
    
    // Point Light
    else if (1 == info.LightType)
    {
        float fAttenu = 1.f;
        
        float fDist = distance(info.vWorldPos.xy, _WorldPos.xy);
        if (fDist < info.fRadius)
        {
            if (g_int_0)
            {
                float fTheta = (fDist / info.fRadius) * (PI / 2.f);
                fAttenu = saturate(cos(fTheta));
            }
            else
            {
                fAttenu = saturate(1.f - fDist / g_Light2D[0].fRadius);
            }
            
            _output.vColor += info.Color.vColor * fAttenu;
        }        
    }
    
    // Spot Light
    else
    {
        float fAttenu = 1.f;    // 각도 감쇠
        float fAttenu2 = 1.f;   // 거리 감쇠
        
        float fDist = distance(info.vWorldPos.xy, _WorldPos.xy);
        
        float2 lightDir = normalize(info.vWorldDir.xy); // 초기 광원의 방향 벡터
        float2 targetDir = normalize(_WorldPos.xy - info.vWorldPos.xy); // 타겟 벡터
        
        
        // 광원 방향과 타겟 방향 사이의 각도를 계산
        float fTheta = acos(dot(lightDir, targetDir));
        
        // 타겟 각도가 광원의 각도 범위 안에 있을 때
        if (fTheta < info.fAngle)
        {
            // 각도에 따른 감쇠 계산
            fAttenu = saturate(1.f - fTheta / info.fAngle);
            
            if (fDist < info.fRadius)
            {
                float fTheta2 = (fDist / info.fRadius) * (PI / 2.f);
                fAttenu2 = saturate(cos(fTheta2));
            }
            else
            {
                fAttenu2 = saturate(1.f - fDist / g_Light2D[0].fRadius);
            }
        }
        // 타겟 각도가 광원 각도 범위 밖이면 보이지 않음
        else
        {
            fAttenu = 0.f;
        }
        
        _output.vColor += info.Color.vColor * fAttenu * fAttenu2;
    }    
}


// ======
// Random
// ======
static float GaussianFilter[5][5] =
{
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.0219f, 0.0983f, 0.1621f, 0.0983f, 0.0219f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.003f, 0.0133f, 0.0219f, 0.0133f, 0.003f,
};

void GaussianSample(in Texture2D _NoiseTex, float2 _vResolution, float _NomalizedThreadID, out float3 _vOut)
{
    float2 vUV = float2(_NomalizedThreadID, 0.5f);
    
    vUV.x += g_time * 0.5f;
    
    // sin 그래프로 텍스쳐의 샘플링 위치 UV 를 계산
    vUV.y -= (sin((_NomalizedThreadID - (g_time /*그래프 우측 이동 속도*/)) * 2.f * 3.1415926535f * 10.f /*반복주기*/) / 2.f);
    
    if (1.f < vUV.x)
        vUV.x = frac(vUV.x);
    else if (vUV.x < 0.f)
        vUV.x = 1.f + frac(vUV.x);
    
    if (1.f < vUV.y)
        vUV.y = frac(vUV.y);
    else if (vUV.y < 0.f)
        vUV.y = 1.f + frac(vUV.y);
        
    int2 pixel = vUV * _vResolution;
    int2 offset = int2(-2, -2);
    float3 vOut = (float3) 0.f;
    
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            vOut += _NoiseTex[pixel + offset + int2(j, i)].xyz * GaussianFilter[i][j];
        }
    }
    
    _vOut = vOut;
}




#endif