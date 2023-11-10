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
            GetComponent<TransformComponent>().PosX += 10.0f;
        }
    }

}