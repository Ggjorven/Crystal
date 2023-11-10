using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Crystal
{

    public class Component
    {
        unsafe public ulong ID;
        unsafe protected Component(ulong entityID) { ID = entityID; }
    }

    public class TagComponent : Component
    {
        public TagComponent() : base(0) { }
        unsafe public TagComponent(ulong entityID) : base(entityID) { }

        unsafe public string Tag
        {
            get => InternalCalls.TagComponent_GetTag(ID);
            set => InternalCalls.TagComponent_SetTag(ID, value);
        }
    }

    public class TransformComponent : Component // TODO(Jorben): Fix, maybe create a transform struct with Vec3's and set the get and sets there
    {
        public TransformComponent() : base(0) { }
        unsafe public TransformComponent(ulong entityID) : base(entityID) { }

        unsafe public float PosX
        {
            get => InternalCalls.TransformComponent_GetPositionX(ID);
            set => InternalCalls.TransformComponent_SetPositionX(ID, value);
        }

        unsafe public float PosY
        {
            get => InternalCalls.TransformComponent_GetPositionY(ID);
            set => InternalCalls.TransformComponent_SetPositionY(ID, value);
        }

        unsafe public float PosZ
        {
            get => InternalCalls.TransformComponent_GetPositionZ(ID);
            set => InternalCalls.TransformComponent_SetPositionZ(ID, value);
        }

        unsafe public float SizeX
        {
            get => InternalCalls.TransformComponent_GetSizeX(ID);
            set => InternalCalls.TransformComponent_SetSizeX(ID, value);
        }

        unsafe public float SizeY
        {
            get => InternalCalls.TransformComponent_GetSizeY(ID);
            set => InternalCalls.TransformComponent_SetSizeY(ID, value);
        }

        unsafe public float SizeZ
        {
            get => InternalCalls.TransformComponent_GetSizeZ(ID);
            set => InternalCalls.TransformComponent_SetSizeZ(ID, value);
        }

        unsafe public float Rotation
        {
            get => InternalCalls.TransformComponent_GetRotation(ID);
            set => InternalCalls.TransformComponent_SetRotation(ID, value);
        }
    }
}