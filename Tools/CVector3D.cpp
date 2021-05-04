#include "CVector3D.h"

namespace Tools
{

CVector3D::CVector3D()
{
}

CVector3D::CVector3D(const CVector3D& crVector)
{
    m_f64X = crVector.m_f64X;
    m_f64Y = crVector.m_f64Y;
    m_f64Z = crVector.m_f64Z;
}

CVector3D::CVector3D(F64 f64X, F64 f64Y, F64 f64Z)
{
    m_f64X = f64X;
    m_f64Y = f64Y;
    m_f64Z = f64Z;
}

CVector3D::CVector3D(const CPoint3D& crPoint1, const CPoint3D& crPoint2)
{
    m_f64X = crPoint2.m_f64X - crPoint1.m_f64X;
    m_f64Y = crPoint2.m_f64Y - crPoint1.m_f64Y;
    m_f64Z = crPoint2.m_f64Z - crPoint1.m_f64Z;
}

CVector3D::~CVector3D()
{
}

CVector3D CVector3D::operator+(CVector3D InputVector)
{
    CVector3D OutputVector;
    F64 f64X, f64Y, f64Z;

    f64X = m_f64X + InputVector.m_f64X;
    f64Y = m_f64Y + InputVector.m_f64Y;
    f64Z = m_f64Z + InputVector.m_f64Z;

    OutputVector.SetCoordinates(f64X, f64Y, f64Z);
    return OutputVector;
}

CVector3D CVector3D::operator+(CVector3D* pInputVector)
{
    CVector3D OutputVector;
    F64 f64X, f64Y, f64Z;

    f64X = m_f64X + pInputVector->m_f64X;
    f64Y = m_f64Y + pInputVector->m_f64Y;
    f64Z = m_f64Z + pInputVector->m_f64Z;

    OutputVector.SetCoordinates(f64X, f64Y, f64Z);
    return OutputVector;
}

CVector3D CVector3D::operator-(CVector3D InputVector)
{
    CVector3D OutputVector;
    F64 f64X, f64Y, f64Z;

    f64X = m_f64X - InputVector.m_f64X;
    f64Y = m_f64Y - InputVector.m_f64Y;
    f64Z = m_f64Z - InputVector.m_f64Z;

    OutputVector.SetCoordinates(f64X, f64Y, f64Z);
    return OutputVector;
}

CVector3D CVector3D::operator-(CVector3D* pInputVector)
{
    CVector3D OutputVector;
    F64 f64X, f64Y, f64Z;

    f64X = m_f64X - pInputVector->m_f64X;
    f64Y = m_f64Y - pInputVector->m_f64Y;
    f64Z = m_f64Z - pInputVector->m_f64Z;

    OutputVector.SetCoordinates(f64X, f64Y, f64Z);
    return OutputVector;
}

CVector3D CVector3D::operator*(F64 f64Scalar)
{
    CVector3D OutputVector;
    F64 f64X, f64Y, f64Z;

    f64X = m_f64X * f64Scalar;
    f64Y = m_f64Y * f64Scalar;
    f64Z = m_f64Z * f64Scalar;

    OutputVector.SetCoordinates(f64X, f64Y, f64Z);
    return OutputVector;
}

BOOL CVector3D::SetCoordinates(F64 f64X, F64 f64Y, F64 f64Z)
{
    m_f64X = f64X;
    m_f64Y = f64Y;
    m_f64Z = f64Z;

    return TRUE;
}

F64 CVector3D::GetAbs()
{
    F64 f64Abs = sqrt(m_f64X * m_f64X + m_f64Y * m_f64Y + m_f64Z * m_f64Z);
    return f64Abs;
}

BOOL CVector3D::SetVectorSum(const CVector3D& crVector1, const CVector3D& crVector2)
{
    m_f64X = crVector1.m_f64X + crVector2.m_f64X;
    m_f64Y = crVector1.m_f64Y + crVector2.m_f64Y;
    m_f64Z = crVector1.m_f64Z + crVector2.m_f64Z;

    return TRUE;
}

BOOL CVector3D::SetVectorSum(CVector3D* pVector1, CVector3D* pVector2)
{
    m_f64X = pVector1->m_f64X + pVector2->m_f64X;
    m_f64Y = pVector1->m_f64Y + pVector2->m_f64Y;
    m_f64Z = pVector1->m_f64Z + pVector2->m_f64Z;

    return TRUE;
}

BOOL CVector3D::SetVectorSubtraction(const CVector3D& crVector1, const CVector3D& crVector2)
{
    m_f64X = crVector1.m_f64X - crVector2.m_f64X;
    m_f64Y = crVector1.m_f64Y - crVector2.m_f64Y;
    m_f64Z = crVector1.m_f64Z - crVector2.m_f64Z;

    return TRUE;
}

BOOL CVector3D::SetVectorSubtraction(CVector3D* pVector1, CVector3D* pVector2)
{
    m_f64X = pVector1->m_f64X - pVector2->m_f64X;
    m_f64Y = pVector1->m_f64Y - pVector2->m_f64Y;
    m_f64Z = pVector1->m_f64Z - pVector2->m_f64Z;

    return TRUE;
}

BOOL CVector3D::MultiplyOnScalar(F64 f64Scalar)
{
    m_f64X *= f64Scalar;
    m_f64Y *= f64Scalar;
    m_f64Z *= f64Scalar;

    return TRUE;
}

BOOL CVector3D::RotateAroundZ(F64 f64AngleCos, F64 f64AngleSin)
{
    m_f64X = m_f64X * f64AngleCos + m_f64Y * f64AngleSin;
    m_f64Y = -m_f64X * f64AngleSin + m_f64Y * f64AngleCos;

    return TRUE;
}

BOOL CVector3D::RotateAroundZ(CVector3D* pResultVector, F64 f64AngleCos, F64 f64AngleSin)
{
    F64 f64X, f64Y, f64Z;

    f64X = m_f64X * f64AngleCos + m_f64Y * f64AngleSin;
    f64Y = -m_f64X * f64AngleSin + m_f64Y * f64AngleCos;
    f64Z = m_f64Z;

    pResultVector->SetCoordinates(f64X, f64Y, f64Z);

    return TRUE;
}

void CVector3D::Print()
{
    printf("X:%.16f\tY:%.16f\tZ:%.16f\n", m_f64X, m_f64Y, m_f64Z);
}

BOOL CVector3D::Copy(const CVector3D& crVector)
{
    m_f64X = crVector.m_f64X;
    m_f64Y = crVector.m_f64Y;
    m_f64Z = crVector.m_f64Z;

    return TRUE;
}

BOOL CVector3D::Copy(CVector3D* pVector)
{
    m_f64X = pVector->m_f64X;
    m_f64Y = pVector->m_f64Y;
    m_f64Z = pVector->m_f64Z;

    return TRUE;
}

} /* End of namespace TOOLS */
