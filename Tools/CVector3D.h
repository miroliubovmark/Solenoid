#ifndef CVECTOR3D_H
#define CVECTOR3D_H

#include "ToolsStable.h"

namespace Tools
{

class CVector3D
{
public:
    CVector3D();
    CVector3D(const CVector3D &crVector);
    CVector3D(F64 f64X, F64 f64Y, F64 f64Z);
    CVector3D(const CPoint3D& crPoint1, const CPoint3D& crPoint2);

    ~CVector3D();

    CVector3D operator+(CVector3D InputVector);
    CVector3D operator+(CVector3D* InputVector);
    CVector3D operator-(CVector3D InputVector);
    CVector3D operator-(CVector3D* InputVector);
    CVector3D operator*(F64 f64Scalar);

    BOOL SetCoordinates(F64 f64X, F64 f64Y, F64 f64Z);
    F64 GetAbs();

    BOOL SetVectorSum(const CVector3D& crVector1, const CVector3D& crVector2);
    BOOL SetVectorSum(CVector3D* pVector1, CVector3D* pVector2);
    BOOL SetVectorSubtraction(const CVector3D& crVector1, const CVector3D& crVector2);
    BOOL SetVectorSubtraction(CVector3D* pVector1, CVector3D* pVector2);

    BOOL MultiplyOnScalar(F64 f64Scalar);

    BOOL RotateAroundZ(F64 f64AngleCos, F64 f64AngleSin);
    BOOL RotateAroundZ(CVector3D* pResultVector, F64 f64AngleCos, F64 f64AngleSin);

    void Print();
    BOOL Copy(const CVector3D& crVector);
    BOOL Copy(CVector3D* pVector);
    BOOL Clear();
    
    F64 m_f64X;
    F64 m_f64Y;
    F64 m_f64Z;
};

} /* End of namespace TOOLS */

#endif // CVECTOR3D_H
