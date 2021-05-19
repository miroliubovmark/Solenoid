#include "ToolsStable.h"

using namespace Tools;


BOOL CrossProductTest()
{
    CVector3D Vector1(1.0, 0.0, 0.0);
    CVector3D Vector2(0.0, 1.0, 0.0);

    CVector3D Vector3;

    CMathFunc::GetCrossProduct(Vector1, Vector2, &Vector3);

    if(Vector3.m_f64X != 0.0)
    {
        return FALSE;
    }
    if(Vector3.m_f64Y != 0.0)
    {
        return FALSE;
    }
    if(Vector3.m_f64Z != 1.0)
    {
        return FALSE;
    }

    //***********************************

    Vector1.SetCoordinates(0.0, 1.0, 0.0);
    Vector2.SetCoordinates(0.0, 0.0, 1.0);

    CMathFunc::GetCrossProduct(Vector1, Vector2, &Vector3);

    if(Vector3.m_f64X != 1.0)
    {
        return FALSE;
    }
    if(Vector3.m_f64Y != 0.0)
    {
        return FALSE;
    }
    if(Vector3.m_f64Z != 0.0)
    {
        return FALSE;
    }

    //***********************************

    Vector1.SetCoordinates(0.0, 0.0, 1.0);
    Vector2.SetCoordinates(1.0, 0.0, 0.0);

    CMathFunc::GetCrossProduct(Vector1, Vector2, &Vector3);

    if(Vector3.m_f64X != 0.0)
    {
        return FALSE;
    }
    if(Vector3.m_f64Y != 1.0)
    {
        return FALSE;
    }
    if(Vector3.m_f64Z != 0.0)
    {
        return FALSE;
    }

    Vector1.SetCoordinates(1.0, 1.0, 2.0);
    Vector2.SetCoordinates(5.0, 6.0, 7.0);

    CMathFunc::GetCrossProduct(Vector1, Vector2, &Vector3);
    Vector3.Print();

    return TRUE;
}

/*BOOL EllInt_1_Test()
{
    F64 f64K = 0.5;

    F64 f64Result = CMathFunc::EllInt_1(f64K);
    printf("f64Result = %f\n", f64Result);

    return TRUE;
}

BOOL EllInt_2_Test()
{
    F64 f64K = 0.5;

    F64 f64Result = CMathFunc::EllInt_2(f64K);
    printf("f64Result = %f\n", f64Result);

    return TRUE;
}
*/

F64 IntegralFunction1(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z)
{
    F64 f64CosPhi = cos(f64Phi);
    F64 f64Result = f64CosPhi * f64CosPhi / pow(f64R * f64R + f64Rs * f64Rs + f64Z * f64Z - 2 * f64R * f64Rs * f64CosPhi, 2.5);

    return f64Result;
}

F64 IntegralFunction2(F64 f64Phi, F64 f64R, F64 f64Rs, F64 f64Z)
{
    F64 f64CosPhi = cos(f64Phi);
    F64 f64Result = f64Phi / pow(f64R * f64R + f64Rs * f64Rs + f64Z * f64Z - 2 * f64R * f64Rs * f64CosPhi, 1.5);

    return f64Result;
}

F64 Integrate()
{
    F64 f64R, f64Rs, f64Z;
    f64R = 0.1;
    f64Rs = 0.025;
    f64Z = 0.1;

    F64 f64LowLimit, f64TopLimit, f64Step, f64Result;
    f64LowLimit = 0.0;
    f64TopLimit = PI;
    f64Step = 0.01;
    f64Result = 0.0;

    F64 f64CurrentValue;
    for(F64 f64Phi = f64LowLimit; f64Phi < f64TopLimit; f64Phi += f64Step)
    {
        f64CurrentValue = IntegralFunction1(f64Phi, f64R, f64Rs, f64Z);
        f64Result += f64CurrentValue * f64Step;
    }

    return f64Result;
}


int main()
{
    printf("========= ToolsTest =========\n\n");

    //EllInt_1_Test();
    //EllInt_2_Test();

    F64 f64Result;
    //f64Result = Integrate();

    //printf("Result = %f\n", f64Result);

    #if 0
    BOOL bRes = CrossProductTest();

    if(bRes)
    {
        printf("CossProduct ----------- OK\n");
    }
    else
    {
        printf("CossProduct ----------- ERROR\n");
    }
    #endif

    return 0;
}
