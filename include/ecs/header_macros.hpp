#pragma once

#include "types.hpp" // IWYU pragma: export

#define ECS_TYPE_TRAITS_HEADER(TYPE_NAME, SHORT_NAME_OR_INT, POCO, ALIGNEMENT) \
	static const ecs::TypeTraits *_ecs_get_type_traits();                      \
                                                                               \
	constexpr static inline const char *_ecs_type_name = #TYPE_NAME;           \
	constexpr static inline std::string _ecs_name = #TYPE_NAME;                \
	constexpr static inline StringOrInt _ecs_short_type_name_or_id =           \
		SHORT_NAME_OR_INT;                                                     \
	constexpr static inline uint32_t _ecs_custom_alignement = ALIGNEMENT;      \
	constexpr static inline bool _ecs_poco = POCO;                             \
                                                                               \
	static ecs::ComponentId _ecs_component_id;                                 \
	static ecs::ComponentId _ecs_get_component_id();                           \
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
	static void _ecs_execute_observers_add(ecs::Entity,                        \
										   ecs::ComponentManager *);           \
	static void _ecs_execute_observers_set(ecs::Entity,                        \
										   ecs::ComponentManager *);           \
	static void _ecs_execute_observers_remove(ecs::Entity,                     \
											  ecs::ComponentManager *);        \
                                                                               \
	static void _ecs_move_to_empty(TYPE_NAME &&src, TYPE_NAME &dst);           \
	static void _ecs_copy_to_empty(const TYPE_NAME &src, TYPE_NAME &dst);      \
	static void _ecs_move_to_existing(TYPE_NAME &&src, TYPE_NAME &dst);        \
	static void _ecs_copy_to_existing(const TYPE_NAME &src, TYPE_NAME *dst);   \
	static void _ecs_construct(TYPE_NAME *ptr);                                \
	static void _ecs_destruct(TYPE_NAME *ptr);                                 \
                                                                               \
	static void _ecs_serialize(struct serializer &ar, const TYPE_NAME &ptr);   \
	static void _ecs_deserialize(struct deserializer &ar, TYPE_NAME &ptr);     \
                                                                               \
	void serialize(struct serializer &ar) const;                               \
	void deserialize(struct deserializer &ar);

#define ECS_TAG_TRAITS(TYPE_NAME, SHORT_NAME_OR_INT)                           \
	static const ecs::TagTraits *_ecs_get_tag_traits();                        \
                                                                               \
	constexpr static inline const char *_ecs_type_name = #TYPE_NAME;           \
	constexpr static inline std::string _ecs_name = _ecs_type_name;            \
	constexpr static inline StringOrInt _ecs_short_type_name_or_id =           \
		SHORT_NAME_OR_INT;                                                     \
	static ecs::TagId _ecs_tag_id;
