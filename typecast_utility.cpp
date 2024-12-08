#include "typecast_utility.hpp"

bool isInt(char str[]) {
	int size = strlen(str);
	bool negative = 0;


	if (size < 1) return false;
	if (str[0] == '-') negative = 1;
	
	if (negative && (size == 1)) return false;
	for (int i = (int)negative; i < size; i++) {
		if (!std::isdigit(str[i])) return false;
	}
	return true;
}