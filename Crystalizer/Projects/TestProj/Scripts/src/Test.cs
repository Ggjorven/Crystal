using Coral.Managed.Interop;

using System;
using Crystal;
using System.Threading.Tasks.Dataflow;

public class Test : Entity // "Mario"
{
    [ValueField]
    public float Speed = 1000.0f;

    [ValueField]
    public float Gravity = 9.81f;

    [ValueField]
    public float YVelocityMax = 9.81f;
    public float YVelocity = 0.0f;

    public bool CanJump = true; // TODO
    
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
            {
                position.Y += Speed * deltaTime;
                YVelocity = 0.0f;
            }

            if (Input.IsKeyPressed(KeyCode.S))
                position.Y -= Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.D))
                position.X += Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.A))
                position.X -= Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.Escape))
                Console.WriteLine("ESCAPED");

            // Update position
            YVelocity += Gravity;
            YVelocity = Math.Min(YVelocity, YVelocityMax);

            //Console.WriteLine(YVelocity);

            position.Y -= YVelocity * deltaTime;
            transform.SetPosition(position);
        }

        if (HasComponent<Renderer2DComponent>())
        {
            Renderer2DComponent r2d = GetComponent<Renderer2DComponent>();
            
            Vec4<float> colour = r2d.GetColour();
            colour.R = 1.0f;
            colour.G = 0.0f;
            colour.B = 0.0f;
            colour.A = 1.0f;

            Texture2D texture = new Texture2D("minion.png");

            // Update colour
            //r2d.SetColour(colour);
            //r2d.SetUseColour(true);

            //r2d.SetTexture(texture);
            //r2d.SetUseTexture(false);
        }
    }

    public override void OnCollision(Entity other)
    {
        //Console.WriteLine("C# Collision with " + other.ID);
        
        if (HasComponent<TransformComponent>() && other.HasComponent<TransformComponent>())
        {
            TransformComponent myTC = GetComponent<TransformComponent>();
            TransformComponent otherTC = other.GetComponent<TransformComponent>();

            var myProps = GetCollisionProperties();
            var otherProps = other.GetCollisionProperties();

            if (myProps.Side == CollisionProperties.CollisionSide.Right)
            {
                //Console.WriteLine("Mario right");
                Vec3<float> newPos = myTC.GetPosition();
                newPos.X = otherTC.GetPosition().X - myTC.GetSize().X;

                myTC.SetPosition(newPos);
            }
            else if (myProps.Side == CollisionProperties.CollisionSide.Left)
            {
                //Console.WriteLine("Mario left");
                Vec3<float> newPos = myTC.GetPosition();
                newPos.X = otherTC.GetPosition().X + otherTC.GetSize().X;

                myTC.SetPosition(newPos);
            }
            else if (myProps.Side == CollisionProperties.CollisionSide.Top)
            {
                //Console.WriteLine("Mario top");
                Vec3<float> newPos = myTC.GetPosition();
                newPos.Y = otherTC.GetPosition().Y - myTC.GetSize().Y;
                YVelocity = 0.0f;

                myTC.SetPosition(newPos);
            }
            else if (myProps.Side == CollisionProperties.CollisionSide.Bottom)
            {
                //Console.WriteLine("Mario bottom");
                Vec3<float> newPos = myTC.GetPosition();
                newPos.Y = otherTC.GetPosition().Y + otherTC.GetSize().Y;
                YVelocity = 0.0f;

                myTC.SetPosition(newPos);
            }
        }
    }
}