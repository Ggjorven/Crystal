#pragma once

//API folder
	//OpenGL
	#include "Crystal/APIs/OpenGL/OpenGLBuffer.hpp"
	#include "Crystal/APIs/OpenGL/OpenGLContext.hpp"
	#include "Crystal/APIs/OpenGL/OpenGLRenderingAPI.hpp"
	#include "Crystal/APIs/OpenGL/OpenGLShader.hpp"
	#include "Crystal/APIs/OpenGL/OpenGLTexture.hpp"
	#include "Crystal/APIs/OpenGL/OpenGLVertexArray.hpp"

	//Vulkan
	#include "Crystal/APIs/Vulkan/VulkanContext.hpp"

//Core folder
#include "Crystal/Core/Application.hpp"
#include "Crystal/Core/Core.hpp"
#include "Crystal/Core/Layer.hpp"
#include "Crystal/Core/LayerStack.hpp"
#include "Crystal/Core/Window.hpp"

//Event folder
	//Codes
	#include "Crystal/Events/Codes/KeyCodes.hpp"
	#include "Crystal/Events/Codes/MouseCodes.hpp"

	//Input
	#include "Crystal/Events/Input/Input.hpp"

#include "Crystal/Events/ApplicationEvent.hpp"
#include "Crystal/Events/Event.hpp"
#include "Crystal/Events/KeyEvent.hpp"
#include "Crystal/Events/MouseEvent.hpp"

//ImGui folder
#include "Crystal/ImGui/BaseImGuiLayer.hpp"

//Platforms
	//Windows
	#include "Crystal/Platforms/Windows/WindowsInput.hpp"
	#include "Crystal/Platforms/Windows/WindowsWindow.hpp"

//Renderer folder
#include "Crystal/Renderer/Buffer.hpp"
#include "Crystal/Renderer/GraphicsContext.hpp"
#include "Crystal/Renderer/OrthoGraphicCamera.hpp"
#include "Crystal/Renderer/OrthoGraphicCameraController.hpp"
#include "Crystal/Renderer/Renderer.hpp"
#include "Crystal/Renderer/Renderer2D.hpp"
#include "Crystal/Renderer/RendererCommand.hpp"
#include "Crystal/Renderer/RenderingAPI.hpp"
#include "Crystal/Renderer/Shader.hpp"
#include "Crystal/Renderer/Texture.hpp"
#include "Crystal/Renderer/VertexArray.hpp"