#pragma once

#include "Crystal/Core/Core.hpp"

#include <string>

namespace Crystal
{

	struct MousePosition
	{
	public:
		double X, Y;

		MousePosition(double x = 0.0f, double y = 0.0f)
			: X(x), Y(y)
		{
		}

		std::string ToString()
		{
			return "X position: " + std::to_string(X) + ", Y position: " + std::to_string(Y);
		}
	};

	#define CR_CURSOR_SHOWN				0x00034001
	#define CR_CURSOR_HIDDEN			0x00034002
	#define CR_CURSOR_DISABLED			0x00034003
	#define CR_CURSOR_CAPTURED			0x00034004

	class Input
	{
	public:
		Input() = default;			//Only to be used by the Engine not the Client
		virtual ~Input() = default;

		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImplementation(keycode); }
		inline static bool IsMousePressed(int button) { return s_Instance->IsMousePressedImplementation(button); }

		inline static MousePosition GetMousePosition() { return s_Instance->GetMousePositionImplementation(); }

		inline static void SetCursorPosition(MousePosition position) { s_Instance->SetCursorPositionImplementation(position); }
		inline static void SetCursorMode(int mode) { s_Instance->SetCursorModeImplementation(mode); }

	protected:
		//Implementation functions dependent on platform
		virtual bool IsKeyPressedImplementation(int keycode) = 0;
		virtual bool IsMousePressedImplementation(int button) = 0;

		virtual MousePosition GetMousePositionImplementation() = 0;

		virtual void SetCursorPositionImplementation(MousePosition position) = 0;
		virtual void SetCursorModeImplementation(int mode) = 0;

	private:
		static Scope<Input> s_Instance;
	};

}