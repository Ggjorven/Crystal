using System;

public class Entity
{
    public void OnCreate()
    {
        Console.WriteLine("ABC");
    }

    public void OnUpdate(float ts)
    {
        Console.WriteLine("ABC", ts);
    }
}