using System;
using Crystal;

public class Spider : Entity
{
    public override void OnCreate()
    {

    }

    public override void OnUpdate(float deltaTime)
    {
        if (deltaTime > 0.1f)
            deltaTime = 0.1f;

        if (HasComponent<TransformComponent>())
        {
        }
    }

    public override void OnCollision(Entity other)
    {
        if (HasComponent<TransformComponent>() && other.HasComponent<TransformComponent>())
        {
            var tc = other.GetComponent<TransformComponent>();

            var size = tc.GetSize();
            if (size.Y != 128.0f) 
                size.Y *= 2.0f;

            tc.SetSize(size);
        }

        Scene.SetSceneByName("New");
    }
}