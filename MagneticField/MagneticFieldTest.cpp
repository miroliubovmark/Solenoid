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

int main()
{
    printf("========= MagneticFieldTest =========\n\n");
    printf("Hello world!\n");

    IntegrateRingOfCurrent_Test();

    return 0;
}
