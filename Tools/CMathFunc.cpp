#include "CMathFunc.h"

namespace Tools
{

CMathFunc::CMathFunc()
{
}

CMathFunc::~CMathFunc()
{
}

#if 0
double CMathFunc::FABS(fftw_complex& complex)
{
    double root = std::sqrt((complex.re * complex.re) + (complex.im * complex.im));
    return root;
}

bool CMathFunc::RFFT(std::vector<double>& rvSignal, std::vector<double>* pvFrequency, std::vector<double>* pvValue, uint32_t u32SampleRate)
{
    size_t SignalSize = rvSignal.size();

    fftw_complex* pComplexSignal = new fftw_complex[SignalSize];
    fftw_complex* pComplexSpectre = new fftw_complex[SignalSize];

    std::vector<double>::iterator iter(rvSignal.begin());
    std::vector<double>::iterator end(rvSignal.end());

    size_t count = 0;
    while(iter != end)
    {
        pComplexSignal[count].re = *(iter++);
        pComplexSignal[count++].im = 0;
    }

    fftw_plan FFT_Plan = fftw_create_plan(SignalSize, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_one(FFT_Plan, pComplexSignal, pComplexSpectre);
    fftw_destroy_plan(FFT_Plan);

    /* Create vectors of frequency and values */
    size_t SpectreSize;
    if(SignalSize % 2 == 0)
    {
        SpectreSize = SignalSize / 2;
    }
    else
    {
        SpectreSize = (SignalSize / 2) + 1;
    }

    pvFrequency->reserve(SpectreSize);
    pvValue->reserve(SpectreSize);

    double delta = static_cast<double>(u32SampleRate) / (2 * static_cast<double>(SpectreSize));

    double CurrentFrequency = 0.0;

    for(size_t i = 0; i < SpectreSize; ++i)
    {
        pvFrequency->push_back(CurrentFrequency);
        pvValue->push_back(FABS(pComplexSpectre[i]));

        CurrentFrequency += delta;
    }

    delete [] pComplexSignal;
    delete [] pComplexSpectre;

    return true;
}

bool CMathFunc::RFFT(fftw_complex* pComplexInput, fftw_complex* pComplexOutput, int Size)
{
    fftw_plan FFT_Plan = fftw_create_plan(Size, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_one(FFT_Plan, pComplexInput, pComplexOutput);
    fftw_destroy_plan(FFT_Plan);

    return true;
}

#endif

BOOL CMathFunc::GetCrossProduct(const CVector3D& crVector1, const CVector3D& crVector2, CVector3D* pResult)
{
    F64 X, Y, Z;

    X = crVector1.m_f64Y * crVector2.m_f64Z - crVector1.m_f64Z * crVector2.m_f64Y;
    Y = crVector1.m_f64Z * crVector2.m_f64X - crVector1.m_f64X * crVector2.m_f64Z;
    Z = crVector1.m_f64X * crVector2.m_f64Y - crVector1.m_f64Y * crVector2.m_f64X;

    BOOL bResult = pResult->SetCoordinates(X ,Y, Z);

    return bResult;
}

BOOL CMathFunc::GetVector(F64 f64X1, F64 f64Y1, F64 f64Z1, F64 f64X2, F64 f64Y2, F64 f64Z2, CVector3D* pVector)
{
    pVector->SetCoordinates(f64X2 - f64X1, f64Y2 - f64Y1, f64Z2 - f64Z1);

    return TRUE;
}

BOOL CMathFunc::GetMiddleOfVector(const CVector3D& crVector, CPoint3D* pPoint)
{
    F64 f64Middle_X, f64Middle_Y, f64Middle_Z;

    f64Middle_X = crVector.m_f64X / 2;
    f64Middle_Y = crVector.m_f64Y / 2;
    f64Middle_Z = crVector.m_f64Z / 2;

    BOOL bResult = pPoint->SetCoordinates(f64Middle_X, f64Middle_Y, f64Middle_Z);
    return bResult;
}

/*F64 CMathFunc::EllInt_1(F64 f64K)
{
    F64 f64Result = boost::math::ellint_1(f64K);
    return f64Result;
}

F64 CMathFunc::EllInt_2(F64 f64K)
{
    F64 f64Result = boost::math::ellint_2(f64K);
    return f64Result;
}
*/

/*
BOOL CMathFunc::WriteCSV(std::vector<std::vector<F64>*> Data, std::string strFileName)
{
    std::ofstream DestinationFile;
    DestinationFile.open(strFileName);

    std::string strCell;

    for(size_t i = 0; i < Data.size(); ++i)
    {
        for(size_t j = 0; j < Data[i].size(); ++j)
        {
            strCell = std::to_string((*Data[i])[j]);

            DestinationFile.write(strCell.c_str(), strCell.size());
            DestinationFile.put(',');
        }
    }

    DestinationFile.close();

    return TRUE;
}
*/

} /* End of namespace Tools */
