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

# Copyright (C) 2022, C. R. Van West
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
