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

    public abstract class Entity
    {
        public ulong ID = 0;

		private Dictionary<Type, Component> m_Components = new Dictionary<Type, Component>();

        public Entity(ulong id = 0) { ID = id; }
        public void SetUUID(ulong id) { ID = id; }

        public void Init()
        {
            var properties = this.GetType().GetFields(/*BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic*/);

            foreach (var property in properties)
            {
                var valueFieldAttribute = property.GetCustomAttribute<ValueField>();
                if (valueFieldAttribute != null)
                {
                    var value = property.GetValue(this);
                    valueFieldAttribute.Process(value, property.Name, ID);
                }
            }
        }


        public abstract void OnCreate();
		public abstract void OnUpdate(float deltaTime);

		// Base function
		public void AddComponent<T>(T component) where T : Component { m_Components[typeof(T)] = component; }
		// TagComponent
		public void AddComponent<TagC>(TagComponent component) where TagC : TagComponent
		{
            component.ID = ID;

            m_Components[typeof(TagComponent)] = component;
			unsafe
			{
                InternalCalls.AddTagComponent(ID, component.Tag);
			}
        }

		public void AddComponent<TransformC>(TransformComponent component) where TransformC : TransformComponent
		{
            component.ID = ID;

            m_Components[typeof(TagComponent)] = component;
            unsafe
            {
                //InternalCalls.AddTransformComponent(ID, component.Tag); // TODO
            }
        }

		public bool HasComponent<T>() where T : Component
		{
			if (m_Components.ContainsKey(typeof(T)))
				return true;

			return false;
		}

        public T GetComponent<T>() where T : Component, new()
        {
			if (HasComponent<T>())
				return (T)m_Components[typeof(T)];

            return new T();
        }

		//-------Components---------
		// Note(Jorben): Purposefully not using AddComponent<> since that also adds it to the engine's memory but that's where this function was called from.
		public void AddTagComponent()
		{
			TagComponent tagComponent = new TagComponent(ID);
			m_Components[typeof(TagComponent)] = tagComponent;
		}

		public void AddTransformComponent()
		{
            TransformComponent transformComponent = new TransformComponent(ID);
			m_Components[typeof(TransformComponent)] = transformComponent;
		}
    }

}