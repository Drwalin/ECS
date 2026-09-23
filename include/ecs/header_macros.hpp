#pragma once

#include "types.hpp" // IWYU pragma: export

#define ECS_TYPE_TRAITS_HEADER_ANY_DENSITY(                                    \
	TYPE_NAME, SHORT_NAME, INT_NAME, ALIGNEMENT, DENSITY, DENSITY_DECL)  \
public:                                                                        \
	static ecs::TypeTraits *_ecs_type_traits;                                  \
	static const ecs::TypeTraits *_ecs_register_type();                        \
                                                                               \
	constexpr static inline ecs::DenseComponent _ecs_dense = DENSITY_DECL;     \
	constexpr static inline ecs::Density _ecs_density = DENSITY;               \
	constexpr static inline const char *_ecs_type_name = #TYPE_NAME;           \
	constexpr static inline StringOrInt _ecs_name = {#TYPE_NAME, 0};           \
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
	static TYPE_NAME &_ecs_access(ecs::Entity, ecs::ComponentManager *);       \
	static TYPE_NAME &_ecs_add(ecs::Entity, ecs::ComponentManager *);          \
	static TYPE_NAME &_ecs_set(ecs::Entity, ecs::ComponentManager *,           \
							   const TYPE_NAME &val);                          \
	static TYPE_NAME &_ecs_set(ecs::Entity, ecs::ComponentManager *,           \
							   TYPE_NAME &&mov_val);                           \
	static TYPE_NAME *_ecs_get(ecs::Entity, const ecs::ComponentManager *);    \
	static void _ecs_remove(ecs::Entity, ecs::ComponentManager *);             \
                                                                               \
	static void _ecs_assure(ecs::Entity, ecs::World *);                        \
	static TYPE_NAME &_ecs_access(ecs::Entity, ecs::World *);                  \
	static TYPE_NAME &_ecs_add(ecs::Entity, ecs::World *);                     \
	static TYPE_NAME &_ecs_set(ecs::Entity, ecs::World *,                      \
							   const TYPE_NAME &val);                          \
	static TYPE_NAME &_ecs_set(ecs::Entity, ecs::World *,                      \
							   TYPE_NAME &&mov_val);                           \
	static TYPE_NAME *_ecs_get(ecs::Entity, const ecs::World *);               \
	static void _ecs_remove(ecs::Entity, ecs::World *);                        \
                                                                               \
	static void _ecs_move_to_empty(TYPE_NAME &&src, TYPE_NAME &dst);           \
	static void _ecs_copy_to_empty(const TYPE_NAME &src, TYPE_NAME &dst);      \
	static void _ecs_move_to_existing(TYPE_NAME &&src, TYPE_NAME &dst);        \
	static void _ecs_copy_to_existing(const TYPE_NAME &src, TYPE_NAME &dst);   \
	static void _ecs_construct(TYPE_NAME *ptr);                                \
	static void _ecs_destruct(TYPE_NAME *ptr);                                 \
                                                                               \
	static ecs::ComponentManager *_ecs_create_component_manager();             \
                                                                               \
	static void _ecs_serialize(struct serializer &ar, const TYPE_NAME &ptr);   \
	static void _ecs_deserialize(struct deserializer &ar, TYPE_NAME &ptr);     \
                                                                               \
	void serialize(struct serializer &ar) const;                               \
	void deserialize(struct deserializer &ar);

#define ECS_TYPE_TRAITS_HEADER_SPARSE(TYPE_NAME, SHORT_NAME, INT_NAME,   \
									  ALIGNEMENT)                              \
	ECS_TYPE_TRAITS_HEADER_ANY_DENSITY(TYPE_NAME, SHORT_NAME, INT_NAME,  \
									   ALIGNEMENT, ecs::SPARSE, {})

#define ECS_TYPE_TRAITS_HEADER_DENSE(TYPE_NAME, SHORT_NAME, INT_NAME,    \
									 ALIGNEMENT, DENSITY_DECL)                 \
	ECS_TYPE_TRAITS_HEADER_ANY_DENSITY(TYPE_NAME, SHORT_NAME, INT_NAME,  \
									   ALIGNEMENT, ecs::DENSE, DENSITY_DECL)

#define ECS_TAG_TRAITS(TYPE_NAME, SHORT_NAME, INT_NAME)                        \
public:                                                                        \
	static ecs::TagTypeTraits *_ecs_tag_traits;                                \
	static const ecs::TagTypeTraits *_ecs_register_tag();                      \
                                                                               \
	constexpr static inline const char *_ecs_type_name = #TYPE_NAME;           \
	constexpr static inline StringOrInt _ecs_short_name = {SHORT_NAME,         \
														   INT_NAME};          \
	static ecs::TagId _ecs_tag_id;
