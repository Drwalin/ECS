#pragma once

#include <vector>

#include "types.hpp" // IWYU pragma: export

namespace ecs
{
class ObserverArray
{
public:
	struct ObserverEntry {
		ObserverFunc on;
	};

	static inline ObserverEntry make_entry(ObserverFunc observer);

	void add(ObserverEntry entry);

	void execute_all_on(Entity entity, World *world, void *component);

private:
	std::vector<ObserverEntry> entries;
};

class ComponentManager
{
public:
	explicit ComponentManager(const TypeTraits &traits);
	ComponentManager() = delete;
	virtual ~ComponentManager();

	const TypeTraits &get_traits() const;
	const TypeTraits *traits_ptr() const; // nullptr when not set
	ComponentId get_component_id() const;

	void register_observer(ObserverType type, ObserverFunc observer);
	void unregister_observer(ObserverType type, ObserverFunc observer);
	void call_observers(World *world, ObserverType type, Entity entity,
						void *component);

protected:
	const TypeTraits traits;
	union {
		struct {
			ObserverArray add;
			ObserverArray set;
			ObserverArray remove;
		} on;
		ObserverArray array[OBSERVER_TYPE_COUNT];
	} observers;
};
} // namespace ecs
