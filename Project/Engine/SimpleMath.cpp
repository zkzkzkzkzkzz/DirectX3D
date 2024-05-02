#include "pch.h"

ofstream& DirectX::SimpleMath::operator<<(ofstream& fout, const Vector2& vec)
{
    fout << vec.x << " " << vec.y;
    return fout;
}

ifstream& DirectX::SimpleMath::operator>>(ifstream& fin, Vector2& vec)
{
    fin >> vec.x >> vec.y;
    return fin;
}

ofstream& DirectX::SimpleMath::operator<<(ofstream& fout, const Vector3& vec)
{
    fout << vec.x << " " << vec.y << " " << vec.z;
    return fout;
}

ifstream& DirectX::SimpleMath::operator>>(ifstream& fin, Vector3& vec)
{
    fin >> vec.x >> vec.y >> vec.z;
    return fin;
}

ofstream& DirectX::SimpleMath::operator<<(ofstream& fout, const Vector4& vec)
{
    fout << vec.x << " " << vec.y << " " << vec.z << " " << vec.w;
    return fout;
}

ifstream& DirectX::SimpleMath::operator>>(ifstream& fin, Vector4& vec)
{
    fin >> vec.x >> vec.y >> vec.z >> vec.w;
    return fin;
}

ofstream& DirectX::SimpleMath::operator<<(ofstream& fout, const Matrix& mat)
{
    fout << mat._11 << " " << mat._12 << " " << mat._13 << " " << mat._14 << endl;
    fout << mat._21 << " " << mat._22 << " " << mat._23 << " " << mat._24 << endl;
    fout << mat._31 << " " << mat._32 << " " << mat._33 << " " << mat._34 << endl;
    fout << mat._41 << " " << mat._42 << " " << mat._43 << " " << mat._44;

    return fout;
}

ifstream& DirectX::SimpleMath::operator>>(ifstream& fin, Matrix& mat)
{
    fin >> mat._11 >> mat._12 >> mat._13 >> mat._14;
    fin >> mat._21 >> mat._22 >> mat._23 >> mat._24;
    fin >> mat._31 >> mat._32 >> mat._33 >> mat._34;
    fin >> mat._41 >> mat._42 >> mat._43 >> mat._44;
    return fin;
}
