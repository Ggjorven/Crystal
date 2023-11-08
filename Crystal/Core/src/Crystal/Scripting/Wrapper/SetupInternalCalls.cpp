#include "crpch.h"
#include "SetupInternalCalls.hpp"

#include "Crystal/Scripting/Wrapper/ECS/Component.hpp"

namespace Crystal::Wrapper
{

	/*
	assembly.AddInternalCall("Example.Managed.ExampleClass", "VectorAddIcall", reinterpret_cast<void*>(&VectorAddIcall));
	assembly.AddInternalCall("Example.Managed.ExampleClass", "PrintStringIcall", reinterpret_cast<void*>(&PrintStringIcall));
	assembly.AddInternalCall("Example.Managed.ExampleClass", "NativeArrayIcall", reinterpret_cast<void*>(&NativeArrayIcall));
	assembly.AddInternalCall("Example.Managed.ExampleClass", "ArrayReturnIcall", reinterpret_cast<void*>(&ArrayReturnIcall));
	assembly.UploadInternalCalls();
	*/

	void Setup::Run(Coral::ManagedAssembly& assembly)
	{
		// TODO(Jorben): Add internal calls
		assembly.AddInternalCall("Crystal.InternalCalls", "TagComponent_GetTag", reinterpret_cast<void*>(&TagComponent_GetTag));
		assembly.AddInternalCall("Crystal.InternalCalls", "TagComponent_SetTag", reinterpret_cast<void*>(&TagComponent_SetTag));

		assembly.UploadInternalCalls();
	}

}