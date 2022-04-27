#include <cstdint>

// minimum characters needed to check uniqueness
namespace Min_Chars {
constexpr const size_t last_name = 9;
constexpr const size_t first_name = 9;
}

template<typename Integer>
constexpr inline Integer ssn_to_int(const string& to_convert) {
	return 100000000*(to_convert[ 0] & 0xf)
	      + 10000000*(to_convert[ 1] & 0xf)
	       + 1000000*(to_convert[ 2] & 0xf)
	        + 100000*(to_convert[ 4] & 0xf)
	         + 10000*(to_convert[ 5] & 0xf)
	          + 1000*(to_convert[ 7] & 0xf)
	           + 100*(to_convert[ 8] & 0xf)
	            + 10*(to_convert[ 9] & 0xf)
	             + 1*(to_convert[10] & 0xf);
}

/* enters the given number of characters from the given string into the given
   integer, most-significant-place-justified. only for CAPITALIZED A-Z
   strings... fine for this */
template<typename Integer>
constexpr inline Integer string_to_int(const string& to_convert,
                                       const size_t chars) {
	const size_t string_length = to_convert.length();
	const size_t first_pass = string_length < chars ? string_length : chars;

	Integer result = 0;
	size_t i = 0;
	for (; i < first_pass; ++i) {
		// effectively store in base-27
		result *= 27;
		result += to_convert[i] - 'A' + 1;
	}
	for (; i < chars; ++i) result *= 27;

	return result;
}

struct Data_Ref {
	uint32_t ssn;
	uint64_t last_name;
	uint64_t first_name;
	Data* data;

	inline void initialize(Data* data);
};

inline void Data_Ref::initialize(Data* data) {
	this->data = data;
	ssn = ssn_to_int<uint32_t>(data->ssn);
	last_name = string_to_int<uint64_t>(data->lastName,
	                                    Min_Chars::last_name);
	first_name = string_to_int<uint64_t>(data->firstName,
	                                     Min_Chars::first_name);
}

template<size_t Bin_Count, size_t Bin_Size>
struct Bin_Array {
	static constexpr const size_t max_size = Bin_Count;

	struct Bin {
		static constexpr const size_t max_size = Bin_Size;

		size_t size;
		Data_Ref contents[Bin_Size];

		inline Bin() : size(0) { }
		inline Data_Ref operator[](size_t index) { return contents[index]; }
		inline void push(Data_Ref& next) { contents[size++] = next; }
	};

	Bin bins[Bin_Count];

	inline Bin_Array() { }
	inline Bin& operator[](size_t index) { return bins[index]; }
};

constexpr const size_t maximum_items = 1'010'000; // one percent over a million
Data_Ref entries[maximum_items];

constexpr const uint_fast8_t radix_bits = 8;
constexpr const size_t radix_base = 1 << radix_bits;
constexpr const size_t radix_mask = radix_base - 1;
constexpr const uint_fast8_t max_radix_shift_ssn = 32 - radix_bits;
constexpr const uint_fast8_t max_radix_shift_first = 48;
constexpr const uint_fast8_t max_radix_shift_last = 48;

constexpr const size_t bin_size = maximum_items; // kind of large
Bin_Array<radix_base, bin_size> bin_array;

void radix_sort_ssns(const size_t count) {
	size_t shift = 0;

	while (true) {
		for (size_t i = 0; i < count; ++i) {
			const uint32_t ssn = entries[i].ssn;
			const size_t bin = (ssn >> shift) & radix_mask;
			bin_array[bin].push(entries[i]);
		}

		// TODO: add a bin iterator that makes this easy
		size_t entry = 0;
		for (size_t bin = 0; bin < radix_base; ++bin) {
			for (size_t i = 0; i < bin_array[bin].size; ++i) {
				entries[entry++] = bin_array[bin][i];
			}
			bin_array[bin].size = 0;
		}

		if (shift == max_radix_shift_ssn) break;
		shift += radix_bits;
	}
}

void radix_sort_first_names(const size_t count) {
	size_t shift = 0;

	while (true) {
		for (size_t i = 0; i < count; ++i) {
			const uint64_t first_name = entries[i].first_name;
			const size_t bin = (first_name >> shift) & radix_mask;
			bin_array[bin].push(entries[i]);
		}

		// TODO: add a bin iterator that makes this easy
		size_t entry = 0;
		for (size_t bin = 0; bin < radix_base; ++bin) {
			for (size_t i = 0; i < bin_array[bin].size; ++i) {
				entries[entry++] = bin_array[bin][i];
			}
			bin_array[bin].size = 0;
		}

		if (shift == max_radix_shift_first) break;
		shift += radix_bits;
	}
}

void radix_sort_last_names(const size_t count) {
	size_t shift = 0;

	while (true) {
		for (size_t i = 0; i < count; ++i) {
			const uint64_t last_name = entries[i].last_name;
			const size_t bin = (last_name >> shift) & radix_mask;
			bin_array[bin].push(entries[i]);
		}

		// TODO: add a bin iterator that makes this easy
		size_t entry = 0;
		for (size_t bin = 0; bin < radix_base; ++bin) {
			for (size_t i = 0; i < bin_array[bin].size; ++i) {
				entries[entry++] = bin_array[bin][i];
			}
			bin_array[bin].size = 0;
		}

		if (shift == max_radix_shift_last) break;
		shift += radix_bits;
	}
}

void sortDataList(list<Data *> &l) {
	const size_t length = l.size();

	size_t index = 0;
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		entries[index++].initialize(*iter);

	radix_sort_ssns(SORT_LENGTH);
	radix_sort_first_names(SORT_LENGTH);
	radix_sort_last_names(SORT_LENGTH);

	index = 0;
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		*iter = entries[index++].data;
}
