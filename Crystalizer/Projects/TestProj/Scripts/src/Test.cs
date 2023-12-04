using Coral.Managed.Interop;

using System;
using Crystal;

public class Test : Entity // "Mario"
{
    [ValueField]
    public float Speed = 1000.0f;

    public override void OnCreate()
    {
        //Console.WriteLine("Test OnCreate");
        //GetComponent<TagComponent>().Tag = " Ioiaeghoigaeh";
        //GetComponent<TransformComponent>().SizeY = 1000.0f;
    }

    public override void OnUpdate(float deltaTime)
    {
        if (HasComponent<TransformComponent>())
        {
            TransformComponent transform = GetComponent<TransformComponent>();

            if (Input.IsKeyPressed(KeyCode.W)) 
                transform.PosY += Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.S))
                transform.PosY -= Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.D))
                transform.PosX += Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.A))
                transform.PosX -= Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Escape))
                Console.WriteLine("ESCAPED");
        }
    }
}