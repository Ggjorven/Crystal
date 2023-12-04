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

            if (Input.IsKeyPressed(KeyCode.Up))
                transform.PosY += Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Down))
                transform.PosY -= Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Right))
                transform.PosX += Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Left))
                transform.PosX -= Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Escape))
                Console.WriteLine("ESCAPED");

            Test test = Scene.GetEntityByTag<Test>("Mario");
            //Console.WriteLine(test.ID);

            TransformComponent marioTransform = test.GetComponent<TransformComponent>();

            Console.WriteLine(marioTransform.PosX + ", " + transform.PosX);

            if (marioTransform.PosX < transform.PosX)
            {
                Console.WriteLine("Less");
            }
            else
            {
                Console.WriteLine("More");
            }
        }

    }
}