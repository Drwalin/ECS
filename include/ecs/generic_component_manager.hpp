#pragma once

#include "ecs.hpp"
#include "component_registry.hpp"

namespace ecs
{
template <typename T, ecs::Density D = T::_ecs_density>
class GenericComponentManager;

template <typename T>
class GenericComponentManager<T, ecs::Density::DENSE> : public ComponentManager
{
public:
	GenericComponentManager() {}
	virtual ~GenericComponentManager() override;

	inline static void assure(Entity e, ComponentManager *cm);
	inline static T &access(Entity e, ComponentManager *cm);
	inline static T &add(Entity e, ComponentManager *cm);
	inline static T &set(Entity e, ComponentManager *cm, const T &val);
	inline static T &set(Entity e, ComponentManager *cm, T &&mov_val);
	inline static T *get(Entity e, const ComponentManager *cm);
	inline static void remove(Entity e, ComponentManager *cm);

private:
};

template <typename T>
class GenericComponentManager<T, ecs::Density::SPARSE> : public ComponentManager
{
public:
	GenericComponentManager() {}
	virtual ~GenericComponentManager() override;

	inline static void assure(Entity e, ComponentManager *cm);
	inline static T &access(Entity e, ComponentManager *cm);
	inline static T &add(Entity e, ComponentManager *cm);
	inline static T &set(Entity e, ComponentManager *cm, const T &val);
	inline static T &set(Entity e, ComponentManager *cm, T &&mov_val);
	inline static T *get(Entity e, const ComponentManager *cm);
	inline static void remove(Entity e, ComponentManager *cm);

private:
};

template <typename T> class GenericComponentBasic
{
public:
	inline static const TypeTraits *register_type()
	{
		if (T::_ecs_type_traits == nullptr || T::_ecs_component_id.id == 0) {
			if (T::_ecs_type_traits || T::_ecs_component_id.id) {
				// TODO: throw error
			}
			T::component_id = TypeRegistry::GenerateNewTypeId();
			const static TypeTraits type_traits{
				T::_ecs_create_component_manager,
				GenericComponentManager<T>::assure,
				+[](Entity e, ComponentManager *m) -> void * {
					return (void *)&GenericComponentManager<T>::access(e, m);
				},
				+[](Entity e, ComponentManager *m) -> void * {
					return (void *)&GenericComponentManager<T>::add(e, m);
				},
				+[](Entity e, ComponentManager *m, const void *p) -> void * {
					return (void *)&GenericComponentManager<T>::set(
						e, m, *(const T *)p);
				},
				+[](Entity e, ComponentManager *m, void *p) -> void * {
					return (void *)&GenericComponentManager<T>::set(
						e, m, std::move(*(T *)p));
				},
				+[](Entity e, const ComponentManager *m) -> void * {
					return (void *)GenericComponentManager<T>::get(e, m);
				},
				+[](Entity e, ComponentManager *m) {
					return GenericComponentManager<T>::remove(e, m);
				},

				+[](void *src, void *dst) {
					GenericComponentManager<T>::move_to_empty(
						std::move(*(T *)src), *(T *)dst);
				},
				+[](const void *src, void *dst) {
					GenericComponentManager<T>::copy_to_empty(*(const T *)src,
															  *(T *)dst);
				},
				+[](void *src, void *dst) {
					GenericComponentManager<T>::move_to_existing(
						std::move(*(T *)src), *(T *)dst);
				},
				+[](const void *src, void *dst) {
					GenericComponentManager<T>::copy_to_existing(
						*(const T *)src, *(T *)dst);
				},
				+[](void *ptr) {
					GenericComponentManager<T>::construct((T *)ptr);
				},
				+[](void *ptr) {
					GenericComponentManager<T>::destruct((T *)ptr);
				},

				+[](struct serializer &ar, const void *ptr) {
					GenericComponentManager<T>::serialize(ar, *(const T *)ptr);
				},
				+[](struct deserializer &ar, void *ptr) {
					GenericComponentManager<T>::deserialize(ar, *(T *)ptr);
				},
			};
			TypeRegistry::RegisterType(T::_ecs_type_traits);
		}
		return T::_ecs_type_traits;
	}

	inline static void move_to_empty(T &&src, T &dst)
	{
		new (&dst) T(std::move(src));
	}
	inline static void copy_to_empty(const T &src, T &dst)
	{
		new (&dst) T(src);
	}
	inline static void move_to_existing(T &&src, T &dst)
	{
		dst = std::move(src);
	}
	inline static void copy_to_existing(const T &src, T &dst)
	{
		dst = src;
	}
	inline static void construct(T *ptr)
	{
		new (static_cast<void *>(ptr)) T();
	}
	inline static void destruct(T *ptr)
	{
		ptr->~T();
	}
};
} // namespace ecs
