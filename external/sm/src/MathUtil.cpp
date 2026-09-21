#include <SM/MathUtil.h>

sm::real sm::MathUtil::lerp(sm::real start, sm::real end, sm::real alpha)
{
    return start + alpha * (end - start);
}

sm::Vec3 sm::MathUtil::lerp(const sm::Vec3 &start, const sm::Vec3 &end, sm::real alpha)
{
    return sm::Vec3(
        sm::MathUtil::lerp(start.x, end.x, alpha),
        sm::MathUtil::lerp(start.y, end.y, alpha),
        sm::MathUtil::lerp(start.z, end.z, alpha)
    );
}