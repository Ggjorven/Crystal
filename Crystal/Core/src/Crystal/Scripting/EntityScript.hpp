#pragma once

#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/UUID.hpp"

#include <Coral/HostInstance.hpp>
#include <Coral/GC.hpp>
#include <Coral/NativeArray.hpp>
#include <Coral/Attribute.hpp>

#include <string>
#include <vector>
#include <utility>
#include <filesystem>

namespace Crystal
{

	struct ComponentList
	{
	public:
		bool TagComponent = false;
		bool TransformComponent = false;

	public:
		ComponentList() = default;
	};

	struct ValueFieldList
	{
	public:
		std::vector<std::pair<std::string, uint8_t>> Bytes;
		std::vector<std::pair<std::string, int8_t>> SBytes;
		std::vector<std::pair<std::string, int16_t>> Shorts;
		std::vector<std::pair<std::string, uint16_t>> UShorts;
		std::vector<std::pair<std::string, int32_t>> Ints;
		std::vector<std::pair<std::string, uint32_t>> UInts;
		std::vector<std::pair<std::string, int64_t>> Longs;
		std::vector<std::pair<std::string, uint64_t>> ULongs;
		std::vector<std::pair<std::string, float>> Floats;
		std::vector<std::pair<std::string, double>> Doubles;
		std::vector<std::pair<std::string, char>> Chars;
		std::vector<std::pair<std::string, bool>> Bools;
		std::vector<std::pair<std::string, std::string>> Strings;

		void Clean() 
		{ 
			Bytes.clear(); SBytes.clear(); Shorts.clear(); UShorts.clear(); Ints.clear(); UInts.clear();
			Longs.clear(); ULongs.clear(); Floats.clear(); Doubles.clear(); Chars.clear(); Bools.clear(); Strings.clear();
		}

	public:
		ValueFieldList() = default;
	};


	class EntityScript
	{
	public:
		EntityScript();
		EntityScript(std::filesystem::path path);
		virtual ~EntityScript();

		void Reload();
		void SetDLL(std::filesystem::path path);
		void SetClass(const std::string& name);
		void SetUUID(CR_UUID uuid) { m_UUID = uuid; }

		template<typename T>
		void AddValueField(const std::string& name, T value);	
		template<>
		void AddValueField<uint8_t>(const std::string& name, uint8_t byteValue);
		template<>
		void AddValueField<int8_t>(const std::string& name, int8_t sbyteValue);
		template<>
		void AddValueField<int16_t>(const std::string& name, int16_t shortVar);
		template<>
		void AddValueField<uint16_t>(const std::string& name, uint16_t ushortVar);
		template<>
		void AddValueField<int32_t>(const std::string& name, int32_t intVar);
		template<>
		void AddValueField<uint32_t>(const std::string& name, uint32_t uintVar);
		template<>
		void AddValueField<int64_t>(const std::string& name, int64_t longVar);
		template<>
		void AddValueField<uint64_t>(const std::string& name, uint64_t ulongVar);
		template<>
		void AddValueField<float>(const std::string& name, float floatValue);
		template<>
		void AddValueField<double>(const std::string& name, double doubleValue);
		template<>
		void AddValueField<char>(const std::string& name, char charValue);
		template<>
		void AddValueField<bool>(const std::string& name, bool boolValue);
		template<>
		void AddValueField<Coral::NativeString>(const std::string& name, Coral::NativeString stringVar);

		void UpdateValueFieldsValues();
		void DisplayValueFields();

		void OnCreate();
		void OnUpdate(Timestep& ts);
		// TODO(Jorben): Extra functionality (ex. Collision)

		std::string& GetClass() { return m_Name; }

		//Components
		void AddTagComponent() { m_Components.TagComponent = true; }
		void AddTransformComponent() { m_Components.TransformComponent = true; }

	private:
		void Load(std::filesystem::path path);
		void LoadClass();

	private:
		std::filesystem::path m_Path;
		std::string m_Name;

		CR_UUID m_UUID = 0;

		bool m_ContextInitialized = false;
		Coral::AssemblyLoadContext m_Context;
		Coral::ManagedAssembly m_Assembly;

		Coral::Type m_Type;
		Coral::ManagedObject m_Object;

		ComponentList m_Components;
		ValueFieldList m_ValueFields;
	};

	template<typename T>
	inline void EntityScript::AddValueField(const std::string& name, T value)
	{
		CR_CORE_ERROR("Value field passed in is not recognized.");
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, uint8_t byteValue)
	{
		m_ValueFields.Bytes.push_back(std::make_pair(name, byteValue));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, int8_t sbyteValue)
	{
		m_ValueFields.SBytes.push_back(std::make_pair(name, sbyteValue));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, int16_t shortVar)
	{
		m_ValueFields.Shorts.push_back(std::make_pair(name, shortVar));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, uint16_t ushortVar)
	{
		m_ValueFields.UShorts.push_back(std::make_pair(name, ushortVar));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, int32_t intVar)
	{
		m_ValueFields.Ints.push_back(std::make_pair(name, intVar));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, uint32_t uintVar)
	{
		m_ValueFields.UInts.push_back(std::make_pair(name, uintVar));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, int64_t longVar)
	{
		m_ValueFields.Longs.push_back(std::make_pair(name, longVar));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, uint64_t ulongVar)
	{
		m_ValueFields.ULongs.push_back(std::make_pair(name, ulongVar));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, float floatValue)
	{
		m_ValueFields.Floats.push_back(std::make_pair(name, floatValue));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, double doubleValue)
	{
		m_ValueFields.Doubles.push_back(std::make_pair(name, doubleValue));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, char charValue)
	{
		m_ValueFields.Chars.push_back(std::make_pair(name, charValue));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, bool boolValue)
	{
		m_ValueFields.Bools.push_back(std::make_pair(name, boolValue));
	}

	template<>
	inline void EntityScript::AddValueField(const std::string& name, Coral::NativeString stringVar)
	{
		m_ValueFields.Strings.push_back(std::make_pair(name, std::string(stringVar)));
	}

}