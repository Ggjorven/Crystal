VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/vendor/stb_image/include"
IncludeDir["GLFW"] = "%{wks.location}/vendor/GLFW/include"
IncludeDir["GLEW"] = "%{wks.location}/vendor/GLEW/include"
IncludeDir["ImGui"] = "%{wks.location}/vendor/ImGui"
IncludeDir["spdlog"] = "%{wks.location}/vendor/spdlog/include"
IncludeDir["glm"] = "%{wks.location}/vendor/glm"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"
