#ifndef CMathFunc_H
#define CMathFunc_H

#include "ToolsStable.h"

namespace Tools
{

class CMathFunc
{
public:
    CMathFunc();
    virtual ~CMathFunc();

    /*
    inline static double FABS(fftw_complex& complex);
    static bool RFFT(std::vector<double>& rSignal, std::vector<double>* pvFrequency, std::vector<double>* pvValue, uint32_t u32SampleRate);
    static bool RFFT(fftw_complex* pComplexInput, fftw_complex* pComplexOutput, int Size);
    */

    static BOOL GetCrossProduct(const CVector3D& crVector1, const CVector3D& crVector2, CVector3D* pResult);
    static inline BOOL GetVector(F64 f64X1, F64 f64Y1, F64 f64Z1, F64 f64X2, F64 f64Y2, F64 f64Z2, CVector3D *pVector);
    static inline BOOL GetMiddleOfVector(const CVector3D& crVector, CPoint3D* pPoint);

    static F64 EllInt_1(F64 f64K);
    static F64 EllInt_2(F64 f64K);

    static BOOL WriteCSV(std::vector<std::vector<F64>> Data, std::string strFileName);
};

} /* End of namespace Tools */
#endif // CMathFunc_H
