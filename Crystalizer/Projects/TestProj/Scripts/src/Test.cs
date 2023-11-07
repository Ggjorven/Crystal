using Coral.Managed.Interop;

using System;

public class Entity
{

    public Entity()
    {
        Console.WriteLine("Constructor");
    }
    public void OnCreate()
    {
        Console.WriteLine("Create");
    }

    public void OnUpdate(float ts)
    {
        Console.WriteLine("Update new" + ts);
        Console.WriteLine("Update again");
    }
}