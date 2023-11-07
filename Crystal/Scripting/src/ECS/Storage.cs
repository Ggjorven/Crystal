using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Crystal;

namespace Crystal
{

    //public class Storage
    //{
    //internal static unsafe delegate*<NativeArray<float>> ArrayReturnIcall;
    //public static unsafe delegate*<NativeArray<float>> ArrayReturnIcall;

    //internal delegate ComponentResult GetComponentDelegate<ComponentResult>(UInt64 uuid);

    //public Storage
    //{
    //}
    //}

    //m_AudioComponent = entity.GetComponent<AudioComponent>();

    /*
     public T GetComponent<T>() where T : Component, new()
      {
          if (HasComponent<T>())
          {
              T component = new T();
              component.Entity = this;
              return component;
          }
          return null;
      }
     */

    public class Storage
    {
        //static unsafe delegate*<ComponentResult, UInt64> GetComponent;

        public Storage() 
        {
        }
    }
}