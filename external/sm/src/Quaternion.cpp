#include <SM/Quaternion.h>

sm::Quaternion::Quaternion(sm::real nx, sm::real ny, sm::real nz, sm::real nw) :
x(nx), y(ny), z(nz), w(nw)
{}

sm::Quaternion& sm::Quaternion::operator+= (const sm::Quaternion &other)
{
    (*this) = (*this) + other;

    return *this;
}

sm::Quaternion& sm::Quaternion::operator*=(const sm::Quaternion &other)
{
    (*this) = (*this) * other;

    return *this;
}

sm::Quaternion& sm::Quaternion::operator*=(sm::real scalar)
{
    (*this) = (*this) * scalar;

    return *this;
}

sm::Quaternion& sm::Quaternion::integrate(const sm::Vec3 &w, sm::real scalar)
{
    const sm::real halfX = w.x * scalar * static_cast<sm::real>(0.5);
    const sm::real halfY = w.y * scalar * static_cast<sm::real>(0.5);
    const sm::real halfZ = w.z * scalar * static_cast<sm::real>(0.5);

    const sm::real prevX = this->x;
    const sm::real prevY = this->y;
    const sm::real prevZ = this->z;
    const sm::real prevW = this->w;
    
    // Global Space
    this->x = halfX * prevW + 1.0f * prevX  - halfY * prevZ + halfZ * prevY;
    this->y = halfY * prevW + halfX * prevZ + 1.0f * prevY  - halfZ * prevX;
    this->z = halfZ * prevW - halfX * prevY + halfY * prevX + 1.0f * prevZ;
    this->w = 1.0f * prevW  - halfX * prevX - halfY * prevY - halfZ * prevZ;
    
    this->normalize();

    return *this;
}

sm::Quaternion& sm::Quaternion::normalize()
{
    sm::real magSqr = this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w;

    if (magSqr > static_cast<sm::real>(0.00001))
    {
        sm::real invMag = static_cast<sm::real>(1) / real_sqrt(magSqr);

        invMag = invMag * (static_cast<sm::real>(1.5) - (static_cast<sm::real>(0.5) * magSqr * invMag * invMag));

        this->x *= invMag;
        this->y *= invMag;
        this->z *= invMag;
        this->w *= invMag;
    }
    else
    {
        this->x = static_cast<sm::real>(0);
        this->y = static_cast<sm::real>(0);
        this->z = static_cast<sm::real>(0);
        this->w = static_cast<sm::real>(1);
    }

    return *this;
}

sm::real sm::Quaternion::dot(const sm::Quaternion &lhs, const sm::Quaternion &rhs)
{
    return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z) + (lhs.w * rhs.w);
}

sm::Vec3 sm::Quaternion::transform(const sm::Vec3 &rotation) const
{
    return (*this) * rotation;
}

sm::Vec3 sm::Quaternion::transformInverse(const sm::Vec3 &rotation) const
{
    sm::Vec3 qVec(-this->x, -this->y, -this->z);

    const sm::Vec3 t = sm::Vec3::crossProduct(qVec, rotation) * static_cast<sm::real>(2);

    return rotation + (t * this->w) + sm::Vec3::crossProduct(qVec, t);
}

sm::Quaternion sm::Quaternion::conjugated() const
{
    return Quaternion(-this->x, -this->y, -this->z, this->w);
}

sm::Quaternion sm::Quaternion::normalized() const
{
    sm::Quaternion result(this->x, this->y, this->z, this->w);

    result.normalize();

    return result;
}