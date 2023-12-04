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
        public ulong ID;
        protected Component(ulong entityID) { ID = entityID; }
    }

    public class TagComponent : Component
    {
        public TagComponent() : base(0) { }
        public TagComponent(ulong entityID) : base(entityID) { }

        unsafe public string Tag
        {
            get => InternalCalls.TagComponent_GetTag(ID)!;
            set => InternalCalls.TagComponent_SetTag(ID, value);
        }
    }

    public class TransformComponent : Component
    {
        public TransformComponent() : base(0) { }

        public TransformComponent(ulong entityID) : base(entityID) { }

        // Provides a copy of the position
        unsafe public Vec3<float> GetPosition()
        {
            Vec3<float> pos = new Vec3<float>(0.0f, 0.0f, 0.0f);
            pos.X = InternalCalls.TransformComponent_GetPositionX(ID);
            pos.Y = InternalCalls.TransformComponent_GetPositionY(ID);
            pos.Z = InternalCalls.TransformComponent_GetPositionZ(ID);

            return pos;
        }
        unsafe public void SetPosition(Vec3<float> position)
        {
            InternalCalls.TransformComponent_SetPositionX(ID, position.X);
            InternalCalls.TransformComponent_SetPositionY(ID, position.Y);
            InternalCalls.TransformComponent_SetPositionZ(ID, position.Z);
        }

        // Provides a copy of the size
        unsafe public Vec3<float> GetSize()
        {
            Vec3<float> pos = new Vec3<float>(0.0f, 0.0f, 0.0f);
            pos.X = InternalCalls.TransformComponent_GetSizeX(ID);
            pos.Y = InternalCalls.TransformComponent_GetSizeY(ID);
            pos.Z = InternalCalls.TransformComponent_GetSizeZ(ID);

            return pos;
        }
        unsafe void SetSize(Vec3<float> size)
        {
            InternalCalls.TransformComponent_SetSizeX(ID, size.X);
            InternalCalls.TransformComponent_SetSizeY(ID, size.Y);
            InternalCalls.TransformComponent_SetSizeZ(ID, size.Z);
        }

        // Provides a copy of the rotation
        unsafe public float GetRotation()
        {
            return InternalCalls.TransformComponent_GetRotation(ID);
        }
        unsafe public void SetRotation(float rotation)
        {
            InternalCalls.TransformComponent_SetRotation(ID, rotation);
        }
    }

    public class Renderer2DComponent : Component
    {
        public Renderer2DComponent() : base(0) { }
        public Renderer2DComponent(ulong entityID) : base(entityID) { }

        unsafe public Texture2D GetTexture()
        {
            Texture2D texture = new Texture2D("");
            texture.Path = InternalCalls.Renderer2DComponent_GetTexturePath(ID)!;

            return texture;
        }
        unsafe public void SetTexture(Texture2D texture)
        {
            InternalCalls.Renderer2DComponent_SetTexturePath(ID, texture.Path);
        }

        unsafe public bool GetUseTexture()
        {
            return InternalCalls.Renderer2DComponent_GetUseTexture(ID);
        }
        unsafe public void SetUseTexture(bool enabled)
        {
            InternalCalls.Renderer2DComponent_SetUseTexture(ID, enabled);
        }

        unsafe public bool GetUseColour()
        {
            return InternalCalls.Renderer2DComponent_GetUseColour(ID);
        }
        unsafe public void SetUseColour(bool enabled)
        {
            InternalCalls.Renderer2DComponent_SetUseColour(ID, enabled);
        }

        unsafe public Vec4<float> GetColour()
        {
            Vec4<float> colour = new Vec4<float>(0.0f, 0.0f, 0.0f, 0.0f);
            colour.R = InternalCalls.Renderer2DComponent_GetColourR(ID);
            colour.G = InternalCalls.Renderer2DComponent_GetColourG(ID);
            colour.B = InternalCalls.Renderer2DComponent_GetColourB(ID);
            colour.A = InternalCalls.Renderer2DComponent_GetColourA(ID);

            return colour;
        }
        unsafe public void SetColour(Vec4<float> colour)
        {
            InternalCalls.Renderer2DComponent_SetColourR(ID, colour.R);
            InternalCalls.Renderer2DComponent_SetColourG(ID, colour.G);
            InternalCalls.Renderer2DComponent_SetColourB(ID, colour.B);
            InternalCalls.Renderer2DComponent_SetColourA(ID, colour.A);
        }
    }

    public class ColliderComponent : Component
    {
        public ColliderComponent() : base(0) { }
        public ColliderComponent(ulong entityID) : base(entityID) { }

        // TODO
    }
}