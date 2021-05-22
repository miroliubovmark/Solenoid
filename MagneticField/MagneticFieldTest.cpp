#include <iostream>

#include "MagneticFieldStable.h"

using namespace Tools;
using namespace MagneticField;

BOOL RingOfCurrent_BioSavar_Test()
{
    F64 f64R = 0.025;      /* m */
    F64 f64Current = 1;    /* A */
    U64 u64NVertexes = 10000;

    CVector3D B;
    CPoint3D RingCentrePoint(0.0, 0.0, 0.0);

    {
        CPoint3D InvestigationPoint(0.0, 0.0, 0.0);

        CIntegration::RingOfCurrent_BioSavar(RingCentrePoint, f64R, f64Current, InvestigationPoint, u64NVertexes, &B);
        CVector3D OnlineSolver(0.0, 0.0, 0.00002513274122871834);

        printf("RingOfCurrent_BioSavar:\t");
        B.Print();

        printf("Online Solver:\t\t");
        OnlineSolver.Print();
        printf("\n");
    }

    {
        CPoint3D InvestigationPoint(0.0, 0.0, 0.1);

        CIntegration::RingOfCurrent_BioSavar(RingCentrePoint, f64R, f64Current, InvestigationPoint, u64NVertexes, &B);
        CVector3D OnlineSolver(0.0, 0.0, 3.585638295755069E-7);

        printf("RingOfCurrent_BioSavar:\t");
        B.Print();

        printf("Online Solver:\t\t");
        OnlineSolver.Print();
        printf("\n");
    }

    {
        CPoint3D InvestigationPoint(0.0, 0.0, 1.0);

        CIntegration::RingOfCurrent_BioSavar(RingCentrePoint, f64R, f64Current, InvestigationPoint, u64NVertexes, &B);
        CVector3D OnlineSolver(0.0, 0.0, 3.923312137214527E-10);

        printf("RingOfCurrent_BioSavar:\t");
        B.Print();

        printf("Online Solver:\t\t");
        OnlineSolver.Print();
        printf("\n");
    }

    {
        CPoint3D InvestigationPoint(0.02, 0.0, 0.1);

        CIntegration::RingOfCurrent_BioSavar(RingCentrePoint, f64R, f64Current, InvestigationPoint, u64NVertexes, &B);
        CVector3D OnlineSolver(9.314471502216973E-8, 0.0, 3.23237063784243E-7);

        printf("RingOfCurrent_BioSavar:\t");
        B.Print();

        printf("Online Solver:\t\t");
        OnlineSolver.Print();
        printf("\n");
    }

    printf("###############\n");
    printf("It seems the CIntegration::RingOfCurrent_BioSavar function works correctly\n");
    printf("###############\n");

    return TRUE;
}

BOOL RingOfCurrent_Field_Test()
{
    printf("##### RingOfCurrent_Field_Test #####\n");

    F64 f64Rs = 0.025;
    F64 f64Current = 1;

    CPoint3D RingCentrePoint(0.0, 0.0, 0.0);
    CPoint3D InvPoint(f64Rs, 0.0, 0.0);

    CVector3D B, B2;

    CIntegration::RingOfCurrent_Field(RingCentrePoint, f64Rs, f64Current, InvPoint, &B);
    CIntegration::RingOfCurrent_BioSavar(RingCentrePoint, f64Rs, f64Current, InvPoint, 10000, &B2);

    B.Print();
    B2.Print();

    return TRUE;
}

BOOL CompareIntegration()
{
    CPoint3D RingCentrePoint(0.0, 0.0, 0.0);
    CPoint3D InvPoint(0.0, 0.0, 0.0);

    CVector3D B_BioSavar, B_Integral;

    B_BioSavar.Clear();
    B_Integral.Clear();

    F64 f64Rs = 0.025;
    F64 f64Current = 1;

    for(F64 f64InvZ = 0.0; f64InvZ < 1.0; f64InvZ += 0.02)
    {
        InvPoint.SetCoordinates(0.1, 0.0, f64InvZ);

        /* Bio-Savar */
        CIntegration::RingOfCurrent_BioSavar(RingCentrePoint, f64Rs, f64Current, InvPoint, 720, &B_BioSavar);

        /* New method */
        CIntegration::RingOfCurrent_Field(RingCentrePoint, f64Rs, f64Current, InvPoint, &B_Integral);

        //printf("%f\n", B2.m_f64Z / B1.m_f64Z);

        printf("InvPoint:\t");
        InvPoint.Print();

        printf("B_BioSavar:\t");
        B_BioSavar.Print();

        printf("B_Integral:\t");
        B_Integral.Print();

        //printf("%f\n", B_Integral.m_f64Z / B_BioSavar.m_f64Z);
        printf("%.10f\n", B_BioSavar.GetAbs());
        printf("%.10f\n", B_Integral.GetAbs());

        printf("\n");
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

BOOL Br_Itegral_Test()
{
    F64 f64R, f64Rs, f64Z, f64N;

    {
        f64R = 1.0;
        f64Rs = 0.025;
        f64Z = 0.0;
        f64N = 1000.0;

        F64 f64WolframResult = 0.235896;
        F64 f64Result = CIntegration::Br_Integral(f64R, f64Rs, f64Z, f64N);

        printf("Wolfram:\t\t\t%f\n", f64WolframResult);
        printf("CIntegration::Br_Integral:\t%f\n\n", f64Result);
    }


    {
        f64R = 1.0;
        f64Rs = 0.025;
        f64Z = 0.1;
        f64N = 1000.0;

        F64 f64WolframResult = 0.115046;
        F64 f64Result = CIntegration::Br_Integral(f64R, f64Rs, f64Z, f64N);

        printf("Wolfram:\t\t\t%f\n", f64WolframResult);
        printf("CIntegration::Br_Integral:\t%f\n\n", f64Result);
    }

    {
        f64R = 0.0;
        f64Rs = 0.025;
        f64Z = 0.1;
        f64N = 100000.0;

        F64 f64WolframResult = 0.0;
        F64 f64Result = CIntegration::Br_Integral(f64R, f64Rs, f64Z, f64N);

        printf("Wolfram:\t\t\t%f\n", f64WolframResult);
        printf("CIntegration::Br_Integral:\t%f\n\n", f64Result);
    }

#if 0
    {
        f64R = 0.0;
        f64Rs = 0.025;
        f64Z = 0.0;
        f64N = 1000.0;

        F64 f64WolframResult = ;
        F64 f64Result = CIntegration::Br_Integral(f64R, f64Rs, f64Z, f64N);

        printf("Wolfram:\t\t\t%f\n", f64WolframResult);
        printf("CIntegration::Br_Integral:\t%f\n\n", f64Result);
    }

    {
        f64R = 0.015;
        f64Rs = 0.025;
        f64Z = 0.05;
        f64N = 1000.0;

        F64 f64WolframResult = ;
        F64 f64Result = CIntegration::Br_Integral(f64R, f64Rs, f64Z, f64N);

        printf("Wolfram:\t\t\t%f\n", f64WolframResult);
        printf("CIntegration::Br_Integral:\t%f\n\n", f64Result);
    }
#endif
    return TRUE;
}

BOOL Bz_Integral1_Test()
{
    F64 f64R, f64Rs, f64Z, f64N;


    {
        f64R = 1.0;
        f64Rs = 0.025;
        f64Z = 0.0;
        f64N = 1000.0;

        F64 f64WolframResult = 19.767;
        F64 f64Result = CIntegration::Bz_Integral1(f64R, f64Rs, f64Z, f64N);

        printf("Wolfram:\t\t\t%f\n", f64WolframResult);
        printf("CIntegration::Bz_Integral1:\t%f\n\n", f64Result);
    }

    {
        f64R = 1.0;
        f64Rs = 0.025;
        f64Z = 1.0;
        f64N = 1000.0;

        F64 f64WolframResult = 6.97968;
        F64 f64Result = CIntegration::Bz_Integral1(f64R, f64Rs, f64Z, f64N);

        printf("Wolfram:\t\t\t%f\n", f64WolframResult);
        printf("CIntegration::Bz_Integral1:\t%f\n\n", f64Result);
    }
#if 0
    {
        f64R = 0.0;
        f64Rs = 0.025;
        f64Z = 0.1;
        f64N = 1000.0;

        F64 f64WolframResult = ;
        F64 f64Result = CIntegration::Bz_Integral1(f64R, f64Rs, f64Z, f64N);

        printf("Wolfram:\t\t\t%f\n", f64WolframResult);
        printf("CIntegration::Bz_Integral1:\t%f\n\n", f64Result);
    }

    {
        f64R = 0.0;
        f64Rs = 0.025;
        f64Z = 0.0;
        f64N = 1000.0;

        F64 f64WolframResult = ;
        F64 f64Result = CIntegration::Bz_Integral1(f64R, f64Rs, f64Z, f64N);

        printf("Wolfram:\t\t\t%f\n", f64WolframResult);
        printf("CIntegration::Bz_Integral1:\t%f\n\n", f64Result);
    }

    {
        f64R = 0.015;
        f64Rs = 0.025;
        f64Z = 0.05;
        f64N = 1000.0;

        F64 f64WolframResult = ;
        F64 f64Result = CIntegration::Bz_Integral1(f64R, f64Rs, f64Z, f64N);

        printf("Wolfram:\t\t\t%f\n", f64WolframResult);
        printf("CIntegration::Bz_Integral1:\t%f\n\n", f64Result);
    }
#endif

    return TRUE;
}

BOOL IntegralTest()
{
    Br_Itegral_Test();
    Bz_Integral1_Test();

    return TRUE;
}

BOOL BZ1_FromR()
{
    F64 f64Rs = 0.025;

    std::list<std::list<F64>*> lst;
    CPoint3D RCP(0.0, 0.0, 0.0);
    CPoint3D InvP;

    CVector3D Res;

    std::list<F64> X;
    std::list<F64> Bz;

    F64 B;

    for(F64 f64X = 0.0; f64X < 2 * f64Rs; f64X += 0.001)
    {
        InvP.SetCoordinates(f64X, 0.0, 0.0);
        B = f64Rs * CIntegration::Bz_Integral1(f64X, f64Rs, 0.0, 10000) - f64X * CIntegration::Bz_Integral2(f64X, f64Rs, 0.0, 10000);
        //CIntegration::RingOfCurrent_BioSavar(RCP, f64Rs, 1.0, InvP, 10000, &Res);

        //B = Res.m_f64Z;

        X.push_back(f64X);
        Bz.push_back(B);
    }

    lst.push_back(&X);
    lst.push_back(&Bz);

    std::string strFileName("/home/mark/Documents/Project/Bz(X)_Int.csv");
    //CMathFunc::WriteCSV(lst, strFileName);

    return TRUE;
}

int main()
{
    printf("========= MagneticFieldTest =========\n\n");

    //RingOfCurrent_BioSavar_Test();
    //RingOfCurrent_Field_Test();

    //Br_Itegral_Test();

    //CompareIntegration();

    //Test2();

    //IntegralTest();

    BZ1_FromR();

    return 0;
}
