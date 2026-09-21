#include <SM/Vec2.h>

namespace sm
{
    Vec2::Vec2()
    : x(0), y(0)
    {};

    Vec2::Vec2(const Vec2 &otherVec)
    : x(otherVec.x), y(otherVec.y)
    {}

    Vec2::Vec2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Vec2::Vec2(const std::array<sm::real, 2> &list)
    {
        this->x = list.at(0);
        this->y = list.at(1);
    }

    Vec2::~Vec2()
    {

    }

    Vec2 Vec2::zero()
    {
        return {0.f, 0.f};
    }

    Vec2 Vec2::up()
    {
        return {0.f, -1.0f};
    }

    Vec2 Vec2::down()
    {
        return {0.f, 1.0f};
    }

    Vec2 Vec2::right()
    {
        return {1.f, 0.f};
    }

    Vec2 Vec2::left()
    {
        return {-1.f, 0.f};
    }

    Vec2 operator + (const Vec2 &lhs, const Vec2 &rhs)
    {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }

    Vec2 operator - (const Vec2 &lhs, const Vec2 &rhs)
    {
        return {lhs.x - rhs.x, lhs.y - rhs.y};
    }

    Vec2 operator * (const Vec2 &vec, float scalar)
    {
        return {vec.x * scalar, vec.y * scalar};
    }

    Vec2 operator / (const Vec2 &vec, float scalar)
    {
        return {vec.x / scalar, vec.y / scalar};
    }

    Vec2 operator * (float scalar, const Vec2 &vec)
    {
        return {vec.x * scalar, vec.y * scalar};
    }

    Vec2 operator / (float scalar, const Vec2 &vec)
    {
        return {vec.x / scalar, vec.y / scalar};
    }

    bool operator == (const Vec2 &lhs, const Vec2 &rhs)
    {
        return (lhs.x == rhs.x && lhs.y == rhs.y);
    }

    bool operator != (const Vec2 &lhs, const Vec2 &rhs)
    {
        return !(lhs == rhs);
    }

    Vec2 Vec2::operator - () const
    {
        return {-this->x, -this->y};
    }

    float Vec2::length() const
    {
        return std::sqrt((this->x * this->x) + (this->y * this->y));
    }

    float Vec2::lengthSquared () const
    {
        return (this->x * this->x) + (this->y * this->y);
    }

    Vec2 Vec2::normalized () const
    {
        float length = this->length();
        if (length != 0)
        {
            return {this->x / length, this->y / length};
        }
        else
        {
            return {0.f, 0.f};
        }
    }

    float Vec2::dotProduct(const Vec2 &otherVec) const
    {
        return ((this->x * otherVec.x) + (this->y * otherVec.y));
    }

    float Vec2::crossProdcut(const Vec2 &otherVec) const
    {
        return ((this->x * otherVec.y) - (this->y * otherVec.x));
    }

    Vec2 Vec2::lerp (const Vec2 &otherVec, float t) const
    {
        return *this + (otherVec - *this).scale(t);
    }

    float Vec2::distance (const Vec2 &otherVec) const
    {
        return (*this - otherVec).length();
    }

    float Vec2::angleBetween(const Vec2 &otherVec) const
    {
        float dotProd = this->dotProduct(otherVec);
        float lengths = this->length() * otherVec.length();
        return std::acos(dotProd / lengths);
    }

    Vec2 Vec2::rotated(float angle) const
    {
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);
        
        return {(this->x * cosA) - (this->y * sinA), (this->x * sinA) + (this->y * cosA)};
    }

    Vec2 Vec2::reflected (const Vec2 &normal) const
    {
        return *this - (2 * normal).scale(this->dotProduct(normal));
    }

    Vec2 Vec2::scaled (float scalar) const
    {
        return {this->x * scalar, this->y * scalar};
    }

    Vec2& Vec2::rotate(float angle)
    {
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);

        float oldX = this->x;

        this->x = (oldX * cosA) - (y * sinA);
        this->y = (oldX * sinA) + (y * cosA);
        
        return *this;
    }

    Vec2& Vec2::scale(float scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    Vec2& Vec2::operator = (const Vec2 &otherVec)
    {
        if (this != &otherVec)
        {
            this->x = otherVec.x;
            this->y = otherVec.y;
        }
        return *this;
    }

    Vec2& Vec2::operator += (const Vec2 &otherVec)
    {
        this->x += otherVec.x;
        this->y += otherVec.y;
        return *this;
    }

    Vec2& Vec2::operator -= (const Vec2 &otherVec)
    {
        this->x -= otherVec.x;
        this->y -= otherVec.y;
        return *this;
    }

    Vec2& Vec2::operator *= (float scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    Vec2& Vec2::operator /= (float scalar)
    {
        this->x /= scalar;
        this->y /= scalar;
        return *this;
    }
};