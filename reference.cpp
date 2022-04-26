#include <algorithm>

constexpr const size_t maximum_items = 1'010'000; // one percent over a million
Data* entries[maximum_items];

void sortDataList(list<Data *> &l) {
	size_t index = 0;
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		entries[index++] = *iter;

	// reverse list for a lark
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		*iter = entries[--index];
}
