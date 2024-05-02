#pragma once
#include "CComponent.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
//#include "CResMgr.h"

#include "CGameObject.h"
#include "components.h"

struct tScriptParam
{
    SCRIPT_PARAM    Type;
    void*           pData;
    bool            View;
    string          Tooltip;
};

class CScript :
    public CComponent
{
private:
    const UINT              m_iScriptType;
    std::unordered_map<string, tScriptParam>    m_umScriptParam;

public:
    UINT GetScriptType() { return m_iScriptType; }
    const auto& GetScriptParam() { return m_umScriptParam; }


protected:
    void Instantiate(Ptr<CPrefab> _Prefab, Vec3 _vWorldPos, int _LayerIdx);
    void AppendScriptParam(const string& _Key, SCRIPT_PARAM _Param, void* _Data, bool _View = false, const string& _Tooltip = {})
    {
        m_umScriptParam[_Key] = tScriptParam{ _Param, _Data, _View, _Tooltip };
    }

public:
    virtual void finaltick() final {}
    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider) {}

    virtual void SaveToFile(FILE* _File) = 0;
    virtual void SaveToFile(ofstream& fout) {};
    virtual void LoadFromFile(FILE* _File) = 0;
    virtual void LoadFromFile(ifstream& fin) {};

    CScript* Clone() = 0;
public:
    CScript(UINT _ScriptType);
    ~CScript();
};

