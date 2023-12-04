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

            // Update position
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
            r2d.SetColour(colour);
            r2d.SetUseColour(false);

            r2d.SetTexture(texture);
            r2d.SetUseTexture(true);
        }
    }
}