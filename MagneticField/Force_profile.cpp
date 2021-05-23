#include <iostream>

#include "MagneticFieldStable.h"


#define strCellSize 30

using namespace Tools;
using namespace MagneticField;

void PrintVector(std::vector<F64> Vector)
{
    for(std::vector<F64>::iterator iter(Vector.begin()); iter != Vector.end(); ++iter)
    {
        printf("%f\n", *iter);
    }
}

BOOL WriteForceProfileToCSV(std::string strFileName, const std::vector<F64>& crVOfX, const std::vector<CVector3D>& crVOfB)
{
    std::ofstream DestinationFile;
    DestinationFile.open(strFileName, std::ofstream::out);

    std::string strX;
    std::string strBx;
    std::string strBy;
    std::string strBz;
    std::string strLine;

    strX.reserve(strCellSize);
    strBx.reserve(strCellSize);
    strBy.reserve(strCellSize);
    strBz.reserve(strCellSize);

    std::string strHeaderLine = "R, Bx, By, Bz\n";
    DestinationFile.write(strHeaderLine.c_str(), static_cast<S64>(strHeaderLine.size()));

    for(size_t i = 0; i < crVOfX.size(); ++i)
    {
        strX = std::to_string(crVOfX[i]);
        strBx = std::to_string(crVOfB[i].m_f64X);
        strBy = std::to_string(crVOfB[i].m_f64Y);
        strBz = std::to_string(crVOfB[i].m_f64Z);

        strLine = strX + "," + strBx + "," + strBy + "," + strBz + "\n";

        DestinationFile.write(strLine.c_str(), static_cast<S64>(strLine.size()));
    }

    DestinationFile.close();

    return TRUE;
}

void PrintLaunchInfo(Solenoid solenoid, U64 u64NInvPoints, F64 f64R1, F64 f64R2)
{
    std::cout << "##### FORCE PROFILE APPLICATION #####\n" << std::endl;
    std::cout << "Parameters used in computations:\n" << std::endl;
    std::cout << "SOLENOID  parameters" << std::endl;
    std::cout << "\tRs = " << solenoid.m_f64Rs << std::endl;
    std::cout << "\tLength = " << solenoid.m_f64SolenoidLength << std::endl;
    std::cout << "\tEdge1_z = " << solenoid.m_SolenoidEdge1.m_f64Z << std::endl;
    std::cout << "\tEdge2_z = " << solenoid.m_SolenoidEdge2.m_f64Z << std::endl;
    std::cout << std::endl;

    std::cout << "INVESTIGATION POINTS  parameters" << std::endl;
    std::cout << "\tNInvestigationPoints = " << u64NInvPoints << std::endl;
    std::cout << "\tMIN distance = " << f64R1 << std::endl;
    std::cout << "\tMAX distance = " << f64R2 << std::endl;

    std::cout << std::endl << std::endl;
}

int main()
{
    /** Length of solenoid */
    F64 f64SolenoidLength = 0.01;    /* m */

    /** Radius of solenoid */
    F64 f64Rs = 0.025;              /* m */

    /** Geometric parameters of solenoid */
    const CPoint3D SolenoidEdge1(0.0, 0.0, -0.05);
    const CPoint3D SolenoidEdge2(0.0, 0.0, -0.15);

    /** Current in wire */
    F64 f64Current = 1;             /* A */

    /** Number of Source Points in solenoid */
    U64 u64NSourcePoints = 1;

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
    U64 u64NInvestigationPoints = 1000;

    /** Range of Investigation Point x-coordinate */
    F64 f64R1, f64R2;
    f64R1 = f64Rs + 0.0001;
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
    CVector3D B;    //B1, B2, B_BS;

    /** Vector of magnetic field derivative */
    CVector3D dB;

    /** Vector of Investigation Point x-coordinate*/
    std::vector<F64> VOfX;

    /** Vector of B for Investigation Points */
    std::vector<CVector3D> VOfB1;
    std::vector<CVector3D> VOfB2;
    std::vector<CVector3D> VOfB_BS;

    /** Magnetic moment */
    CVector3D MagneticMoment;

    /** Volume of the ball */
    F64 f64V = 1;

    /** Force */
    CVector3D F;

    PrintLaunchInfo(solenoid, u64NInvestigationPoints, f64R1, f64R2);

    VOfX.reserve(u64NInvestigationPoints);
    VOfB1.reserve(u64NInvestigationPoints);
    VOfB2.reserve(u64NInvestigationPoints);
    VOfB_BS.reserve(u64NInvestigationPoints);

    CPoint3D RingCentrePoint(0.0, 0.0, -0.1);


    std::list<F64> lst_Bx, lst_By, lst_Bz, lst_dBr_dr, lst_dBr_dz, lst_Fr, lst_x;
    std::list<std::list<F64>*> lstData;

    F64 Field_dBr[2];

    F64 f64MagneticMoment_R, f64F1, f64F2, f64Fr;

    for(U64 u64i = 0; u64i < u64NInvestigationPoints; ++u64i)
    {
        /* Update investigation point */
        f64InvPointX = f64R1 + f64Step * static_cast<F64>(u64i);
        InvestigationPoint.SetCoordinates(f64InvPointX, f64InvPointY, f64InvPointZ);

        /* Get field and field derivatives */
        CIntegration::RingOfCurrent_Field(RingCentrePoint, f64Rs, f64Current * WireDensity * 0.1, InvestigationPoint, &B);
        CIntegration::RingOfCurrent_FieldDerivative(RingCentrePoint, f64Rs, f64Current * WireDensity * 0.1, InvestigationPoint, Field_dBr);

        /* Get magnetic moment projection on R axis */
        GetMagneticMoment(B, f64V, MagneticMoment);
        f64MagneticMoment_R = sqrt(MagneticMoment.m_f64X * MagneticMoment.m_f64X + MagneticMoment.m_f64Y * MagneticMoment.m_f64Y);

        /* Get Force projection on R axis */
        f64F1 = f64MagneticMoment_R * Field_dBr[0];
        f64F2 = MagneticMoment.m_f64Z * Field_dBr[1];

        f64Fr = f64F1 + f64F2;

        /* Append new values to lists */
        lst_x.push_back(InvestigationPoint.m_f64X);
        //lst_Bx.push_back(B.m_f64X);
        //lst_By.push_back(B.m_f64Y);
        //lst_Bz.push_back(B.m_f64Z);

        //lst_dBr_dr.push_back(Field_dBr[0]);
        //lst_dBr_dz.push_back(Field_dBr[1]);

        lst_Fr.push_back(f64Fr);
    }

    lstData.push_back(&lst_x);

    //lstData.push_back(&lst_Bx);
    //lstData.push_back(&lst_By);
    //lstData.push_back(&lst_Bz);

    //lstData.push_back(&lst_dBr_dr);
    //lstData.push_back(&lst_dBr_dz);

    lstData.push_back(&lst_Fr);

    //PrintVector(VOfX);
    /*
    for(size_t i = 0; i < VOfB1.size(); ++i)
    {
        printf("%.10f\t%.10f\t%.10f\n", VOfB1[i].m_f64X, VOfB2[i].m_f64X, VOfB_BS[i].m_f64X);
        //printf("%f\n", VOfB_BS[i].m_f64X / VOfB2[i].m_f64X);
    }
    */

    std::string strHeader("Bx, By, Bz, dBr_dr, dBr_dz, Fr\n");
    std::string strDestinationFileName("/home/mark/Documents/MagneticField_Data/ForceProfile_Int.csv");
    CMathFunc::WriteCSV(lstData, strDestinationFileName, strHeader);

    return 0;
}
