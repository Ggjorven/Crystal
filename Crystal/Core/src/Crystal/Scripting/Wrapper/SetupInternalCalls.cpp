#include "crpch.h"
#include "SetupInternalCalls.hpp"

#include "Crystal/Core/Events/Input/Input.hpp"
#include "Crystal/Scripting/Wrapper/Core/WindowWrapper.hpp"

#include "Crystal/Scripting/Wrapper/ECS/EntityWrapper.hpp"
#include "Crystal/Scripting/Wrapper/ECS/ComponentWrapper.hpp"

#include "Crystal/Scripting/Wrapper/Data/Scene/SceneWrapper.hpp"

#define CR_ADD_INTERNAL(name, functionPtr) \
    assembly.AddInternalCall("Crystal.InternalCalls", name, reinterpret_cast<void*>(functionPtr))

namespace Crystal::Wrapper
{

	void Setup::Run(Coral::ManagedAssembly& assembly) // TODO(Jorben): Replace everything with CR_ADD_INTERNAL(...)
	{
		// ---Core---
		CR_ADD_INTERNAL("Input_IsKeyPressed", &Input::IsKeyPressed);

		CR_ADD_INTERNAL("Window_GetWindowWidth", &Window::Window_GetWindowWidth);
		CR_ADD_INTERNAL("Window_GetWindowHeight", &Window::Window_GetWindowHeight);

		// ---Scene---
		CR_ADD_INTERNAL("GetUUIDByTag", &Scene::GetUUIDByTag);
		CR_ADD_INTERNAL("SetSceneByName", &Scene::SetSceneByName);

		// ---ECS---
		// TagComponent
		assembly.AddInternalCall("Crystal.InternalCalls", "AddTagComponent", reinterpret_cast<void*>(&Entity::AddTagComponent));
		/// Setters
		assembly.AddInternalCall("Crystal.InternalCalls", "TagComponent_SetTag", reinterpret_cast<void*>(&Component::TagComponent_SetTag));
		/// Getters
		assembly.AddInternalCall("Crystal.InternalCalls", "TagComponent_GetTag", reinterpret_cast<void*>(&Component::TagComponent_GetTag));

		// TransformComponent
		/// Setters
		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_SetPositionX", reinterpret_cast<void*>(&Component::TransformComponent_SetPositionX));
		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_SetPositionY", reinterpret_cast<void*>(&Component::TransformComponent_SetPositionY));
		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_SetPositionZ", reinterpret_cast<void*>(&Component::TransformComponent_SetPositionZ));

		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_SetSizeX", reinterpret_cast<void*>(&Component::TransformComponent_SetSizeX));
		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_SetSizeY", reinterpret_cast<void*>(&Component::TransformComponent_SetSizeY));
		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_SetSizeZ", reinterpret_cast<void*>(&Component::TransformComponent_SetSizeZ));

		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_SetRotation", reinterpret_cast<void*>(&Component::TransformComponent_SetRotation));
		/// Getters
		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_GetPositionX", reinterpret_cast<void*>(&Component::TransformComponent_GetPositionX));
		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_GetPositionY", reinterpret_cast<void*>(&Component::TransformComponent_GetPositionY));
		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_GetPositionZ", reinterpret_cast<void*>(&Component::TransformComponent_GetPositionZ));

		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_GetSizeX", reinterpret_cast<void*>(&Component::TransformComponent_GetSizeX));
		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_GetSizeY", reinterpret_cast<void*>(&Component::TransformComponent_GetSizeY));
		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_GetSizeZ", reinterpret_cast<void*>(&Component::TransformComponent_GetSizeZ));

		assembly.AddInternalCall("Crystal.InternalCalls", "TransformComponent_GetRotation", reinterpret_cast<void*>(&Component::TransformComponent_GetRotation));

		// Renderer2DComponent
		/// Setters
		CR_ADD_INTERNAL("Renderer2DComponent_SetTexturePath", &Component::Renderer2DComponent_SetTexturePath);

		CR_ADD_INTERNAL("Renderer2DComponent_SetUseColour", &Component::Renderer2DComponent_SetUseColour);
		CR_ADD_INTERNAL("Renderer2DComponent_SetUseTexture", &Component::Renderer2DComponent_SetUseTexture);

		CR_ADD_INTERNAL("Renderer2DComponent_SetColourR", &Component::Renderer2DComponent_SetColourR);
		CR_ADD_INTERNAL("Renderer2DComponent_SetColourG", &Component::Renderer2DComponent_SetColourG);
		CR_ADD_INTERNAL("Renderer2DComponent_SetColourB", &Component::Renderer2DComponent_SetColourB);
		CR_ADD_INTERNAL("Renderer2DComponent_SetColourA", &Component::Renderer2DComponent_SetColourA);
		 
		/// Getters
		CR_ADD_INTERNAL("Renderer2DComponent_GetTexturePath", &Component::Renderer2DComponent_GetTexturePath);

		CR_ADD_INTERNAL("Renderer2DComponent_GetUseColour", &Component::Renderer2DComponent_GetUseColour);
		CR_ADD_INTERNAL("Renderer2DComponent_GetUseTexture", &Component::Renderer2DComponent_GetUseTexture);

		CR_ADD_INTERNAL("Renderer2DComponent_GetColourR", &Component::Renderer2DComponent_GetColourR);
		CR_ADD_INTERNAL("Renderer2DComponent_GetColourG", &Component::Renderer2DComponent_GetColourG);
		CR_ADD_INTERNAL("Renderer2DComponent_GetColourB", &Component::Renderer2DComponent_GetColourB);
		CR_ADD_INTERNAL("Renderer2DComponent_GetColourA", &Component::Renderer2DComponent_GetColourA);

		// ScriptComponent
		/// Setters
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_Byte", &Component::ScriptComponent_AddValueField_Byte);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_SByte", &Component::ScriptComponent_AddValueField_SByte);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_Short", &Component::ScriptComponent_AddValueField_Short);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_UShort", &Component::ScriptComponent_AddValueField_UShort);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_Int", &Component::ScriptComponent_AddValueField_Int);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_UInt", &Component::ScriptComponent_AddValueField_UInt);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_Long", &Component::ScriptComponent_AddValueField_Long);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_ULong", &Component::ScriptComponent_AddValueField_ULong);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_Float", &Component::ScriptComponent_AddValueField_Float);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_Double", &Component::ScriptComponent_AddValueField_Double);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_Char", &Component::ScriptComponent_AddValueField_Char);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_Bool", &Component::ScriptComponent_AddValueField_Bool);
		CR_ADD_INTERNAL("ScriptComponent_AddValueField_String", &Component::ScriptComponent_AddValueField_String);

		// CameraComponent2D
		/// Setters
		CR_ADD_INTERNAL("CameraComponent2D_SetPositionX", &Component::CameraComponent2D_SetPositionX);
		CR_ADD_INTERNAL("CameraComponent2D_SetPositionY", &Component::CameraComponent2D_SetPositionY);

		CR_ADD_INTERNAL("CameraComponent2D_SetSizeX", &Component::CameraComponent2D_SetSizeX);
		CR_ADD_INTERNAL("CameraComponent2D_SetSizeY", &Component::CameraComponent2D_SetSizeY);

		CR_ADD_INTERNAL("CameraComponent2D_SetZoom", &Component::CameraComponent2D_SetZoom);
		CR_ADD_INTERNAL("CameraComponent2D_SetRotation", &Component::CameraComponent2D_SetRotation);
		CR_ADD_INTERNAL("CameraComponent2D_SetPrimary", &Component::CameraComponent2D_SetPrimary);

		/// Getters
		CR_ADD_INTERNAL("CameraComponent2D_GetPositionX", &Component::CameraComponent2D_GetPositionX);
		CR_ADD_INTERNAL("CameraComponent2D_GetPositionY", &Component::CameraComponent2D_GetPositionY);

		CR_ADD_INTERNAL("CameraComponent2D_GetSizeX", &Component::CameraComponent2D_GetSizeX);
		CR_ADD_INTERNAL("CameraComponent2D_GetSizeY", &Component::CameraComponent2D_GetSizeY);

		CR_ADD_INTERNAL("CameraComponent2D_GetZoom", &Component::CameraComponent2D_GetZoom);
		CR_ADD_INTERNAL("CameraComponent2D_GetRotation", &Component::CameraComponent2D_GetRotation);
		CR_ADD_INTERNAL("CameraComponent2D_GetPrimary", &Component::CameraComponent2D_GetPrimary);

		// CameraComponent3D
		/// Setters
		CR_ADD_INTERNAL("CameraComponent3D_SetPositionX", &Component::CameraComponent3D_SetPositionX);
		CR_ADD_INTERNAL("CameraComponent3D_SetPositionY", &Component::CameraComponent3D_SetPositionY);
		CR_ADD_INTERNAL("CameraComponent3D_SetPositionZ", &Component::CameraComponent3D_SetPositionZ);

		CR_ADD_INTERNAL("CameraComponent3D_SetSizeX", &Component::CameraComponent3D_SetSizeX);
		CR_ADD_INTERNAL("CameraComponent3D_SetSizeY", &Component::CameraComponent3D_SetSizeY);

		CR_ADD_INTERNAL("CameraComponent3D_SetZoom", &Component::CameraComponent3D_SetZoom);
		CR_ADD_INTERNAL("CameraComponent3D_SetRotation", &Component::CameraComponent3D_SetRotation);
		CR_ADD_INTERNAL("CameraComponent3D_SetPrimary", &Component::CameraComponent3D_SetPrimary);

		CR_ADD_INTERNAL("CameraComponent3D_SetFOV", &Component::CameraComponent3D_SetFOV);
		CR_ADD_INTERNAL("CameraComponent3D_SetYaw", &Component::CameraComponent3D_SetYaw);
		CR_ADD_INTERNAL("CameraComponent3D_SetPitch", &Component::CameraComponent3D_SetPitch);

		/// Getters
		CR_ADD_INTERNAL("CameraComponent3D_GetPositionX", &Component::CameraComponent3D_GetPositionX);
		CR_ADD_INTERNAL("CameraComponent3D_GetPositionY", &Component::CameraComponent3D_GetPositionY);
		CR_ADD_INTERNAL("CameraComponent3D_GetPositionZ", &Component::CameraComponent3D_GetPositionZ);

		CR_ADD_INTERNAL("CameraComponent3D_GetSizeX", &Component::CameraComponent3D_GetSizeX);
		CR_ADD_INTERNAL("CameraComponent3D_GetSizeY", &Component::CameraComponent3D_GetSizeY);

		CR_ADD_INTERNAL("CameraComponent3D_GetZoom", &Component::CameraComponent3D_GetZoom);
		CR_ADD_INTERNAL("CameraComponent3D_GetRotation", &Component::CameraComponent3D_GetRotation);
		CR_ADD_INTERNAL("CameraComponent3D_GetPrimary", &Component::CameraComponent3D_GetPrimary);

		CR_ADD_INTERNAL("CameraComponent3D_GetFOV", &Component::CameraComponent3D_GetFOV);
		CR_ADD_INTERNAL("CameraComponent3D_GetYaw", &Component::CameraComponent3D_GetYaw);
		CR_ADD_INTERNAL("CameraComponent3D_GetPitch", &Component::CameraComponent3D_GetPitch);

		/// Entity
		CR_ADD_INTERNAL("HasComponent_TagComponent", &Entity::HasComponent_TagComponent);
		CR_ADD_INTERNAL("HasComponent_TransformComponent", &Entity::HasComponent_TransformComponent);
		CR_ADD_INTERNAL("HasComponent_Renderer2DComponent", &Entity::HasComponent_Renderer2DComponent);
		CR_ADD_INTERNAL("HasComponent_ScriptComponent", &Entity::HasComponent_ScriptComponent);
		CR_ADD_INTERNAL("HasComponent_ColliderComponent", &Entity::HasComponent_ColliderComponent);






		assembly.UploadInternalCalls();
	}

}