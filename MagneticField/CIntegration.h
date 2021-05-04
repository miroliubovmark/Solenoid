#ifndef CINTEGRATION_H
#define CINTEGRATION_H

#include "MagneticFieldStable.h"
#include "Tools/ToolsStable.h"


namespace MagneticField
{

using namespace Tools;

class CIntegration
{
public:
    CIntegration();
    ~CIntegration();


    static BOOL IntegrateRingOfCurrent(const CPoint3D RingCentrePoint, const F64 f64R, const F64 f64Current, const CPoint3D InvestigationPoint, const U64 u64NVertexes, CVector3D *pResult);
};

} /* End of namespace MAGNETICFIELD */

#endif // CINTEGRATION_H
