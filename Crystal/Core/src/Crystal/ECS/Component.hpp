#pragma once

#include "Crystal/Utils/CustomTypes.hpp"
#include "Crystal/Core/UUID.hpp"
#include "Crystal/Renderer/Texture.hpp"
#include "Crystal/Scripting/EntityScript.hpp"
#include "Crystal/ECS/ColliderComponents.hpp"

#include "Crystal/Renderer/2D/OrthoGraphicCamera.hpp"
#include "Crystal/Renderer/3D/PerspectiveCamera.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <filesystem>

namespace Crystal::ECS
{

    struct Component : public std::enable_shared_from_this<Component>
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

	// TODO(Jorben): Add like different types/models
	struct Renderer3DComponent : public Component
	{
	public:
		bool Enable = true;
		Vec4<float> Colour = { 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture = nullptr;

		bool UseTexture = false;
		bool UseColour = true;

	public:
		Renderer3DComponent();
		Renderer3DComponent(const Renderer3DComponent& other);
		Renderer3DComponent(const Vec4<float>& colour);
		Renderer3DComponent(Ref<Texture2D> texture);
		Renderer3DComponent(Ref<Texture2D> texture, const Vec4<float>& colour);
		virtual ~Renderer3DComponent();
	};

	struct ColliderComponent : public Component
	{
	public:
		Ref<AABBCollider> AABB;

	public:
		ColliderComponent();
		ColliderComponent(const ColliderComponent& other);
		virtual ~ColliderComponent();

		void Clean() const;
	};

	struct ScriptComponent : public Component
	{
	public:
		Ref<EntityScript> Script;

	public:
		ScriptComponent();
		ScriptComponent(const ScriptComponent& other);
		virtual ~ScriptComponent();
	};

	struct CameraComponent2D : public Component
	{
		Ref<OrthoGraphicCamera> Camera = nullptr;

		Vec2<float> Position = { 0.0f, 0.0f };
		Vec2<float> Size = { 1280.0f, 720.0f }; // This is not the actual size of the camera, the size gets set in the constructor
		float Zoom = 1.0f;
		float Rotation = 0.0f;

		bool Primary = true;

		CameraComponent2D();
		CameraComponent2D(const CameraComponent2D& other);
	};

	struct CameraComponent3D : public Component
	{
		Ref<PerspectiveCamera> Camera = nullptr;

		Vec3<float> Position = { 0.0f, 0.0f, 0.0f };
		Vec2<float> Size = { 1280.0f, 720.0f }; // This is not the actual size of the camera, the size gets set in the constructor
		float Zoom = 1.0f;
		float Rotation = 0.0f;

		float FOV = 45.f;

		bool Primary = true;

		CameraComponent3D();
		CameraComponent3D(const CameraComponent3D& other);
	};

}