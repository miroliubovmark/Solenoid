#include <iostream>

#include "MagneticFieldStable.h"

using namespace Tools;
using namespace MagneticField;

BOOL IntegrateRingOfCurrent_Test()
{
    F64 f64R = 0.025;      /* m */
    F64 f64Current = 1;    /* A */
    U64 u64NVertexes = 360;

    CPoint3D RingCentrePoint(0.0, 0.0, 0.0);
    CPoint3D InvestigationPoint(0.0, 0.0, 0.0);

    CVector3D B;

    CIntegration::IntegrateRingOfCurrent(RingCentrePoint, f64R, f64Current, InvestigationPoint, u64NVertexes, &B);
    printf("B = ");
    B.Print();

    return TRUE;
}

BOOL CompareIntegration()
{
    CPoint3D RingCentrePoint(0.0, 0.0, 0.0);
    CPoint3D InvPoint(0.0, 0.0, 0.0);

    CVector3D B1, B2;

    B1.Clear();
    B2.Clear();

    F64 f64Rs = 0.025;
    F64 f64Current = 1;

    for(F64 f64InvX = 0.0; f64InvX < 1.0; f64InvX += 0.02)
    {
        /* Bio-Savar */
        CIntegration::IntegrateRingOfCurrent(RingCentrePoint, f64Rs, f64Current, InvPoint, 720, &B1);

        /* New method */
        CIntegration::RingOfCurrent_Field(RingCentrePoint, f64Rs, f64Current, InvPoint, &B2);

        printf("%f\n", B2.m_f64Z / B1.m_f64Z);

        //printf("B1\n");
        //B1.Print();
        //printf("\n");

        //printf("B2\n");
        //B2.Print();
    }

    return TRUE;
}

BOOL Test1()
{
    CPoint3D RingCentrePoint(0.0, 0.0, -0.1);
    CPoint3D InvPoint(0.5, 0.0, 0.0);

    CVector3D B;

    F64 f64Rs = 0.025;
    F64 f64Current = 1;

    CIntegration::RingOfCurrent_Field(RingCentrePoint, f64Rs, f64Current, InvPoint, &B);

    return  TRUE;
}

BOOL Test2()
{
    CPoint3D RingCentrePoint(0.0, 0.0, -0.1);
    CPoint3D InvPoint(0.035, 0.0, -0.05);

    CVector3D B;

    F64 f64Rs = 0.025;
    F64 f64Current = 100;

    for(F64 f64R = 0.0; f64R < 10.0; f64R += 10E-2)
    {
        //F64 f64Result = CIntegration::Br_IntegralFunction(0, f64R, f64Rs, -0.1);
        F64 f64Result = CIntegration::Br_Integral(f64R, f64Rs, -0.1, 100);
        CIntegration::RingOfCurrent_Field(RingCentrePoint, f64Rs, f64Current, InvPoint, &B);
        printf("%f\n", f64Result);
    }

    //CIntegration::RingOfCurrent_Field(RingCentrePoint, f64Rs, f64Current, InvPoint, &B);
    printf("B = ");
    B.Print();

    return  TRUE;
}

int main()
{
    printf("========= MagneticFieldTest =========\n\n");
    printf("Hello world!\n");

    //IntegrateRingOfCurrent_Test();

    CompareIntegration();

    //Test2();

    return 0;
}
