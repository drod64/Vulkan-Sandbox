#ifndef SM_MATRIX_3X4_H
#define SM_MATRIX_3X4_H
#include <stdexcept>
#include <SM/Vec3.h>

namespace sm {
/**
 * This Matrix actually only holds 12 elements. However, it implicity uses [0,0,0,1] as the last row for
 * a 4x4 Matrix effect.
 */
class Matrix3x4 {
private:
    real m_matrix[12] = {1, 0, 0, 0,
                         0, 1, 0, 0,
                         0, 0, 1, 0};

    void setMatrix(const real *matrix);
public:
    /**
     * @param row the desired row
     * @return a sm::real pointer offset by row
     */
    real* operator[](size_t row);

    /**
     * @param row the desired row
     * @return a const sm::real pointer offset by row
     */
    const real* operator[](size_t row) const;
    
    /**
     * Translates the Matrix3x4 by a Vec3 in global coordinates.
     * 
     * NOTE: Ignores orientation.
     * @param v the Vec3 to translate by
     * @return reference to this
     */
    Matrix3x4& operator+=(const Vec3 &v);

    /**
     * Adds two Matrix3x4s together.
     * @param other the other Matrix3x4
     * @return a reference to this
     */
    Matrix3x4& operator+=(const Matrix3x4 &other);
    
    /**
     * Multiplies two Matrix3x4s together.
     * @param other the other Matrix3x4
     * @return a reference to this
     */
    Matrix3x4& operator*=(const Matrix3x4 &other);
    
    /**
     * Multiplies the Matrix3x4 by a scalar.
     * @param scalar the scalar to multiply by
     * @return a reference to this
     */
    Matrix3x4& operator*=(real scalar);
    
    /**
     * Translates the Matrix3x4 by a Vec3 in the global coordinates.
     * 
     * NOTE: This translation ignores orientation.
     * @param v the Vec3 to translate by
     * @return reference to this
     */
    void translate(const Vec3 &v);

    /**
     * Translates the Matrix3x4 by a Vec3 in the local coordinates.
     * 
     * NOTE: This translation takes orientation into account.
     * @param v the Vec3 to translate by
     * @return reference to this
     */
    void translate_local(const Vec3 &v);

    /**
     * Inverses the Matrix3x4 in-place.
     */
    void inverse();
    
    /**
     * Sets the data of the Matrix3x4.
     * @param mat the sm::Matrix3x4 to copy from
     */
    void setMatrix3x4(const Matrix3x4 &mat);
    
    /**
     * @return the internal sm::real[]
     */
    sm::real* data();

    /**
     * @return the const internal sm::real[]
     */
    const sm::real *data() const;
    
    /**
     * Transforms a point vector (local -> global).
     * @param v the Vec3 point to transform
     * @return the resulting transformation point
     */
    [[nodiscard]] Vec3 transformPoint(const Vec3 &v) const;
    
    /**
     * Transforms a point vector (but inverse!) (global -> local).
     * @param v the Vec3 point to transform
     * @return the resulting transformation point
     */
    [[nodiscard]] Vec3 transformPointInv(const Vec3 &v) const;
    
    /**
     * Transforms a directional vector (local -> global).
     * @param v the Vec3 directional vector
     * @return the resulting transformation direction
     */
    [[nodiscard]] Vec3 transformDirection(const sm::Vec3 &v) const;

    /**
     * Transforms a directional vector (but inverse!) (global -> local).
     * @param v the Vec3 directional vector
     * @return the resulting transformation direction
     */
    [[nodiscard]] Vec3 transformDirectionInv(const sm::Vec3 &v) const;

    [[nodiscard]] inline sm::Vec3 getForward() const
    {
        return sm::Vec3(this->m_matrix[2], this->m_matrix[6], this->m_matrix[10]);
    }

    [[nodiscard]] inline sm::Vec3 getUp() const
    {
        return sm::Vec3(this->m_matrix[1], this->m_matrix[5], this->m_matrix[9]);
    }

    [[nodiscard]] inline sm::Vec3 getRight() const
    {
        return sm::Vec3(this->m_matrix[0], this->m_matrix[4], this->m_matrix[8]);
    }

    [[nodiscard]] inline sm::Vec3 getPosition() const
    {
        return sm::Vec3(this->m_matrix[3], this->m_matrix[7], this->m_matrix[11]);
    }
    
    /**
     * Returns a globally translated version of the Matrix3x4.
     * 
     * NOTE: This is a non-modifying function. Also ignores orientation.
     * @return the translated copy-version of the Matrix3x4
     */
    [[nodiscard]] Matrix3x4 translated(const Vec3 &v) const;
    
    /**
     * Returns a locally translated version of the Matrix3x4.
     * 
     * NOTE: This is a non-modifying function. Also takes orientation into account.
     * @return the translated copy-version of the Matrix3x4
     */
    [[nodiscard]] Matrix3x4 translatedLocal(const Vec3 &v) const;

    /**
     * Returns an inversed version of the Matrix3x4.
     * 
     * NOTE: This is a non-modifying function.
     * @return the inverse copy-version of the Matrix3x4
     */
    [[nodiscard]] sm::Matrix3x4 inversed() const;
}; // class Matrix3x4

// Math operator overload declarations.
[[nodiscard]] Matrix3x4 operator+(Matrix3x4 lhs, const Matrix3x4 &rhs);

[[nodiscard]] Matrix3x4 operator*(Matrix3x4 lhs, const Matrix3x4 &rhs);
[[nodiscard]] Matrix3x4 operator*(Matrix3x4 mat, real scalar);
[[nodiscard]] Matrix3x4 operator*(real scalar, Matrix3x4 mat);

[[nodiscard]] Vec3 operator*(const Vec3 &v, const Matrix3x4 &mat);
[[nodiscard]] Vec3 operator*(const Matrix3x4 &mat, const Vec3 &v);

} // namespace sm

// Math operator overload implementations.
inline sm::Matrix3x4 sm::operator+(sm::Matrix3x4 lhs, const sm::Matrix3x4 &rhs)
{
    lhs += rhs;

    return lhs;
}

inline sm::Matrix3x4 sm::operator*(sm::Matrix3x4 lhs, const sm::Matrix3x4 &rhs)
{
    lhs *= rhs;

    return lhs;
}

inline sm::Matrix3x4 sm::operator*(sm::Matrix3x4 mat, sm::real scalar)
{
    mat *= scalar;
    return mat;
}

inline sm::Matrix3x4 sm::operator*(sm::real scalar, sm::Matrix3x4 mat)
{
    mat *= scalar;
    return mat;
}

inline sm::Vec3 sm::operator*(const sm::Matrix3x4 &mat, const sm::Vec3 &v)
{
    return mat.transformPoint(v);
}

inline sm::Vec3 sm::operator*(const sm::Vec3 &v, const sm::Matrix3x4 &mat)
{
    return mat.transformPoint(v);
}

#endif // SM_MATRIX_3x4_H