#pragma once

#include <cstdint>

#include <string>

struct StringOrInt {
	std::string s;
	uint32_t i;
};

struct StdString {
	std::string s;
};

namespace ecs
{
enum Density { SPARSE = 0, DENSE = 1 };
static inline constexpr uint32_t MAX_DENSE_COMPONENTS = 31;

struct DenseComponent {
	uint32_t byte_offset = 0; // x > 24 
	uint32_t bit_offset = 0; // 0 <= x <= 30
	uint32_t alignement = 0;
	uint32_t enabled = 0;
	
	uint32_t total_dense_components = 0;
	uint32_t total_alignement = 0;
	uint32_t total_size = 0;
};

enum ObserverType {
	OBSERVER_ADD = 0,
	OBSERVER_REMOVE = 1,
	OBSERVER_CHANGE = 2
};

class World;
class ComponentManager;
class TagManager;

struct Entity {
	uint32_t id;
	uint32_t version;
};

struct ComponentId {
	uint32_t id;
};

using ObserverFunc = void(Entity, World *, void *component);

struct TagId {
	uint32_t id;
};

struct TypeTraits {
	ecs::ComponentManager *(*const create_component_manager)();

	void (*const assure)(Entity, ComponentManager *);
	void *(*const access)(Entity, ComponentManager *);
	void *(*const add)(Entity, ComponentManager *);
	void *(*const set_copy)(Entity, ComponentManager *, const void *ptr);
	void *(*const set_move)(Entity, ComponentManager *, void *mov_ptr);
	void *(*const get)(Entity, const ComponentManager *);
	void (*const remove)(Entity, ComponentManager *);

	void (*const move_to_empty)(void *src, void *dst);
	void (*const copy_to_empty)(const void *src, void *dst);
	void (*const move_to_existing)(void *src, void *dst);
	void (*const copy_to_existing)(const void *src, void *dst);
	void (*const construct)(void *ptr);
	void (*const destruct)(void *ptr);

	void (*const serialize)(struct serializer &ar, const void *ptr);
	// deserialize into existing
	void (*const deserialize)(struct deserializer &ar, void *ptr);

	const char *type_name;
	const std::string name;
	const StringOrInt short_name; // used for serialzation
	const uint32_t bytes;
	const uint32_t alignement;
	const ComponentId component_id;
};

struct TagTypeTraits {
	const char *type_name;
	const StringOrInt short_type_name_or_id; // used for serialzation
	const TagId tag_id;
};
} // namespace ecs
