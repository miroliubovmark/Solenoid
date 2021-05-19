#ifndef CPOINT3D_H
#define CPOINT3D_H

#include "ToolsStable.h"

namespace Tools
{

class CPoint3D
{
public:
    CPoint3D();
    CPoint3D(F64 f64X, F64 f64Y, F64 f64Z);
    CPoint3D(const CPoint3D& crPoint);

    ~CPoint3D();

    BOOL SetCoordinates(F64 f64X, F64 f64Y, F64 f64Z);
    BOOL Copy(const CPoint3D& crPoint);
    void Print();
    
    F64 m_f64X;
    F64 m_f64Y;
    F64 m_f64Z;
};

} /* End of namespace TOOLS */

#endif // CPOINT3D_H
