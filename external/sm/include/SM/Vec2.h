#ifndef SM_VEC2_H
#define SM_VEC2_H
#include <array>
#include <cmath>
#include <SM/Precision.h>

namespace sm {

// TODO test all the functions of this class.
class Vec2 {
public:
    float x;
    float y;

    Vec2();
    Vec2(const Vec2 &otherVec);
    Vec2(float x, float y);
    Vec2(const std::array<sm::real, 2> &list);
    ~Vec2();

    static Vec2 zero();
    static Vec2 up();
    static Vec2 down();
    static Vec2 right();
    static Vec2 left();

    friend Vec2 operator + (const Vec2 &lhs, const Vec2 &rhs);
    friend Vec2 operator - (const Vec2 &lhs, const Vec2 &rhs);
    friend Vec2 operator * (const Vec2 &vec, float scalar);
    friend Vec2 operator / (const Vec2 &vec, float scalar);
    friend Vec2 operator * (float scalar, const Vec2 &vec);
    friend Vec2 operator / (float scalar, const Vec2 &vec);
    friend bool operator == (const Vec2 &lhs, const Vec2 &rhs);
    friend bool operator != (const Vec2 &lhs, const Vec2 &rhs);

    Vec2 operator - () const;
    float length () const;
    float lengthSquared () const;
    Vec2 normalized () const;
    float dotProduct(const Vec2 &otherVec) const;
    float crossProdcut(const Vec2 &otherVec) const;
    Vec2 lerp (const Vec2 &otherVec, float t) const;
    float distance (const Vec2 &otherVec) const;
    float angleBetween(const Vec2 &otherVec) const;
    Vec2 rotated(float angle) const;
    Vec2 reflected (const Vec2 &normal) const;
    Vec2 scaled(float scalar) const;
    
    Vec2& rotate(float angle);
    Vec2& scale(float scalar);
    Vec2& operator = (const Vec2 &otherVec);
    Vec2& operator += (const Vec2 &otherVec);
    Vec2& operator -= (const Vec2 &otherVec);
    Vec2& operator *= (float scalar);
    Vec2& operator /= (float scalar);

};

};

#endif // SM_VEC2_H