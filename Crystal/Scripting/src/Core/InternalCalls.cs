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

        // ScriptComponent
        /// EntityScript
        internal static unsafe delegate*<ulong, byte, void> ScriptComponent_AddValueField_Byte;
        internal static unsafe delegate*<ulong, sbyte, void> ScriptComponent_AddValueField_SByte;
        internal static unsafe delegate*<ulong, short, void> ScriptComponent_AddValueField_Short;
        internal static unsafe delegate*<ulong, ushort, void> ScriptComponent_AddValueField_UShort;
        internal static unsafe delegate*<ulong, int, void> ScriptComponent_AddValueField_Int;
        internal static unsafe delegate*<ulong, uint, void> ScriptComponent_AddValueField_UInt;
        internal static unsafe delegate*<ulong, long, void> ScriptComponent_AddValueField_Long;
        internal static unsafe delegate*<ulong, ulong, void> ScriptComponent_AddValueField_ULong;
        internal static unsafe delegate*<ulong, float, void> ScriptComponent_AddValueField_Float;
        internal static unsafe delegate*<ulong, double, void> ScriptComponent_AddValueField_Double;
        internal static unsafe delegate*<ulong, char, void> ScriptComponent_AddValueField_Char;
        internal static unsafe delegate*<ulong, bool, void> ScriptComponent_AddValueField_Bool;
        internal static unsafe delegate*<ulong, string, void> ScriptComponent_AddValueField_String;
    }
}