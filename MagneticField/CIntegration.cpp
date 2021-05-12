#include "CIntegration.h"

namespace MagneticField
{

CIntegration::CIntegration()
{
}

CIntegration::~CIntegration()
{
}

BOOL CIntegration::IntegrateRingOfCurrent(const CPoint3D RingCentrePoint, const F64 f64R, const F64 f64Current, const CPoint3D InvestigationPoint, const U64 u64NVertexes, CVector3D *pResult)
{
    F64 f64Phi = 2 * PI / static_cast<F64>(u64NVertexes);

    F64 f64CosPhi = cos(f64Phi);
    F64 f64SinPhi = sin(f64Phi);

    CVector3D* pCentreToInvPoint = new CVector3D(RingCentrePoint, InvestigationPoint);
    CVector3D* pCurrentRadialVector = new CVector3D(f64R, 0.0, 0.0);
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
        pCurrentB->MultiplyOnScalar(f64Current / pow(pRadiusVector->GetAbs(), 3));

        pB->SetVectorSum(pB, pCurrentB);

        /* Update CurrentRadialVector for the next step */
        pCurrentRadialVector->Copy(pNextRadialVector);

        /*
        printf("dl::  ");
        pdL->Print();
        printf("RV::  ");
        pRadiusVector->Print();
        printf("\n");
        */
    }

    pResult->Copy(pB);

    return TRUE;
}
BOOL CIntegration::IntegrateSolenoid(const F64 f64Rs, const CPoint3D Border1, const CPoint3D Border2, const CPoint3D InvestigationPoint, U64 u64N, F64 I_0, F64 WireDensity, CVector3D *pResult)
{
    F64 f64Step;
    f64Step = (Border2.m_f64Z - Border1.m_f64Z) / u64N;

    CPoint3D RingCentrePoint;
    CVector3D CurrentB;

    F64 X, Y, Z, Current;

    for(U64 i = 0; i < u64N; i += 1)
    {
        X = Border1.m_f64X;
        Y = Border2.m_f64Y;
        Z = Border1.m_f64Z + f64Step * i;
        RingCentrePoint.SetCoordinates(X, Y, Z);

        Current = I_0 * WireDensity * f64Step;

        RingOfCurrent_Field(RingCentrePoint, f64Rs, Current, InvestigationPoint, &CurrentB);
        pResult->SetVectorSum(*pResult, CurrentB);
    }

    return TRUE;
}

BOOL CIntegration::RingOfCurrent_Field(const CPoint3D RingCentrePoint, const F64 f64Rs, const F64 f64Current, const CPoint3D InvestigationPoint, CVector3D *pResult)
{
    F64 f64R_Result, f64Z_Result, f64X_Result, f64Y_Result, f64R_Integral, f64Z_Integral1, f64Z_Integral2, f64N, f64CosTheta, f64SinTheta;

    f64N = 720;

    F64 f64R, f64Z;
    f64R = sqrt(InvestigationPoint.m_f64X * InvestigationPoint.m_f64X + InvestigationPoint.m_f64Y * InvestigationPoint.m_f64Y);
    f64Z = InvestigationPoint.m_f64Z - RingCentrePoint.m_f64Z;

    f64SinTheta = (InvestigationPoint.m_f64Y - RingCentrePoint.m_f64Y) / f64R;
    f64CosTheta = (InvestigationPoint.m_f64X - RingCentrePoint.m_f64X) / f64R;

    f64R_Integral = Br_Integral(f64R, f64Rs, RingCentrePoint.m_f64Z, f64N);
    f64R_Result = Mu0 * f64Current / (2 * PI) * (InvestigationPoint.m_f64Z - RingCentrePoint.m_f64Z) * f64Rs * f64R_Integral;

    f64Z_Integral1 = Bz_Integral1(f64R, f64Rs, f64Z, f64N);
    f64Z_Integral2 = Bz_Integral2(f64R, f64Rs, f64Z, f64N);
    f64Z_Result = Mu0 * f64Current / (2 * PI) * f64Rs * (f64Rs * f64Z_Integral1 - f64R * f64Z_Integral2);

    f64X_Result = f64R_Result * f64CosTheta;
    f64Y_Result = f64R_Result * f64SinTheta;

    pResult->SetCoordinates(f64X_Result, f64Y_Result, f64Z_Result);

    return TRUE;
}

F64 CIntegration::Br_Integral(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N)
{
    F64 f64LowLimit, f64TopLimit, f64Step, f64Result;
    f64LowLimit = 0.0;
    f64TopLimit = PI;
    f64Step = 2 * PI / f64N;
    f64Result = 0.0;

    F64 f64CurrentValue;

    for(F64 f64Phi = f64LowLimit; f64Phi < f64TopLimit; f64Phi += f64Step)
    {
        f64CurrentValue = Br_IntegralFunction(f64Phi, f64R, f64Rs, f64Z);
        f64Result += f64CurrentValue * f64Step;
    }

    return f64Result;
}

F64 CIntegration::Bz_Integral1(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N)
{
    F64 f64LowLimit, f64TopLimit, f64Step, f64Result;
    f64LowLimit = 0.0;
    f64TopLimit = PI;
    f64Step = 2 * PI / f64N;
    f64Result = 0.0;

    F64 f64CurrentValue;

    for(F64 f64Phi = f64LowLimit; f64Phi < f64TopLimit; f64Phi += f64Step)
    {
        f64CurrentValue = Bz_IntegralFunction1(f64Phi, f64R, f64Rs, f64Z);
        f64Result += f64CurrentValue * f64Step;
    }

    return f64Result;
}

F64 CIntegration::Bz_Integral2(F64 f64R, F64 f64Rs, F64 f64Z, F64 f64N)
{
    F64 f64LowLimit, f64TopLimit, f64Step, f64Result;
    f64LowLimit = 0.0;
    f64TopLimit = PI;
    f64Step = 2 * PI / f64N;
    f64Result = 0.0;

    F64 f64CurrentValue;

    for(F64 f64Phi = f64LowLimit; f64Phi < f64TopLimit; f64Phi += f64Step)
    {
        f64CurrentValue = Bz_IntegralFunction2(f64Phi, f64R, f64Rs, f64Z);
        f64Result += f64CurrentValue * f64Step;
    }

    return f64Result;
}

F64 CIntegration::Br_IntegralFunction(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z)
{
    F64 f64CosPhi = cos(f64Phi);
    F64 f64Result = f64CosPhi / pow(f64R * f64R + f64Rs * f64Rs + f64Z * f64Z - 2 * f64R * f64Rs * f64CosPhi, 1.5);

    return f64Result;
}

F64 CIntegration::Bz_IntegralFunction1(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z)
{
    F64 f64CosPhi = cos(f64Phi);
    F64 f64Result = f64Phi / pow(f64R * f64R + f64Rs * f64Rs + f64Z * f64Z - 2 * f64R * f64Rs * f64CosPhi, 1.5);

    return f64Result;
}

F64 CIntegration::Bz_IntegralFunction2(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z)
{
    F64 f64CosPhi = cos(f64Phi);
    F64 f64Result = f64CosPhi / pow(f64R * f64R + f64Rs * f64Rs + f64Z * f64Z - 2 * f64R * f64Rs * f64CosPhi, 1.5);

    return f64Result;
}

} /* End of namespace MAGNETICFIELD */
