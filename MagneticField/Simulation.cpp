#include <iostream>

#include "MagneticFieldStable.h"

using namespace Tools;
using namespace MagneticField;

/*
 * Model
 *
 * dX / dt = F(t, X)
 *
 * X = [x,  Vx, y,  Vy]
 * F = [Vx, Ax, Vy, Ay]
 *
*/

inline BOOL GetF(const CVector4D& crX, const Solenoid& crSolenoid, Ball& rBall, CPoint3D& rInvestigationPoint, CVector4D* pF)
{
    CVector3D Force3D;
    rInvestigationPoint.SetCoordinates(crX.m_f64X1, crX.m_f64X3, crSolenoid.m_SolenoidEdge1.m_f64Z);

    CIntegration::IntegrateSolenoid_Force(crSolenoid, rBall, rInvestigationPoint, 1000, &Force3D);

    F64 Ax, Ay;
    Ax = Force3D.m_f64X / rBall.m_f64M;
    Ay = Force3D.m_f64Y / rBall.m_f64M;

    pF->m_f64X1 = crX.m_f64X2;      /* X1 - Vx */
    pF->m_f64X2 = Ax;               /* X2 - Ax */
    pF->m_f64X3 = crX.m_f64X4;      /* X3 - Vy */
    pF->m_f64X4 = Ay;               /* X4 - Ay */

    return TRUE;
}

inline BOOL GetF_R2(const CVector4D& crX, const Solenoid& crSolenoid, Ball& rBall, CPoint3D& rInvestigationPoint, CVector4D* pF)
{
    F64 f64R = sqrt(crX.m_f64X1 * crX.m_f64X1 + crX.m_f64X3 * crX.m_f64X3);

    if(f64R < 1E-5)
    {
        pF->SetCoordinates(crX.m_f64X2, 0.0, crX.m_f64X4, 0.0);
        return TRUE;
    }

    F64 f64F = -1 / (f64R * f64R);
    F64 f64Cos, F64Sin;

    f64Cos = crX.m_f64X1 / f64R;
    F64Sin = crX.m_f64X3 / f64R;

    F64 f64Fx, f64Fy;
    f64Fx = f64F * f64Cos;
    f64Fy = f64F * F64Sin;

    printf("Fx = %f,    Fy = %f\n", f64Fx, f64Fy);

    pF->SetCoordinates(crX.m_f64X2, f64Fx, crX.m_f64X4, f64Fy);

    return TRUE;
}

BOOL Runge_Kutta_4(CVector4D X, F64 f64T_0, F64 f64H, size_t zNIterations, Solenoid solenoid, Ball ball, std::vector<CPoint3D>* pTrajectory)
{
    CPoint3D InvestigationPoint, TrajectoryPoint;

    CVector4D F, F1, K1, K2, K3, K4;

    CVector4D X_half;

    for(size_t i = 0; i < zNIterations; ++i)
    {
        GetF_R2(X, solenoid, ball, InvestigationPoint, &F1);

        K1 = F1 * f64H;
        X = X + K1 * (f64H / 2);

        TrajectoryPoint.SetCoordinates(X.m_f64X1, X.m_f64X3, 0.0);
        //TrajectoryPoint.Print();
        //X.Print();

        pTrajectory->push_back(TrajectoryPoint);
    }

    return TRUE;
}

void PrintLaunchParameters(const Solenoid& crSolenoid, const Ball& crBall)
{
    std::cout << "##### SIMULATION APPLICATION #####\n" << std::endl;
    std::cout << "Parameters used in calculations:\n" << std::endl;
    std::cout << "SOLENOID  parameters" << std::endl;
    std::cout << "\tRs = " << crSolenoid.m_f64Rs << std::endl;
    std::cout << "\tCore Mu = " << crSolenoid.m_f64Core_Mu << std::endl;
    std::cout << "\tEdge1_z = " << crSolenoid.m_SolenoidEdge1.m_f64Z << std::endl;
    std::cout << "\tEdge2_z = " << crSolenoid.m_SolenoidEdge2.m_f64Z << std::endl;
    std::cout << std::endl;

    std::cout << "BALL parameters" << std::endl;
    std::cout << "\tRadius = " << crBall.m_f64Radius << std::endl;
    std::cout << "\tVolume = " << crBall.m_f64Volume << std::endl;
    std::cout << "\tM = " << crBall.m_f64M << std::endl;
    std::cout << "\tMu = " << crBall.m_f64Mu << std::endl;

    std::cout << std::endl << std::endl;
}

int main()
{
    CPoint3D SolenoidEdge1(0.0, 0.0, 0.0);
    CPoint3D SolenoidEdge2(0.0, 0.0, -0.15);

    Solenoid solenoid;

    solenoid.m_f64Rs = 0.005;
    solenoid.m_SolenoidEdge1.Copy(SolenoidEdge1);
    solenoid.m_SolenoidEdge2.Copy(SolenoidEdge2);
    solenoid.m_f64Current = 1.0;
    solenoid.m_f64Core_Mu = 400.0;
    solenoid.m_u64NSourcePoints = 100;

    Ball ball;
    ball.m_f64Mu = 5000;
    ball.m_f64Radius = 5E-4;
    ball.m_f64Volume = 4 / 3 * PI * ball.m_f64Radius * ball.m_f64Radius * ball.m_f64Radius;
    ball.m_f64M = ball.m_f64Volume * 7700.0;

    PrintLaunchParameters(solenoid, ball);

    F64 f64X, f64Y, f64T;
    U64 u64NIterations = 100;

    f64X = 0.006;
    f64Y = 0.0;
    f64T = 0.0;
    CVector4D vBodyState(f64X, 0.0, f64Y, 0.1);     /* X1 - X ##### X2 - Vx ##### X3 - Y ##### X4 - Vy */

    std::vector<CPoint3D> Trajectory;
    Trajectory.reserve(u64NIterations);

    Runge_Kutta_4(vBodyState, f64T, 1E-2, u64NIterations, solenoid, ball, &Trajectory);

    std::list<F64>* pColumn1 = new std::list<F64>;
    std::list<F64>* pColumn2 = new std::list<F64>;

    for(U64 i = 0; i < u64NIterations; ++i)
    {
        pColumn1->push_back(Trajectory[i].m_f64X);
        pColumn2->push_back(Trajectory[i].m_f64Y);
    }

    std::list<std::list<F64>*> lst;
    lst.push_back(pColumn1);
    lst.push_back(pColumn2);

    CMathFunc::WriteCSV(lst, "/home/mark/Documents/MagneticField_Data/Traj.csv");

    return 0;
}
