using System;
using Crystal;

public class Test : Entity
{

    public void OnCreate()
    {
        //Console.WriteLine("(Test) OnCreate");

        TagComponent tag = new TagComponent(ID);
        tag.Tag = "Mario";
        
        AddComponent<TagComponent>(tag);
    }

    public void OnUpdate(float ts)
    {
        //Console.WriteLine("(Test) OnUpdate, ts: " + ts);

        if (HasComponent<TagComponent>())
        {
            GetComponent<TagComponent>().Tag = "Mario";
        }
        if (HasComponent<TransformComponent>())
        {
            TransformComponent transform = GetComponent<TransformComponent>();

            if (Input.IsKeyPressed(KeyCode.W)) 
                transform.PosY += 1500f * ts;

            if (Input.IsKeyPressed(KeyCode.S))
                transform.PosY -= 1500f * ts;

            if (Input.IsKeyPressed(KeyCode.D))
                transform.PosX += 1500f * ts;

            if (Input.IsKeyPressed(KeyCode.A))
                transform.PosX -= 1500f * ts;

            if (Input.IsKeyPressed(KeyCode.Escape))
                Console.WriteLine("ESCAPED");
        }
    }

}