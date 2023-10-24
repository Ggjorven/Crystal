#pragma once


#include "Crystal/Core/Core.hpp"

#include "Crystal/Core/Events/Input/Input.hpp"

namespace Crystal
{

	class WindowsInput : public Input
	{
	public:
		WindowsInput() = default;
		virtual ~WindowsInput() = default;

		bool IsKeyPressedImplementation(int keycode) override;
		bool IsMousePressedImplementation(int button) override;

		MousePosition GetMousePositionImplementation() override;

		void SetCursorPositionImplementation(MousePosition position) override;
		void SetCursorModeImplementation(int mode) override;
	};

}
