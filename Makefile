reference: provided.cpp reference.cpp
	c++ -D REFERENCE -o reference provided.cpp

mine: provided.cpp mine.cpp
	c++ -o mine provided.cpp

.PHONY: test
test: reference mine
	@./test.sh

.PHONY: clean
clean:
	-rm reference mine
