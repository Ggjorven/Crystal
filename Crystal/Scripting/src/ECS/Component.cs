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
        unsafe protected ulong ID;
        unsafe protected Component(ulong entityID) { ID = entityID; }
    }

    public class TagComponent : Component
    {
        public TagComponent() : base(0) { }
        unsafe public TagComponent(ulong entityID, string tag = "None")
            : base(entityID)
        {
            InternalCalls.TagComponent_SetTag(base.ID, tag);
        }

        unsafe public string GetTag() { return InternalCalls.TagComponent_GetTag(base.ID); }
        unsafe public void SetTag(string value) { InternalCalls.TagComponent_SetTag(base.ID, value); }
    }

    public class TransformComponent : Component
    {
        public TransformComponent() : base(0) { }
        unsafe public TransformComponent(ulong entityID) : base(entityID)
        {

        }
    }
}