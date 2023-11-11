using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Crystal;

namespace Crystal
{

    public class Input
    {
        unsafe public static bool IsKeyPressed(KeyCode code) { return InternalCalls.Input_IsKeyPressed((int)code); }
    }

}
