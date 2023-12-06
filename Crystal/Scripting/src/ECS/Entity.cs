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

    public class Entity
    {
        public ulong ID = 0;

		private Dictionary<Type, Component> m_Components = new Dictionary<Type, Component>();
        private CollisionProperties m_CollisionProperties = new CollisionProperties();

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
                    valueFieldAttribute.Process(value!, property.Name, ID);
                }
            }
        }


        virtual public void OnCreate() { }
		virtual public void OnUpdate(float deltaTime) { }

        virtual public void OnCollision(Entity other) { }

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

        // TransformComponent
		public void AddComponent<TransformC>(TransformComponent component) where TransformC : TransformComponent
		{
            component.ID = ID;

            m_Components[typeof(TransformComponent)] = component;
            unsafe
            {
                //InternalCalls.AddTransformComponent(ID, component.Tag); // TODO
            }
        }

        // Renderer2DComponent
        public void AddComponent<Renderer2DC>(Renderer2DComponent component) where Renderer2DC : Renderer2DComponent
        {
            component.ID = ID;

            m_Components[typeof(Renderer2DComponent)] = component;
            unsafe
            {
                //InternalCalls.AddRenderer2DComponent(ID, component.Tag); // TODO
            }
        }

        public void AddComponent<ColliderC>(ColliderComponent component) where ColliderC : ColliderComponent
        {
            component.ID = ID;

            m_Components[typeof(ColliderComponent)] = component;
            unsafe
            {
                //InternalCalls.AddRenderer2DComponent(ID, component.Tag); // TODO
            }
        }

        public bool HasComponent<T>() where T : Component
		{
            unsafe
            {
                if (typeof(T) == typeof(TagComponent))
                {
                    return InternalCalls.HasComponent_TagComponent(ID);
                }

                if (typeof(T) == typeof(TransformComponent))
                {
                    return InternalCalls.HasComponent_TransformComponent(ID);
                }

                if (typeof(T) == typeof(Renderer2DComponent))
                {
                    return InternalCalls.HasComponent_Renderer2DComponent(ID);
                }

                if (typeof(T) == typeof(ColliderComponent))
                {
                    return InternalCalls.HasComponent_ColliderComponent(ID);
                }

                /* // TODO(Jorben): Add all components
                if (typeof(T) == typeof(TagComponent))
                {
                    return InternalCalls.HasComponent_TagComponent(ID);
                }
                */
            }
            return false;
		}

        public T GetComponent<T>() where T : Component, new()
        {
			if (HasComponent<T>())
            {
                // TODO(Jorben): Make this not create a new Component every frame.
                if (m_Components.ContainsKey(typeof(T)))
                {
                    return (T)m_Components[typeof(T)];
                }

                m_Components[typeof(T)] = new T();
                m_Components[typeof(T)].ID = ID;

                return (T)m_Components[typeof(T)];
            }

            return new T();
        }

        public void SetLastCollision(CollisionProperties properties) { m_CollisionProperties = properties; }
        public CollisionProperties GetCollisionProperties() { return m_CollisionProperties; }

        public void OnCollisionInternal(ulong target, int typeOne, int sideOne, int typeTwo, int sideTwo)
        {
            Entity e = new Entity();
            e.SetUUID(target);

            CollisionProperties twoProperties = new CollisionProperties();
            twoProperties.Type = (CollisionProperties.CollisionType)typeTwo;
            twoProperties.Side = (CollisionProperties.CollisionSide)sideTwo;
            e.SetLastCollision(twoProperties);

            CollisionProperties oneProperties = new CollisionProperties();
            oneProperties.Type = (CollisionProperties.CollisionType)typeOne;
            oneProperties.Side = (CollisionProperties.CollisionSide)sideOne;
            SetLastCollision(oneProperties);



            OnCollision(e);
        }
    }

}