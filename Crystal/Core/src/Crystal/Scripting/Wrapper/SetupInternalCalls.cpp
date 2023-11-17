#include "crpch.h"
#include "SetupInternalCalls.hpp"

#include "Crystal/Core/Events/Input/Input.hpp"

#include "Crystal/Scripting/Wrapper/ECS/Entity.hpp"
#include "Crystal/Scripting/Wrapper/ECS/Component.hpp"

#define CR_ADD_INTERNAL(name, functionPtr) \
    assembly.AddInternalCall("Crystal.InternalCalls", name, reinterpret_cast<void*>(functionPtr))


namespace Crystal::Wrapper
{

	void Setup::Run(Coral::ManagedAssembly& assembly) // TODO(Jorben): Replace everything with CR_ADD_INTERNAL(...)
	{
		// ---Core---
		CR_ADD_INTERNAL("Input_IsKeyPressed", &Input::IsKeyPressed);

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

		assembly.UploadInternalCalls();
	}

}