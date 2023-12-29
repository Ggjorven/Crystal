#include "crpch.h"
#include "WindowsInput.hpp"


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Crystal/Core/Application.hpp"

namespace Crystal
{
    Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();



    bool WindowsInput::IsKeyPressedImplementation(int keycode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        int state = glfwGetKey(window, keycode);

        // Note(Jorben): This is needed for some reason to stop false triggers?
        if ((state == GLFW_PRESS || state == GLFW_REPEAT))
        {
            std::stringstream ss;
			ss << "KeyPressedEvent: " << keycode << " (" << state << ")";
            std::string str = ss.str();
        }

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMousePressedImplementation(int button)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    MousePosition WindowsInput::GetMousePositionImplementation()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { xPos, yPos };
    }

    void WindowsInput::SetCursorPositionImplementation(MousePosition position)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        glfwSetCursorPos(window, position.X, position.Y);
    }

    void WindowsInput::SetCursorModeImplementation(int mode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        glfwSetInputMode(window, GLFW_CURSOR, mode);
    }

}
