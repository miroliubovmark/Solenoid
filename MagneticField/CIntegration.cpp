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

} /* End of namespace MAGNETICFIELD */
