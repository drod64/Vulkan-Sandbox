#include <SM/Matrix3x4.h>
#include <SM/Quaternion.h>

void sm::Matrix3x4::setMatrix(const sm::real *matrix)
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
    this->m_matrix[9] = matrix[9];
    this->m_matrix[10] = matrix[10];
    this->m_matrix[11] = matrix[11];
}

sm::real* sm::Matrix3x4::operator[](size_t row)
{
    return &this->m_matrix[row * 4];
}

const sm::real* sm::Matrix3x4::operator[](size_t row) const
{
    return &this->m_matrix[row * 4];
}

sm::Matrix3x4& sm::Matrix3x4::operator+=(const sm::Vec3 &v)
{
    this->m_matrix[3] += v.x;
    this->m_matrix[7] += v.y;
    this->m_matrix[11] += v.z;

    return *this;
}

sm::Matrix3x4& sm::Matrix3x4::operator+=(const sm::Matrix3x4 &other)
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
    this->m_matrix[9] += other.m_matrix[9];
    this->m_matrix[10] += other.m_matrix[10];
    this->m_matrix[11] += other.m_matrix[11];

    return *this;
}

sm::Matrix3x4& sm::Matrix3x4::operator*=(const sm::Matrix3x4 &other)
{
    const sm::real a = this->m_matrix[0], b = this->m_matrix[1], c = this->m_matrix[2], d = this->m_matrix[3];
    const sm::real e = this->m_matrix[4], f = this->m_matrix[5], g = this->m_matrix[6], h = this->m_matrix[7];
    const sm::real i = this->m_matrix[8], j = this->m_matrix[9], k = this->m_matrix[10], l = this->m_matrix[11];

    const sm::real m = other.m_matrix[0], n = other.m_matrix[1], o = other.m_matrix[2], p = other.m_matrix[3];
    const sm::real q = other.m_matrix[4], r = other.m_matrix[5], s = other.m_matrix[6], t = other.m_matrix[7];
    const sm::real u = other.m_matrix[8], v = other.m_matrix[9], w = other.m_matrix[10], x = other.m_matrix[11];

    this->m_matrix[0] = (a * m) + (b * q) + (c * u); // + 0
    this->m_matrix[1] = (a * n) + (b * r) + (c * v); // + 0
    this->m_matrix[2] = (a * o) + (b * s) + (c * w); // + 0
    this->m_matrix[3] = (a * p) + (b * t) + (c * x) + d;

    this->m_matrix[4] = (e * m) + (f * q) + (g * u); // + 0
    this->m_matrix[5] = (e * n) + (f * r) + (g * v); // + 0
    this->m_matrix[6] = (e * o) + (f * s) + (g * w); // + 0
    this->m_matrix[7] = (e * p) + (f * t) + (g * x) + h;
    
    this->m_matrix[8] = (i * m) + (j * q) + (k * u); // + 0
    this->m_matrix[9] = (i * n) + (j * r) + (k * v); // + 0
    this->m_matrix[10] = (i * o) + (j * s) + (k * w); // + 0
    this->m_matrix[11] = (i * p) + (j * t) + (k * x) + l;

    return *this;
}

sm::Matrix3x4& sm::Matrix3x4::operator*=(sm::real scalar)
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
    this->m_matrix[9] *= scalar;
    this->m_matrix[10] *= scalar;
    this->m_matrix[11] *= scalar;

    return *this;
}

void sm::Matrix3x4::translate(const sm::Vec3 &v)
{
    (*this) += v;
}

void sm::Matrix3x4::translate_local(const sm::Vec3 &v)
{
    const sm::real x = this->m_matrix[0] * v.x + this->m_matrix[1] * v.y + this->m_matrix[2] * v.z;
    const sm::real y = this->m_matrix[4] * v.x + this->m_matrix[5] * v.y + this->m_matrix[6] * v.z;
    const sm::real z = this->m_matrix[8] * v.x + this->m_matrix[9] * v.y + this->m_matrix[10] * v.z;

    this->m_matrix[3] += x;
    this->m_matrix[7] += y;
    this->m_matrix[11] += z;
}

void sm::Matrix3x4::inverse()
{
    const sm::real a = this->m_matrix[0], b = this->m_matrix[1], c = this->m_matrix[2];
    const sm::real d = this->m_matrix[4], e = this->m_matrix[5], f = this->m_matrix[6];
    const sm::real g = this->m_matrix[8], h = this->m_matrix[9], i = this->m_matrix[10];

    const sm::real tx = this->m_matrix[3], ty = this->m_matrix[7], tz = this->m_matrix[11];

    const sm::real c11 = e * i - f * h;
    const sm::real c21 = f * g - d * i;
    const sm::real c31 = d * h - e * g;

    const sm::real det = a * c11 + b * c21 + c * c31;

    if (real_abs(det) < static_cast<sm::real>(1e-6))
    {
        throw std::runtime_error("[Matrix3x4]::inversed: Error. Matrix is singular.");
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

    const sm::real itx = -(r00 * tx + r01 * ty + r02 * tz);
    const sm::real ity = -(r10 * tx + r11 * ty + r12 * tz);
    const sm::real itz = -(r20 * tx + r21 * ty + r22 * tz);

    this->m_matrix[0] = r00;
    this->m_matrix[1] = r01;
    this->m_matrix[2] = r02;
    this->m_matrix[3] = itx;

    this->m_matrix[4] = r10;
    this->m_matrix[5] = r11;
    this->m_matrix[6] = r12;
    this->m_matrix[7] = ity;

    this->m_matrix[8] = r20;
    this->m_matrix[9] = r21;
    this->m_matrix[10] = r22;
    this->m_matrix[11] = itz;
}

void sm::Matrix3x4::setMatrix3x4(const sm::Matrix3x4 &mat)
{
    this->setMatrix(mat.data());
}

sm::real* sm::Matrix3x4::data()
{
    return this->m_matrix;
}

const sm::real* sm::Matrix3x4::data() const
{
    return this->m_matrix;
}

sm::Vec3 sm::Matrix3x4::transformPoint(const sm::Vec3 &v) const
{
    const sm::real x = (this->m_matrix[0] * v.x) + (this->m_matrix[1] * v.y) + (this->m_matrix[2] * v.z) + this->m_matrix[3];
    const sm::real y = (this->m_matrix[4] * v.x) + (this->m_matrix[5] * v.y) + (this->m_matrix[6] * v.z) + this->m_matrix[7];
    const sm::real z = (this->m_matrix[8] * v.x) + (this->m_matrix[9] * v.y) + (this->m_matrix[10] * v.z) + this->m_matrix[11];

    return sm::Vec3(x, y, z);
}

sm::Vec3 sm::Matrix3x4::transformPointInv(const sm::Vec3 &v) const
{
    const sm::real dx = v.x - this->m_matrix[3];
    const sm::real dy = v.x - this->m_matrix[7];
    const sm::real dz = v.x - this->m_matrix[11];

    return sm::Vec3(
        this->m_matrix[0] * dx + this->m_matrix[4] * dy + this->m_matrix[8] * dz,
        this->m_matrix[1] * dx + this->m_matrix[5] * dy + this->m_matrix[9] * dz,
        this->m_matrix[2] * dx + this->m_matrix[6] * dy + this->m_matrix[10] * dz
    );
}

sm::Vec3 sm::Matrix3x4::transformDirection(const sm::Vec3 &v) const
{
    const sm::real x = (this->m_matrix[0] * v.x) + (this->m_matrix[1] * v.y) + (this->m_matrix[2] * v.z);
    const sm::real y = (this->m_matrix[4] * v.x) + (this->m_matrix[5] * v.y) + (this->m_matrix[6] * v.z);
    const sm::real z = (this->m_matrix[8] * v.x) + (this->m_matrix[9] * v.y) + (this->m_matrix[10] * v.z);

    return sm::Vec3(x, y, z);
}

sm::Vec3 sm::Matrix3x4::transformDirectionInv(const sm::Vec3 &v) const
{
    const sm::real x = (this->m_matrix[0] * v.x) + (this->m_matrix[4] * v.y) + (this->m_matrix[8] * v.z);
    const sm::real y = (this->m_matrix[1] * v.x) + (this->m_matrix[5] * v.y) + (this->m_matrix[9] * v.z);
    const sm::real z = (this->m_matrix[2] * v.x) + (this->m_matrix[6] * v.y) + (this->m_matrix[10] * v.z);

    return sm::Vec3(x, y, z);
}

sm::Matrix3x4 sm::Matrix3x4::translated(const sm::Vec3 &v) const
{
    sm::Matrix3x4 result;

    result.setMatrix3x4(*this);
    
    result += v;

    return result;
}

sm::Matrix3x4 sm::Matrix3x4::translatedLocal(const sm::Vec3 &v) const
{
    sm::Matrix3x4 result;

    result.setMatrix3x4(*this);

    result.translate_local(v);

    return result;
}

sm::Matrix3x4 sm::Matrix3x4::inversed() const
{
    sm::Matrix3x4 result;

    result.setMatrix3x4(*this);
    
    result.inverse();

    return result;
}