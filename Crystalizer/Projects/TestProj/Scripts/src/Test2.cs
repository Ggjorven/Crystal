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
                Console.WriteLine("ESCAPED");

            Test test = Scene.GetEntityByTag<Test>("Mario");
            TransformComponent marioTransform = test.GetComponent<TransformComponent>();

            Console.WriteLine(position.X + ", " + marioTransform.GetPosition().X);

            if (position.X < marioTransform.GetPosition().X)
            {
                //Console.WriteLine("Less");
            }
            else
            {
                //Console.WriteLine("More");
            }

            //Update position
            transform.SetPosition(position);
        }

    }
}