using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Crystal;
using System.Reflection;

namespace Crystal
{

    public class Scene
    {
        unsafe public static T GetEntityByTag<T>(string tag) where T : Entity, new()
        {
            T e = new T();
            e.SetUUID(InternalCalls.GetUUIDByTag(tag));

            return e;
        }

        unsafe public static void SetSceneByName(string name)
        {
            InternalCalls.SetSceneByName(name);
        }
    }

}