using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Crystal
{

    unsafe public class InternalCalls
    {
        /*
            Components 
        */
        //TagComponent
        internal static unsafe delegate*<ulong, NativeString> TagComponent_GetTag;
        internal static unsafe delegate*<ulong, NativeString, void> TagComponent_SetTag;

    }

}