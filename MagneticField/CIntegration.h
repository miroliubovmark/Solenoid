#ifndef CINTEGRATION_H
#define CINTEGRATION_H

#include "MagneticFieldStable.h"
#include "Tools/ToolsStable.h"


#define Mu0 (4 * PI * (1E-7))
#define LowLimit 0
#define TopLimit PI

/** Number of iterations for B_Integral1 Inimplementating the accuracy 0.1% */
#define B_Integral1_Niterations 2000

/** Number of iterations for B_Integral2 Inimplementating the accuracy 0.1% */
#define B_Integral2_Niterations 1000

/** Number of iterations for dB_Integral1 Inimplementating the accuracy 0.1% */
#define dB_Integral1_Niterations 2000

/** Number of iterations for dB_Integral2 Inimplementating the accuracy 0.1% */
#define dB_Integral2_Niterations 2000


#define GetMagneticMoment(B, f64V, f64Mu, MagneticMoment) \
{\
    (MagneticMoment).m_f64X = (f64Mu - 1) * (B).m_f64X * (f64V) / (f64Mu * Mu0);\
    (MagneticMoment).m_f64Y = (f64Mu - 1) * (B).m_f64Y * (f64V) / (f64Mu * Mu0);\
    (MagneticMoment).m_f64Z = (f64Mu - 1) * (B).m_f64Z * (f64V) / (f64Mu * Mu0);\
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
    //F64 m_f64SolenoidLength;

    /** Radius of solenoid */
    F64 m_f64Rs;

    /** Mu of solenoid core */
    F64 m_f64Core_Mu;

    /** Geometric parameters of solenoid */
    CPoint3D m_SolenoidEdge1;
    CPoint3D m_SolenoidEdge2;

    /** Current in wire */
    F64 m_f64Current = 1;

    /** Number of Source Points in solenoid */
    U64 m_u64NSourcePoints;
};


struct Ball
{
    /** Mu of ball material */
    F64 m_f64Mu;

    /** Radius of the ball */
    F64 m_f64Radius;

    /** Volume of the ball */
    F64 m_f64Volume;

    /** Mass of the ball */
    F64 m_f64M;

    /** Vector of magnetic moment */
    CVector3D m_MagneticMoment;
};


class CIntegration
{
public:
    CIntegration();
    ~CIntegration();

    static BOOL IntegrateSolenoid_Field(const Solenoid& crSolenoid, const CPoint3D& crInvestigationPoint,
                                        F64 WireDensity, CVector3D *pResult);
    static BOOL IntegrateSolenoid_Force(const Solenoid& crSolenoid, Ball& rBall, const CPoint3D& crInvestigationPoint,
                                        F64 f64WireDensity, F64* pf64Fr_Result);
    static BOOL IntegrateSolenoid_Force(const Solenoid& crSolenoid, Ball& rBall, const CPoint3D& crInvestigationPoint,
                                        const std::vector<F64>& crVWireDensity, F64* pf64Fr_Result);
    static BOOL IntegrateSolenoid_Force(const Solenoid& crSolenoid, Ball& rBall, const CPoint3D& crInvestigationPoint,
                                        F64 f64WireDensity, CVector3D* pForce);
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
