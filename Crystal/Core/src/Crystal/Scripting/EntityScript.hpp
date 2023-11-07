#pragma once

#include "Crystal/Core/Core.hpp"

#include <Coral/HostInstance.hpp>
#include <Coral/GC.hpp>
#include <Coral/NativeArray.hpp>
#include <Coral/Attribute.hpp>

#include <filesystem>

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

		std::string& GetClass() { return m_Name; }

	private:
		void Load(std::filesystem::path path);

	private:
		std::string m_Name;
		bool m_Set = false;

		bool m_ContextInitialized = false;
		Coral::AssemblyLoadContext m_Context;
		Coral::ManagedAssembly m_Assembly;

		Coral::Type m_Type;
		Coral::ManagedObject m_Object;
	};

}