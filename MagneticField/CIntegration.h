#ifndef CINTEGRATION_H
#define CINTEGRATION_H

#include "MagneticFieldStable.h"
#include "Tools/ToolsStable.h"


#define Mu0 (4 * PI * (10E-7))


namespace MagneticField
{

using namespace Tools;

class CIntegration
{
public:
    CIntegration();
    ~CIntegration();

    static BOOL IntegrateSolenoid(const F64 f64Rs, const CPoint3D Border1, const CPoint3D Border2, const CPoint3D InvestigationPoint,
                                  U64 N, F64 I_0, F64 WireDensity, CVector3D *pResult);
    static BOOL IntegrateRingOfCurrent(const CPoint3D RingCentrePoint, const F64 f64R, const F64 f64Current,
                                       const CPoint3D InvestigationPoint, const U64 u64NVertexes, CVector3D *pResult);

    static BOOL RingOfCurrent_Field(const CPoint3D RingCentrePoint, const F64 f64Rs, const F64 f64Current,
                                    const CPoint3D InvestigationPoint, CVector3D *pResult);

    static inline F64 Br_Integral(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N);
    static inline F64 Br_IntegralFunction(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z);
    static inline F64 Bz_Integral1(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N);
    static inline F64 Bz_Integral2(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N);
    static inline F64 Bz_IntegralFunction1(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z);
    static inline F64 Bz_IntegralFunction2(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z);

};

} /* End of namespace MAGNETICFIELD */

#endif // CINTEGRATION_H
