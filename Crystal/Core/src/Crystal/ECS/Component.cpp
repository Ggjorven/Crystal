#include "crpch.h"
#include "Component.hpp"

#include  "Crystal/Core/Application.hpp"

namespace Crystal::ECS
{

	Component::Component()
	{
		//CR_CORE_TRACE("Component");
	}

	Component::~Component()
	{
		//CR_CORE_TRACE("~Component");
	}


	TagComponent::TagComponent() = default;

	TagComponent::TagComponent(const TagComponent& other) = default;

	TagComponent::TagComponent(const std::string& tag)
		: Tag(tag) {}

	TagComponent::~TagComponent() {}

	TagComponent::operator std::string& ()
	{
		return Tag;
	}

	TagComponent::operator const std::string& () const
	{
		return Tag;
	}


	TransformComponent::TransformComponent() = default;

	TransformComponent::TransformComponent(const TransformComponent& other) = default;

	TransformComponent::TransformComponent(const Vec3<float>& position, const Vec3<float>& size, float rotation)
		: Position(position), Size(size), Rotation(rotation) {}

	TransformComponent::~TransformComponent() { }


	Renderer2DComponent::Renderer2DComponent() = default;

	Renderer2DComponent::Renderer2DComponent(const Renderer2DComponent& other) = default;

	Renderer2DComponent::Renderer2DComponent(const Vec4<float>& colour)
		: Colour(colour), UseTexture(false), UseColour(true) {}

	Renderer2DComponent::Renderer2DComponent(Ref<Texture2D> texture)
		: Texture(texture), UseTexture(true), UseColour(false) {}

	Renderer2DComponent::Renderer2DComponent(Ref<Texture2D> texture, const Vec4<float>& colour)
		: Texture(texture), Colour(colour), UseTexture(true), UseColour(false) {}

	Renderer2DComponent::~Renderer2DComponent() { }


	Renderer3DComponent::Renderer3DComponent() = default;

	Renderer3DComponent::Renderer3DComponent(const Renderer3DComponent& other) = default;

	Renderer3DComponent::Renderer3DComponent(const Vec4<float>& colour)
		: Colour(colour), UseTexture(false), UseColour(true) {}

	Renderer3DComponent::Renderer3DComponent(Ref<Texture2D> texture)
		: Texture(texture), UseTexture(true), UseColour(false) {}

	Renderer3DComponent::Renderer3DComponent(Ref<Texture2D> texture, const Vec4<float>& colour)
		: Texture(texture), Colour(colour), UseTexture(true), UseColour(false) {}

	Renderer3DComponent::~Renderer3DComponent() { }


	ColliderComponent::ColliderComponent() = default;

	ColliderComponent::ColliderComponent(const ColliderComponent& other) = default;

	ColliderComponent::~ColliderComponent()
	{
		//Clean();
	}

	void ColliderComponent::Clean() const
	{
		// TODO
		//if (AABB.get()) AABB.reset();
	}


	ScriptComponent::ScriptComponent() 
		: Script(CreateRef<EntityScript>()) { }

	ScriptComponent::ScriptComponent(const ScriptComponent& other) = default;

	ScriptComponent::~ScriptComponent() { }


	CameraComponent2D::CameraComponent2D()
	{
		const Window& window = Application::Get().GetWindow();

		Camera = CreateRef<OrthoGraphicCamera>((float)window.GetViewportWidth() / 2.0f * -1, (float)window.GetViewportWidth() / 2.0f,
			(float)window.GetViewportHeight() / 2.0f * -1, (float)window.GetViewportHeight() / 2.0f);
	}

	CameraComponent2D::CameraComponent2D(const CameraComponent2D& other) = default;


	CameraComponent3D::CameraComponent3D()
	{
		const Window& window = Application::Get().GetWindow();
		
		Camera = CreateRef<PerspectiveCamera>((float)window.GetViewportWidth(), (float)window.GetViewportHeight());
		Camera->UpdateArea();
	}

	CameraComponent3D::CameraComponent3D(const CameraComponent3D& other) = default;

}