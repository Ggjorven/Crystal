using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Crystal
{

    unsafe public class InternalCalls
    {
        // ---Core---
        internal static unsafe delegate*<int, bool> Input_IsKeyPressed;

        internal static unsafe delegate*<uint> Window_GetWindowWidth;
        internal static unsafe delegate*<uint> Window_GetWindowHeight;

        // ---Scene---
        internal static unsafe delegate*<NativeString, ulong> GetUUIDByTag;
        internal static unsafe delegate*<NativeString, void> SetSceneByName;
        
        // ---ECS---
        // TagComponent
        internal static unsafe delegate*<ulong, NativeString, void> AddTagComponent;

        internal static unsafe delegate*<ulong, NativeString, void> TagComponent_SetTag;
        internal static unsafe delegate*<ulong, NativeString> TagComponent_GetTag;

        // TransformComponent
        internal static unsafe delegate*<ulong, void> AddTransformComponent;

        internal static unsafe delegate*<ulong, float, void> TransformComponent_SetPositionX;
        internal static unsafe delegate*<ulong, float, void> TransformComponent_SetPositionY;
        internal static unsafe delegate*<ulong, float, void> TransformComponent_SetPositionZ;
        internal static unsafe delegate*<ulong, float, void> TransformComponent_SetSizeX;
        internal static unsafe delegate*<ulong, float, void> TransformComponent_SetSizeY;
        internal static unsafe delegate*<ulong, float, void> TransformComponent_SetSizeZ;
        internal static unsafe delegate*<ulong, float, void> TransformComponent_SetRotation;

        internal static unsafe delegate*<ulong, float> TransformComponent_GetPositionX;
        internal static unsafe delegate*<ulong, float> TransformComponent_GetPositionY;
        internal static unsafe delegate*<ulong, float> TransformComponent_GetPositionZ;
        internal static unsafe delegate*<ulong, float> TransformComponent_GetSizeX;
        internal static unsafe delegate*<ulong, float> TransformComponent_GetSizeY;
        internal static unsafe delegate*<ulong, float> TransformComponent_GetSizeZ;
        internal static unsafe delegate*<ulong, float> TransformComponent_GetRotation;

        // Renderer2DComponent
        internal static unsafe delegate*<ulong, NativeString, void> Renderer2DComponent_SetTexturePath;

        internal static unsafe delegate*<ulong, bool, void> Renderer2DComponent_SetUseColour;
        internal static unsafe delegate*<ulong, bool, void> Renderer2DComponent_SetUseTexture;

        internal static unsafe delegate*<ulong, float, void> Renderer2DComponent_SetColourR;
        internal static unsafe delegate*<ulong, float, void> Renderer2DComponent_SetColourG;
        internal static unsafe delegate*<ulong, float, void> Renderer2DComponent_SetColourB;
        internal static unsafe delegate*<ulong, float, void> Renderer2DComponent_SetColourA;

        internal static unsafe delegate*<ulong, NativeString> Renderer2DComponent_GetTexturePath;

        internal static unsafe delegate*<ulong, bool> Renderer2DComponent_GetUseColour;
        internal static unsafe delegate*<ulong, bool> Renderer2DComponent_GetUseTexture;

        internal static unsafe delegate*<ulong, float> Renderer2DComponent_GetColourR;
        internal static unsafe delegate*<ulong, float> Renderer2DComponent_GetColourG;
        internal static unsafe delegate*<ulong, float> Renderer2DComponent_GetColourB;
        internal static unsafe delegate*<ulong, float> Renderer2DComponent_GetColourA;

        // ScriptComponent
        internal static unsafe delegate*<ulong, NativeString, byte, void> ScriptComponent_AddValueField_Byte;
        internal static unsafe delegate*<ulong, NativeString, sbyte, void> ScriptComponent_AddValueField_SByte;
        internal static unsafe delegate*<ulong, NativeString, short, void> ScriptComponent_AddValueField_Short;
        internal static unsafe delegate*<ulong, NativeString, ushort, void> ScriptComponent_AddValueField_UShort;
        internal static unsafe delegate*<ulong, NativeString, int, void> ScriptComponent_AddValueField_Int;
        internal static unsafe delegate*<ulong, NativeString, uint, void> ScriptComponent_AddValueField_UInt;
        internal static unsafe delegate*<ulong, NativeString, long, void> ScriptComponent_AddValueField_Long;
        internal static unsafe delegate*<ulong, NativeString, ulong, void> ScriptComponent_AddValueField_ULong;
        internal static unsafe delegate*<ulong, NativeString, float, void> ScriptComponent_AddValueField_Float;
        internal static unsafe delegate*<ulong, NativeString, double, void> ScriptComponent_AddValueField_Double;
        internal static unsafe delegate*<ulong, NativeString, char, void> ScriptComponent_AddValueField_Char;
        internal static unsafe delegate*<ulong, NativeString, bool, void> ScriptComponent_AddValueField_Bool;
        internal static unsafe delegate*<ulong, NativeString, NativeString, void> ScriptComponent_AddValueField_String;

        // CameraComponent2D
        internal static unsafe delegate*<ulong, float, void> CameraComponent2D_SetPositionX;
        internal static unsafe delegate*<ulong, float, void> CameraComponent2D_SetPositionY;

        internal static unsafe delegate*<ulong, float, void> CameraComponent2D_SetSizeX;
        internal static unsafe delegate*<ulong, float, void> CameraComponent2D_SetSizeY;

        internal static unsafe delegate*<ulong, float, void> CameraComponent2D_SetZoom;
        internal static unsafe delegate*<ulong, float, void> CameraComponent2D_SetRotation;
        internal static unsafe delegate*<ulong, bool, void> CameraComponent2D_SetPrimary;

        internal static unsafe delegate*<ulong, float> CameraComponent2D_GetPositionX;
        internal static unsafe delegate*<ulong, float> CameraComponent2D_GetPositionY;

        internal static unsafe delegate*<ulong, float> CameraComponent2D_GetSizeX;
        internal static unsafe delegate*<ulong, float> CameraComponent2D_GetSizeY;

        internal static unsafe delegate*<ulong, float> CameraComponent2D_GetZoom;
        internal static unsafe delegate*<ulong, float> CameraComponent2D_GetRotation;
        internal static unsafe delegate*<ulong, bool> CameraComponent2D_GetPrimary;

        // CameraComponent3D
        internal static unsafe delegate*<ulong, float, void> CameraComponent3D_SetPositionX;
        internal static unsafe delegate*<ulong, float, void> CameraComponent3D_SetPositionY;
        internal static unsafe delegate*<ulong, float, void> CameraComponent3D_SetPositionZ;

        internal static unsafe delegate*<ulong, float, void> CameraComponent3D_SetSizeX;
        internal static unsafe delegate*<ulong, float, void> CameraComponent3D_SetSizeY;

        internal static unsafe delegate*<ulong, float, void> CameraComponent3D_SetZoom;
        internal static unsafe delegate*<ulong, float, void> CameraComponent3D_SetRotation;
        internal static unsafe delegate*<ulong, bool, void> CameraComponent3D_SetPrimary;

        internal static unsafe delegate*<ulong, float, void> CameraComponent3D_SetFOV;
        internal static unsafe delegate*<ulong, float, void> CameraComponent3D_SetYaw;
        internal static unsafe delegate*<ulong, float, void> CameraComponent3D_SetPitch;

        internal static unsafe delegate*<ulong, float> CameraComponent3D_GetPositionX;
        internal static unsafe delegate*<ulong, float> CameraComponent3D_GetPositionY;
        internal static unsafe delegate*<ulong, float> CameraComponent3D_GetPositionZ;

        internal static unsafe delegate*<ulong, float> CameraComponent3D_GetSizeX;
        internal static unsafe delegate*<ulong, float> CameraComponent3D_GetSizeY;

        internal static unsafe delegate*<ulong, float> CameraComponent3D_GetZoom;
        internal static unsafe delegate*<ulong, float> CameraComponent3D_GetRotation;
        internal static unsafe delegate*<ulong, bool> CameraComponent3D_GetPrimary;

        internal static unsafe delegate*<ulong, float> CameraComponent3D_GetFOV;
        internal static unsafe delegate*<ulong, float> CameraComponent3D_GetYaw;
        internal static unsafe delegate*<ulong, float> CameraComponent3D_GetPitch;

        /// Entity functions
        internal static unsafe delegate*<ulong, bool> HasComponent_TagComponent;
        internal static unsafe delegate*<ulong, bool> HasComponent_TransformComponent;
        internal static unsafe delegate*<ulong, bool> HasComponent_Renderer2DComponent;
        internal static unsafe delegate*<ulong, bool> HasComponent_ScriptComponent;
        internal static unsafe delegate*<ulong, bool> HasComponent_ColliderComponent;
    }
}