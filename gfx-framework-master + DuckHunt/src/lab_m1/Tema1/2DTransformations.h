#pragma once

using namespace std;

#include "utils/glm_utils.h"

namespace tr2D
{
    // Translate matrix
    inline glm::mat3 Translate(double translateX, double translateY)
    {
        return glm::transpose(
            glm::mat3(1, 0, translateX,
                0, 1, translateY,
                0, 0, 1)
        );
    }

    // Scale matrix
    inline glm::mat3 Scale(double scaleX, double scaleY)
    {
        return glm::transpose(
            glm::mat3(scaleX, 0, 0,
                0, scaleY, 0,
                0, 0, 1)
        );
    }

    // Rotate matrix
    inline glm::mat3 Rotate(double radians)
    {
        return glm::transpose(
            glm::mat3(cos(radians), -sin(radians), 0,
                sin(radians), cos(radians), 0,
                0, 0, 1)
        );
    }
}   // namespace tr2D