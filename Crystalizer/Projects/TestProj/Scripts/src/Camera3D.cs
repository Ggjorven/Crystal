using System;
using Crystal;

public class NewCam : PerspectiveCamera
{
    [ValueField]
    public float X = 0.0f;

    public override void OnCreate()
    {
        SetPosition(new Vec3<float>(0.0f, 0.0f, 0.0f));
    }

    public override void OnUpdate(float deltaTime)
    {
        if (deltaTime > 0.1f)
            deltaTime = 0.1f;

        var pos = GetPosition();
        //SetPosition(new Vec3<float>(pos.X, pos.Y, pos.Z + deltaTime * deltaTime)); ;

        SetYaw(GetYaw() + 10.0f * deltaTime);

        SetSize(new Vec2<float>((float)Window.GetWidth(), (float)Window.GetHeight()));
    }
}