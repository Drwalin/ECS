#pragma once

#include <string_view>

#include "types.hpp"

namespace ecs
{
class TypeRegistry
{
public:
	static ComponentId GenerateNewTypeId();
	static void RegisterType(TypeTraits *tt);

	static const TypeTraits *GetTypeTraitsByName(std::string_view name);
	static const TypeTraits *GetTypeTraitsByName(const std::string &name);
	static const TypeTraits *GetTypeTraitsById(ComponentId id);
};

class TagTypeRegistry
{
public:
	static TagId GenerateNewTypeId();
	static void RegisterType(TypeTraits *tt);

	static const TagTypeTraits *GetTypeTraitsByName(std::string_view name);
	static const TagTypeTraits *GetTypeTraitsByName(const std::string &name);
	static const TagTypeTraits *GetTypeTraitsById(TagId id);
};
} // namespace ecs
