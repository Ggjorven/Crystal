#include "crpch.h"
#include "Storage.hpp"

namespace Crystal::ECS
{

	//std::unordered_map<Component::Type, std::unordered_map<CR_UUID, Component>> Storage::s_Components;

	std::unordered_map<CR_UUID, TransformComponent> Storage::s_TransformComponents;


}