using Coral.Managed.Interop;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Crystal;

/*
		public T GetComponent<T>() where T : Component, new()
		{
			Type componentType = typeof(T);

			if (!HasComponent<T>())
			{
				if (m_ComponentCache.ContainsKey(componentType))
					m_ComponentCache.Remove(componentType);

				return null;
			}

			if (!m_ComponentCache.ContainsKey(componentType))
			{
				T component = new T { Entity = this };
				m_ComponentCache.Add(componentType, component);
				return component;
			}

			return m_ComponentCache[componentType] as T;
		}
*/

namespace Crystal
{

    public class Entity
    {
        public ulong ID = 0;

		private Dictionary<Type, Component> m_Components = new Dictionary<Type, Component>();

        
        public Entity(ulong id = 0) { ID = id; }
        public void SetUUID(ulong id) { ID = id; }

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

		/*
			All component adding from C++
		*/
		public void AddTagComponent()
		{
			TagComponent tagComponent = new TagComponent(ID);
			m_Components[typeof(TagComponent)] = tagComponent; // Note(Jorben): Purposefully not using AddComponent<> since that also adds it to the engine's memory but that where this function was called from.
		}
    }

}