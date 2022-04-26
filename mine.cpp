constexpr const size_t maximum_items = 1'010'000; // one percent over a million
Data* entries[maximum_items];

void insertion_sort(Data** start, Data** end);

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

inline void swap(Data** first, Data** second) {
	Data* temp = *second;
	*second = *first;
	*first = temp;
}

inline void sort_three(Data** one, Data** two, Data** three) {
	if (compare(*one, *three) > 0) swap(one, three);
	if (compare(*one, *two) > 0) swap(one, two);
	if (compare(*two, *three) > 0) swap(two, three);
}

inline ptrdiff_t partition(Data** start, Data** end) {
	const ptrdiff_t length = end - start;
	const ptrdiff_t midway = length / 2;

	// put the median-of-three in the right place
	sort_three(start, start + midway, end - 1);
	Data* median = start[midway];
	swap(start + midway, end - 1);

	ptrdiff_t left = 0;
	ptrdiff_t right = length - 2;

	while (true) {
		while (compare(median, start[left]) > 0) ++left;
		while (compare(median, start[right]) < 0 && right > left) --right;

		if (right <= left) break;

		swap(start[left], start[right]);
	}

	// swap the pivot back to where it needs to go
	swap(start + left, end - 1);

	return left;
}

void quick_sort(Data** start, Data** end) {
	const ptrdiff_t length = end - start;

	if (length < 20) {
		insertion_sort(start, end);
		return;
	}

	const ptrdiff_t midway = partition(start, end);
	quick_sort(start, start + midway);
	quick_sort(start + midway + 1, end);
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

	quick_sort(entries, entries + SORT_LENGTH);

	index = 0;
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		*iter = entries[index++];
}
