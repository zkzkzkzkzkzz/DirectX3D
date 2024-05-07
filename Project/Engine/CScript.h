#pragma once
#include "CComponent.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
//#include "CResMgr.h"

#include "CGameObject.h"
#include "components.h"

#include <variant>

struct tScriptParam
{
    SCRIPT_PARAM    Type;
    void*           pData;
    float           fmin;
    float           fMax;
    bool            View;
    string          Tooltip;
    FUNC_PARAM      FuncType;
    vector<std::variant<int, float, Vec2, Vec3, Vec4>> CallbackArgs;
    
//public:
//    tScriptParam(SCRIPT_PARAM type, void* data, float _min, float _max, bool view, const string& tooltip, FUNC_PARAM funcType, const std::vector<std::variant<int, float, Vec2, Vec3, Vec4>>& args)
//        : Type(type), pData(data), fmin(_min), fMax(_max), View(view), Tooltip(tooltip), CallbackArgs(args) {}
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
    void AppendScriptParam(const string& _Key, SCRIPT_PARAM _Param, void* _Data, float _min = 0.f, float _Max = 0.f, bool _View = false, const string& _Tooltip = {})
    {
        m_umScriptParam[_Key] = tScriptParam{ _Param, _Data, _min, _Max, _View, _Tooltip};
    }

    template<typename FuncType, typename... Args>
    void TAppendScriptParam(const string& _Key, SCRIPT_PARAM _Param, FUNC_PARAM _FuncParam, FuncType _Func, Args&&... args)
    {
        // 콜백 함수의 인자들을 저장하는 벡터 생성
        std::vector<std::variant<int, float, Vec2, Vec3, Vec4>> callbackArgs = { std::forward<Args>(args)... };

        // 새로운 스크립트 파라미터 생성 후 맵에 추가
        m_umScriptParam[_Key] = tScriptParam{ _Param, &_Func, 0.f, 0.f, false, {}, _FuncParam, callbackArgs };
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

