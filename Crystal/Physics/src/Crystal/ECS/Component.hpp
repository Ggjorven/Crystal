#pragma once

#include "Crystal/Core/UUID.hpp"
#include "Crystal/Renderer/Texture.hpp"

#include <glm/glm.hpp>

namespace Crystal::ECS
{

    struct Component
    {
    public:
		Component() = default;
		virtual ~Component() = default;
    };

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}

		operator std::string& () { return Tag; }
		operator const std::string& () const { return Tag; }
	};

    struct TransformComponent : public Component
    {
    public:
		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::vec3& position, const glm::vec3& size, float rotation)
			: Position(position), Size(size), Rotation(rotation) {}

        glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Size = { 0.0f, 0.0f, 0.0f };
        float Rotation = 0.0f;
    };

	struct ScriptComponent : public Component
	{
		std::string Path;

		ScriptComponent() = default;
		ScriptComponent(const ScriptComponent& other) = default;
		ScriptComponent(const std::string& path)
			: Path(path) {}
	};

	struct Renderer2DComponent
	{
		glm::vec4 Colour = { 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture;

		Renderer2DComponent() = default;
		Renderer2DComponent(const Renderer2DComponent& other) = default;
		Renderer2DComponent(const glm::vec4& colour) 
			: Colour(colour) {}
		Renderer2DComponent(Ref<Texture2D> texture) 
			: Texture(texture) {}
		Renderer2DComponent(Ref<Texture2D> texture, const glm::vec4& colour)
			: Texture(texture), Colour(colour) {}
	};

	/*
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;

		CameraComponent() = default;
		CameraComponent(const CameraComponent& other) = default;

		operator SceneCamera& () { return Camera; }
		operator const SceneCamera& () const { return Camera; }
	};
	*/

}