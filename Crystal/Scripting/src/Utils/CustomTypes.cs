using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Crystal;

namespace Crystal
{
    
    public class Vec2<T>
    {
        public T X;
        public T Y;

        public Vec2(T x, T y)
        {
            X = x;
            Y = y;
        }
    }

    public class Vec3<T>
    {
        public T X;
        public T Y;
        public T Z;

        public Vec3(T x, T y, T z)
        {
            X = x;
            Y = y;
            Z = z;
        }
    }

    public class Vec4<T>
    {
        public T R;
        public T G;
        public T B;
        public T A;

        public Vec4(T r, T g, T b, T a)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }
    }

}