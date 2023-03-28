#pragma once

#include <glm/glm.hpp>
#include <string>

namespace butterfly
{
    /* struct TransformComponent */
    /* { */
    /* }; */

    struct TagComponent
    {
        std::string tag;
    };

    struct CameraComponent
    {
        glm::mat4 projection;
    };

} // namespace butterfly
