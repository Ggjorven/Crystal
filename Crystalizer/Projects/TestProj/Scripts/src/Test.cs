using Coral.Managed.Interop;
using Crystal;

using System;

public class Placeholder : Crystal.Entity
{

    public void OnCreate()
    {
        Console.WriteLine("Creation function");
        GetComponent<TagComponent>().SetTag("abc");
    }

    public void OnUpdate(float ts)
    {
        Console.WriteLine("Update timestep: " + ts);
    }

}