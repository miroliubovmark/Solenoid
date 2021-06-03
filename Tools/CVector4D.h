#ifndef CVector4D_H
#define CVector4D_H

#include "ToolsStable.h"

namespace Tools
{

class CVector4D
{
public:
    CVector4D();

    CVector4D(const CVector4D &crVector4D);
    CVector4D(F64 f64X1, F64 f64X2, F64 f64X3, F64 f64X4);
    //CVector4D(const CPoint3D& crPoint1, const CPoint3D& crPoint2);

    ~CVector4D();


    CVector4D operator+(CVector4D InputVector);
    CVector4D operator*(F64 f64Scalar);

    BOOL SetCoordinates(F64 f64X1, F64 f64X2, F64 f64X3, F64 f64X4);
    F64 GetAbs();

    BOOL SetVectorSum(const CVector4D& crVector1, const CVector4D& crVector2);
    BOOL SetVectorSum(CVector4D* pVector1, CVector4D* pVector2);
    BOOL SetVectorSubtraction(const CVector4D& crVector1, const CVector4D& crVector2);
    BOOL SetVectorSubtraction(CVector4D* pVector1, CVector4D* pVector2);

    BOOL MultiplyOnScalar(F64 f64Scalar);

    void Print();
    BOOL Copy(const CVector4D& crVector4D);
    BOOL Copy(CVector4D* pVector4D);
    BOOL Clear();

    F64 m_f64X1, m_f64X2, m_f64X3, m_f64X4;
};

} /* End of namespace TOOLS */

#endif // CVector4D_H
