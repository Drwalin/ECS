#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "types.hpp"
#include "entity_manager.hpp"
#include "dense_component_manager.hpp"

namespace ecs
{
class World
{
public:
	World();
	~World();

	World(const World &) = delete;
	World &operator=(const World &) = delete;
	World(World &&) = delete;
	World &operator=(World &&) = delete;

	void begin_tick();
	void end_tick();

	Entity add();
	void remove(Entity entity);
	void clear();

	bool is_alive(Entity entity) const;
	uint32_t get_entity_count() const;
	bool empty() const;

	void for_each_entity(const std::function<void(Entity)> &fn) const;
	void for_each_entity(const std::function<void(Entity)> &fn);

	template <typename T> inline void assure(Entity entity);
	template <typename T> inline T &access(Entity entity);
	template <typename T> inline T &add(Entity entity);
	template <typename T> inline T &set(Entity entity, const T &val);
	template <typename T> inline T &set(Entity entity, T &&mov_val);
	template <typename T> inline T *get(Entity entity) const;
	template <typename T> inline bool has(Entity entity) const;
	template <typename T> inline void remove(Entity entity);
	template <typename T>
	inline void execute_observers(ObserverType type, Entity entity);
	template <typename T>
	inline void execute_observers(ObserverType type, Entity entity, T *ptr);

	void assure(Entity entity, ComponentId component);
	void *access(Entity entity, ComponentId component);
	void *add(Entity entity, ComponentId component);
	void *set_copy(Entity entity, ComponentId component, const void *ptr);
	void *set_move(Entity entity, ComponentId component, void *mov_ptr);
	void *get(Entity entity, ComponentId component) const;
	bool has(Entity entity, ComponentId component) const;
	void remove(Entity entity, ComponentId component);
	void execute_observers(ObserverType type, Entity entity,
						   ComponentId component);
	void execute_observers(ObserverType type, Entity entity,
						   ComponentManager *man, void *comp);

	// managers are created on first access for a registered component id
	ComponentManager *access_component_manager(ComponentId id);
	ComponentManager *get_component_manager(ComponentId id);
	const ComponentManager *get_component_manager(ComponentId id) const;

	EntityManager &access_entity_manager();
	const EntityManager &get_entity_manager() const;

	DenseComponentManager &get_dense_component_manager();
	const DenseComponentManager &get_dense_component_manager() const;

	void register_observer(ObserverType type, ComponentId id,
						   ObserverFunc observer);

	void
	for_each_component(Entity entity,
					   std::function<void(World *, Entity, ComponentManager *,
										  void *component)>
						   func);
	void
	for_each_component(Entity entity,
					   std::function<void(World *, Entity, ComponentManager *,
										  const void *component)>
						   func) const;

private:
	void flush_deferred_removals(); // TODO: is it required or are components
									// removed instantly?

	std::vector<std::unique_ptr<ComponentManager>> managers;
	std::vector<Entity> deferredRemovals; // TODO: is it needed?
	DenseComponentManager denseComponentManager;
	EntityManager entityManager;
	bool tickActive = false;
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
template <typename T> inline bool World::has(Entity entity) const
{
	return get<T>(entity) != nullptr;
}
template <typename T> inline void World::remove(Entity entity)
{
	T::_ecs_remove(entity, this);
}
template <typename T>
inline void World::execute_observers(ObserverType type, Entity entity)
{
	execute_observers(type, entity, T::_ecs_component_id);
}
template <typename T>
inline void World::execute_observers(ObserverType type, Entity entity, T *ptr)
{
	execute_observers(type, entity, get_component_manager(T::_ecs_component_id),
					  ptr);
}
} // namespace ecs
