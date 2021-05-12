#include <iostream>

#include "MagneticFieldStable.h"

using namespace Tools;
using namespace MagneticField;

int main()
{
    printf("main()\n");

    F64 f64H_0 = 0.20;     /* m */
    F64 f64Rs = 0.025;      /* m */
    F64 f64Current = 1;    /* A */
    U64 u64NVertexes = 360;
    F64 dz = 0.2;
    F64 n = 1000;
    U64 N = 100;
    F64 I_0 = 1;

    CPoint3D Border1(0.0, 0.0, 0.0);
    CPoint3D Border2(0.0, 0.0, -f64H_0);
    CPoint3D RingCentrePoint(0.0, 0.0, 0.0);
    CPoint3D InvestigationPoint(0.1, 0.0, 0.0);
    CVector3D Result;

    //CIntegration::IntegrateRingOfCurrent(RingCentrePoint, f64R, f64Current, InvestigationPoint, u64NVertexes);

    F64 f64CurrentInRing = f64Current * n * dz;
    //CIntegration::RingOfCurrent_Field(RingCentrePoint, f64Rs, f64CurrentInRing, InvestigationPoint, &Result);
    CIntegration::IntegrateSolenoid(f64Rs, Border1, Border2, InvestigationPoint, N, I_0, n, &Result);
    Result.Print();
    return 0;
}
