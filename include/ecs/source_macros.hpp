#pragma once

#include "types.hpp" // IWYU pragma: export
#include "ecs.hpp"

#include "component_registry.hpp"
#include "example_usage.hpp"

#define ECS_TYPE_TRAITS_DEFINITION(TYPE_NAME)
using TYPE_NAME = ExamplePosition;
ecs::TypeTraits *_ecs_type_traits = nullptr;
const ecs::TypeTraits *TYPE_NAME::_ecs_register_type()
{
	if (_ecs_type_traits == nullptr || _ecs_component_id.id == 0) {
		if (_ecs_type_traits || _ecs_component_id.id) {
			// TODO: throw error
		}
		_ecs_component_id = ecs::TypeRegistry::GenerateNewTypeId();
		const static ecs::TypeTraits type_traits{
			_ecs_assure,
			+[](ecs::Entity e, ecs::ComponentManager *m) -> void * {
				return (void *)&_ecs_access(e, m);
			},
			+[](ecs::Entity e, ecs::ComponentManager *m) -> void * {
				return (void *)&_ecs_add(e, m);
			},
			+[](ecs::Entity e, ecs::ComponentManager *m,
				const void *p) -> void * {
				return (void *)&_ecs_set(e, m, *(const TYPE_NAME *)p);
			},
			+[](ecs::Entity e, ecs::ComponentManager *m, void *p) -> void * {
				return (void *)&_ecs_set(e, m, std::move(*(TYPE_NAME *)p));
			},
			+[](ecs::Entity e, const ecs::ComponentManager *m) -> void * {
				return (void *)_ecs_get(e, m);
			},
			+[](ecs::Entity e, ecs::ComponentManager *m) {
				return _ecs_remove(e, m);
			},

			+[](ecs::Entity e, ecs::ComponentManager *m) {
				return _ecs_execute_observers_add(e, m);
			},
			+[](ecs::Entity e, ecs::ComponentManager *m) {
				return _ecs_execute_observers_set(e, m);
			},
			+[](ecs::Entity e, ecs::ComponentManager *m) {
				return _ecs_execute_observers_remove(e, m);
			},

			+[](void *src, void *dst) {
				_ecs_move_to_empty(std::move(*(TYPE_NAME *)src),
								   *(TYPE_NAME *)dst);
			},
			+[](const void *src, void *dst) {
				_ecs_copy_to_empty(*(const TYPE_NAME *)src, *(TYPE_NAME *)dst);
			},
			+[](void *src, void *dst) {
				_ecs_move_to_existing(std::move(*(TYPE_NAME *)src),
									  *(TYPE_NAME *)dst);
			},
			+[](const void *src, void *dst) {
				_ecs_copy_to_existing(*(const TYPE_NAME *)src,
									  *(TYPE_NAME *)dst);
			},
			+[](void *ptr) { _ecs_construct((TYPE_NAME *)ptr); },
			+[](void *ptr) { _ecs_destruct((TYPE_NAME *)ptr); },

			+[](struct serializer &ar, const void *ptr)
			{
				_ecs_serialize(ar, *(const TYPE_NAME*)ptr);
			},
			+[](struct deserializer &ar, void *ptr)
			{
				_ecs_deserialize(ar, *(TYPE_NAME*)ptr);
			},
		};
		ecs::TypeRegistry::RegisterType(_ecs_type_traits);
	}
	return _ecs_type_traits;
}

ecs::ComponentId TYPE_NAME::_ecs_component_id = 0;

ecs::ComponentManager *TYPE_NAME::_ecs_get_component_manager(ecs::World *w);

void TYPE_NAME::_ecs_assure(ecs::Entity e, ecs::ComponentManager *cm);
TYPE_NAME &TYPE_NAME::_ecs_access(ecs::Entity e, ecs::ComponentManager *cm);
TYPE_NAME &TYPE_NAME::_ecs_add(ecs::Entity e, ecs::ComponentManager *cm);
TYPE_NAME &TYPE_NAME::_ecs_set(ecs::Entity e, ecs::ComponentManager *cm,
							   const TYPE_NAME &val);
TYPE_NAME &TYPE_NAME::_ecs_set(ecs::Entity e, ecs::ComponentManager *cm,
							   TYPE_NAME &&mov_val);
TYPE_NAME *TYPE_NAME::_ecs_get(ecs::Entity e, const ecs::ComponentManager *cm);
void TYPE_NAME::_ecs_remove(ecs::Entity e, ecs::ComponentManager *cm);

void TYPE_NAME::_ecs_execute_observers_add(ecs::Entity e,
										   ecs::ComponentManager *cm);
void TYPE_NAME::_ecs_execute_observers_set(ecs::Entity e,
										   ecs::ComponentManager *cm);
void TYPE_NAME::_ecs_execute_observers_remove(ecs::Entity e,
											  ecs::ComponentManager *cm);

void TYPE_NAME::_ecs_assure(ecs::Entity e, ecs::World *w);
TYPE_NAME &TYPE_NAME::_ecs_access(ecs::Entity e, ecs::World *w);
TYPE_NAME &TYPE_NAME::_ecs_add(ecs::Entity e, ecs::World *w);
TYPE_NAME &TYPE_NAME::_ecs_set(ecs::Entity e, ecs::World *w,
							   const TYPE_NAME &val);
TYPE_NAME &TYPE_NAME::_ecs_set(ecs::Entity e, ecs::World *w,
							   TYPE_NAME &&mov_val);
TYPE_NAME *TYPE_NAME::_ecs_get(ecs::Entity e, const ecs::World *w);
void TYPE_NAME::_ecs_remove(ecs::Entity e, ecs::World *w);

void TYPE_NAME::_ecs_execute_observers_add(ecs::Entity e, ecs::World *w);
void TYPE_NAME::_ecs_execute_observers_set(ecs::Entity e, ecs::World *w);
void TYPE_NAME::_ecs_execute_observers_remove(ecs::Entity e, ecs::World *w);

void TYPE_NAME::_ecs_move_to_empty(TYPE_NAME &&src, TYPE_NAME &dst);
void TYPE_NAME::_ecs_copy_to_empty(const TYPE_NAME &src, TYPE_NAME &dst);
void TYPE_NAME::_ecs_move_to_existing(TYPE_NAME &&src, TYPE_NAME &dst);
void TYPE_NAME::_ecs_copy_to_existing(const TYPE_NAME &src, TYPE_NAME &dst);
void TYPE_NAME::_ecs_construct(TYPE_NAME *ptr);
void TYPE_NAME::_ecs_destruct(TYPE_NAME *ptr);

void TYPE_NAME::_ecs_serialize(struct serializer &ar, const TYPE_NAME &ptr);
void TYPE_NAME::_ecs_deserialize(struct deserializer &ar, TYPE_NAME &ptr);

void serialize(struct serializer &ar) const;
void deserialize(struct deserializer &ar);

#define ECS_TAG_TRAITS(TYPE_NAME)
using TYPE_NAME = ExampleTagPlayer;
ecs::TagTypeTraits *_ecs_tag_traits = nullptr;
const ecs::TagTypeTraits *TYPE_NAME::_ecs_register_tag();
const ecs::TagTypeTraits *TYPE_NAME::_ecs_get_tag_traits();

ecs::TagId TYPE_NAME::_ecs_tag_id = 0;
