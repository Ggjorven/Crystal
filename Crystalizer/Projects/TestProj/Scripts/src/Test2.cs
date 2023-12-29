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

    public override void OnCollision(Entity other)
    {
        if (HasComponent<TransformComponent>() && other.HasComponent<TransformComponent>())
        {
            TransformComponent myTC = GetComponent<TransformComponent>();
            TransformComponent otherTC = other.GetComponent<TransformComponent>();

            var myProps = GetCollisionProperties();
            var otherProps = other.GetCollisionProperties();

            switch (myProps.Side)
            {
                case CollisionProperties.CollisionSide.Right:
                    Vec3<float> newPos = myTC.GetPosition();
                    newPos.X = otherTC.GetPosition().X - myTC.GetSize().X;
                    myTC.SetPosition(newPos);
                    break;

                case CollisionProperties.CollisionSide.Left:
                    newPos = myTC.GetPosition();
                    newPos.X = otherTC.GetPosition().X + otherTC.GetSize().X;
                    myTC.SetPosition(newPos);
                    break;

                case CollisionProperties.CollisionSide.Top:
                    newPos = myTC.GetPosition();
                    newPos.Y = otherTC.GetPosition().Y - myTC.GetSize().Y;

                    myTC.SetPosition(newPos);
                    break;

                case CollisionProperties.CollisionSide.Bottom:
                    newPos = myTC.GetPosition();
                    newPos.Y = otherTC.GetPosition().Y + otherTC.GetSize().Y;
                    myTC.SetPosition(newPos);
                    break;
            }
        }
    }
}