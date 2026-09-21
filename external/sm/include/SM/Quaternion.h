#ifndef SM_QUATERNION_H
#define SM_QUATERNION_H
#include <cstddef>
#include <cstdint>
#include <SM/Precision.h>
#include <SM/Vec3.h>

namespace sm {
struct Quaternion {
    union {
        struct { sm::real x, y, z, w; };
        sm::real data[4];
    };

    explicit Quaternion(real nx = static_cast<real>(0), real ny = static_cast<real>(0),
                        real nz = static_cast<real>(0), real nw = static_cast<real>(1));
    
    Quaternion& operator+=(const Quaternion &other);

    Quaternion& operator*=(const Quaternion &other);

    Quaternion& operator*=(real scalar);

    Quaternion& integrate(const Vec3 &w, real scalar);

    Quaternion& normalize();

    [[nodiscard]] static sm::real dot(const Quaternion &lhs, const Quaternion &rhs);
    
    [[nodiscard]] Vec3 transform(const Vec3 &rotation) const;

    [[nodiscard]] Vec3 transformInverse(const Vec3 &rotation) const;

    [[nodiscard]] Quaternion conjugated() const;

    [[nodiscard]] Quaternion normalized() const;

}; // class Quaternion

// Ensures the entire struct stays exactly 16 bytes (4 floats * 4 bytes)
static_assert(sizeof(sm::Quaternion) == 16, "[sm::Quaternion]: Error. Quaternion size must be exactly 16 bytes!");

// Ensures the memory address of the array is identical to the x variable
static_assert(offsetof(Quaternion, data) == offsetof(Quaternion, x), "[sm::Quaternion]: Error. Array and x variable must align!");

// Math operator overload declarations.
[[nodiscard]] Quaternion operator+ (Quaternion lhs, const Quaternion &rhs);

[[nodiscard]] Quaternion operator* (Quaternion lhs, const Quaternion &rhs);

[[nodiscard]] Quaternion operator* (Quaternion quat, real scalar);
[[nodiscard]] Quaternion operator* (real scalar, Quaternion quat);

[[nodiscard]] Vec3 operator* (const Quaternion &quat, const Vec3 &v);
[[nodiscard]] Vec3 operator* (const Vec3 &v, const Quaternion &quat);
} // namespace sm

// Math operator overload implementations

inline sm::Quaternion sm::operator+(sm::Quaternion lhs, const sm::Quaternion &rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    lhs.w += rhs.w;

    return lhs;
}

inline sm::Quaternion sm::operator* (sm::Quaternion lhs, const sm::Quaternion &rhs)
{
    const sm::real x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
    const sm::real y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
    const sm::real z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;
    const sm::real w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;

    lhs.x = x;
    lhs.y = y;
    lhs.z = z;
    lhs.w = w;

    return lhs;
}

inline sm::Quaternion sm::operator* (sm::Quaternion quat, sm::real scalar)
{
    quat.x *= scalar;
    quat.y *= scalar;
    quat.z *= scalar;
    quat.w *= scalar;

    return quat;
}

inline sm::Quaternion sm::operator* (sm::real scalar, sm::Quaternion quat)
{
    quat.x *= scalar;
    quat.y *= scalar;
    quat.z *= scalar;
    quat.w *= scalar;

    return quat;
}

inline sm::Vec3 sm::operator* (const sm::Quaternion &quat, const sm::Vec3 &v)
{
    sm::Vec3 qVec(quat.x, quat.y, quat.z);

    const sm::Vec3 t = sm::Vec3::crossProduct(qVec, v) * static_cast<sm::real>(2);

    return v + (t * quat.w) + sm::Vec3::crossProduct(qVec, t);
}

inline sm::Vec3 sm::operator* (const sm::Vec3 &v, const sm::Quaternion &quat)
{
    sm::Vec3 qVec(quat.x, quat.y, quat.z);

    const sm::Vec3 t = sm::Vec3::crossProduct(qVec, v) * static_cast<sm::real>(2);

    return v + (t * quat.w) + sm::Vec3::crossProduct(qVec, t);
}

#endif // SM_QUATERNION_H