#pragma once

#include <glm/glm.hpp>
#include <string>

#include "ScriptableEntity.h"

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

	struct NativeScriptComponent
	{
        NativeScriptComponent() = default;

		ScriptableEntity* instance = nullptr;

		std::function<void()> instantiateScript;
		std::function<void()> destroyScript;

		std::function<void(ScriptableEntity*)> onCreate;
		std::function<void(ScriptableEntity*, float)> onUpdate;
		std::function<void(ScriptableEntity*)> onDestroy;

		template <typename T>
		void bind()
		{
			instantiateScript = [this](){ instance = new T(); };
			destroyScript = [this](){ static_cast<T*>(instance)->onDestroy(); instance = nullptr; };

			onCreate = [](ScriptableEntity* instance){ static_cast<T*>(instance)->onCreate(); };
			onUpdate = [](ScriptableEntity* instance, float dt){ static_cast<T*>(instance)->onUpdate(dt); };
			onDestroy = [](ScriptableEntity* instance){ static_cast<T*>(instance)->onDestroy(); };
		}
	};

} // namespace butterfly
