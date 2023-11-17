#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/UUID.hpp"

#include <Coral/HostInstance.hpp>
#include <Coral/GC.hpp>
#include <Coral/NativeArray.hpp>
#include <Coral/Attribute.hpp>

#include <filesystem>

namespace Crystal
{
	namespace ECS
	{
		struct TagComponent;
	}

	struct ComponentQueue
	{
	public:
		bool TagComponent = false;
		bool TransformComponent = false;

	public:
		ComponentQueue() = default;
	};

	class EntityScript
	{
	public:
		EntityScript();
		EntityScript(std::filesystem::path path);
		virtual ~EntityScript();

		void SetDLL(std::filesystem::path path);
		void SetClass(const std::string& name);
		void SetUUID(CR_UUID uuid) { m_UUID = uuid; }

		void OnCreate();
		void OnUpdate(Timestep& ts);
		// TODO(Jorben): Extra functionality (ex. Collision)

		std::string& GetClass() { return m_Name; }

		//Components
		void AddTagComponent();
		void AddTransformComponent();

	private:
		void Load(std::filesystem::path path);
		void LoadClass();

	private:
		std::filesystem::path m_Path;
		std::string m_Name;

		CR_UUID m_UUID = 0;
		bool m_Set = false;

		bool m_ContextInitialized = false;
		Coral::AssemblyLoadContext m_Context;
		Coral::ManagedAssembly m_Assembly;

		Coral::Type m_Type;
		Coral::ManagedObject m_Object;

		ComponentQueue m_Queue;
		// TODO(Jorben): Add ValueField vector for C#
	};

}