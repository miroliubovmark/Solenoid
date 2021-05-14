#ifndef CINTEGRATION_H
#define CINTEGRATION_H

#include "MagneticFieldStable.h"
#include "Tools/ToolsStable.h"


#define Mu0 (4 * PI * (10E-7))


namespace MagneticField
{

using namespace Tools;

struct Solenoid
{
    /** Length of solenoid */
    F64 m_f64SolenoidLength;

    /** Radius of solenoid */
    F64 m_f64Rs;

    /** Geometric parameters of solenoid */
    CPoint3D m_SolenoidEdge1;
    CPoint3D m_SolenoidEdge2;

    /** Current in wire */
    F64 m_f64Current = 1;

    /** Number of Source Points in solenoid */
    U64 m_u64NSourcePoints;
};


class CIntegration
{
public:
    CIntegration();
    ~CIntegration();

    static BOOL IntegrateSolenoid(const Solenoid& rSolenoid, const CPoint3D& crInvestigationPoint,
                                  F64 WireDensity, CVector3D *pResult);
    static BOOL IntegrateRingOfCurrent(const CPoint3D RingCentrePoint, const F64 f64R, const F64 f64Current,
                                       const CPoint3D InvestigationPoint, const U64 u64NVertexes, CVector3D *pResult);
    static BOOL RingOfCurrent_Field(const CPoint3D& crRingCentrePoint, const F64 f64Rs, const F64 f64Current,
                                    const CPoint3D& crInvestigationPoint, CVector3D *pResult);

    static inline F64 Br_Integral(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N);
    static inline F64 Br_IntegralFunction(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z);
    static inline F64 Bz_Integral1(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N);
    static inline F64 Bz_Integral2(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N);
    static inline F64 Bz_IntegralFunction1(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z);
    static inline F64 Bz_IntegralFunction2(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z);

};

} /* End of namespace MAGNETICFIELD */

#endif // CINTEGRATION_H
