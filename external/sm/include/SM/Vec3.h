#ifndef SM_VEC3_H
#define SM_VEC3_H
#include <array>
#include <assert.h>
#include <SM/Precision.h>

namespace sm {

class Vec3 {
public:
    real x = static_cast<real>(0);
    real y = static_cast<real>(0);
    real z = static_cast<real>(0);

    /**
     * Explicit constructor.
     * @param x the x-axis position
     * @param y the y-axis position
     * @param z the z-axis position
     */
    constexpr Vec3(real x = static_cast<real>(0), real y = static_cast<real>(0), real z = static_cast<real>(0)) :
    x(x),
    y(y),
    z(z),
    _pad(0)
    {}

    /**
     * Explicit construtor that accepts array-style declaration.
     * @param list an array-style declaration of size 3
     */
    constexpr Vec3(const std::array<real, 3> &list) :
    x(list.at(0)),
    y(list.at(1)),
    z(list.at(2)),
    _pad(0)
    {}

    /**
     * Inverts the contents of the Vector3.
     */
    void invert();

    /**
     * Calculates the magnitude of the Vector3.
     * @return the magnitude (length) of the Vector3
     */
    real magnitude() const;

    /**
     * Calculates the squared magnitude of the Vector3.
     * @return the squared magnitude (length) of the Vector3
     */
    real sqrMagnitude() const;

    /**
     * Normalizes the Vector3.
     */
    void normalize();

    /**
     * Clears the Vec3.
     * Essentially resets x, y, and z to zero.
     */
    void clear();
    
    ////////////////////////////////////////
    //   Modifying Overloaded Operators   //
    ////////////////////////////////////////
    Vec3& operator *= (real scalar);
    Vec3& operator += (const Vec3 &vec);
    Vec3& operator -= (const Vec3 &vec);
    Vec3& operator %= (const Vec3 & vec);
    
    ////////////////////////////////////////////
    //   Non-Modifying Overloaded Operators   //
    ////////////////////////////////////////////
    constexpr Vec3 operator * (const real scalar) const
    {
        return Vec3(this->x * scalar, this->y * scalar, this->z * scalar);
    }
    
    Vec3 operator + (const Vec3 &vec) const;
    Vec3 operator - (const Vec3 &vec) const;
    constexpr Vec3 operator % (const Vec3 &vec) const
    {
        return Vec3(this->y * vec.z - this->z * vec.y,
                    this->z * vec.x - this->x * vec.z,
                    this->x * vec.y - this->y * vec.x);
    }

    /**
     * Updates this Vector3 by multiplying its components with the components of another Vec3.
     * @param vec the other Vec3 to perform the operation with
     * @return this
     */
    Vec3& componentProductUpdate(const Vec3 &vec);

    /**
     * Updates this Vector3 by adding a scaled Vector3 to itself.
     * @param vec the Vec3 to add
     * @param scalar the scalar to apply to the Vec3 argument
     * @return this
     */
    Vec3& addScaledVector(const Vec3 &vec, real scalar);

    //////////////////////////////
    //     Static Functions     //
    //////////////////////////////

    /**
     * Creates a normalized Vector3 copy.
     * @param v the Vector3
     * @return the normalized version of the Vector3
     */
    static Vec3 normalized(const Vec3 &v);

    /**
     * Returns the dot product between two Vec3s
     * @param v1 the first Vec3
     * @param v2 the second Vec3
     * @return a floating-point scalar
     */
    constexpr static real dot(const Vec3& v1, const Vec3 &v2)
    {
        return  v1.x * v2.x +
                v1.y * v2.y +
                v1.z * v2.z;
    }

    /**
     * Calculates the component product between two Vec3s.
     * @param v1 the first Vec3
     * @param v2 the second Vec3
     * @return a brand new Vec3 representing the component product between both Vec3s
     */
    static Vec3 componentProduct(const Vec3 &v1, const Vec3 &v2);

    /**
     * Calcualtes the vector (cross) product between two Vec3s.
     * @param v1 the first Vec3
     * @param v2 the second Vec3
     * @return a brand new Vec3 representing the vector product between both Vec3s
     */
    constexpr static Vec3 crossProduct(const Vec3 &v1, const Vec3 &v2)
    {
        return v1 % v2;
    }

private:
    float _pad;
}; // class Vec3

} // namespace sm

#endif // SM_VEC3_H