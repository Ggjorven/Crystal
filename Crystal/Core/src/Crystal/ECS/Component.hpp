#pragma once

#include "Crystal/Utils/CustomTypes.hpp"
#include "Crystal/Core/UUID.hpp"
#include "Crystal/Renderer/Texture.hpp"
#include "Crystal/Scripting/EntityScript.hpp"

#include <glm/glm.hpp>

#include <filesystem>

namespace Crystal::ECS
{

    struct Component
    {
    public:
		Component() = default;
		virtual ~Component() = default;
    };

	struct TagComponent : public Component
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
		virtual ~TagComponent() 
		{ CR_CORE_TRACE("TagComponent"); }

		operator std::string& () { return Tag; }
		operator const std::string& () const { return Tag; }
	};

    struct TransformComponent : public Component
    {
    public:
		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const Vec3<float>& position, const Vec3<float>& size, float rotation)
			: Position(position), Size(size), Rotation(rotation) {}
		virtual ~TransformComponent() 
		{ CR_CORE_TRACE("TransformComponent"); }


		Vec3<float> Position = { 0.0f, 0.0f, 0.0f };
		Vec3<float> Size = { 0.0f, 0.0f, 0.0f };
        float Rotation = 0.0f;
    };

	struct Renderer2DComponent : public Component
	{
		bool Enable = true;
		Vec4<float> Colour = { 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture = nullptr;

		bool UseTexture;
		bool UseColour;

		Renderer2DComponent() = default;
		Renderer2DComponent(const Renderer2DComponent& other) = default;
		Renderer2DComponent(const Vec4<float>& colour)
			: Colour(colour), UseTexture(false), UseColour(true) {}
		Renderer2DComponent(Ref<Texture2D> texture) 
			: Texture(texture), UseTexture(true), UseColour(false) {}
		Renderer2DComponent(Ref<Texture2D> texture, const Vec4<float>& colour)
			: Texture(texture), Colour(colour), UseTexture(true), UseColour(false) {}
		virtual ~Renderer2DComponent() 
		{ CR_CORE_TRACE("Renderer2DComponent"); }
	};

	struct ScriptComponent : public Component
	{
		std::filesystem::path Path;
		Ref<EntityScript> Script;

		ScriptComponent() 
			: Script(CreateRef<EntityScript>()) {}
		ScriptComponent(const ScriptComponent& other) = default;
		ScriptComponent(const std::filesystem::path& path)
			: Path(path), Script(CreateRef<EntityScript>(path)) {}
		virtual ~ScriptComponent() 
		{ CR_CORE_TRACE("ScriptComponent");  }
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