#ifndef CINTEGRATION_H
#define CINTEGRATION_H

#include "MagneticFieldStable.h"
#include "Tools/ToolsStable.h"


#define Mu0 (4 * PI * (1E-7))
#define LowLimit 0
#define TopLimit PI

#define Mu 5000

#define GetMagneticMoment(B, f64V, pMagneticMoment) \
{\
    (pMagneticMoment).m_f64X = (Mu - 1) * (B).m_f64X * (f64V) / (Mu * Mu0);\
    (pMagneticMoment).m_f64Y = (Mu - 1) * (B).m_f64Y * (f64V) / (Mu * Mu0);\
    (pMagneticMoment).m_f64Z = (Mu - 1) * (B).m_f64Z * (f64V) / (Mu * Mu0);\
}

#define GetForce(MagneticMoment, Field_dBr, F)\
{\
    (F).m_f64X = (MagneticMoment).m_f64X * (Field_dBr)[0];\
    (F).m_f64Y = (MagneticMoment).m_f64Y * (Field_dBr)[0];\
    (F).m_f64Z = (MagneticMoment).m_f64Z * (Field_dBr)[1];\
}

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
    static BOOL RingOfCurrent_BioSavar(const CPoint3D RingCentrePoint, const F64 f64Rs, const F64 f64Current,
                                       const CPoint3D InvestigationPoint, const U64 u64NVertexes, CVector3D *pResult);
    static BOOL RingOfCurrent_Field(const CPoint3D& crRingCentrePoint, const F64 f64Rs, const F64 f64Current,
                                    const CPoint3D& crInvestigationPoint, CVector3D *pResult);
    static BOOL RingOfCurrent_FieldDerivative(const CPoint3D& crRingCentrePoint, const F64 f64Rs, const F64 f64Current,
                                              const CPoint3D& crInvestigationPoint, F64* Field_dBr);

    static F64 B_Integral1(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N);
    static F64 B_IntegralFunction1(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z);

    static F64 B_Integral2(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N);
    static F64 B_IntegralFunction2(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z);

    static F64 dB_Integral1(F64 f64R, F64 f64Rs, F64 f64Z, U64 u64N);
    static F64 dB_IntegralFunction1(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z);

    static F64 dB_Integral2(F64 f64R, F64 f64Rs, F64 f64Z, U64 u64N);
    static F64 dB_IntegralFunction2(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z);
};

} /* End of namespace MAGNETICFIELD */

#endif // CINTEGRATION_H
