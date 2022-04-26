constexpr const size_t maximum_items = 1'010'000; // one percent over a million
Data* entries[maximum_items];

int compare(Data* first, Data* second) {
	const int last_name_comp = first->lastName.compare(second->lastName);
	const int first_name_comp = first->firstName.compare(second->firstName);
	const int ssn_comp = first->ssn.compare(second->ssn);

	if (last_name_comp < 0) { // ordered by last name
		return -1;
	} else if (last_name_comp == 0) { // last names equal
		if (first_name_comp < 0) { // ordered by first name
			return -1;
		} else if (first_name_comp == 0) { // first names equal
			if (ssn_comp < 0) { // ordered enough by ssns
				return -1;
			} else if (ssn_comp == 0) { // exactly equal
				return 0;
			}
		}
	}

	return 1;
}

void insertion_sort(Data** start, Data** end) {
	const ptrdiff_t length = end - start;

	for (ptrdiff_t i = 0; i < length; ++i) {
		Data* elem = start[i];

		ptrdiff_t j = i;
		for (; j > 0; --j) {
			if (compare(elem, start[j - 1]) < 0) {
				// less than the current element, so should go earlier;
				// move the section forward
				start[j] = start[j - 1];
			} else {
				// found the spot!
				break;
			}
		}

		start[j] = elem;
	}
}

void sortDataList(list<Data *> &l) {
	const size_t length = l.size();

	size_t index = 0;
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		entries[index++] = *iter;

	insertion_sort(entries, entries + 1000);

	index = 0;
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		*iter = entries[index++];
}
