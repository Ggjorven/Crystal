#pragma once

#include <Crystal/Crystal.hpp>

#include <Coral/HostInstance.hpp>
#include <Coral/GC.hpp>
#include <Coral/NativeArray.hpp>
#include <Coral/Attribute.hpp>

using namespace Crystal;

class CoralLayer : public Layer
{
public:
	CoralLayer(ApplicationInfo& info)
		: m_AppInfo(info)
	{
	}
	virtual ~CoralLayer() = default;

	void OnAttach() override
	{
		m_CoralSettings.CoralDirectory = std::string(Utils::GetEnviromentVariable("CRYSTAL_DIR")) + "\\bin\\Debug-windows-x86_64\\Coral\\";
		//m_CoralSettings.ExceptionCallback = ...;

		m_Host.Initialize(m_CoralSettings);

		m_Context = m_Host.CreateAssemblyLoadContext("Crystal");
		std::string path = Utils::GetEnviromentVariable("CRYSTAL_DIR") + std::string("\\bin\\Debug-windows-x86_64\\Coral\\") + std::string("Script.dll");
		m_Assembly = m_Context.LoadAssembly(path);

		m_Type = m_Assembly.GetType("Entity");
		m_Object = m_Type.CreateInstance();

		m_Object.InvokeMethod("OnCreate");
	}

	void OnDetach() override
	{

	}

	void OnUpdate(Timestep& ts)
	{
		m_Object.InvokeMethod("OnUpdate", (float)ts);
	}

	void OnRender()
	{

	}

	void OnEvent(Event& e)
	{

	}

private:
	ApplicationInfo m_AppInfo;

	Coral::HostSettings m_CoralSettings;
	Coral::HostInstance m_Host;

	Coral::AssemblyLoadContext m_Context;
	Coral::ManagedAssembly m_Assembly;

	Coral::Type m_Type;
	Coral::ManagedObject m_Object;
};
