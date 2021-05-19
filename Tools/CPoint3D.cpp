#include "CPoint3D.h"

namespace Tools
{

CPoint3D::CPoint3D()
{
}

CPoint3D::CPoint3D(F64 f64X, F64 f64Y, F64 f64Z)
{
    m_f64X = f64X;
    m_f64Y = f64Y;
    m_f64Z = f64Z;
}

CPoint3D::CPoint3D(const CPoint3D& crPoint)
{
    m_f64X = crPoint.m_f64X;
    m_f64Y = crPoint.m_f64Y;
    m_f64Z = crPoint.m_f64Z;
}

CPoint3D::~CPoint3D()
{
}

BOOL CPoint3D::SetCoordinates(F64 f64X, F64 f64Y, F64 f64Z)
{
    m_f64X = f64X;
    m_f64Y = f64Y;
    m_f64Z = f64Z;

    return TRUE;
}

BOOL CPoint3D::Copy(const CPoint3D& crPoint)
{
    m_f64X = crPoint.m_f64X;
    m_f64Y = crPoint.m_f64Y;
    m_f64Z = crPoint.m_f64Z;

    return TRUE;
}

void CPoint3D::Print()
{
    printf("X:%.16f\tY:%.16f\tZ:%.16f\n", m_f64X, m_f64Y, m_f64Z);
}

} /* End of namespace TOOLS */
