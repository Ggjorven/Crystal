#include "Baselayer.hpp"

Baselayer* Baselayer::s_Instance = nullptr;

ImVec2 Baselayer::s_WindowMin = ImVec2(0.0f, 0.0f);
ImVec2 Baselayer::s_WindowMax = ImVec2(0.0f, 0.0f); //To be set in some Init function