#pragma once

#include <string>
#include <string_view>

#include "types.hpp"

namespace ecs
{
class TypeRegistry
{
public:
	static inline constexpr ComponentId INVALID_COMPONENT_ID = {0};

	static ComponentId GenerateNewTypeId();
	static void RegisterType(TypeTraits *tt);

	static const TypeTraits *GetTypeTraitsByName(std::string_view name);
	static const TypeTraits *GetTypeTraitsByName(const std::string &name);
	static const TypeTraits *GetTypeTraitsById(ComponentId id);
	static const TypeTraits *
	GetTypeTraitsByShortName(const StringOrInt &short_name);

	static uint32_t GetRegisteredTypeCount();
};

class TagTypeRegistry
{
public:
	static inline constexpr TagId INVALID_TAG_ID = {0};

	static TagId GenerateNewTypeId();
	static void RegisterType(TagTypeTraits *tt);

	static const TagTypeTraits *GetTypeTraitsByName(std::string_view name);
	static const TagTypeTraits *GetTypeTraitsByName(const std::string &name);
	static const TagTypeTraits *GetTypeTraitsById(TagId id);
	static const TagTypeTraits *
	GetTypeTraitsByShortName(const StringOrInt &short_name);

	static uint32_t GetRegisteredTypeCount();
};
} // namespace ecs
