#ifndef SM_ORIENTATIONS_H
#define SM_ORIENTATIONS_H
#include <SM/Precision.h>

namespace sm {
struct Quaternion;
struct Vec3;

    Quaternion fromAxisAngle(const Vec3 &axis, sm::real angle);

    Quaternion fromEuler(sm::real pitch, sm::real yaw, sm::real roll);

    Quaternion lookAt(const Vec3 &source, const Vec3 &target, const Vec3 &globalUp);
} // namespace sm

#endif // SM_ORIENTATIONS_H