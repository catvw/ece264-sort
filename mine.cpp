#include <cstdint>

// minimum characters needed to check uniqueness
namespace Min_Chars {
constexpr const size_t last_name = 4; // holy shit!
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
		// effectively store in base-26
		result *= 26;
		result += to_convert[i] - 'A';
	}
	for (; i < chars; ++i) result *= 26;

	return result;
}

struct Data_Ref {
	uint32_t ssn;
	uint32_t last_name;
	uint64_t first_name;
	Data* data;

	inline void initialize(Data* data);
};

inline void Data_Ref::initialize(Data* data) {
	this->data = data;
	ssn = ssn_to_int<uint32_t>(data->ssn);
	last_name = string_to_int<uint32_t>(data->lastName,
	                                    Min_Chars::last_name);
	first_name = string_to_int<uint64_t>(data->firstName,
	                                     Min_Chars::first_name);
}

constexpr const size_t maximum_items = 1'010'000; // one percent over a million
Data_Ref entries[maximum_items];

void sortDataList(list<Data *> &l) {
	const size_t length = l.size();

	size_t index = 0;
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		entries[index++].initialize(*iter);

	index = 0;
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		*iter = entries[index++].data;
}
