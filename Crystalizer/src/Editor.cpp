#include "Editor.hpp"

EditorLayer* EditorLayer::s_Instance = nullptr;

ImVec2 EditorLayer::s_WindowMin = ImVec2(0.0f, 0.0f);
ImVec2 EditorLayer::s_WindowMax = ImVec2(0.0f, 0.0f); //To be set in some Init function