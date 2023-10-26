#pragma once

//===================
//-------Core--------
//===================
//API folder
	//OpenGL
	#include "Crystal/APIs/OpenGL/OpenGLBuffer.hpp"
	#include "Crystal/APIs/OpenGL/OpenGLContext.hpp"
	#include "Crystal/APIs/OpenGL/OpenGLFrameBuffer.hpp"
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
	#include "Crystal/Core/Events/ApplicationEvent.hpp"
	#include "Crystal/Core/Events/Event.hpp"
	#include "Crystal/Core/Events/KeyEvent.hpp"
	#include "Crystal/Core/Events/MouseEvent.hpp"

	//Codes
		#include "Crystal/Core/Events/Codes/KeyCodes.hpp"
		#include "Crystal/Core/Events/Codes/MouseCodes.hpp"

	//Input
		#include "Crystal/Core/Events/Input/Input.hpp"

//ImGui folder
#include "Crystal/ImGui/BaseImGuiLayer.hpp"

//Platforms
	//Windows
	#include "Crystal/Platforms/Windows/WindowsInput.hpp"
	#include "Crystal/Platforms/Windows/WindowsUtilities.hpp"
	#include "Crystal/Platforms/Windows/WindowsWindow.hpp"

//Renderer folder
#include "Crystal/Renderer/Buffer.hpp"
#include "Crystal/Renderer/FrameBuffer.hpp"
#include "Crystal/Renderer/GraphicsContext.hpp"
#include "Crystal/Renderer/Renderer.hpp"
#include "Crystal/Renderer/RendererCommand.hpp"
#include "Crystal/Renderer/RenderingAPI.hpp"
#include "Crystal/Renderer/Shader.hpp"
#include "Crystal/Renderer/Texture.hpp"
#include "Crystal/Renderer/VertexArray.hpp"
	//2D
	#include "Crystal/Renderer/2D/OrthoGraphicCamera.hpp"
	#include "Crystal/Renderer/2D/Renderer2D.hpp"

	//3D
	#include "Crystal/Renderer/3D/PerspectiveCamera.hpp"
	#include "Crystal/Renderer/3D/Renderer3D.hpp"

//Utils folder
#include "Crystal/Utils/Utils.hpp"


//===================
//------Physics------
//===================
//ECS
#include "Crystal/ECS/Component.hpp"
#include "Crystal/ECS/Storage.hpp"
#include "Crystal/ECS/Entity.hpp"