using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Crystal
{

    public class Component
    {
        unsafe public ulong ID;
        unsafe protected Component(ulong entityID) { ID = entityID; }
    }

    public class TagComponent : Component
    {
        public TagComponent() : base(0) { }
        unsafe public TagComponent(ulong entityID) : base(entityID) { }

        unsafe public string Tag
        {
            get => InternalCalls.TagComponent_GetTag(ID);
            set => InternalCalls.TagComponent_SetTag(ID, value);
        }
    }

    public class TransformComponent : Component
    {
        public TransformComponent() : base(0) { }
        unsafe public TransformComponent(ulong entityID) : base(entityID) { }

        
    }
}