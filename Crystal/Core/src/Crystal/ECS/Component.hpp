#pragma once

#include "Crystal/Utils/CustomTypes.hpp"
#include "Crystal/Core/UUID.hpp"
#include "Crystal/Renderer/Texture.hpp"
#include "Crystal/Scripting/EntityScript.hpp"
#include "Crystal/ECS/ColliderComponents.hpp"

#include <glm/glm.hpp>

#include <filesystem>

namespace Crystal::ECS
{

    struct Component
    {
    public:
		Component();
		virtual ~Component();
    };

	struct TagComponent : public Component
	{
	public:
		std::string Tag;

	public:
		TagComponent();
		TagComponent(const TagComponent& other);
		TagComponent(const std::string& tag);
		virtual ~TagComponent();

		operator std::string& ();
		operator const std::string& () const;
	};

    struct TransformComponent : public Component
    {
    public:
		Vec3<float> Position = { 0.0f, 0.0f, 0.0f };
		Vec3<float> Size = { 0.0f, 0.0f, 0.0f };
		float Rotation = 0.0f;

	public:
		TransformComponent();
		TransformComponent(const TransformComponent& other);
		TransformComponent(const Vec3<float>& position, const Vec3<float>& size, float rotation);
		virtual ~TransformComponent();
    };

	struct Renderer2DComponent : public Component
	{
	public:
		bool Enable = true;
		Vec4<float> Colour = { 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture = nullptr;

		bool UseTexture = false;
		bool UseColour = true;

	public:
		Renderer2DComponent();
		Renderer2DComponent(const Renderer2DComponent& other);
		Renderer2DComponent(const Vec4<float>& colour);
		Renderer2DComponent(Ref<Texture2D> texture);
		Renderer2DComponent(Ref<Texture2D> texture, const Vec4<float>& colour);
		virtual ~Renderer2DComponent();
	};

	struct ColliderComponent : public Component
	{
	public:
		AABBCollider* AABB = nullptr;

	public:
		ColliderComponent();
		ColliderComponent(const ColliderComponent& other);
		virtual ~ColliderComponent();

		void Clean() const;
	};

	struct ScriptComponent : public Component
	{
	public:
		std::filesystem::path Path;
		Ref<EntityScript> Script;

	public:
		ScriptComponent();
		ScriptComponent(const ScriptComponent& other);
		ScriptComponent(const std::filesystem::path& path);
		virtual ~ScriptComponent();
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