using Coral.Managed.Interop;

using System;
using Crystal;

public class Test : Entity
{
    [ValueField]
    public int b = 0;

    [ValueField]
    public float a = 0.0f;

    public override void OnCreate()
    {
    }

    public override void OnUpdate(float deltaTime)
    {

        if (HasComponent<TransformComponent>())
        {
            TransformComponent transform = GetComponent<TransformComponent>();

            if (Input.IsKeyPressed(KeyCode.W)) 
                transform.PosY += 1500f * deltaTime;

            if (Input.IsKeyPressed(KeyCode.S))
                transform.PosY -= 1500f * deltaTime;

            if (Input.IsKeyPressed(KeyCode.D))
                transform.PosX += 1500f * deltaTime;

            if (Input.IsKeyPressed(KeyCode.A))
                transform.PosX -= 1500f * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Escape))
                Console.WriteLine("ESCAPED");
        }
    }
}