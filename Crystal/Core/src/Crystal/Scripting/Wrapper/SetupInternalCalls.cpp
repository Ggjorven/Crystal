#include "crpch.h"
#include "SetupInternalCalls.hpp"

#include "Crystal/Scripting/Wrapper/ECS/Entity.hpp"
#include "Crystal/Scripting/Wrapper/ECS/Component.hpp"

namespace Crystal::Wrapper
{

	void Setup::Run(Coral::ManagedAssembly& assembly)
	{
		// TagComponent
		assembly.AddInternalCall("Crystal.InternalCalls", "AddTagComponent", reinterpret_cast<void*>(&Entity::AddTagComponent));
		/// Setters
		assembly.AddInternalCall("Crystal.InternalCalls", "TagComponent_SetTag", reinterpret_cast<void*>(&Component::TagComponent_SetTag));
		/// Getters
		assembly.AddInternalCall("Crystal.InternalCalls", "TagComponent_GetTag", reinterpret_cast<void*>(&Component::TagComponent_GetTag));

		// TransformComponent
		//assembly.AddInternalCall("Crystal.InternalCalls", "AddTransformComponent", reinterpret_cast<void*>(&Entity::AddTransformComponent)); // TODO
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

		assembly.UploadInternalCalls();
	}

}