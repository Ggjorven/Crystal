using System;
using Crystal;

public class Test : Entity // "Mario"
{
    [ValueField]
    public float Speed = 550.0f;

    [ValueField]
    public float Gravity = 3000.0f;

    [ValueField]
    public float JumpHeight = 1450.0f;

    [ValueField]
    public float YVelocityMax = -2000.0f;

    public float YVelocity = 0.0f;

    public bool CanJump = true;

    public float Timer = 0.0f;
    
    public override void OnCreate()
    {

    }

    public override void OnUpdate(float deltaTime)
    {
        if (deltaTime > 0.1f)
            deltaTime = 0.1f;

        if (HasComponent<TransformComponent>())
        {
            TransformComponent transform = GetComponent<TransformComponent>();
            Vec3<float> position = transform.GetPosition();

            if (transform.GetSize().Y == 128.0f)
            {
                if (Timer < 5.0f)
                    Timer += deltaTime;
                else
                    transform.SetSize(new Vec3<float>(transform.GetSize().X, 64.0f, 0.0f));
            }
            else
            {
                Timer = 0.0f;
            }

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
            YVelocity -= Gravity * deltaTime;
            YVelocity = Math.Clamp(YVelocity, YVelocityMax, 5000.0f);

            position.Y += YVelocity * deltaTime;
            transform.SetPosition(position);

            CanJump = false;
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