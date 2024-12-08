#include "display_utility.hpp"

void displayRoom(std::vector<char> room)
{
	for (int i = 0; i < 9; i++)
	{
		std::cout << room[i];
		if ((i + 1) % 3 == 0) std::cout << std::endl;
	}
}

void displayAllRooms()
{
	for (int i = 0; i < 15; i++)
	{
		std::cout << i << std::endl;
		displayRoom(rooms[i]);
		std::cout << std::endl;
	}
}

template<typename T>
void displayArr(T arr[], int length)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << arr[i];
		if (i != length - 1) std::cout << " ";
	}
}

void displayMapValues(char map[], int HEIGHT, int WIDTH)
{
	for (int i = 0; i < HEIGHT * WIDTH; i++)
	{
		std::cout << " " << int(map[i]);
		if ((i + 1) % WIDTH == 0) std::cout << std::endl;
	}
}

/// <summary>
/// prepares a buffer with the ascii represenatation of the rooms,
/// then prints it to the console
/// </summary>
/// <param name="map"></param>
/// <param name="HEIGHT"></param>
/// <param name="WIDTH"></param>
void displayMap(std::vector<char> map, int HEIGHT, int WIDTH, char block, char path, char uncharted, bool MERGED)
{

	int buffer_size = (MERGED) ? ((WIDTH * 2 + 1) * (HEIGHT * 2 + 1)) : (WIDTH * HEIGHT * 9);
	std::vector<char> buffer;
	for (int i = 0; i < buffer_size; i++) {
		buffer.push_back(uncharted);
	}
	for (int i = 0; i < HEIGHT * WIDTH; i++)
	{
		if (map[i] > 15) continue;
		std::vector<char>room = rooms[map[i]];
		// index / width * 9 = row
		// index % width * 3 = column
		// final index = row * width + column
		int row = (i / WIDTH) * ((MERGED) ? 1 : 9);
		int col = (i % WIDTH) * ((MERGED) ? 2 : 3);
		int element = MERGED ? (row * 2 * (2 * WIDTH + 1) + col) : (row * WIDTH + col);
		for (int j = 0; j < 9; j++) {
			int correction = j / 3;
			char symbol = room[j];
			if (symbol == '.') symbol = path;
			else if (symbol == '#') symbol = block;
			buffer[element + j % 3 + (MERGED ? (2 * WIDTH + 1) : (WIDTH * 3)) * correction] = symbol;
		}
	}
	for (int i = 0; i < buffer_size; i++) {
		std::cout << buffer[i];
		if ((i + 1) % (MERGED?(WIDTH*2+1):(WIDTH * 3)) == 0) std::cout << std::endl;
	}
}

void displayLine(char c, int length) {
	for (int i = 0; i < length; i++) {
		std::cout << c;
	}
	std::cout << std::endl;
}
