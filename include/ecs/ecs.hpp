#pragma once

#include <vector>

#include "types.hpp" // IWYU pragma: export

namespace ecs
{
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

class ComponentBase
{
public:
	virtual ~ComponentBase();

	TypeTraits traits;

	// ... base class for component global data and component manager functions
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
