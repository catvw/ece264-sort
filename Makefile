reference: provided.cpp reference.cpp
	c++ -g -D REFERENCE -o reference provided.cpp

mine: provided.cpp mine.cpp lookup_tables.hpp
	c++ -g -o mine provided.cpp

.PHONY: test
test: reference mine
	@./test.sh

.PHONY: clean
clean:
	-rm reference mine output*.txt
