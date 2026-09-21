#ifndef SM_MATH_UTIL_H
#define SM_MATH_UTIL_H
#include <SM/Precision.h>
#include <SM/Vec3.h>

namespace sm {
class MathUtil {
public:
    static sm::real lerp(sm::real start, sm::real end, sm::real alpha);

    static sm::Vec3 lerp(const sm::Vec3 &start, const sm::Vec3 &end, sm::real alpha);
}; // class MathUtil
} // namespace sm

#endif // SM_MATH_UTIL_H