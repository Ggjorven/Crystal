#include "crpch.h"
#include "SceneRenderer.hpp"

#include "Crystal/Renderer/2D/Renderer2D.hpp"
#include "Crystal/Renderer/3D/Renderer3D.hpp"

namespace Crystal
{

	SceneRenderer2D::SceneRenderer2D(ECS::Storage& storage, Ref<OrthoGraphicCamera>& camera)
		: m_Storage(storage), m_Camera(camera)
	{
	}

	SceneRenderer2D::~SceneRenderer2D()
	{
	}

	void SceneRenderer2D::RenderScene()
	{
		for (auto& r2dC : m_Storage.GetComponentsMap<ECS::Renderer2DComponent>())
		{
			CR_UUID uuid = r2dC.first;
			if (m_Storage.HasComponent<ECS::TransformComponent>(uuid)) // Note(Jorben): Removed r2d.Enable maybe put it back sometime
			{
				auto& r2d = m_Storage.GetComponent<ECS::Renderer2DComponent>(uuid);
				auto& transform = m_Storage.GetComponent<ECS::TransformComponent>(uuid);

				if (r2d.Texture && r2d.UseTexture)
					Renderer2D::DrawQuad(Vec2<float>(transform.Position.x, transform.Position.y), Vec2<float>(transform.Size.x, transform.Size.y), Vec2<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f), r2d.Texture, false, m_Camera);
				else if (r2d.UseColour)
					Renderer2D::DrawQuad(Vec2<float>(transform.Position.x, transform.Position.y), Vec2<float>(transform.Size.x, transform.Size.y), Vec2<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f), r2d.Colour, false, m_Camera);
				else
					Renderer2D::DrawQuad(Vec2<float>(transform.Position.x, transform.Position.y), Vec2<float>(transform.Size.x, transform.Size.y), Vec2<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f), Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f), false, m_Camera);
			}	
		}
	}

	void SceneRenderer2D::RenderScene(Ref<OrthoGraphicCamera>& camera)
	{
		for (auto& r2dC : m_Storage.GetComponentsMap<ECS::Renderer2DComponent>())
		{
			CR_UUID uuid = r2dC.first;
			if (m_Storage.HasComponent<ECS::TransformComponent>(uuid)) // Note(Jorben): Removed r2d.Enable maybe put it back sometime
			{
				auto& r2d = m_Storage.GetComponent<ECS::Renderer2DComponent>(uuid);
				auto& transform = m_Storage.GetComponent<ECS::TransformComponent>(uuid);

				if (r2d.Texture && r2d.UseTexture)
					Renderer2D::DrawQuad(Vec2<float>(transform.Position.x, transform.Position.y), Vec2<float>(transform.Size.x, transform.Size.y), Vec2<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f), r2d.Texture, false, camera);
				else if (r2d.UseColour)
					Renderer2D::DrawQuad(Vec2<float>(transform.Position.x, transform.Position.y), Vec2<float>(transform.Size.x, transform.Size.y), Vec2<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f), r2d.Colour, false, camera);
				else
					Renderer2D::DrawQuad(Vec2<float>(transform.Position.x, transform.Position.y), Vec2<float>(transform.Size.x, transform.Size.y), Vec2<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f), Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f), false, camera);
			}
		}
	}

	void SceneRenderer2D::RenderScene(ECS::Storage& storage, Ref<OrthoGraphicCamera>& camera)
	{
		for (auto& r2dC : storage.GetComponentsMap<ECS::Renderer2DComponent>())
		{
			CR_UUID uuid = r2dC.first;
			if (storage.HasComponent<ECS::TransformComponent>(uuid)) // Note(Jorben): Removed r2d.Enable maybe put it back sometime
			{
				auto& r2d = storage.GetComponent<ECS::Renderer2DComponent>(uuid);
				auto& transform = storage.GetComponent<ECS::TransformComponent>(uuid);

				if (r2d.Texture && r2d.UseTexture)
					Renderer2D::DrawQuad(Vec2<float>(transform.Position.x, transform.Position.y), Vec2<float>(transform.Size.x, transform.Size.y), Vec2<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f), r2d.Texture, false, camera);
				else if (r2d.UseColour)
					Renderer2D::DrawQuad(Vec2<float>(transform.Position.x, transform.Position.y), Vec2<float>(transform.Size.x, transform.Size.y), Vec2<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f), r2d.Colour, false, camera);
				else
					Renderer2D::DrawQuad(Vec2<float>(transform.Position.x, transform.Position.y), Vec2<float>(transform.Size.x, transform.Size.y), Vec2<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f), Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f), false, camera);
			}
		}
	}

	SceneRenderer3D::SceneRenderer3D(ECS::Storage& storage)
		: m_Storage(storage)
	{
	}

	SceneRenderer3D::SceneRenderer3D(ECS::Storage& storage, Ref<PerspectiveCamera>& camera)
		: m_Storage(storage), m_Camera(camera)
	{
	}

	SceneRenderer3D::~SceneRenderer3D()
	{
	}

	void SceneRenderer3D::RenderScene() // TODO(Jorben): Add a way to also render 2D elements
	{
		for (auto& r3dC : m_Storage.GetComponentsMap<ECS::Renderer3DComponent>())
		{
			CR_UUID uuid = r3dC.first;
			if (m_Storage.HasComponent<ECS::TransformComponent>(uuid)) // Note(Jorben): Removed r3d.Enable maybe put it back sometime
			{
				auto& r3d = m_Storage.GetComponent<ECS::Renderer3DComponent>(uuid);
				auto& transform = m_Storage.GetComponent<ECS::TransformComponent>(uuid);

				if (r3d.Texture && r3d.UseTexture) // TODO(Jorben): Add textured cubes and more
					Renderer3D::DrawCube(transform.Position, transform.Size, Vec3<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f, transform.Size.z / 2.0f), r3d.Colour, false, m_Camera);
				else if (r3d.UseColour)
					Renderer3D::DrawCube(transform.Position, transform.Size, Vec3<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f, transform.Size.z / 2.0f), r3d.Colour, false, m_Camera);
				else
					Renderer3D::DrawCube(transform.Position, transform.Size, Vec3<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f, transform.Size.z / 2.0f), Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f), false, m_Camera);
			}
		}
	}

	void SceneRenderer3D::RenderScene(Ref<PerspectiveCamera>& camera)
	{
		for (auto& r3dC : m_Storage.GetComponentsMap<ECS::Renderer3DComponent>())
		{
			CR_UUID uuid = r3dC.first;
			if (m_Storage.HasComponent<ECS::TransformComponent>(uuid)) // Note(Jorben): Removed r3d.Enable maybe put it back sometime
			{
				auto& r3d = m_Storage.GetComponent<ECS::Renderer3DComponent>(uuid);
				auto& transform = m_Storage.GetComponent<ECS::TransformComponent>(uuid);

				if (r3d.Texture && r3d.UseTexture) // TODO(Jorben): Add textured cubes and more
					Renderer3D::DrawCube(transform.Position, transform.Size, Vec3<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f, transform.Size.z / 2.0f), r3d.Colour, false, camera);
				else if (r3d.UseColour)
					Renderer3D::DrawCube(transform.Position, transform.Size, Vec3<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f, transform.Size.z / 2.0f), r3d.Colour, false, camera);
				else
					Renderer3D::DrawCube(transform.Position, transform.Size, Vec3<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f, transform.Size.z / 2.0f), Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f), false, camera);
			}
		}
	}

	void SceneRenderer3D::RenderScene(ECS::Storage& storage, Ref<PerspectiveCamera>& camera)
	{
		for (auto& r3dC : storage.GetComponentsMap<ECS::Renderer3DComponent>())
		{
			CR_UUID uuid = r3dC.first;
			if (storage.HasComponent<ECS::TransformComponent>(uuid)) // Note(Jorben): Removed r3d.Enable maybe put it back sometime
			{
				auto& r3d = storage.GetComponent<ECS::Renderer3DComponent>(uuid);
				auto& transform = storage.GetComponent<ECS::TransformComponent>(uuid);

				if (r3d.Texture && r3d.UseTexture) // TODO(Jorben): Add textured cubes and more
					Renderer3D::DrawCube(transform.Position, transform.Size, Vec3<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f, transform.Size.z / 2.0f), r3d.Colour, false, camera);
				else if (r3d.UseColour)
					Renderer3D::DrawCube(transform.Position, transform.Size, Vec3<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f, transform.Size.z / 2.0f), r3d.Colour, false, camera);
				else
					Renderer3D::DrawCube(transform.Position, transform.Size, Vec3<float>(transform.Size.x / 2.0f, transform.Size.y / 2.0f, transform.Size.z / 2.0f), Vec4<float>(1.0f, 1.0f, 1.0f, 1.0f), false, camera);
			}
		}
	}

}