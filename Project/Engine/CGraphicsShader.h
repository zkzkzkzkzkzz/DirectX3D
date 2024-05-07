﻿#pragma once
#include "CShader.h"


struct tScalarParam
{
    SCALAR_PARAM    Type;
    string          Desc;
    float           min;
    float           Max;
    bool            View;
    string          Tooltip;
};

struct tTexParam
{
    TEX_PARAM       Type;
    string          Desc;
};


class CGraphicsShader :
    public CShader
{
private:
    ComPtr<ID3DBlob>    m_VSBlob;
    ComPtr<ID3DBlob>    m_HSBlob;
    ComPtr<ID3DBlob>    m_DSBlob;
    ComPtr<ID3DBlob>    m_GSBlob;
    ComPtr<ID3DBlob>    m_PSBlob;

    ComPtr<ID3D11VertexShader>      m_VS;
    ComPtr<ID3D11HullShader>        m_HS;
    ComPtr<ID3D11DomainShader>      m_DS;
    ComPtr<ID3D11GeometryShader>    m_GS;
    ComPtr<ID3D11PixelShader>       m_PS;

    ComPtr<ID3D11InputLayout>       m_Layout;
    D3D11_PRIMITIVE_TOPOLOGY        m_Topology;

    // Rasterizer State
    RS_TYPE                         m_RSType;

    // OutputMerge
    // DepthStencilState
    DS_TYPE                         m_DSType;
     
    // BlendState
    BS_TYPE                         m_BSType;

    // Shader Domain
    SHADER_DOMAIN                   m_Domain;

    // Shader 파라미터 목록
    vector<tScalarParam>            m_ScalarParam;
    vector<tTexParam>               m_TexParam;

public:
    int CreateVertexShader(const wstring& _strRelativePath, const string& _strFuncName);
   /* int CreateHullShader();
    int CreateDomainShader();*/
    int CreateGeometryShader(const wstring& _strRelativePath, const string& _strFuncName);
    int CreatePixelShader(const wstring& _strRelativePath, const string& _strFuncName);

    D3D11_PRIMITIVE_TOPOLOGY GetTopology() { return m_Topology; }

    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _Topology) { m_Topology = _Topology; }
    void SetRSType(RS_TYPE _Type) { m_RSType = _Type; }
    void SetDSType(DS_TYPE _Type) { m_DSType = _Type; }
    void SetBSType(BS_TYPE _Type) { m_BSType = _Type; }
    void SetDomain(SHADER_DOMAIN _domain) { m_Domain = _domain; }

    SHADER_DOMAIN GetDomain() { return m_Domain; }


    void AddScalarParam(SCALAR_PARAM _Param, const string& _Desc, float _min = 0.f, float _Max = 0.f, bool _View = false, const string& _Tooltip = {})
    {
        m_ScalarParam.push_back(tScalarParam{ _Param , _Desc, _min, _Max, _View, _Tooltip });
    }
    void AddTexParam(TEX_PARAM _Param, const string& _Desc){ m_TexParam.push_back(tTexParam{ _Param , _Desc });}
    const vector<tScalarParam>& GetScalarParam() { return  m_ScalarParam; }
    const vector<tTexParam>& GetTexParam() { return m_TexParam; }


public:
    virtual int UpdateData();

public:
    CGraphicsShader();
    ~CGraphicsShader();
};

