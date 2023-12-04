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
            Vec3<float> position = transform.GetPosition();

            if (Input.IsKeyPressed(KeyCode.W)) 
                position.Y += Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.S))
                position.Y -= Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.D))
                position.X += Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.A))
                position.X -= Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Escape))
                Console.WriteLine("ESCAPED");

            //Update position
            transform.SetPosition(position);
        }
    }
}