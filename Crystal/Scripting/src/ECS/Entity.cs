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

		public void AddComponent<T>(T component) where T : Component
		{
            Console.WriteLine("(AddComponent) Adding component " + typeof(T).Name);
			m_Components[typeof(T)] = component;
		}

		public bool HasComponent<T>() where T : Component
		{
			if (m_Components.ContainsKey(typeof(T)))
			{
				Console.WriteLine("(HasComponent) Has Component");
				return true;
			}

			Console.WriteLine("(HasComponent) No Component");
			return false;
		}

        public T GetComponent<T>() where T : Component, new()
        {
			if (HasComponent<T>())
			{
				Console.WriteLine("(GetComponent) Has Component");
				return (T)m_Components[typeof(T)];
			}

            Console.WriteLine("(GetComponent) No Component");
            return new T();
        }

		/*
			All component adding from C++
		*/
		public void AddTagComponent(string tag)
		{
			Console.WriteLine("(AddTagComponent) Adding tag component in C#");
			TagComponent tagComponent = new TagComponent(ID);
			AddComponent<TagComponent>(tagComponent);
		}
    }

}