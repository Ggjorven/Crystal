using System;
using Crystal;

public class MarioCamera : OrthoGraphicCamera
{
    public override void OnCreate()
    {
        SetPosition(new Vec2<float>(Window.GetWidth() / 2.0f, Window.GetHeight() / 2.0f));
    }

    public override void OnUpdate(float deltaTime)
    {
        if (deltaTime > 0.1f)
            deltaTime = 0.1f;

        SetSize(new Vec2<float>((float)Window.GetWidth(), (float)Window.GetHeight()));
        SetPosition(new Vec2<float>(GetPosition().X + (deltaTime * 10.0f), GetPosition().Y));
    }
}