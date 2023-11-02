#pragma once

#include "Crystal/Core/Core.hpp"

#include <filesystem>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/class.h>
#include <mono/metadata/debug-helpers.h>

namespace Crystal
{

	class EntityScript
	{
	public:
		EntityScript() = default;
		EntityScript(std::filesystem::path path);
		virtual ~EntityScript();

		void SetDLL(std::filesystem::path path);
		void SetClass(const std::string& name);

		void OnCreate();
		void OnUpdate(Timestep& ts);
		// TODO(Jorben): Extra functionality (ex. Collision)

	private:
        MonoAssembly* m_Assembly = nullptr;
        MonoImage* m_Image = nullptr;

        MonoClass* m_Class = nullptr;
        MonoObject* m_EntityObject = nullptr;

		MonoMethod* m_OnCreateMethod = nullptr;
		MonoMethod* m_OnUpdateMethod = nullptr;
	};

}