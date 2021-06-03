#include "CVector4D.h"

namespace Tools
{

CVector4D::CVector4D()
{
}

CVector4D::CVector4D(const CVector4D& crVector4D)
{
    m_f64X1 = crVector4D.m_f64X1;
    m_f64X2 = crVector4D.m_f64X2;
    m_f64X3 = crVector4D.m_f64X3;
    m_f64X4 = crVector4D.m_f64X4;
}

CVector4D::CVector4D(F64 f64X1, F64 f64X2, F64 f64X3, F64 f64X4)
{
    m_f64X1 = f64X1;
    m_f64X2 = f64X2;
    m_f64X3 = f64X3;
    m_f64X4 = f64X4;
}

/*
CVector4D::CVector4D(const CPoint3D& crPoint1, const CPoint3D& crPoint2)
{
    m_f64X = crPoint2.m_f64X - crPoint1.m_f64X;
    m_f64Y = crPoint2.m_f64Y - crPoint1.m_f64Y;
    m_f64Z = crPoint2.m_f64Z - crPoint1.m_f64Z;
}
*/

CVector4D::~CVector4D()
{
}

CVector4D CVector4D::operator+(CVector4D InputVector)
{
    CVector4D OutputVector;
    F64 f64X1, f64X2, f64X3, f64X4;

    f64X1 = m_f64X1 + InputVector.m_f64X1;
    f64X2 = m_f64X2 + InputVector.m_f64X2;
    f64X3 = m_f64X3 + InputVector.m_f64X3;
    f64X4 = m_f64X4 + InputVector.m_f64X4;

    OutputVector.SetCoordinates(f64X1, f64X2, f64X3, f64X4);
    return OutputVector;
}

CVector4D CVector4D::operator*(F64 f64Scalar)
{
    CVector4D OutputVector;
    F64 f64X1, f64X2, f64X3, f64X4;

    f64X1 = m_f64X1 * f64Scalar;
    f64X2 = m_f64X2 * f64Scalar;
    f64X3 = m_f64X3 * f64Scalar;
    f64X4 = m_f64X4 * f64Scalar;

    OutputVector.SetCoordinates(f64X1, f64X2, f64X3, f64X4);
    return OutputVector;
}

BOOL CVector4D::SetCoordinates(F64 f64X1, F64 f64X2, F64 f64X3, F64 f64X4)
{
    m_f64X1 = f64X1;
    m_f64X2 = f64X2;
    m_f64X3 = f64X3;
    m_f64X4 = f64X4;

    return TRUE;
}

F64 CVector4D::GetAbs()
{
    F64 f64Abs = sqrt(m_f64X1 * m_f64X1 + m_f64X2 * m_f64X2 + m_f64X3 * m_f64X3 + m_f64X4 * m_f64X4);
    return f64Abs;
}

BOOL CVector4D::SetVectorSum(const CVector4D& crVector1, const CVector4D& crVector2)
{
    m_f64X1 = crVector1.m_f64X1 + crVector2.m_f64X1;
    m_f64X2 = crVector1.m_f64X2 + crVector2.m_f64X2;
    m_f64X3 = crVector1.m_f64X3 + crVector2.m_f64X3;
    m_f64X4 = crVector1.m_f64X4 + crVector2.m_f64X4;

    return TRUE;
}

BOOL CVector4D::SetVectorSum(CVector4D* pVector1, CVector4D* pVector2)
{
    m_f64X1 = pVector1->m_f64X1 + pVector2->m_f64X1;
    m_f64X2 = pVector1->m_f64X2 + pVector2->m_f64X2;
    m_f64X3 = pVector1->m_f64X3 + pVector2->m_f64X3;
    m_f64X4 = pVector1->m_f64X4 + pVector2->m_f64X4;

    return TRUE;
}

BOOL CVector4D::SetVectorSubtraction(const CVector4D& crVector1, const CVector4D& crVector2)
{
    m_f64X1 = crVector1.m_f64X1 - crVector2.m_f64X1;
    m_f64X2 = crVector1.m_f64X2 - crVector2.m_f64X2;
    m_f64X3 = crVector1.m_f64X3 - crVector2.m_f64X3;
    m_f64X4 = crVector1.m_f64X4 - crVector2.m_f64X4;

    return TRUE;
}

BOOL CVector4D::SetVectorSubtraction(CVector4D* pVector1, CVector4D* pVector2)
{
    m_f64X1 = pVector1->m_f64X1 - pVector2->m_f64X1;
    m_f64X2 = pVector1->m_f64X2 - pVector2->m_f64X2;
    m_f64X3 = pVector1->m_f64X3 - pVector2->m_f64X3;
    m_f64X4 = pVector1->m_f64X4 - pVector2->m_f64X4;

    return TRUE;
}

BOOL CVector4D::MultiplyOnScalar(F64 f64Scalar)
{
    m_f64X1 *= f64Scalar;
    m_f64X2 *= f64Scalar;
    m_f64X3 *= f64Scalar;
    m_f64X4 *= f64Scalar;

    return TRUE;
}

void CVector4D::Print()
{
    printf("X1:%.16f\tX2:%.16f\tX3:%.16f\tX4:%.16f\n", m_f64X1, m_f64X2, m_f64X3, m_f64X4);
}

BOOL CVector4D::Copy(const CVector4D& crVector4D)
{
    m_f64X1 = crVector4D.m_f64X1;
    m_f64X2 = crVector4D.m_f64X2;
    m_f64X3 = crVector4D.m_f64X3;
    m_f64X4 = crVector4D.m_f64X4;

    return TRUE;
}

BOOL CVector4D::Copy(CVector4D* pVector4D)
{
    m_f64X1 = pVector4D->m_f64X1;
    m_f64X2 = pVector4D->m_f64X2;
    m_f64X3 = pVector4D->m_f64X3;
    m_f64X4 = pVector4D->m_f64X4;

    return TRUE;
}

BOOL CVector4D::Clear()
{
    m_f64X1 = 0.0;
    m_f64X2 = 0.0;
    m_f64X3 = 0.0;
    m_f64X4 = 0.0;

    return TRUE;
}

} /* End of namespace TOOLS */
