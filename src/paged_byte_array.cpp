#include <cassert>
#include <bit>
#include <limits>

#include "../include/ecs/paged_byte_array.hpp"

namespace ecs
{
PagedByteArray::~PagedByteArray()
{
	if (pages != nullptr) {
		for (uint32_t i = 0; i < pages_capacity; ++i) {
			free(pages[i]);
		}
	}
	free(pages);
	pages = nullptr;
	pages_count = 0;
	pages_capacity = 0;
	present_pages_count = 0;
	this->element_size = 0;
	this->page_elements = 0;
	page_elements_bit_offset = 0;
	page_mask = 0;
	elements_mask = 0;
}

void PagedByteArray::init(uint32_t element_size, uint32_t page_elements)
{
	this->~PagedByteArray();

	const bool valid_page_size = std::has_single_bit(page_elements);
	assert(element_size != 0);
	assert(valid_page_size);
	if (element_size == 0 || !valid_page_size) {
		return;
	}
	assert((element_size * page_elements) >= 64);
	assert(page_elements >= 16);

	this->element_size = element_size;
	this->page_elements = page_elements;
	page_elements_bit_offset = std::bit_width(page_elements) - 1;
	page_mask = (~0u) << page_elements_bit_offset;
	elements_mask = ~page_mask;
}

void *PagedByteArray::access(uint32_t element_id)
{
	assert(element_size);
	assert(page_elements);
	assert(element_id < 0x7FFFFFFF);
	uint32_t page = page_id_from_element_id(element_id);
	if (pages_capacity <= page) {
		uint32_t size = 16;
		while (size <= page) {
			if (size > UINT32_MAX / 2) {
				return nullptr;
			}
			size *= 2;
		}
		uint8_t **new_pages =
			(uint8_t **)realloc(pages, sizeof(uint8_t *) * size);
		if (new_pages == nullptr) {
			return nullptr;
		}
		pages = new_pages;
		memset(pages + pages_capacity, 0,
			   (size - pages_capacity) * sizeof(uint8_t *));
		pages_capacity = size;
	}
	if (pages[page] == nullptr) {
		if (pages_count <= page) {
			pages_count = page + 1;
		}
		pages[page] = (uint8_t *)malloc(element_size * page_elements);
		if (pages[page] == nullptr) {
			return nullptr;
		}
		if (memset_zero) {
			memset(pages[page], 0, element_size * page_elements);
		}
		present_pages_count++;
	}
	uint32_t id = element_id & elements_mask;
	return (void *)&(pages[page][static_cast<size_t>(id) * element_size]);
}

void *PagedByteArray::try_get(uint32_t element_id)
{
	const PagedByteArray *self = this;
	return (void *)self->try_get(element_id);
}

const void *PagedByteArray::try_get(uint32_t element_id) const
{
	assert(element_size);
	assert(page_elements);
	uint32_t page = page_id_from_element_id(element_id);
	if (!is_page_present(page)) {
		return nullptr;
	}
	uint32_t id = element_id & elements_mask;
	return (const void *)&(pages[page][id * element_size]);
}

uint32_t PagedByteArray::page_id_from_element_id(uint32_t element_id) const
{
	return element_id >> page_elements_bit_offset;
}
uint32_t PagedByteArray::first_element_in_page(uint32_t page_id) const
{
	return page_id << page_elements_bit_offset;
}

bool PagedByteArray::is_page_present(uint32_t page_id) const
{
	return pages != nullptr && page_id < pages_count && pages[page_id] != nullptr;
}

void PagedByteArray::remove_page(uint32_t page_id)
{
	if (pages == nullptr || pages_count <= page_id) {
		return;
	}
	if (pages[page_id] == nullptr) {
		return;
	}
	free(pages[page_id]);
	pages[page_id] = nullptr;
	present_pages_count--;
	for (; pages_count > 0 && pages[pages_count - 1] == nullptr;
		 --pages_count) {
	}
}

size_t PagedByteArray::get_memory_usage()
{
	return sizeof(uint8_t *) * pages_capacity +
		   (size_t)element_size * page_elements * present_pages_count;
}
} // namespace ecs
