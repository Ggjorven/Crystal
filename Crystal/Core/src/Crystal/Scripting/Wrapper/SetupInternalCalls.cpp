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

		assembly.AddInternalCall("Crystal.InternalCalls", "TagComponent_GetTag", reinterpret_cast<void*>(&Component::TagComponent_GetTag));
		assembly.AddInternalCall("Crystal.InternalCalls", "TagComponent_SetTag", reinterpret_cast<void*>(&Component::TagComponent_SetTag));

		// TransformComponent

		assembly.UploadInternalCalls();
	}

}