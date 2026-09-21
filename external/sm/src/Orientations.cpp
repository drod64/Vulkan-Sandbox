#include <SM/Orientations.h>
#include <SM/Quaternion.h>
#include <SM/Vec3.h>

sm::Quaternion sm::fromAxisAngle(const sm::Vec3 &axis, sm::real angle)
{
    sm::real halfAngle = angle * static_cast<sm::real>(0.5);
    sm::real sinHalf = real_sin(halfAngle);

    sm::Quaternion result;
    result.x = axis.x * sinHalf;
    result.y = axis.y * sinHalf;
    result.z = axis.z * sinHalf;
    result.w = real_cos(halfAngle);
    
    return result;
}

sm::Quaternion sm::fromEuler(sm::real pitch, sm::real yaw, sm::real roll)
{
    sm::real p = pitch * static_cast<sm::real>(0.5);
    sm::real y = yaw * static_cast<sm::real>(0.5);
    sm::real r = roll * static_cast<sm::real>(0.5);

    sm::real sinP = real_sin(p);
    sm::real cosP = real_cos(p);
    sm::real sinY = real_sin(y);
    sm::real cosY = real_cos(y);
    sm::real sinR = real_sin(r);
    sm::real cosR = real_cos(r);

    Quaternion q;

    q.x = (sinP * cosY * cosR) + (cosP * sinY * sinR);
    q.y = (cosP * sinY * cosR) - (sinP * cosY * sinR);
    q.z = (cosP * cosY * sinR) - (sinP * sinY * cosR);
    q.w = (cosP * cosY * cosR) + (sinP * sinY * sinR);

    return q;
}

sm::Quaternion sm::lookAt(const sm::Vec3 &source, const sm::Vec3 &target, const sm::Vec3 &globalUp)
{
    sm::Vec3 forward = target - source;
    forward.normalize();

    sm::Vec3 right = sm::Vec3::crossProduct(globalUp, forward);
    right.normalize();
    
    sm::Vec3 up = sm::Vec3::crossProduct(forward, right);

    sm::real m00 = right.x; sm::real m01 = up.x; sm::real m02 = forward.x;
    sm::real m10 = right.y; sm::real m11 = up.y; sm::real m12 = forward.y;
    sm::real m20 = right.z; sm::real m21 = up.z; sm::real m22 = forward.z;

    sm::Quaternion quat;
    sm::real trace = m00 + m11 + m22;

    if (trace > static_cast<sm::real>(0))
    {
        sm::real s = static_cast<sm::real>(0.5) / real_sqrt(trace + static_cast<sm::real>(1));

        quat.x = (m21 - m12) * s;
        quat.y = (m02 - m20) * s;
        quat.z = (m10 - m01) * s;
        quat.w = static_cast<sm::real>(0.25) / s;
    }
    else
    {
        if (m00 > m11  && m00 > m22)
        {
            sm::real s = static_cast<sm::real>(2) * real_sqrt(static_cast<sm::real>(1) + m00 - m11 - m22);

            quat.x = static_cast<sm::real>(0.25) * s;
            quat.y = (m01 + m10) / s;
            quat.z = (m02 + m20) / s;
            quat.w = (m21 - m12) / s;
        }
        else if (m11 > m22)
        {
            sm::real s = static_cast<sm::real>(2) * real_sqrt(static_cast<sm::real>(1) + m11 - m00 - m22);

            quat.x = (m01 + m10) / s;
            quat.y = static_cast<sm::real>(0.25) * s;
            quat.z = (m12 + m21) / s;
            quat.w = (m02 - m20) / s;
        }
        else
        {
            sm::real s = static_cast<sm::real>(2) * real_sqrt(static_cast<sm::real>(1) + m22 - m00 - m11);

            quat.x = (m02 + m20) / s;
            quat.y = (m12 + m21) / s;
            quat.z = static_cast<sm::real>(0.25) * s;
            quat.w = (m10 + m01) / s;
        }
    }

    quat.normalize();

    return quat;
}