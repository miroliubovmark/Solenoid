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

    return TRUE;
}

int main()
{
    printf("========= ToolsTest =========\n\n");

    BOOL bRes = CrossProductTest();

    if(bRes)
    {
        printf("CossProduct ----------- OK\n");
    }
    else
    {
        printf("CossProduct ----------- ERROR\n");
    }

    return 0;
}
