#pragma once

#include "ecs.hpp"
#include "component_registry.hpp"

namespace ecs
{
template <typename T, ecs::Density D = T::_ecs_density>
class GenericComponentManager;

}

#include "generic_component_manager_dense.hpp"	// IWYU pragma: export
#include "generic_component_manager_sparse.hpp" // IWYU pragma: export

namespace ecs
{
template <typename T> class GenericComponentBasic
{
public:
	inline static const TypeTraits *register_type()
	{
		if (T::_ecs_type_traits == nullptr || T::_ecs_component_id.id == 0) {
			if (T::_ecs_type_traits || T::_ecs_component_id.id) {
				// TODO: throw error
			}
			T::_ecs_component_id = TypeRegistry::GenerateNewTypeId();
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

				T::_ecs_type_name,
				T::_ecs_name.s,
				T::_ecs_short_name,
				(uint32_t)sizeof(T),
				T::_ecs_custom_alignement,
				T::_ecs_component_id,
				T::_ecs_density,
			};
			T::_ecs_type_traits =
				const_cast<TypeTraits *>(&type_traits);
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
	inline static void copy_to_existing(const T &src, T &dst) { dst = src; }
	inline static void construct(T *ptr) { new (static_cast<void *>(ptr)) T(); }
	inline static void destruct(T *ptr) { ptr->~T(); }
};

template <typename T> class GenericTagBasic
{
public:
	inline static const TagTypeTraits *register_tag()
	{
		if (T::_ecs_tag_traits == nullptr || T::_ecs_tag_id.id == 0) {
			if (T::_ecs_tag_traits || T::_ecs_tag_id.id) {
				// TODO: throw error
			}
			T::_ecs_tag_id = TagTypeRegistry::GenerateNewTypeId();
			const static TagTypeTraits tag_traits{
				T::_ecs_type_name,
				T::_ecs_short_name,
				T::_ecs_tag_id,
			};
			T::_ecs_tag_traits = const_cast<TagTypeTraits *>(&tag_traits);
			TagTypeRegistry::RegisterType(T::_ecs_tag_traits);
		}
		return T::_ecs_tag_traits;
	}
};
} // namespace ecs
