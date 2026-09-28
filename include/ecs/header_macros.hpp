#pragma once

#include "types.hpp" // IWYU pragma: export

#define ECS_TYPE_TRAITS_HEADER_ANY_DENSITY(T, SHORT_NAME, INT_NAME,            \
										   ALIGNEMENT, DENSITY, ...)           \
public:                                                                        \
	static ecs::TypeTraits *_ecs_type_traits;                                  \
	static const ecs::TypeTraits *_ecs_register_type();                        \
                                                                               \
	constexpr static inline ecs::DenseComponent _ecs_dense = __VA_ARGS__;      \
	constexpr static inline ecs::Density _ecs_density = DENSITY;               \
	constexpr static inline const char *_ecs_type_name = #T;                   \
	constexpr static inline StringOrInt _ecs_name = {#T, 0};                   \
	constexpr static inline StringOrInt _ecs_short_name = {SHORT_NAME,         \
														   INT_NAME};          \
	constexpr static inline uint32_t _ecs_custom_alignement = ALIGNEMENT;      \
                                                                               \
	static ecs::ComponentId _ecs_component_id;                                 \
                                                                               \
	static ecs::ComponentManager *_ecs_access_component_manager(ecs::World *); \
	static ecs::ComponentManager *_ecs_get_component_manager(ecs::World *);    \
	static const ecs::ComponentManager *_ecs_get_component_manager(            \
		const ecs::World *);                                                   \
                                                                               \
	static void _ecs_assure(ecs::Entity, ecs::ComponentManager *);             \
	static T &_ecs_access(ecs::Entity, ecs::ComponentManager *);               \
	static T &_ecs_add(ecs::Entity, ecs::ComponentManager *);                  \
	static T &_ecs_set(ecs::Entity, ecs::ComponentManager *, const T &val);    \
	static T &_ecs_set(ecs::Entity, ecs::ComponentManager *, T &&mov_val);     \
	static T *_ecs_get(ecs::Entity, const ecs::ComponentManager *);            \
	static void _ecs_remove(ecs::Entity, ecs::ComponentManager *);             \
                                                                               \
	static void _ecs_assure(ecs::Entity, ecs::World *);                        \
	static T &_ecs_access(ecs::Entity, ecs::World *);                          \
	static T &_ecs_add(ecs::Entity, ecs::World *);                             \
	static T &_ecs_set(ecs::Entity, ecs::World *, const T &val);               \
	static T &_ecs_set(ecs::Entity, ecs::World *, T &&mov_val);                \
	static T *_ecs_get(ecs::Entity, const ecs::World *);                       \
	static void _ecs_remove(ecs::Entity, ecs::World *);                        \
                                                                               \
	static void _ecs_move_to_empty(T &&src, T &dst);                           \
	static void _ecs_copy_to_empty(const T &src, T &dst);                      \
	static void _ecs_move_to_existing(T &&src, T &dst);                        \
	static void _ecs_copy_to_existing(const T &src, T &dst);                   \
	static void _ecs_construct(T *ptr);                                        \
	static void _ecs_destruct(T *ptr);                                         \
                                                                               \
	static ecs::ComponentManager *_ecs_create_component_manager();             \
                                                                               \
	static void _ecs_serialize(struct serializer &ar, const T &ptr);           \
	static void _ecs_deserialize(struct deserializer &ar, T &ptr);             \
                                                                               \
	static void (*_ecs_serialize_temporal)(struct serializer & ar,             \
										   const T &ptr, ecs::World *);        \
	static void (*_ecs_deserialize_temporal)(struct deserializer & ar,         \
											 T & ptr, ecs::World *);           \
	static void (*_ecs_serialize_permanent)(struct serializer & ar,            \
											const T &ptr, ecs::World *);       \
	static void (*_ecs_deserialize_permanent)(struct deserializer & ar,        \
											  T & ptr, ecs::World *);          \
                                                                               \
	void serialize(struct serializer &ar) const;                               \
	void deserialize(struct deserializer &ar);

#define ECS_TYPE_TRAITS_HEADER_SPARSE(T, SHORT_NAME, INT_NAME, ALIGNEMENT)     \
	ECS_TYPE_TRAITS_HEADER_ANY_DENSITY(T, SHORT_NAME, INT_NAME, ALIGNEMENT,    \
									   ecs::SPARSE, {0, 0, 0, 0, 0, 0, 0})

#define ECS_TYPE_TRAITS_HEADER_DENSE(T, SHORT_NAME, INT_NAME, ALIGNEMENT, ...) \
	ECS_TYPE_TRAITS_HEADER_ANY_DENSITY(T, SHORT_NAME, INT_NAME, ALIGNEMENT,    \
									   ecs::DENSE, __VA_ARGS__)

#define ECS_TAG_TRAITS(T, SHORT_NAME, INT_NAME)                                \
public:                                                                        \
	static ecs::TagTypeTraits *_ecs_tag_traits;                                \
	static const ecs::TagTypeTraits *_ecs_register_tag();                      \
                                                                               \
	constexpr static inline const char *_ecs_type_name = #T;                   \
	constexpr static inline StringOrInt _ecs_short_name = {SHORT_NAME,         \
														   INT_NAME};          \
	static ecs::TagId _ecs_tag_id;
