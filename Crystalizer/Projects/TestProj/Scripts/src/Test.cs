using System;
using Crystal;

public class Test : Entity
{

    public void OnCreate()
    {
        TagComponent tag = new TagComponent(ID);
        tag.Tag = "Test";
        
        AddComponent<TagComponent>(tag);
        //tag.Tag = "Test2";
    }

    public void OnUpdate(float ts)
    {
        if (HasComponent<TagComponent>())
        {
            GetComponent<TagComponent>().Tag = "fageag";
        }
        if (HasComponent<TransformComponent>())
        {
            TransformComponent transform = GetComponent<TransformComponent>();

            if (Input.IsKeyPressed(KeyCode.W)) 
                transform.PosY += 10;

            if (Input.IsKeyPressed(KeyCode.S))
                transform.PosY -= 10;

            //GetComponent<TransformComponent>().PosX += 10.0f;
        }
    }

}