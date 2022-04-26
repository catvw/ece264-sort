#include <algorithm>

constexpr const size_t maximum_items = 1'010'000; // one percent over a million
Data* entries[maximum_items];

bool are_ordered(Data* first, Data* second) {
	const int last_name_comp = first->lastName.compare(second->lastName);
	const int first_name_comp = first->firstName.compare(second->firstName);
	const int ssn_comp = first->ssn.compare(second->ssn);

	if (last_name_comp < 0) { // ordered by last name
		return true;
	} else if (last_name_comp == 0) { // last names equal
		if (first_name_comp < 0) { // ordered by first name
			return true;
		} else if (first_name_comp == 0) { // first names equal
			if (ssn_comp < 0) { // ordered enough by ssns
				return true;
			}
		}
	}

	return false; // not ordered yet, or equal
}

void sortDataList(list<Data *> &l) {
	const size_t length = l.size();

	size_t index = 0;
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		entries[index++] = *iter;

	sort(entries, entries + length, are_ordered);

	index = 0;
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		*iter = entries[index++];
}
