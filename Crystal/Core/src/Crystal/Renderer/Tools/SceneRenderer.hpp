#pragma once

#include "Crystal/Core/Core.hpp"

#include "Crystal/Renderer/2D/OrthoGraphicCamera.hpp"
#include "Crystal/Renderer/3D/PerspectiveCamera.hpp"

#include "Crystal/ECS/Storage.hpp"

namespace Crystal
{

	class SceneRenderer2D
	{
	public:
		SceneRenderer2D(ECS::Storage& storage, Ref<OrthoGraphicCamera>& camera);
		virtual ~SceneRenderer2D();

		void RenderScene();
		void RenderScene(Ref<OrthoGraphicCamera>& camera);
		static void RenderScene(ECS::Storage& storage, Ref<OrthoGraphicCamera>& camera);

		inline void SetStorage(ECS::Storage& storage) { m_Storage = storage; }
		inline void SetCamera(Ref<OrthoGraphicCamera>& camera) { m_Camera = camera; }

	private:
		ECS::Storage& m_Storage;
		Ref<OrthoGraphicCamera>& m_Camera;
	};

	class SceneRenderer3D // TODO
	{
	public:
		SceneRenderer3D() = default;
		//SceneRenderer3D(ECS::Storage& storage, Ref<PerspectiveCamera>& camera) = default;
	};

}