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
        Console.WriteLine("Creation function");
    }

    public void OnUpdate(float ts)
    {
        Console.WriteLine("Update timestep: " + ts);
    }
}