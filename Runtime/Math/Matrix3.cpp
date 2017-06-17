#include "Matrix3.h"

using namespace Seer;

Matrix3 Matrix3::linearInterpolate(const Matrix3& a, const Matrix3& b, real prop)
{
    Matrix3 result;
    for (unsigned i = 0; i < 9; i++) {
        result.data[i] = a.data[i] * (1-prop) + b.data[i] * prop;
    }
    return result;
}

Seer::Matrix3::Matrix3(const Vector3& rkAxis, real fAngle)
{

}


