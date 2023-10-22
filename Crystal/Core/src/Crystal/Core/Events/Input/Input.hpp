#pragma once

#include "Crystal/Core/Core.hpp"

#include <string>

namespace Crystal
{

	struct MousePosition
	{
	public:
		float X, Y;

		MousePosition(float x = 0.0f, float y = 0.0f)
			: X(x), Y(x)
		{
		}

		std::string ToString()
		{
			return "X position: " + std::to_string(X) + ", Y position: " + std::to_string(Y);
		}
	};



	class Input
	{
	public:
		Input() = default;			//Only to be used by the Engine not the Client
		virtual ~Input() = default;

		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImplementation(keycode); }
		inline static bool IsMousePressed(int button) { return s_Instance->IsMousePressedImplementation(button); }

		inline static MousePosition GetMousePosition() { return s_Instance->GetMousePositionImplementation(); }

	protected:
		//Implementation functions dependent on platform
		virtual bool IsKeyPressedImplementation(int keycode) = 0;
		virtual bool IsMousePressedImplementation(int button) = 0;

		virtual MousePosition GetMousePositionImplementation() = 0;

	private:
		static Scope<Input> s_Instance;
	};

}