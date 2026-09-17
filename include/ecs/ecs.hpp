#pragma once

#include <cstdint>

#include <string>
#include <vector>

namespace ecs
{
class World;
class ComponentManager;

struct Entity {
	uint32_t id;
	uint32_t version;
};

class ObserverArray
{
public:
	struct ObserverEntry {
		void (*on)(Entity entity, ComponentManager *manager, void *component);
	};

	std::vector<ObserverEntry> entries;

	void Add(ObserverArray entry);
	void ExecuteAllOn(Entity entity, ComponentManager *manager,
					  void *component);
};

struct TypeTraits {
	void (*const assure)(Entity entity, ComponentManager *manager);
	void *(*const access)(Entity entity, ComponentManager *manager);
	void *(*const add)(Entity entity, ComponentManager *manager);
	void *(*const set_copy)(Entity entity, ComponentManager *manager, const void *ptr);
	void *(*const set_move)(Entity entity, ComponentManager *manager, void *mov_ptr);
	void *(*const get)(Entity entity, const ComponentManager *manager);
	void (*const remove)(Entity entity, ComponentManager *manager);

	void (*const execute_observers_add)(Entity entity, ComponentManager *manager);
	void (*const execute_observers_set)(Entity entity, ComponentManager *manager);
	void (*const execute_observers_remove)(Entity entity, ComponentManager *manager);

	void (*const move_to_empty)(void *src, void *dst);
	void (*const copy_to_empty)(const void *src, void *dst);
	void (*const move_to_existing)(void *src, void *dst);
	void (*const copy_to_existing)(const void *src, void *dst);
	void (*const construct)(void *ptr);
	void (*const destruct)(void *ptr);

	void (*const serialize)(struct serializer &ar, const void *ptr);
	void (*const deserialize)(struct deserializer &ar, void *ptr);

	const char *type_name;
	const std::string name;
	const uint32_t bytes;
	const uint32_t alignement;
	const bool poco;
};

class ComponentBase
{
public:
	virtual ~ComponentBase();

	TypeTraits traits;

	// ... base class for component global data and component manager functions
};

struct ComponentId {
	uint32_t id;
};

struct ComponentEntry {
	void (*const optimize)(ComponentManager *manager);
	void (*const clear)(ComponentManager *manager);

	void (*const assure)(Entity entity, ComponentManager *manager);
	void *(*const access)(Entity entity, ComponentManager *manager);
	void *(*const add)(Entity entity, ComponentManager *manager);
	void *(*const set_scopy)(Entity entity, ComponentManager *manager,
							 const void *ptr);
	void *(*const set_move)(Entity entity, ComponentManager *manager,
							void *mov_ptr);
	void *(*const get)(Entity entity, const ComponentManager *manager);
	void (*const remove)(Entity entity, ComponentManager *manager);
	void (*const execute_observers_add)(Entity entity,
										ComponentManager *manager);
	void (*const execute_observers_set)(Entity entity,
										ComponentManager *manager);
	void (*const execute_observers_remove)(Entity entity,
										   ComponentManager *manager);
	// 	void (*const serialize)(Entity entity, const ComponentManager *manager);
	// 	void (*const deserialize)(Entity entity, ComponentManager *manager);

	TypeTraits *type_traits;
};

class ComponentManager
{
public:
	virtual ~ComponentManager();

	World *world;
	ComponentEntry componentEntry;
	// ...

	union {
		struct {
			ObserverArray add;
			ObserverArray set;
			ObserverArray remove;
		} on;
		ObserverArray array[3];
	} observers;
};

class World
{
public:
	void begin_tick();
	void end_tick();

	Entity add();
	void remove(Entity entity);

	template <typename T> void assure(Entity entity);
	template <typename T> T &access(Entity entity);
	template <typename T> T &add(Entity entity);
	template <typename T> T &set(Entity entity, const T &val);
	template <typename T> T &set(Entity entity, T &&mov_val);
	template <typename T> T *get(Entity entity) const;
	template <typename T> void remove(Entity entity);
	template <typename T> void execute_observers_add(Entity entity);
	template <typename T> void execute_observers_set(Entity entity);
	template <typename T> void execute_observers_remove(Entity entity);

	void assure(Entity entity, ComponentId component);
	void *access(Entity entity, ComponentId component);
	void *add(Entity entity, ComponentId component);
	void *set_copy(Entity entity, ComponentId component, const void *ptr);
	void *set_move(Entity entity, ComponentId component, void *mov_ptr);
	void *get(Entity entity, ComponentId component) const;
	void remove(Entity entity, ComponentId component);
	void execute_observers_add(Entity entity, ComponentId component);
	void execute_observers_set(Entity entity, ComponentId component);
	void execute_observers_remove(Entity entity, ComponentId component);

private:
};
} // namespace ecs
