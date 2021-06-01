#include <iostream>

#include "MagneticFieldStable.h"


#define strCellSize 30

using namespace Tools;
using namespace MagneticField;



int main()
{
    /** Radius of solenoid */
    F64 f64Rs = 0.005;              /* m */

    /** Current in wire */
    F64 f64Current = 1;             /* A */

    CPoint3D RingCentrePoint(0.0, 0.0, 0.0);
    CPoint3D InvestigationPoint;
    CVector3D B;

    std::list<std::list<F64>*> lstResult;
    std::string strHeader("");

    F64 f64InitX, f64InitY, f64InitZ;
    f64InitX = 0.0;
    f64InitY = 0.0;
    f64InitZ = 0.0;

    F64 f64Discretization = 1E-4;
    F64 f64X_InitStep = 0.0005;
    F64 f64X_CurrentStep;

    CVector3D B0;
    CPoint3D InitInvestigationPoint(0.0, 0.0, 0.0);
    CIntegration::RingOfCurrent_Field(RingCentrePoint, f64Rs, f64Current, InitInvestigationPoint, &B0);

    F64 f64AbsB0 = B0.GetAbs();


    F64 f64X, f64Y, f64Z;
    BOOL bFlag;


    while(f64InitX < f64Rs - 0.0004)
    {
        f64X = f64InitX;
        f64Y = f64InitY;
        f64Z = f64InitZ;

        InvestigationPoint.SetCoordinates(f64X, f64Y, f64Z);

        std::list<F64>* plstOfPoints_X = new std::list<F64>;
        std::list<F64>* plstOfPoints_Y = new std::list<F64>;
        std::list<F64>* plstOfPoints_Z = new std::list<F64>;

        F64 f64XLimit, f64ZLimit;
        f64XLimit = 0.05;
        f64ZLimit = 0.05;

        bFlag = TRUE;

        while(InvestigationPoint.m_f64Z >= 0.0)
        {
            if((fabs(InvestigationPoint.m_f64X) > f64XLimit) || (fabs(InvestigationPoint.m_f64Z) > f64ZLimit))
            {
                break;
            }

            plstOfPoints_X->push_back(InvestigationPoint.m_f64X);
            plstOfPoints_Y->push_back(InvestigationPoint.m_f64Y);
            plstOfPoints_Z->push_back(InvestigationPoint.m_f64Z);

            //CIntegration::RingOfCurrent_BioSavar(RingCentrePoint, f64Rs, f64Current, InvestigationPoint, 10000, &B);
            CIntegration::RingOfCurrent_Field(RingCentrePoint, f64Rs, f64Current, InvestigationPoint, &B);

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

        printf("%f\n", f64InitX);
    }

    strHeader += '\n';

    std::string strFileName("/home/mark/Documents/MagneticField_Data/LinesOfForce_Int_updated.csv");
    CMathFunc::WriteCSV(lstResult, strFileName, strHeader);

    return 0;
}
