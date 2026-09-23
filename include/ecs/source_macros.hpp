#pragma once

#include <cassert>

#include "types.hpp" // IWYU pragma: export

#include "generic_component_manager.hpp"

#define ECS_TYPE_TRAITS_DEFINITION(T)                                          \
	ecs::TypeTraits *T::_ecs_type_traits = nullptr;                            \
	const ecs::TypeTraits *T::_ecs_register_type()                             \
	{                                                                          \
		return ecs::GenericComponentBasic<T>::register_type();                 \
	}                                                                          \
                                                                               \
	ecs::ComponentId T::_ecs_component_id = {0};                               \
                                                                               \
	ecs::ComponentManager *T::_ecs_access_component_manager(ecs::World *w)     \
	{                                                                          \
		assert(_ecs_component_id.id != 0);                                     \
		return w->access_component_manager(_ecs_component_id);                 \
	}                                                                          \
	ecs::ComponentManager *T::_ecs_get_component_manager(ecs::World *w)        \
	{                                                                          \
		assert(_ecs_component_id.id != 0);                                     \
		return w->get_component_manager(_ecs_component_id);                    \
	}                                                                          \
	const ecs::ComponentManager *T::_ecs_get_component_manager(                \
		const ecs::World *w)                                                   \
	{                                                                          \
		assert(_ecs_component_id.id != 0);                                     \
		return w->get_component_manager(_ecs_component_id);                    \
	}                                                                          \
                                                                               \
	void T::_ecs_assure(ecs::Entity e, ecs::ComponentManager *cm)              \
	{                                                                          \
		ecs::GenericComponentManager<T>::assure(e, cm);                        \
	}                                                                          \
	T &T::_ecs_access(ecs::Entity e, ecs::ComponentManager *cm)                \
	{                                                                          \
		return ecs::GenericComponentManager<T>::access(e, cm);                 \
	}                                                                          \
	T &T::_ecs_add(ecs::Entity e, ecs::ComponentManager *cm)                   \
	{                                                                          \
		return ecs::GenericComponentManager<T>::add(e, cm);                    \
	}                                                                          \
	T &T::_ecs_set(ecs::Entity e, ecs::ComponentManager *cm, const T &val)     \
	{                                                                          \
		return ecs::GenericComponentManager<T>::set(e, cm, val);               \
	}                                                                          \
	T &T::_ecs_set(ecs::Entity e, ecs::ComponentManager *cm, T &&mov_val)      \
	{                                                                          \
		return ecs::GenericComponentManager<T>::set(e, cm, mov_val);           \
	}                                                                          \
	T *T::_ecs_get(ecs::Entity e, const ecs::ComponentManager *cm)             \
	{                                                                          \
		return ecs::GenericComponentManager<T>::get(e, cm);                    \
	}                                                                          \
	void T::_ecs_remove(ecs::Entity e, ecs::ComponentManager *cm)              \
	{                                                                          \
		ecs::GenericComponentManager<T>::remove(e, cm);                        \
	}                                                                          \
                                                                               \
	void T::_ecs_assure(ecs::Entity e, ecs::World *w)                          \
	{                                                                          \
		_ecs_assure(e, _ecs_access_component_manager(w));                      \
	}                                                                          \
	T &T::_ecs_access(ecs::Entity e, ecs::World *w)                            \
	{                                                                          \
		return _ecs_access(e, _ecs_access_component_manager(w));               \
	}                                                                          \
	T &T::_ecs_add(ecs::Entity e, ecs::World *w)                               \
	{                                                                          \
		return _ecs_add(e, _ecs_access_component_manager(w));                  \
	}                                                                          \
	T &T::_ecs_set(ecs::Entity e, ecs::World *w, const T &val)                 \
	{                                                                          \
		return _ecs_set(e, _ecs_access_component_manager(w), val);             \
	}                                                                          \
	T &T::_ecs_set(ecs::Entity e, ecs::World *w, T &&mov_val)                  \
	{                                                                          \
		return _ecs_set(e, _ecs_access_component_manager(w), mov_val);         \
	}                                                                          \
	T *T::_ecs_get(ecs::Entity e, const ecs::World *w)                         \
	{                                                                          \
		return _ecs_get(e, _ecs_get_component_manager(w));                     \
	}                                                                          \
	void T::_ecs_remove(ecs::Entity e, ecs::World *w)                          \
	{                                                                          \
		_ecs_remove(e, _ecs_get_component_manager(w));                         \
	}                                                                          \
                                                                               \
	void T::_ecs_move_to_empty(T &&src, T &dst)                                \
	{                                                                          \
		ecs::GenericComponentBasic<T>::move_to_empty(std::move(src), dst);     \
	}                                                                          \
	void T::_ecs_copy_to_empty(const T &src, T &dst)                           \
	{                                                                          \
		ecs::GenericComponentBasic<T>::copy_to_empty(src, dst);                \
	}                                                                          \
	void T::_ecs_move_to_existing(T &&src, T &dst)                             \
	{                                                                          \
		ecs::GenericComponentBasic<T>::move_to_existing(std::move(src), dst);  \
	}                                                                          \
	void T::_ecs_copy_to_existing(const T &src, T &dst)                        \
	{                                                                          \
		ecs::GenericComponentBasic<T>::copy_to_existing(src, dst);             \
	}                                                                          \
	void T::_ecs_construct(T *ptr)                                             \
	{                                                                          \
		ecs::GenericComponentBasic<T>::construct(ptr);                         \
	}                                                                          \
	void T::_ecs_destruct(T *ptr)                                              \
	{                                                                          \
		ecs::GenericComponentBasic<T>::destruct(ptr);                          \
	}                                                                          \
                                                                               \
	ecs::ComponentManager *T::_ecs_create_component_manager()                  \
	{                                                                          \
		return new ecs::GenericComponentManager<T>;                            \
	}                                                                          \
                                                                               \
	void T::_ecs_serialize(struct serializer &ar, const T &ptr)                \
	{                                                                          \
		ptr.serialize(ar);                                                     \
	}                                                                          \
	void T::_ecs_deserialize(struct deserializer &ar, T &ptr)                  \
	{                                                                          \
		ptr.deserialize(ar);                                                   \
	}

// void T::serialize(struct serializer &ar) const;
// void T::deserialize(struct deserializer &ar);
//
// #define ECS_TAG_TRAITS(TYPE_NAME)
// using TYPE_NAME = ExampleTagPlayer;
// ecs::TagTypeTraits *_ecs_tag_traits = nullptr;
// const ecs::TagTypeTraits *TYPE_NAME::_ecs_register_tag();
// const ecs::TagTypeTraits *TYPE_NAME::_ecs_get_tag_traits();
//
// ecs::TagId TYPE_NAME::_ecs_tag_id = 0;

#include "example_usage.hpp"

ECS_TYPE_TRAITS_DEFINITION(ExamplePosition)
