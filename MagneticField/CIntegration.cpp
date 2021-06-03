#include "CIntegration.h"

namespace MagneticField
{

CIntegration::CIntegration()
{
}

CIntegration::~CIntegration()
{
}

BOOL CIntegration::RingOfCurrent_BioSavar(const CPoint3D RingCentrePoint, const F64 f64Rs, const F64 f64Current, const CPoint3D InvestigationPoint, const U64 u64NVertexes, CVector3D *pResult)
{
    F64 f64Phi = 2 * PI / static_cast<F64>(u64NVertexes);

    F64 f64CosPhi = cos(f64Phi);
    F64 f64SinPhi = sin(f64Phi);

    CVector3D* pCentreToInvPoint = new CVector3D(RingCentrePoint, InvestigationPoint);
    CVector3D* pCurrentRadialVector = new CVector3D(f64Rs, 0.0, 0.0);
    CVector3D* pNextRadialVector = new CVector3D;

    CVector3D* pdL = new CVector3D;
    CVector3D* pRadiusVector = new CVector3D;

    CVector3D* pCurrentB = new CVector3D;
    CVector3D* pB = new CVector3D(0.0, 0.0, 0.0);

    for(U64 i = 0; i < u64NVertexes; ++i)
    {
        /* Get dL */
        pCurrentRadialVector->RotateAroundZ(pNextRadialVector, f64CosPhi, f64SinPhi);
        pdL->SetVectorSubtraction(pNextRadialVector, pCurrentRadialVector);

        /* Get Radius-vector */
        pRadiusVector->SetVectorSubtraction(pCentreToInvPoint, pNextRadialVector);
        pRadiusVector->SetVectorSum((*pdL) * 0.5, *pRadiusVector);

        /* Get B from the element of current */
        CMathFunc::GetCrossProduct(*pdL, *pRadiusVector, pCurrentB);
        pCurrentB->MultiplyOnScalar(f64Current * Mu0 / (4 * PI * pow(pRadiusVector->GetAbs(), 3)));

        pB->SetVectorSum(pB, pCurrentB);

        /* Update CurrentRadialVector for the next step */
        pCurrentRadialVector->Copy(pNextRadialVector);
    }

    pResult->Copy(pB);

    return TRUE;
}

BOOL CIntegration::IntegrateSolenoid_Field(const Solenoid& crSolenoid, const CPoint3D& crInvestigationPoint, F64 f64WireDensity, CVector3D *pResult)
{
    F64 f64Step;
    f64Step = (crSolenoid.m_SolenoidEdge2.m_f64Z- crSolenoid.m_SolenoidEdge1.m_f64Z) / crSolenoid.m_u64NSourcePoints;

    CPoint3D RingCentrePoint;
    CVector3D CurrentB;

    pResult->Clear();

    F64 f64RingCentrePoint_X, f64RingCentrePoint_Y, f64RingCentrePoint_Z, f64Current;
    f64RingCentrePoint_X = crSolenoid.m_SolenoidEdge1.m_f64X;
    f64RingCentrePoint_Y = crSolenoid.m_SolenoidEdge1.m_f64Y;
    f64RingCentrePoint_Z = crSolenoid.m_SolenoidEdge1.m_f64Z + (f64Step / 2);

    for(U64 i = 0; i < crSolenoid.m_u64NSourcePoints; ++i)
    {
        RingCentrePoint.SetCoordinates(f64RingCentrePoint_X, f64RingCentrePoint_Y, f64RingCentrePoint_Z);
        f64Current = crSolenoid.m_f64Current * f64WireDensity * fabs(f64Step);

        RingOfCurrent_Field(RingCentrePoint, crSolenoid.m_f64Rs, f64Current, crInvestigationPoint, &CurrentB);
        pResult->SetVectorSum(*pResult, CurrentB);

        f64RingCentrePoint_Z += f64Step;
    }

    return TRUE;
}

BOOL CIntegration::IntegrateSolenoid_Force(const Solenoid& crSolenoid, Ball& rBall, const CPoint3D& crInvestigationPoint, F64 f64WireDensity, F64* pf64Fr_Result)
{
    *pf64Fr_Result = 0;

    F64 f64Step;
    f64Step = (crSolenoid.m_SolenoidEdge2.m_f64Z- crSolenoid.m_SolenoidEdge1.m_f64Z) / crSolenoid.m_u64NSourcePoints;

    CPoint3D RingCentrePoint;
    CVector3D CurrentB;

    F64 f64RingCentrePoint_X, f64RingCentrePoint_Y, f64RingCentrePoint_Z, f64Current;
    f64RingCentrePoint_X = crSolenoid.m_SolenoidEdge1.m_f64X;
    f64RingCentrePoint_Y = crSolenoid.m_SolenoidEdge1.m_f64Y;
    f64RingCentrePoint_Z = crSolenoid.m_SolenoidEdge1.m_f64Z + (f64Step / 2);

    F64 Field_dBr[2];
    F64 f64MagneticMoment_R, f64F1, f64F2, f64CurrentFr;

    for(U64 i = 0; i < crSolenoid.m_u64NSourcePoints; ++i)
    {
        /* Set updated co-ordinates to RingCentrePoint */
        RingCentrePoint.SetCoordinates(f64RingCentrePoint_X, f64RingCentrePoint_Y, f64RingCentrePoint_Z);

        /* Calculate Total current in the RingOfCurrent */
        f64Current = crSolenoid.m_f64Current * f64WireDensity * fabs(f64Step);

        /* Calculate Fied and FieldDerivative */
        RingOfCurrent_Field(RingCentrePoint, crSolenoid.m_f64Rs, f64Current, crInvestigationPoint, &CurrentB);
        RingOfCurrent_FieldDerivative(RingCentrePoint, crSolenoid.m_f64Rs, f64Current, crInvestigationPoint, Field_dBr);

        /* Get magnetic moment projection on R-axis */
        GetMagneticMoment(CurrentB, rBall.m_f64Volume, rBall.m_f64Mu, rBall.m_MagneticMoment);
        f64MagneticMoment_R = sqrt(rBall.m_MagneticMoment.m_f64X * rBall.m_MagneticMoment.m_f64X +
                                   rBall.m_MagneticMoment.m_f64Y * rBall.m_MagneticMoment.m_f64Y);

        /* Get Force projection on R-axis */
        f64F1 = crSolenoid.m_f64Core_Mu * f64MagneticMoment_R * Field_dBr[0];
        f64F2 = crSolenoid.m_f64Core_Mu * rBall.m_MagneticMoment.m_f64Z * Field_dBr[1];

        f64CurrentFr = f64F1 + f64F2;

        /* Append force of current RingOfCurrent to f64Fr_Result */
        *pf64Fr_Result += f64CurrentFr;

        /* Increase Ring Centre Point Z co-ordinate */
        f64RingCentrePoint_Z += f64Step;
    }

    return TRUE;
}

BOOL CIntegration::IntegrateSolenoid_Force(const Solenoid& crSolenoid, Ball& rBall, const CPoint3D& crInvestigationPoint, F64 f64WireDensity, CVector3D* pForce)
{
    F64 f64Fr_Result = 0;

    F64 f64Step;
    f64Step = (crSolenoid.m_SolenoidEdge2.m_f64Z- crSolenoid.m_SolenoidEdge1.m_f64Z) / crSolenoid.m_u64NSourcePoints;

    CPoint3D RingCentrePoint;
    CVector3D CurrentB;

    F64 f64RingCentrePoint_X, f64RingCentrePoint_Y, f64RingCentrePoint_Z, f64Current;
    f64RingCentrePoint_X = crSolenoid.m_SolenoidEdge1.m_f64X;
    f64RingCentrePoint_Y = crSolenoid.m_SolenoidEdge1.m_f64Y;
    f64RingCentrePoint_Z = crSolenoid.m_SolenoidEdge1.m_f64Z + (f64Step / 2);

    F64 Field_dBr[2];
    F64 f64MagneticMoment_R, f64F1, f64F2, f64CurrentFr;

    for(U64 i = 0; i < crSolenoid.m_u64NSourcePoints; ++i)
    {
        /* Set updated co-ordinates to RingCentrePoint */
        RingCentrePoint.SetCoordinates(f64RingCentrePoint_X, f64RingCentrePoint_Y, f64RingCentrePoint_Z);

        /* Calculate Total current in the RingOfCurrent */
        f64Current = crSolenoid.m_f64Current * f64WireDensity * fabs(f64Step);

        /* Calculate Fied and FieldDerivative */
        RingOfCurrent_Field(RingCentrePoint, crSolenoid.m_f64Rs, f64Current, crInvestigationPoint, &CurrentB);
        RingOfCurrent_FieldDerivative(RingCentrePoint, crSolenoid.m_f64Rs, f64Current, crInvestigationPoint, Field_dBr);

        /* Get magnetic moment projection on R-axis */
        GetMagneticMoment(CurrentB, rBall.m_f64Volume, rBall.m_f64Mu, rBall.m_MagneticMoment);
        f64MagneticMoment_R = sqrt(rBall.m_MagneticMoment.m_f64X * rBall.m_MagneticMoment.m_f64X +
                                   rBall.m_MagneticMoment.m_f64Y * rBall.m_MagneticMoment.m_f64Y);

        /* Get Force projection on R-axis */
        f64F1 = crSolenoid.m_f64Core_Mu * f64MagneticMoment_R * Field_dBr[0];
        f64F2 = crSolenoid.m_f64Core_Mu * rBall.m_MagneticMoment.m_f64Z * Field_dBr[1];

        f64CurrentFr = f64F1 + f64F2;

        /* Append force of current RingOfCurrent to f64Fr_Result */
        f64Fr_Result += f64CurrentFr;

        /* Increase Ring Centre Point Z co-ordinate */
        f64RingCentrePoint_Z += f64Step;
    }

    CVector3D SolenoidToInv_Vector(crSolenoid.m_SolenoidEdge1, crInvestigationPoint);
    F64 f64R, f64CosTheta, f64SinTheta;

    f64R = SolenoidToInv_Vector.GetAbs();

    if(f64R < 1E-5)
    {
        f64SinTheta = 0.0;
        f64CosTheta = 0.0;
    }
    else
    {
        f64CosTheta = (crInvestigationPoint.m_f64X - crSolenoid.m_SolenoidEdge1.m_f64X) / f64R;
        f64SinTheta = (crInvestigationPoint.m_f64Y - crSolenoid.m_SolenoidEdge1.m_f64Y) / f64R;
    }

    F64 f64ForceX, f64ForceY, f64ForceZ;
    f64ForceX = f64Fr_Result * f64CosTheta;
    f64ForceY = f64Fr_Result * f64SinTheta;
    f64ForceZ = 0.0;

    pForce->SetCoordinates(f64ForceX, f64ForceY, f64ForceZ);

    return TRUE;
}

BOOL CIntegration::RingOfCurrent_Field(const CPoint3D& crRingCentrePoint, const F64 f64Rs, const F64 f64Current, const CPoint3D& crInvestigationPoint, CVector3D *pResult)
{
    F64 f64R_Result, f64Z_Result, f64X_Result, f64Y_Result, f64R_Integral, f64Z_Integral1, f64Z_Integral2, f64N, f64CosTheta, f64SinTheta;

    //f64N = 1000;

    F64 f64R, f64Z;
    f64R = sqrt(crInvestigationPoint.m_f64X * crInvestigationPoint.m_f64X + crInvestigationPoint.m_f64Y * crInvestigationPoint.m_f64Y);
    f64Z = crInvestigationPoint.m_f64Z - crRingCentrePoint.m_f64Z;

    if(f64R < 1E-10)
    {
        f64SinTheta = 0.0;
        f64CosTheta = 0.0;
    }
    else
    {
        f64SinTheta = (crInvestigationPoint.m_f64Y - crRingCentrePoint.m_f64Y) / f64R;
        f64CosTheta = (crInvestigationPoint.m_f64X - crRingCentrePoint.m_f64X) / f64R;
    }

    f64R_Integral = B_Integral1(f64R, f64Rs, f64Z, B_Integral1_Niterations);
    f64R_Result = Mu0 * f64Current / (2 * PI) * f64Z * f64Rs * f64R_Integral;

    f64Z_Integral1 = B_Integral2(f64R, f64Rs, f64Z, B_Integral2_Niterations);
    f64Z_Integral2 = B_Integral1(f64R, f64Rs, f64Z, B_Integral1_Niterations);
    f64Z_Result = Mu0 * f64Current * f64Rs / (2 * PI) * (f64Rs * f64Z_Integral1 - f64R * f64Z_Integral2);

    f64X_Result = f64R_Result * f64CosTheta;
    f64Y_Result = f64R_Result * f64SinTheta;

    pResult->SetCoordinates(f64X_Result, f64Y_Result, f64Z_Result);

    return TRUE;
}

BOOL CIntegration::RingOfCurrent_FieldDerivative(const CPoint3D& crRingCentrePoint, const F64 f64Rs, const F64 f64Current, const CPoint3D& crInvestigationPoint, F64* Field_dBr)
{
    F64 f64_dB_dR_Result, f64_dB_dZ_Result, f64_dIntegral1, f64_dIntegral2;

    F64 f64R, f64Z;
    f64R = sqrt(crInvestigationPoint.m_f64X * crInvestigationPoint.m_f64X + crInvestigationPoint.m_f64Y * crInvestigationPoint.m_f64Y);
    f64Z = crInvestigationPoint.m_f64Z - crRingCentrePoint.m_f64Z;
    U64 u64N = 10000;

    f64_dIntegral1 = dB_Integral1(f64R, f64Rs, f64Z, u64N);
    f64_dIntegral2 = dB_Integral2(f64R, f64Rs, f64Z, u64N);

    f64_dB_dR_Result = -(3 * Mu0 * f64Current * f64Rs) / (2 * PI) * f64Z * (f64R * f64_dIntegral1 - f64Rs * f64_dIntegral2);
    f64_dB_dZ_Result = (Mu0 * f64Current * f64Rs) / (2 * PI) * ((f64R * f64R + f64Rs * f64Rs - 2 * f64Z * f64Z) * f64_dIntegral1 -
                                                                (2 * f64R * f64Rs * f64_dIntegral2));

    Field_dBr[0] = f64_dB_dR_Result;
    Field_dBr[1] = f64_dB_dZ_Result;

    return TRUE;
}

F64 CIntegration::B_Integral1(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N)
{
    F64 f64LowLimit, f64TopLimit, f64Step, f64Result;
    f64LowLimit = LowLimit;
    f64TopLimit = TopLimit;
    f64Step = (f64TopLimit - f64LowLimit) / f64N;
    f64Result = 0.0;

    F64 f64CurrentValue;

    for(F64 f64Phi = f64LowLimit; f64Phi < f64TopLimit; f64Phi += f64Step)
    {
        f64CurrentValue = B_IntegralFunction1(f64Phi, f64R, f64Rs, f64Z);
        f64Result += f64CurrentValue * f64Step;
    }

    return f64Result;
}

F64 CIntegration::B_Integral2(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N)
{
    F64 f64LowLimit, f64TopLimit, f64Step, f64Result;
    f64LowLimit = LowLimit;
    f64TopLimit = TopLimit;
    f64Step = (f64TopLimit - f64LowLimit) / f64N;
    f64Result = 0.0;

    F64 f64CurrentValue;

    for(F64 f64Phi = f64LowLimit; f64Phi < f64TopLimit; f64Phi += f64Step)
    {
        f64CurrentValue = B_IntegralFunction2(f64Phi, f64R, f64Rs, f64Z);
        f64Result += f64CurrentValue * f64Step;
    }

    return f64Result;
}

F64 CIntegration::dB_Integral1(F64 f64R, F64 f64Rs, F64 f64Z, U64 u64N)
{
    F64 f64LowLimit, f64TopLimit, f64Step, f64Result;
    f64LowLimit = LowLimit;
    f64TopLimit = TopLimit;
    f64Step = (f64TopLimit - f64LowLimit) / static_cast<F64>(u64N);
    f64Result = 0.0;

    F64 f64CurrentValue;

    for(F64 f64Phi = f64LowLimit; f64Phi < f64TopLimit; f64Phi += f64Step)
    {
        f64CurrentValue = dB_IntegralFunction1(f64Phi, f64R, f64Rs, f64Z);
        f64Result += f64CurrentValue * f64Step;
    }
    return f64Result;
}

F64 CIntegration::dB_Integral2(F64 f64R, F64 f64Rs, F64 f64Z, U64 u64N)
{
    F64 f64LowLimit, f64TopLimit, f64Step, f64Result;
    f64LowLimit = LowLimit;
    f64TopLimit = TopLimit;
    f64Step = (f64TopLimit - f64LowLimit) / static_cast<F64>(u64N);
    f64Result = 0.0;

    F64 f64CurrentValue;

    for(F64 f64Phi = f64LowLimit; f64Phi < f64TopLimit; f64Phi += f64Step)
    {
        f64CurrentValue = dB_IntegralFunction2(f64Phi, f64R, f64Rs, f64Z);
        f64Result += f64CurrentValue * f64Step;
    }
    return f64Result;
}


F64 CIntegration::B_IntegralFunction1(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z)
{
    F64 f64CosPhi = cos(f64Phi);
    F64 f64Result = f64CosPhi / pow(f64R * f64R + f64Rs * f64Rs + f64Z * f64Z - 2 * f64R * f64Rs * f64CosPhi, 1.5);

    return f64Result;
}

F64 CIntegration::B_IntegralFunction2(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z)
{
    F64 f64CosPhi = cos(f64Phi);
    F64 f64Result = 1 / pow(f64R * f64R + f64Rs * f64Rs + f64Z * f64Z - 2 * f64R * f64Rs * f64CosPhi, 1.5);

    return f64Result;
}

F64 CIntegration::dB_IntegralFunction1(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z)
{
    F64 f64CosPhi = cos(f64Phi);
    F64 f64Result = f64CosPhi / pow(f64R * f64R + f64Rs * f64Rs + f64Z * f64Z - 2 * f64R * f64Rs * f64CosPhi, 2.5);

    return f64Result;
}

F64 CIntegration::dB_IntegralFunction2(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z)
{
    F64 f64CosPhi = cos(f64Phi);
    F64 f64Result = f64CosPhi * f64CosPhi / pow(f64R * f64R + f64Rs * f64Rs + f64Z * f64Z - 2 * f64R * f64Rs * f64CosPhi, 2.5);

    return f64Result;
}

} /* End of namespace MAGNETICFIELD */
