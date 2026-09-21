#ifndef SM_MATRIX_3X3_H
#define SM_MATRIX_3X3_H
#include <cstdint>
#include <stdexcept>
#include <SM/Precision.h>
#include <SM/Vec3.h>

namespace sm {
struct Matrix3x3 {
private:
    sm::real m_matrix[9] = {1,0,0,
                            0,1,0,
                            0,0,1};
    
    /**
     * Sets the internal array to represent a 3x3 matrix.
     * This function simply copies the values from the passed in sm::real*
     * 
     * @param matrix the sm::real* to copy from
     */
    void setMatrix(const sm::real *matrix);

public:
    /**
     * @param row the desired row
     * @return a sm::real pointer offset by row
     */
    sm::real* operator[] (uint32_t row);
    
    /**
     * @param row the desired row
     * @return a sm::real pointer offset by row
     */
    const sm::real* operator[] (uint32_t row) const;
    
    /**
     * Adds a Matrix3x3.
     * @param other the Matrix3x3 to add
     * @return a reference to this
     */
    Matrix3x3& operator+=(const Matrix3x3 &other);
    
    /**
     * Multiplies the Matrix3x3 by another Matrix3x3.
     * @param other the other Matrix3x3
     * @return a reference to this
     */
    Matrix3x3& operator*=(const Matrix3x3 &other);
    
    /**
     * Multiplies the Matrix3x3 by a scalar.
     * @param scalar the scalar to multiply by
     * @return a reference to this
     */
    Matrix3x3& operator*=(real scalar);
    
    /**
     * Transposes the Matrix3x3 in-place.
     */
    void transpose();
    
    /**
     * Inverses the Matrix3x3 in-place.
     */
    void inverse();
    
    /**
     * Absolutes the Matrix3x3 in-place.
     */
    void absolute();
    
    /**
     * Sets the data of the Matrix3x3.
     * @param mat the Matrix3x3 to copy from
     */
    void setMatrix3x3(const Matrix3x3 &mat);
    
    /**
     * @return the internal sm::real[]
     */
    sm::real* data();
    
    /**
     * @return the const internal sm::real[]
     */
    const sm::real* data() const;
    
    /**
     * Transforms a vector (local -> global).
     * @param v the Vec3
     * @return the resulting transformation vector
     */
    [[nodiscard]] Vec3 transform(const Vec3 &v) const;

    /**
     * Transforms a vector (but inverse!) (global -> local).
     * @param v the Vec3
     * @return the resulting transformation vector (inverse)
     */
    [[nodiscard]] Vec3 transformInverse(const Vec3 &v) const;

    /**
     * Returns an absolute version of the Matrix3x3.
     * 
     * NOTE: This is a non-modifying function.
     * @return the absolute copy-version of the Matrix3x3
     */
    [[nodiscard]] sm::Matrix3x3 absoluted() const;
    
    /**
     * Returns a transposed version of the Matrix3x3.
     * 
     * NOTE: This is a non-modifying function.
     * @return the transpose copy-version of the Matrix3x3
     */
    [[nodiscard]] sm::Matrix3x3 transposed() const;
    
    /**
     * Returns an inversed version of the Matrix3x3.
     * 
     * NOTE: This is a non-modifying function.
     * @return the inverse copy-version of the Matrix3x3
     */
    [[nodiscard]] sm::Matrix3x3 inversed() const;
}; // class Matrix3x3

// Math operator overload declarations
[[nodiscard]] Matrix3x3 operator+ (Matrix3x3 lhs, const Matrix3x3 &rhs);

[[nodiscard]] Matrix3x3 operator* (Matrix3x3 lhs, const Matrix3x3 &rhs);
[[nodiscard]] Matrix3x3 operator* (Matrix3x3 mat, real scalar);
[[nodiscard]] Matrix3x3 operator* (real scalar, Matrix3x3 mat);

[[nodiscard]] Vec3 operator* (const Vec3 &v, const Matrix3x3 &mat);
[[nodiscard]] Vec3 operator* (const Matrix3x3 &mat, const Vec3 &v);
} // namespace sm

// Math operator overload implementations
inline sm::Matrix3x3 sm::operator+(sm::Matrix3x3 lhs, const sm::Matrix3x3 &rhs)
{
    lhs += rhs;

    return lhs;
}

inline sm::Matrix3x3 sm::operator*(sm::Matrix3x3 lhs, const sm::Matrix3x3 &rhs)
{
    lhs *= rhs;

    return lhs;
}

inline sm::Matrix3x3 sm::operator*(sm::Matrix3x3 mat, sm::real scalar)
{
    mat *= scalar;

    return mat;
}
inline sm::Matrix3x3 sm::operator*(sm::real scalar, sm::Matrix3x3 mat)
{
    mat *= scalar;

    return mat;
}

inline sm::Vec3 sm::operator*(const sm::Matrix3x3 &mat, const sm::Vec3 &v)
{
    return mat.transform(v);
}

inline sm::Vec3 sm::operator* (const sm::Vec3 &v, const sm::Matrix3x3 &mat)
{
    return mat.transform(v);
}

#endif // SM_MATRIX_3X3_H