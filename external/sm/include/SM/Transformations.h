#ifndef SM_TRANSFORMATIONS_H
#define SM_TRANSFORMATIONS_H

namespace sm {
struct Quaternion;
struct Matrix3x3;
struct Matrix3x4;
struct Vec3;

    /**
     * Converts a Quaternion to a Matrix3x3.
     * @param quat a sm::Quaternion
     * @return a sm::Matrix3x3
     */
    Matrix3x3 toMatrix3x3(const Quaternion &quat);

    /**
     * Combines a Quaternion and Vec3 into a singular Matrix3x4.
     * @param quat a sm::Quaternion
     * @param vec a sm::Vec3
     * @return a sm::Matrix3x4
     */
    Matrix3x4 toMatrix3x4(const Quaternion &quat, const Vec3 &vec);

    /**
     * Returns a global position.
     * @param localPos the local position
     * @param transform the Matrix3x4 transform
     * @return a global position
     */
    Vec3 localToGlobalPos(const Vec3 &localPos, const Matrix3x4 &transform);

    /**
     * Returns a local position of a transform.
     * @param globalPos the global position
     * @param transform the Matrix3x4 transform
     * @return a local position
     */
    Vec3 globalToLocalPos(const Vec3 &globalPos, const Matrix3x4 &transform);

    /**
     * Returns a global direction.
     * @param localDir the local direction
     * @param transform the Matrix3x4 transform
     * @return a global direction
     */
    Vec3 localToGlobalDir(const Vec3 &localDir, const Matrix3x4 &transform);

    /**
     * Returns a local direction of a transform.
     * @param globalDir the global direction
     * @param transform the Matrix3x4 transform
     * @return a local direction
     */
    Vec3 globalToLocalDir(const Vec3 &globalDir, const Matrix3x4 &transform);
} // namespace sm

#endif // SM_TRANSFORMATIONS_H