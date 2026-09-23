#pragma once

#include "types.hpp" // IWYU pragma: export
#include "ecs.hpp"

#include "component_registry.hpp"
#include "generic_component_manager.hpp"

namespace ecs
{
template<typename T>
class TypeManImpl {
public:
	inline static const TypeTraits *register_type()
	{
		if (T::_ecs_type_traits == nullptr || T::_ecs_component_id.id == 0) {
			if (T::_ecs_type_traits || T::_ecs_component_id.id) {
				// TODO: throw error
			}
			T::component_id = TypeRegistry::GenerateNewTypeId();
			const static TypeTraits type_traits{
				assure,
				+[](Entity e, ComponentManager *m) -> void * {
					return (void *)&access(e, m);
				},
				+[](Entity e, ComponentManager *m) -> void * {
					return (void *)&add(e, m);
				},
				+[](Entity e, ComponentManager *m, const void *p) -> void * {
					return (void *)&set(e, m, *(const T *)p);
				},
				+[](Entity e, ComponentManager *m, void *p) -> void * {
					return (void *)&set(e, m, std::move(*(T *)p));
				},
				+[](Entity e, const ComponentManager *m) -> void * {
					return (void *)get(e, m);
				},
				+[](Entity e, ComponentManager *m) {
					return remove(e, m);
				},

				+[](void *src, void *dst) {
					move_to_empty(std::move(*(T *)src),
									   *(T *)dst);
				},
				+[](const void *src, void *dst) {
					copy_to_empty(*(const T *)src, *(T *)dst);
				},
				+[](void *src, void *dst) {
					move_to_existing(std::move(*(T *)src),
										  *(T *)dst);
				},
				+[](const void *src, void *dst) {
					copy_to_existing(*(const T *)src,
										  *(T *)dst);
				},
				+[](void *ptr) { construct((T *)ptr); },
				+[](void *ptr) { destruct((T *)ptr); },

				+[](struct serializer &ar, const void *ptr)
				{
					serialize(ar, *(const T*)ptr);
				},
				+[](struct deserializer &ar, void *ptr)
				{
					deserialize(ar, *(T*)ptr);
				},
			};
			TypeRegistry::RegisterType(T::_ecs_type_traits);
		}
		return T::_ecs_type_traits;
	}

	inline static ComponentManager *get_component_manager(World *w)
	{
		assert(T::_ecs_component_id.id != 0);
		return w->get_component_manager(T::_ecs_component_id);
	}

	inline static void assure(Entity e, ComponentManager *cm);
	inline static T &access(Entity e, ComponentManager *cm);
	inline static T &add(Entity e, ComponentManager *cm);
	inline static T &set(Entity e, ComponentManager *cm, const T &val);
	inline static T &set(Entity e, ComponentManager *cm, T &&mov_val);
	inline static T *get(Entity e, const ComponentManager *cm);
	inline static void remove(Entity e, ComponentManager *cm);

	inline static void execute_observers_add(Entity e, ComponentManager *cm);
	inline static void execute_observers_set(Entity e, ComponentManager *cm);
	inline static void execute_observers_remove(Entity e, ComponentManager *cm);

	inline static void assure(Entity e, World *w);
	inline static T &access(Entity e, World *w);
	inline static T &add(Entity e, World *w);
	inline static T &set(Entity e, World *w, const T &val);
	inline static T &set(Entity e, World *w, T &&mov_val);
	inline static T *get(Entity e, const World *w);
	inline static void remove(Entity e, World *w);

	inline static void execute_observers_add(Entity e, World *w);
	inline static void execute_observers_set(Entity e, World *w);
	inline static void execute_observers_remove(Entity e, World *w);

	inline static void move_to_empty(T &&src, T &dst);
	inline static void copy_to_empty(const T &src, T &dst);
	inline static void move_to_existing(T &&src, T &dst);
	inline static void copy_to_existing(const T &src, T &dst);
	inline static void construct(T *ptr);
	inline static void destruct(T *ptr);

	inline static void serialize(struct serializer &ar, const T &ptr);
	inline static void deserialize(struct deserializer &ar, T &ptr);
};
}
