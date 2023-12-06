using Coral.Managed.Interop;

using System;
using Crystal;
using System.Threading.Tasks.Dataflow;

public class Test : Entity // "Mario"
{
    [ValueField]
    public float Speed = 550.0f;

    [ValueField]
    public float Gravity = 9.81f;

    [ValueField]
    public float JumpHeight = 990.0f;

    [ValueField]
    public float YVelocityMax = -1000.0f;

    public float YVelocity = 0.0f;

    public bool CanJump = true; 
    
    public override void OnCreate()
    {

    }

    public override void OnUpdate(float deltaTime)
    {
        if (HasComponent<TransformComponent>())
        {
            TransformComponent transform = GetComponent<TransformComponent>();
            Vec3<float> position = transform.GetPosition();

            if (Input.IsKeyPressed(KeyCode.W) && CanJump)
            {
                YVelocity = JumpHeight;
            }

            if (Input.IsKeyPressed(KeyCode.S))
                position.Y -= Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.D))
                position.X += Speed * deltaTime;

            if (Input.IsKeyPressed(KeyCode.A))
                position.X -= Speed * deltaTime;

            // Update position
            YVelocity -= Gravity;
            YVelocity = Math.Clamp(YVelocity, YVelocityMax, 5000.0f);

            position.Y += YVelocity * deltaTime;
            transform.SetPosition(position);

            CanJump = false;
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

                    if (YVelocity > 0.0f)
                        YVelocity = 0.0f;

                    myTC.SetPosition(newPos);
                    break;

                case CollisionProperties.CollisionSide.Bottom:
                    newPos = myTC.GetPosition();
                    newPos.Y = otherTC.GetPosition().Y + otherTC.GetSize().Y;
                    YVelocity = 0.0f;
                    CanJump = true;
                    myTC.SetPosition(newPos);
                    break;
            }
        }
    }
}