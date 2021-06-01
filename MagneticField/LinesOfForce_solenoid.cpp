#include <iostream>

#include "MagneticFieldStable.h"


#define strCellSize 30

using namespace Tools;
using namespace MagneticField;



int main()
{   
    /** Radius of solenoid */
    F64 f64Rs = 0.005;              /* m */

    /** Geometric parameters of solenoid */
    const CPoint3D SolenoidEdge1(0.0, 0.0, 0.0);
    const CPoint3D SolenoidEdge2(0.0, 0.0, -0.15);

    /** Current in wire */
    F64 f64Current = 1;             /* A */

    /** Number of Source Points in solenoid */
    U64 u64NSourcePoints = 100;

    /** Wire density */
    F64 f64WireDensity = 1000;

    /** Mu of solenoid core */
    F64 f64Core_Mu = 400.0;

    /** Solenoid structure */
    Solenoid solenoid;

    /* Fill solenoid structure */
    solenoid.m_f64Current = f64Current;
    solenoid.m_f64Rs = f64Rs;
    solenoid.m_f64Core_Mu = f64Core_Mu;
    solenoid.m_SolenoidEdge1.Copy(SolenoidEdge1);
    solenoid.m_SolenoidEdge2.Copy(SolenoidEdge2);
    solenoid.m_u64NSourcePoints = u64NSourcePoints;

    /** Investigation point */
    CPoint3D InvestigationPoint;

    /** Vectors of magnetic induction */
    CVector3D B, B0;

    /** List of data that will be written to CSV file */
    std::list<std::list<F64>*> lstResult;

    /** Header line for CSV file */
    std::string strHeader("");

    /** Initial coordinates for the begining of first line */
    F64 f64InitX, f64InitY, f64InitZ;

    f64InitX = solenoid.m_SolenoidEdge1.m_f64X;
    f64InitY = solenoid.m_SolenoidEdge1.m_f64Y;
    f64InitZ = (solenoid.m_SolenoidEdge1.m_f64Z + solenoid.m_SolenoidEdge2.m_f64Z) / 2;

    F64 f64Discretization = 1E-3;
    F64 f64X_InitStep = 5E-4;
    F64 f64X_CurrentStep;

    CPoint3D InitInvestigationPoint(f64InitX, f64InitY, f64InitZ);
    //CIntegration::RingOfCurrent_Field(RingCentrePoint, f64Rs, f64Current, InitInvestigationPoint, &B0);
    CIntegration::IntegrateSolenoid_Field(solenoid, InitInvestigationPoint, f64WireDensity, &B0);

    /** Absolute value of magnetic induction in the centre of solenoid */
    F64 f64AbsB0 = B0.GetAbs();


    F64 f64X, f64Y, f64Z;
    BOOL bFlag;

    /** Size of the area where the field is conserving */
    F64 f64XLimit, f64ZLimit;
    f64XLimit = 0.20;
    f64ZLimit = 0.20;

    /* Cycle for building lines of force with initial point in the central section of solenoid */
    while(f64InitX < f64Rs - 0.0001)
    {
        f64X = f64InitX;
        f64Y = f64InitY;
        f64Z = f64InitZ;

        InvestigationPoint.SetCoordinates(f64X, f64Y, f64Z);

        std::list<F64>* plstOfPoints_X = new std::list<F64>;
        std::list<F64>* plstOfPoints_Y = new std::list<F64>;
        std::list<F64>* plstOfPoints_Z = new std::list<F64>;

        bFlag = TRUE;

        /* Cycle for building line of force from the specified initial point */
        while(InvestigationPoint.m_f64Z >= f64InitZ)
        {
            if((fabs(InvestigationPoint.m_f64X - f64InitX) > f64XLimit) || (fabs(InvestigationPoint.m_f64Z - f64InitZ) > f64ZLimit))
            {
                break;
            }

            plstOfPoints_X->push_back(InvestigationPoint.m_f64X);
            plstOfPoints_Y->push_back(InvestigationPoint.m_f64Y);
            plstOfPoints_Z->push_back(InvestigationPoint.m_f64Z);

            CIntegration::IntegrateSolenoid_Field(solenoid, InvestigationPoint, f64WireDensity, &B);

            if(bFlag)
            {
                f64X_CurrentStep = f64X_InitStep * f64AbsB0 / B.GetAbs();
                printf("CurrentStep = %f\n", f64X_CurrentStep);
                bFlag = FALSE;
            }

            B.MultiplyOnScalar(f64Discretization / B.GetAbs());

            InvestigationPoint.AppendVector(B);
        }

        lstResult.push_back(plstOfPoints_X);
        lstResult.push_back(plstOfPoints_Y);
        lstResult.push_back(plstOfPoints_Z);

        strHeader += std::to_string(f64InitX) + ',' + std::to_string(f64InitX) + ',' + std::to_string(f64InitX) + ',';

        f64InitX += f64X_CurrentStep;

        printf("InitX = %f\n", f64InitX);
    }

    strHeader += '\n';

    std::string strFileName("/home/mark/Documents/MagneticField_Data/LinesOfForce_solenoid.csv");
    CMathFunc::WriteCSV(lstResult, strFileName, strHeader);

    return 0;
}
