#include <SM/Matrix3x3.h>

void sm::Matrix3x3::setMatrix(const sm::real *matrix)
{
    this->m_matrix[0] = matrix[0];
    this->m_matrix[1] = matrix[1];
    this->m_matrix[2] = matrix[2];

    this->m_matrix[3] = matrix[3];
    this->m_matrix[4] = matrix[4];
    this->m_matrix[5] = matrix[5];

    this->m_matrix[6] = matrix[6];
    this->m_matrix[7] = matrix[7];
    this->m_matrix[8] = matrix[8];
}

sm::real* sm::Matrix3x3::operator[](uint32_t row)
{
    return &this->m_matrix[row * 3];
}

const sm::real* sm::Matrix3x3::operator[](uint32_t row) const
{
    return &this->m_matrix[row * 3];
}

sm::Matrix3x3& sm::Matrix3x3::operator+=(const sm::Matrix3x3 &other)
{
    this->m_matrix[0] += other.m_matrix[0];
    this->m_matrix[1] += other.m_matrix[1];
    this->m_matrix[2] += other.m_matrix[2];

    this->m_matrix[3] += other.m_matrix[3];
    this->m_matrix[4] += other.m_matrix[4];
    this->m_matrix[5] += other.m_matrix[5];

    this->m_matrix[6] += other.m_matrix[6];
    this->m_matrix[7] += other.m_matrix[7];
    this->m_matrix[8] += other.m_matrix[8];

    return *this;
}

sm::Matrix3x3& sm::Matrix3x3::operator*=(const sm::Matrix3x3 &other)
{
    const sm::real a = this->m_matrix[0], b = this->m_matrix[1], c = this->m_matrix[2];
    const sm::real d = this->m_matrix[3], e = this->m_matrix[4], f = this->m_matrix[5];
    const sm::real g = this->m_matrix[6], h = this->m_matrix[7], i = this->m_matrix[8];

    const sm::real j = other.m_matrix[0], k = other.m_matrix[1], l = other.m_matrix[2];
    const sm::real m = other.m_matrix[3], n = other.m_matrix[4], o = other.m_matrix[5];
    const sm::real p = other.m_matrix[6], q = other.m_matrix[7], r = other.m_matrix[8];

    this->m_matrix[0] = (a * j) + (b * m) + (c * p);
    this->m_matrix[1] = (a * k) + (b * n) + (c * q);
    this->m_matrix[2] = (a * l) + (b * o) + (c * r);

    this->m_matrix[3] = (d * j) + (e * m) + (f * p);
    this->m_matrix[4] = (d * k) + (e * n) + (f * q);
    this->m_matrix[5] = (d * l) + (e * o) + (f * r);

    this->m_matrix[6] = (g * j) + (h * m) + (i * p);
    this->m_matrix[7] = (g * k) + (h * n) + (i * q);
    this->m_matrix[8] = (g * l) + (h * o) + (i * r);

    return *this;
}

sm::Matrix3x3& sm::Matrix3x3::operator*=(sm::real scalar)
{
    this->m_matrix[0] *= scalar;
    this->m_matrix[1] *= scalar;
    this->m_matrix[2] *= scalar;

    this->m_matrix[3] *= scalar;
    this->m_matrix[4] *= scalar;
    this->m_matrix[5] *= scalar;

    this->m_matrix[6] *= scalar;
    this->m_matrix[7] *= scalar;
    this->m_matrix[8] *= scalar;

    return *this;
}

void sm::Matrix3x3::transpose()
{
    const sm::real b = this->m_matrix[1], c = this->m_matrix[2];
    const sm::real d = this->m_matrix[3], f = this->m_matrix[5];
    const sm::real g = this->m_matrix[6], h = this->m_matrix[7];

    // a, e, i do not not change position.

    this->m_matrix[1] = d;
    this->m_matrix[2] = g;

    this->m_matrix[3] = b;
    this->m_matrix[5] = h;

    this->m_matrix[6] = c;
    this->m_matrix[7] = f;
}

void sm::Matrix3x3::inverse()
{
    const sm::real a = this->m_matrix[0], b = this->m_matrix[1], c = this->m_matrix[2];
    const sm::real d = this->m_matrix[3], e = this->m_matrix[4], f = this->m_matrix[5];
    const sm::real g = this->m_matrix[6], h = this->m_matrix[7], i = this->m_matrix[8];

    const sm::real c11 = e * i - f * h;
    const sm::real c21 = f * g - d * i;
    const sm::real c31 = d * h - e * g;

    const sm::real det = a * c11 + b * c21 + c * c31;

    if (real_abs(det) < static_cast<sm::real>(1e-6))
    {
        throw std::runtime_error("[Matrix3x3]::inversed: Error. Matrix is singular.");
    }

    const sm::real invDet = static_cast<sm::real>(1) / det;

    const sm::real r00 = c11 * invDet;
    const sm::real r01 = (c * h - b * i) * invDet;
    const sm::real r02 = (b * f - c * e) * invDet;
    
    const sm::real r10 = c21 * invDet;
    const sm::real r11 = (a * i - c * g) * invDet;
    const sm::real r12 = (c * d - a * f) * invDet;
    
    const sm::real r20 = c31 * invDet;
    const sm::real r21 = (b * g - a * h) * invDet;
    const sm::real r22 = (a * e - b * d) * invDet;

    this->m_matrix[0] = r00;
    this->m_matrix[1] = r01;
    this->m_matrix[2] = r02;

    this->m_matrix[3] = r10;
    this->m_matrix[4] = r11;
    this->m_matrix[5] = r12;

    this->m_matrix[6] = r20;
    this->m_matrix[7] = r21;
    this->m_matrix[8] = r22;
}

void sm::Matrix3x3::absolute()
{
    (*this)[0][0] = real_abs((*this)[0][0]);
    (*this)[0][1] = real_abs((*this)[0][1]);
    (*this)[0][2] = real_abs((*this)[0][2]);

    (*this)[1][0] = real_abs((*this)[1][0]);
    (*this)[1][1] = real_abs((*this)[1][1]);
    (*this)[1][2] = real_abs((*this)[1][2]);

    (*this)[2][0] = real_abs((*this)[2][0]);
    (*this)[2][1] = real_abs((*this)[2][1]);
    (*this)[2][2] = real_abs((*this)[2][2]);
}

void sm::Matrix3x3::setMatrix3x3(const sm::Matrix3x3 &mat)
{
    this->setMatrix(mat.data());
}

sm::real* sm::Matrix3x3::data()
{
    return this->m_matrix;
}

const sm::real* sm::Matrix3x3::data() const
{
    return this->m_matrix;
}

sm::Vec3 sm::Matrix3x3::transform(const sm::Vec3 &v) const
{
    const sm::real x = this->m_matrix[0] * v.x + this->m_matrix[1] * v.y + this->m_matrix[2] * v.z;
    const sm::real y = this->m_matrix[3] * v.x + this->m_matrix[4] * v.y + this->m_matrix[5] * v.z;
    const sm::real z = this->m_matrix[6] * v.x + this->m_matrix[7] * v.y + this->m_matrix[8] * v.z;

    return sm::Vec3(x, y, z);
}

sm::Vec3 sm::Matrix3x3::transformInverse(const sm::Vec3 &v) const
{
    const sm::real x = this->m_matrix[0] * v.x + this->m_matrix[3] * v.y + this->m_matrix[6] * v.z;
    const sm::real y = this->m_matrix[1] * v.x + this->m_matrix[4] * v.y + this->m_matrix[7] * v.z;
    const sm::real z = this->m_matrix[2] * v.x + this->m_matrix[5] * v.y + this->m_matrix[8] * v.z;

    return sm::Vec3(x, y, z);
}

sm::Matrix3x3 sm::Matrix3x3::absoluted() const
{
    sm::Matrix3x3 result;

    result.setMatrix(this->m_matrix);

    result.absolute();

    return result;
}

sm::Matrix3x3 sm::Matrix3x3::transposed() const
{
    sm::Matrix3x3 result;

    result.setMatrix(this->m_matrix);

    result.transpose();
    
    return result;
}

sm::Matrix3x3 sm::Matrix3x3::inversed() const
{
    sm::Matrix3x3 result;

    result.setMatrix(this->m_matrix);

    result.inverse();

    return result;
}