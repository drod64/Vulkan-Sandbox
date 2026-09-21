#include <SM/Vec3.h>

void sm::Vec3::invert()
{
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
}

sm::real sm::Vec3::magnitude() const
{
    return real_sqrt(this->x * this->x +
                    this->y * this->y +
                    this->z * this->z);
}

sm::real sm::Vec3::sqrMagnitude() const
{
    return  this->x * this->x +
            this->y * this->y +
            this->z * this->z;
}

void sm::Vec3::normalize()
{
    real mag = this->magnitude();

    if (mag > 0)
    {
        *this *= ((real)1 / mag);
    }
}

void sm::Vec3::clear()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

sm::Vec3& sm::Vec3::operator *= (real scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    
    return *this;
}

sm::Vec3& sm::Vec3::operator += (const sm::Vec3 &vec)
{
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;

    return *this;
}

sm::Vec3& sm::Vec3::operator -= (const sm::Vec3 &vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;
    
    return *this;
}

sm::Vec3& sm::Vec3::operator %= (const sm::Vec3 &vec)
{
    *this = *this % vec;

    return *this;
}

sm::Vec3 sm::Vec3::operator + (const sm::Vec3 &vec) const
{
    return Vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

sm::Vec3 sm::Vec3::operator - (const sm::Vec3 &vec) const
{
    return Vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

sm::Vec3& sm::Vec3::componentProductUpdate(const sm::Vec3 &vec)
{
    this->x *= vec.x;
    this->y *= vec.y;
    this->z *= vec.z;

    return *this;
}

sm::Vec3& sm::Vec3::addScaledVector(const sm::Vec3 &vec, real scalar)
{
    this->x += (vec.x * scalar);
    this->y += (vec.y * scalar);
    this->z += (vec.z * scalar);

    return *this;
}

sm::Vec3 sm::Vec3::normalized(const sm::Vec3 &v)
{
    sm::real sqrMagnitude = v.sqrMagnitude();

    if (sqrMagnitude == 0) return {0, 0, 0};
    
    sm::real invMag = ((sm::real)1 / real_sqrt(sqrMagnitude));

    return v * invMag;
}

sm::Vec3 sm::Vec3::componentProduct(const sm::Vec3 &v1, const sm::Vec3 &v2)
{
    return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}