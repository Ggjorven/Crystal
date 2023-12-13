using Coral.Managed.Interop;

using System;
using Crystal;

public class Test2 : Entity // "Red"
{
    [ValueField]
    public float Speed = 1000.0f;

    public override void OnCreate()
    {
        //Console.WriteLine("Test2 OnCreate");
        //GetComponent<TagComponent>().Tag = " Ioiaeghoigaeh";
        //GetComponent<TransformComponent>().SizeY = 1000.0f;
    }

    public override void OnUpdate(float deltaTime)
    {
        if (HasComponent<TransformComponent>())
        {
            TransformComponent transform = GetComponent<TransformComponent>();
            Vec3<float> position = transform.GetPosition();

            if (Input.IsKeyPressed(KeyCode.Up))
                position.Y += Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Down))
                position.Y -= Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Right))
                position.X += Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Left))
                position.X -= Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Escape))
                Scene.SetSceneByName("Mario");

            //Update position
            transform.SetPosition(position);
        }

    }
}