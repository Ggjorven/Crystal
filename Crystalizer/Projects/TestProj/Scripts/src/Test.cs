using Coral.Managed.Interop;
using Crystal;

using System;

public class Placeholder : Entity
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
            GetComponent<TagComponent>().Tag = "JOJGOIEGJ";
        }
    }

}