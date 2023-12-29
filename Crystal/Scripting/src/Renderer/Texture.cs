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

    public class Texture2D
    { 
        public Texture2D(string path)
        {
            Path = path;
        }

        public string Path;
    }


}