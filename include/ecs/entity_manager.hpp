#pragma once

#include <vector>
#include <map>
#include <functional>

#include "types.hpp" // IWYU pragma: export

namespace ecs
{
class EntityManager
{
public:
	static inline constexpr uint32_t INVALID_ENTITY_ID = 0;
	static inline constexpr uint32_t INVALID_OFFSET = 0xFFFFFFFFu;

	Entity add();
	void remove(Entity entity);
	void clear();

	bool is_alive(Entity entity) const;
	bool is_alive_id(uint32_t id) const;
	uint32_t get_version(uint32_t id) const;
	uint32_t get_entity_count() const;
	uint32_t get_capacity() const;
	bool empty() const;

	Entity get_entity(uint32_t id) const;

	void for_each_alive(const std::function<void(Entity)> &fn) const;
	void for_each_alive(const std::function<void(Entity)> &fn);

	uint32_t get_component_offset(Entity entity, ComponentId component) const;

private:
	std::vector<uint32_t> entityVersion;
	std::vector<uint32_t> emptyEntityIds;
	std::vector<std::map<ComponentId, uint32_t>> componentsOffsets;
};
} // namespace ecs
