using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Crystal;

namespace Crystal
{

    public class CollisionProperties
    {
        public enum CollisionType
        {
            None = 0, AABB
        };

        public enum CollisionSide
        {
            None = 0, Right, Left, Top, Bottom
        };

	    public CollisionType Type = CollisionType.None;
        public CollisionSide Side = CollisionSide.None;
    }


}
