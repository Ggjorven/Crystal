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
    }

}