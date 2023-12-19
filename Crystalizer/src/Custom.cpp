#include "Custom.hpp"

#include <GL/glew.h>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

CustomLayer::CustomLayer(const ApplicationInfo& appinfo)
{
}

CustomLayer::~CustomLayer()
{
}

void CustomLayer::OnAttach()
{
    // Define texture data (e.g., a checkerboard pattern)
    const int textureWidth = 512;
    const int textureHeight = 512;

    Ref<Texture2D> texture = Texture2D::Create(textureWidth, textureHeight);
    texture->Bind(0);

    // Example data creation
    std::vector<glm::vec4> textureData(512 * 512, glm::vec4(0.5f, 1.0f, 1.0f, 1.0f));  // Adjust based on your data format
    //texture->SetData(textureData.data(), sizeof(float) * textureData.size());

    // Define compute shader source code
    std::string computeShaderSource = R"(
    #version 430

    layout(set = 0, binding = 0) buffer InputBuffer {
        vec4 inputData[];
    };

    layout(set = 0, binding = 1) buffer OutputBuffer {
        vec4 outputData[];
    };

    layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

    void main() {
        uint index = gl_GlobalInvocationID.x;

        if (index < inputData.length()) {
            // Extract the RGB values from the input
            vec3 color = inputData[index].rgb;

            // Define the thickness of the red line
            float lineThickness = 1000.0;

            // Calculate the distance from the center and compare
            if (abs(int(index) - int(inputData.length()) / 2) < int(lineThickness) / 2) {
                color = vec3(1.0, 0.0, 0.0); // Set the color to red
            }

            color = vec3(1.0, 0.0, 0.0);

            // Output the modified color
            outputData[index] = vec4(color, inputData[index].a);
        }
    }

)";

    // Create and use the compute shader
    Ref<ComputeShader<glm::vec4, glm::vec4>> computeShader = CreateComputeShader<glm::vec4, glm::vec4>(computeShaderSource);
    computeShader->SetGroupSize(1, 1, 1); // Adjust according to your input size
    computeShader->CreateOutputBuffer(textureData.size() * sizeof(glm::vec4));

    // Bind the compute shader
    computeShader->Bind();
    computeShader->SetInputBuffer(textureData);
    computeShader->Dispatch(textureData.size(), 1, 1, sizeof(glm::vec4) * textureData.size());
    std::vector<glm::vec4> results = computeShader->GetResults(); // Assuming each element represents RGBA
    //texture->SetData(results);
    computeShader->UnBind();
}



void CustomLayer::OnDetach()
{
}

void CustomLayer::OnUpdate(Timestep& ts)
{
}

void CustomLayer::OnRender()
{
}

void CustomLayer::OnImGuiRender()
{
}

void CustomLayer::OnEvent(Event& e)
{
}
