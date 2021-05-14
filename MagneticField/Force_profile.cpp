#include <iostream>

#include "MagneticFieldStable.h"

using namespace Tools;
using namespace MagneticField;

void LaunchInfo()
{
    std::cout << "FORCE PROFILE" << std::endl;
}

void PrintVector(std::vector<F64> Vector)
{

    for(std::vector<F64>::iterator iter(Vector.begin()); iter != Vector.end(); ++iter)
    {
        printf("%f\n", *iter);
    }
}

//void()

int main()
{
    LaunchInfo();

    /** Length of solenoid */
    F64 f64SolenoidLength = 0.2;    /* m */

    /** Radius of solenoid */
    F64 f64Rs = 0.025;              /* m */

    /** Geometric parameters of solenoid */
    const CPoint3D SolenoidEdge1(0.0, 0.0, 0.0);
    const CPoint3D SolenoidEdge2(0.0, 0.0, -f64SolenoidLength);

    /** Current in wire */
    F64 f64Current = 1;             /* A */

    /** Number of Source Points in solenoid */
    U64 u64NSourcePoints = 1000;

    /** Wire density */
    F64 WireDensity = 1000;

    /** Fill solenoid structure */
    Solenoid solenoid;
    solenoid.m_f64Current = f64Current;
    solenoid.m_f64Rs = f64Rs;
    solenoid.m_f64SolenoidLength = f64SolenoidLength;
    solenoid.m_SolenoidEdge1.Copy(SolenoidEdge1);
    solenoid.m_SolenoidEdge2.Copy(SolenoidEdge2);
    solenoid.m_u64NSourcePoints = u64NSourcePoints;


    /** Investigation Point */
    CPoint3D InvestigationPoint;

    /** Number of Investigation points */
    U64 u64NInvestigationPoints = 3;

    /** Range of Investigation Point x-coordinate */
    F64 f64R1, f64R2;
    f64R1 = f64Rs + 0.01;
    f64R2 = 1;                      /* m */

    /** Distance between Investigation Points */
    F64 f64Step = (f64R2 - f64R1) / u64NInvestigationPoints;

    /** Coordinates of Investigation Point */
    F64 f64InvPointX, f64InvPointY, f64InvPointZ;

    /** Investigation Point initial coordinates */
    f64InvPointX = f64R1;
    f64InvPointY = solenoid.m_SolenoidEdge1.m_f64Y;
    f64InvPointZ = solenoid.m_SolenoidEdge1.m_f64Z;

    /** Vector of magnetic induction */
    CVector3D B;

    /** Vector of Investigation Point x-coordinate*/
    std::vector<F64> VOfX;

    /** Vector of B for Investigation Points */
    std::vector<CVector3D> VOfB;

    VOfX.reserve(u64NInvestigationPoints);
    VOfB.reserve(u64NInvestigationPoints);


    for(U64 u64i = 0; u64i < u64NInvestigationPoints; ++u64i)
    {
        f64InvPointX = f64R1 + f64Step * static_cast<F64>(u64i);
        InvestigationPoint.SetCoordinates(f64InvPointX, f64InvPointY, f64InvPointZ);

        CIntegration::IntegrateSolenoid(solenoid, InvestigationPoint, WireDensity, &B);

        VOfX.push_back(f64InvPointX);
        VOfB.push_back(B);
    }


    PrintVector(VOfX);
    return 0;
}
