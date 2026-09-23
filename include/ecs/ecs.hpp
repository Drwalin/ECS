#pragma once

#include <vector>
#include <memory>
#include <map>

#include "types.hpp" // IWYU pragma: export

namespace ecs
{
class ObserverArray
{
public:
	struct ObserverEntry {
		void (*on)(Entity entity, ComponentManager *manager, void *component);
	};

	void Add(ObserverArray entry);
	void ExecuteAllOn(Entity entity, World *world, void *component);

private:
	std::vector<ObserverEntry> entries;
};

class ComponentManager
{
public:
	ComponentManager();
	virtual ~ComponentManager();

	void RegisterObserver(ObserverType type, ObserverFunc observer);

protected:
	union {
		struct {
			ObserverArray add;
			ObserverArray set;
			ObserverArray remove;
		} on;
		ObserverArray array[3];
	} observers;
	TypeTraits traits;
};

class EntityManager
{
public:
	Entity add();
	void remove(Entity entity);
	void clear();

private:
	std::vector<uint32_t> entityVersion;
	std::vector<uint32_t> emptyEntityIds;
	std::vector<std::map<ComponentId, uint32_t>> componentsOffsets;
};

class World
{
public:
	World();
	~World();

	void begin_tick();
	void end_tick();

	Entity add();
	void remove(Entity entity);
	void clear();

	template <typename T> inline void assure(Entity entity);
	template <typename T> inline T &access(Entity entity);
	template <typename T> inline T &add(Entity entity);
	template <typename T> inline T &set(Entity entity, const T &val);
	template <typename T> inline T &set(Entity entity, T &&mov_val);
	template <typename T> inline T *get(Entity entity) const;
	template <typename T> inline void remove(Entity entity);
	template <typename T> inline void execute_observers(ObserverType type, Entity entity);

	void assure(Entity entity, ComponentId component);
	void *access(Entity entity, ComponentId component);
	void *add(Entity entity, ComponentId component);
	void *set_copy(Entity entity, ComponentId component, const void *ptr);
	void *set_move(Entity entity, ComponentId component, void *mov_ptr);
	void *get(Entity entity, ComponentId component) const;
	void remove(Entity entity, ComponentId component);
	void execute_observers(ObserverType type, Entity entity, ComponentId component);
	void execute_observers(ObserverType type, Entity entity, ComponentManager *man, void *comp);
	
	ComponentManager *get_component_manager(ComponentId id);
	
	void RegisterObserver(ObserverType type, ComponentId id,
						  ObserverFunc observer);

private:
	std::vector<std::unique_ptr<ComponentManager>> managers;
	EntityManager entityManager;
};

template <typename T> inline void World::assure(Entity entity)
{
	T::_ecs_assure(entity, this);
}
template <typename T> inline T &World::access(Entity entity)
{
	return T::_ecs_access(entity, this);
}
template <typename T> inline T &World::add(Entity entity)
{
	return T::_ecs_add(entity, this);
}
template <typename T> inline T &World::set(Entity entity, const T &val)
{
	return T::_ecs_set(entity, this, val);
}
template <typename T> inline T &World::set(Entity entity, T &&mov_val)
{
	return T::_ecs_set(entity, this, std::move(mov_val));
}
template <typename T> inline T *World::get(Entity entity) const
{
	return T::_ecs_get(entity, this);
}
template <typename T> inline void World::remove(Entity entity)
{
	T::_ecs_remove(entity, this);
}
template <typename T> inline void World::execute_observers(ObserverType type, Entity entity)
{
	execute_observers(type, entity, get_component_manager(T::_ecs_component_id));
}
} // namespace ecs
