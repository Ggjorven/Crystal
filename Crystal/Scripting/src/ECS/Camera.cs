using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Crystal;
using System.Reflection;
using System.Security.Cryptography.X509Certificates;

namespace Crystal
{

    unsafe public class OrthoGraphicCamera : Entity
    {
        public OrthoGraphicCamera(ulong id = 0)
            : base(id) { }

        public void SetPosition(Vec2<float> position)
        {
            InternalCalls.CameraComponent2D_SetPositionX(ID, position.X);
            InternalCalls.CameraComponent2D_SetPositionY(ID, position.Y);
        }

        public Vec2<float> GetPosition()
        {
            Vec2<float> position = new Vec2<float>(0.0f, 0.0f);

            position.X = InternalCalls.CameraComponent2D_GetPositionX(ID);
            position.Y = InternalCalls.CameraComponent2D_GetPositionY(ID);

            return position;
        }

        public void SetSize(Vec2<float> size)
        {
            InternalCalls.CameraComponent2D_SetSizeX(ID, size.X);
            InternalCalls.CameraComponent2D_SetSizeY(ID, size.Y);
        }

        public Vec2<float> GetSize()
        {
            Vec2<float> size = new Vec2<float>(0.0f, 0.0f);

            size.X = InternalCalls.CameraComponent2D_GetSizeX(ID);
            size.Y = InternalCalls.CameraComponent2D_GetSizeY(ID);

            return size;
        }

        public void SetZoom(float zoom)
        {
            InternalCalls.CameraComponent2D_SetZoom(ID, zoom);
        }

        public float GetZoom()
        {
            return InternalCalls.CameraComponent2D_GetZoom(ID);
        }

        public void SetRotation(float rotation)
        {
            InternalCalls.CameraComponent2D_SetRotation(ID, rotation);
        }

        public float GetRotation()
        {
            return InternalCalls.CameraComponent2D_GetRotation(ID);
        }

        public void SetPrimary(bool primary)
        {
            InternalCalls.CameraComponent2D_SetPrimary(ID, primary);
        }

        public bool GetPrimary()
        {
            return InternalCalls.CameraComponent2D_GetPrimary(ID);
        }

    }

    unsafe public class PerspectiveCamera : Entity
    {
        public PerspectiveCamera(ulong id = 0)
            : base(id) { }

        public void SetPosition(Vec3<float> position)
        {
            InternalCalls.CameraComponent3D_SetPositionX(ID, position.X);
            InternalCalls.CameraComponent3D_SetPositionY(ID, position.Y);
            InternalCalls.CameraComponent3D_SetPositionZ(ID, position.Z);
        }

        public Vec3<float> GetPosition()
        {
            Vec3<float> position = new Vec3<float>(0.0f, 0.0f, 0.0f);

            position.X = InternalCalls.CameraComponent3D_GetPositionX(ID);
            position.Y = InternalCalls.CameraComponent3D_GetPositionY(ID);
            position.Z = InternalCalls.CameraComponent3D_GetPositionZ(ID);

            return position;
        }

        public void SetSize(Vec2<float> size)
        {
            InternalCalls.CameraComponent3D_SetSizeX(ID, size.X);
            InternalCalls.CameraComponent3D_SetSizeY(ID, size.Y);
        }

        public Vec2<float> GetSize()
        {
            Vec2<float> size = new Vec2<float>(0.0f, 0.0f);

            size.X = InternalCalls.CameraComponent3D_GetSizeX(ID);
            size.X = InternalCalls.CameraComponent3D_GetSizeY(ID);

            return size;
        }

        public void SetZoom(float zoom)
        {
            InternalCalls.CameraComponent3D_SetZoom(ID, zoom);
        }

        public float GetZoom()
        {
            return InternalCalls.CameraComponent3D_GetZoom(ID);
        }

        public void SetRotation(float rotation)
        {
            InternalCalls.CameraComponent3D_SetRotation(ID, rotation);
        }

        public float GetRotation()
        {
            return InternalCalls.CameraComponent3D_GetRotation(ID);
        }

        public void SetPrimary(bool primary)
        {
            InternalCalls.CameraComponent3D_SetPrimary(ID, primary);
        }

        public bool GetPrimary()
        {
            return InternalCalls.CameraComponent3D_GetPrimary(ID);
        }

        public void SetFOV(float fov)
        {
            InternalCalls.CameraComponent3D_SetFOV(ID, fov);
        }

        public float GetFOV()
        {
            return InternalCalls.CameraComponent3D_GetFOV(ID);
        }

        public void SetYaw(float yaw)
        {
            InternalCalls.CameraComponent3D_SetYaw(ID, yaw);
        }

        public float GetYaw()
        {
            return InternalCalls.CameraComponent3D_GetYaw(ID);
        }

        public void SetPitch(float pitch)
        {
            InternalCalls.CameraComponent3D_SetPitch(ID, pitch);
        }

        public float GetPitch()
        {
            return InternalCalls.CameraComponent3D_GetPitch(ID);
        }

    }
}