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


        //Console.WriteLine("Update");
        var mario = Scene.GetEntityByTag<Test>("Mario");
        if (mario.HasComponent<TransformComponent>())
        {
            var tranform = mario.GetComponent<TransformComponent>();

            Vec2<float> position = new Vec2<float>(Window.GetWidth() / 2.0f, Window.GetHeight() / 2.0f);
            
            if (tranform.GetPosition().X < (int)(Window.GetWidth() / 2.0f) - (int)(tranform.GetSize().X / 2.0f))
            {
                SetPosition(new Vec2<float>(Window.GetWidth() / 2.0f, Window.GetHeight() / 2.0f));

            }
            else
            {
                position.X += tranform.GetPosition().X - (int)(Window.GetWidth() / 2.0f - tranform.GetSize().X / 2.0f); //- tranform.GetSize().X / 2.0f;

                SetPosition(position);
            }
        }

        SetSize(new Vec2<float>((float)Window.GetWidth(), (float)Window.GetHeight()));
    }
}