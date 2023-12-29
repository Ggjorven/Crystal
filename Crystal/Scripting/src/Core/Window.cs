using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Crystal;
using System.Reflection;
using System.Security.Cryptography.X509Certificates;

namespace Crystal
{

    unsafe public class Window
    {
        static public uint GetWidth()
        {
            return InternalCalls.Window_GetWindowWidth();
        }

        static public uint GetHeight()
        {
            return InternalCalls.Window_GetWindowHeight();
        }
    }
}