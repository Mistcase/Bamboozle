#pragma once

#include "Butterfly/Core.h"

#include <filesystem>
#include <vector>

namespace butterfly
{
	class Texture;
	class Shader;
	class UniformBuffer;

	class Material
	{
	public:
		struct LightingParams
		{
			float kAmbient;
			float kDiffuse;
			float kSpecular;
			float shininess;
		};

		using Textures = std::vector<Ref<Texture>>;
		static Ref<Material> Create(Shader* shader, const LightingParams& params, Textures&& textures);

		void apply() const;

	private:
		Material(Shader* shader, const LightingParams& params, Textures&& textures);

	private:
		Textures m_textures;
		Shader* m_shader;

		Ref<UniformBuffer> m_uniformBuffer;

	private:
		enum class MaterialTextureType
		{
			Default,
			SpecularMap,

			Count
		};

		struct MaterialBuffer
		{
			float ka;
			float kd;
			float ks;
			float sa;

			int textureDefault;
			int textureSpecularMap;
		};
		MaterialBuffer m_uniformBufferData;
	};


} // namespace butterfly
