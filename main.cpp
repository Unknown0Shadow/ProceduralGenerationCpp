#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif //IOSTREAM_H
#ifndef MAP_n_VECTOR
#define MAP_n_VECTOR
#include <unordered_map>
#include <vector>
#endif //MAP_n_VECTOR
#include "rooms.hpp"
#include "display_utility.hpp"
#include <random>
#include <queue>
#include <time.h>
#include <cstring>

const char EMPTY_CELL = 127;

void generateMap(std::vector<char>& dest, short height, short width, bool CONTINUITY, bool DEBUG);
void pushLaunchOption(std::queue<char> &queue, char);

int main(int argc, char** argv)
{
	short HEIGHT = 0;
	short WIDTH = 0;
	char BLOCK = 178;
	char PATH = 176;
	char UNCHARTED = '.';
	bool MERGED = false;
	bool CONTINUITY = false;
	bool DEBUG = false;

	// launch options
	std::queue<char> flags;
	if (argc > 1)
	{
		// -w width, -h height, -b block, -p path, -u uncharted
		// -c continuity, -d debug mode
		// example: proceduralGenerator.exe - w 20 - h 10 - c - b #  - p .
		for (int i = 1; i < argc; i++)
		{
			if ((strlen(argv[i]) != 2) && (flags.size() == 0))
			{
				std::cout << "unrecognized argument " << argv[i] << std::endl;
				continue;
			}
			if ((strncmp(argv[i], "-w", 2) == 0))
			{
				pushLaunchOption(flags, 'w');
			}
			else if ((strncmp(argv[i], "-h", 2) == 0))
			{
				pushLaunchOption(flags, 'h');
			}
			else if ((strncmp(argv[i], "-b", 2) == 0))
			{
				pushLaunchOption(flags, 'b');
			}
			else if ((strncmp(argv[i], "-p", 2) == 0))
			{
				pushLaunchOption(flags, 'p');
			}
			else if ((strncmp(argv[i], "-u", 2) == 0))
			{
				pushLaunchOption(flags, 'u');
			}
			else if ((strncmp(argv[i], "-c", 2) == 0))
			{
				pushLaunchOption(flags, 'x');
				CONTINUITY = true;
			}
			else if ((strncmp(argv[i], "-d", 2) == 0))
			{
				pushLaunchOption(flags, 'x');
				DEBUG = true;
			}
			else if ((strncmp(argv[i], "-m", 2) == 0))
			{
				pushLaunchOption(flags, 'x');
				MERGED = true;
			}
			else if (flags.front() == 'w')
			{
				WIDTH = atoi(argv[i]);
				if (WIDTH < 4 || WIDTH > 50) WIDTH = 0;
				flags.pop();
			}
			else if (flags.front() == 'h')
			{
				HEIGHT = atoi(argv[i]);
				if (HEIGHT < 4 || HEIGHT > 50) HEIGHT = 0;
				flags.pop();
			}
			else if (flags.front() == 'b')
			{
				BLOCK = argv[i][0];
				flags.pop();
			}
			else if (flags.front() == 'p')
			{
				PATH = argv[i][0];
				flags.pop();
			}
			else if (flags.front() == 'u')
			{
				UNCHARTED = argv[i][0];
				flags.pop();
			}
		}
		if (flags.size() != 0) {
			std::cout << "Unhandled parameter -" << flags.front() << std::endl;
			flags.pop();
		}
	}
	else { // if the app was launched without launch options
			char input[2] = { ' ' };
			char answer = 'n';
			std::cout << "Wall symbol = ";
			std::cin.getline(input, 2);
			std::cin.clear();
			BLOCK = input[0];
			std::cout << "Path symbol = ";
			std::cin.getline(input, 2);
			std::cin.clear();
			PATH = input[0];
			std::cout << "Uncharted symbol = ";
			std::cin.getline(input, 2);
			std::cin.clear();
			UNCHARTED = input[0];
			std::cout << "Merged walls? (y/n) : ";
			answer = 'n';
			std::cin >> answer;
			std::cin.clear();
			if (answer == 'y' || answer == 'Y') MERGED = true;
			else MERGED = false;
			std::cout << "Continuous generation? (y/n) : ";
			answer = 'n';
			std::cin >> answer;
			std::cin.clear();
			if (answer == 'y' || answer == 'Y') CONTINUITY = true;
			else CONTINUITY = false;
	}
	while (std::cin.fail() || WIDTH < 4 || WIDTH > 50)
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		std::cout << "Map width (between 4 and 50) = ";
		std::cin >> WIDTH;
	} 
	while (std::cin.fail() || HEIGHT < 4 || HEIGHT > 50)
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		std::cout << "Map height (between 4 and 50) = ";
		std::cin >> HEIGHT;
	}
	if(std::cin.fail()) std::cin.ignore();
	
	// app logic
	std::vector<char> generatedMap;
	for (int i = 0; i < HEIGHT * WIDTH; i++) {
		generatedMap.push_back(EMPTY_CELL);
	}
	srand((unsigned int)time(nullptr));
	generateMap(generatedMap, HEIGHT, WIDTH, CONTINUITY, DEBUG);
	displayMap(generatedMap, HEIGHT, WIDTH, BLOCK, PATH, UNCHARTED, MERGED);
	/* // uncomment these lines to display both merged and unmerged mazes;
	std::cout << "Normal sized map" << std::endl;
	displayMap(generatedMap, HEIGHT, WIDTH, BLOCK, PATH, UNCHARTED, false);
	std::cout << "Compressed map" << std::endl;
	displayMap(generatedMap, HEIGHT, WIDTH, BLOCK, PATH, UNCHARTED, true);
	//*/

	// end
	system("PAUSE");
	return 0;
}

void pushLaunchOption(std::queue<char> &queue, char c) {
	if (queue.size() != 0) {
		std::cout << "Unhandled parameter -" << queue.front() << std::endl;
		queue.pop();
	}
	if (c != 'x') queue.push(c);
}


/// <summary>
/// starting from the middle of the array, expands outwards with random rooms
/// </summary>
/// <param name="dest"></param>
void generateMap(std::vector<char>& dest, short HEIGHT, short WIDTH, bool CONTINUITY, bool DEBUG)
{
	std::vector<char> available;
	std::queue<int> to_process;
	char params[4] = { 0, 0, 0, 0 }; // binary reversed, 0 path, 1 wall, 2 any

	int current = HEIGHT * WIDTH / 2 + (HEIGHT % 2 == 0) * (WIDTH / 2); //middle
	// middle is H*W/2 + W/2 for even HEIGHT, H*W/2 for odd HEIGHT
	if (DEBUG) {
		std::cout << "HEIGHT * WIDTH / 2 + ((HEIGHT * WIDTH) % 2 == 0): " << HEIGHT << "_" << WIDTH << "_" << (HEIGHT * WIDTH) % 2 << "_" << WIDTH / 2 << std::endl;
		std::cout << "middle " << current << "_" << ((HEIGHT * WIDTH) % 2 == 0) * (WIDTH / 2) << std::endl;
	}
	dest[current] = 0;
	to_process.push(current - WIDTH); // up
	to_process.push(current + 1); // right
	to_process.push(current + WIDTH); // down
	to_process.push(current - 1); // left

	int loop_nr = 1;
	while (!to_process.empty())
	{
		// clean up
		available.clear();
		std::fill_n(params, 4, -1);

		// pop
		current = to_process.front();
		to_process.pop();

		if (DEBUG) std::cout << "Current node: " << current << std::endl;

		// check neighbourhood relations 1 up, 2 right, 4 down, 8 left
		if (dest[current] != EMPTY_CELL) continue; // it is already set

		// up
		if (current - WIDTH >= 0) { // not outside bounds
			if (dest[current - WIDTH] != EMPTY_CELL) // is set => must fit
			{
				if ((dest[current - WIDTH] & 4) == 0) params[0] = 0; // path
				else params[0] = 1; // dead end
				if (DEBUG) {
					std::cout << "Up " << (int)params[0] << " stats: " << current - WIDTH << "_>_0" << std::endl;
					displayRoom(rooms[dest[current - WIDTH]]);
				}
			}
			else // is not set
			{
				if (DEBUG) std::cout << "Up Empty" << std::endl;
				params[0] = 2; // undetermined => to be chosen randomly
				if (!CONTINUITY) to_process.push(current - WIDTH); // queue up
			}
		}
		else {
			if (DEBUG) std::cout << "Can't go up: " << current - WIDTH << std::endl;
			params[0] = 1; // out of bounds => wall
		}

		// right
		if ((current + 1 < HEIGHT * WIDTH) && ((current + 1) % WIDTH != 0))
		{
			if (dest[current + 1] != EMPTY_CELL)
			{
				if ((dest[current + 1] & 8) == 0) params[1] = 0;
				else params[1] = 1;
				if (DEBUG) {
					std::cout << "Right " << (int)params[1] << " stats: " << current + 1 << "_>_0" << std::endl;
					displayRoom(rooms[dest[current + 1]]);
				}
			}
			else
			{
				if (DEBUG) std::cout << "Right Empty" << std::endl;
				params[1] = 2;
				if (!CONTINUITY) to_process.push(current + 1);
			}
		}
		else {
			if (DEBUG) std::cout << "Can't go right: " << current + 1 << std::endl;
			params[1] = 1;
		}

		// down
		if (current + WIDTH < HEIGHT * WIDTH)
		{
			if (dest[current + WIDTH] != EMPTY_CELL)
			{
				if ((dest[current + WIDTH] & 1) == 0) params[2] = 0;
				else params[2] = 1;
				if (DEBUG) {
					std::cout << "Down " << (int)params[2] << " stats: " << current + WIDTH << "_>_0" << std::endl;
					displayRoom(rooms[dest[current + WIDTH]]);
				}
			}
			else
			{
				if (DEBUG) std::cout << "Down Empty" << std::endl;
				params[2] = 2;
				if (!CONTINUITY) to_process.push(current + WIDTH);
			}
		}
		else {
			if (DEBUG) std::cout << "Can't go down: " << current + WIDTH << std::endl;
			params[2] = 1;
		}

		// left
		if ((current - 1 >= 0) && (current % WIDTH != 0))
		{
			if (dest[current - 1] != EMPTY_CELL)
			{
				if ((dest[current - 1] & 2) == 0) params[3] = 0;
				else params[3] = 1;
				if (DEBUG) {
					std::cout << "Left " << (int)params[3] << " stats: " << current - 1 << "_>_0" << std::endl;
					displayRoom(rooms[dest[current - 1]]);
				}
			}
			else {
				if (DEBUG) std::cout << "Left Empty" << std::endl;
				params[3] = 2;
				if (!CONTINUITY) to_process.push(current - 1);
			}
		}
		else {
			if (DEBUG) std::cout << "Can't go left: " << current - 1 << std::endl;
			params[3] = 1;
		}

		// prepare possible rooms
		/*
		if (CONTINUITY && (params[0] * params[1] * params[2] * params[3] != 0)) {
			std::cout << (int)(params[0] * params[1] * params[2] * params[3]) << std::endl;
			continue;
		}
		*/
		for (int i = 0; i < 15; i++)
		{
			if (DEBUG) {
				std::cout << "Option " << i << std::endl;
				displayRoom(rooms[i]);
			}
			if ((params[0] != 2) && ((i & 1) != params[0]))
			{
				if (DEBUG) std::cout << "Denied " << (i & 1) << "_!=_" << (int)params[0] << std::endl;
				continue;
			}
			if ((params[1] != 2) && ((i & 2) != params[1] * 2))
			{
				if (DEBUG) std::cout << "Denied " << (i & 2) << "_!=_" << (int)params[1] * 2 << std::endl;
				continue;
			}
			if ((params[2] != 2) && ((i & 4) != params[2] * 4))
			{
				if (DEBUG) std::cout << "Denied " << (i & 4) << "_!=_" << (int)params[2] * 4 << std::endl;
				continue;
			}
			if ((params[3] != 2) && ((i & 8) != params[3] * 8))
			{
				if (DEBUG) std::cout << "Denied " << (i & 8) << "_!=_" << (int)params[3] * 8 << std::endl;
				continue;
			}
			if (DEBUG) std::cout << "Accepted" << std::endl;
			available.push_back(i);
		}

		// set room
		if (available.size() == 0) // if this happens, something went wrong
		{
			dest[current] = 16;
			if (DEBUG) std::cout << "ERROR, no available rooms" << std::endl;
			continue;
		}
		dest[current] = available[rand() % available.size()];
		if (DEBUG) {
			std::cout << "[" << current << "] chosen node" << std::endl;
			displayRoom(rooms[dest[current]]);
		}
		// queue up
		if (DEBUG) {
			std::cout << "queue size " << to_process.size() << std::endl;
		}
		if (CONTINUITY)
		{	
			params[0] = ((dest[current] & 4) == 0) ? 0 : 1;
			params[1] = ((dest[current] & 8) == 0) ? 0 : 1;
			params[2] = ((dest[current] & 1) == 0) ? 0 : 1;
			params[3] = ((dest[current] & 2) == 0) ? 0 : 1;
			if (DEBUG) std::cout << (int)params[0] << "_" << (int)params[1] << "_" << (int)params[2] << "_" << (int)params[3] << " ";
			if (DEBUG) std::cout << "push [";
			if ((params[2] == 0) && (current - WIDTH >= 0) && (dest[current - WIDTH] == EMPTY_CELL)) {
				if (DEBUG) std::cout << " Up(" << current << "->" << current - WIDTH << ")";
				to_process.push(current - WIDTH);
			}
			if ((params[3] == 0) && (current + 1 < HEIGHT * WIDTH) && (dest[current + 1] == EMPTY_CELL)) {
				if (DEBUG) std::cout << " Right(" << current << "->" << current + 1 << ")";
				to_process.push(current + 1);
			}
			if ((params[0] == 0) && (current + WIDTH < HEIGHT * WIDTH) && (dest[current + WIDTH] == EMPTY_CELL)) {
				if (DEBUG) std::cout << " Down(" << current << "->" << current + WIDTH << ")";
				to_process.push(current + WIDTH);
			}
			if ((params[1] == 0) && (current - 1 >= 0) && (dest[current - 1] == EMPTY_CELL)) {
				if (DEBUG) std::cout << " Left(" << current << "->" << current - 1 << ")";
				to_process.push(current - 1);
			}
			if (DEBUG) std::cout << " ]" << std::endl;
		}
		if (DEBUG) {
			std::cout << "queue size " << to_process.size() << std::endl;
		}
		if (DEBUG) {
			displayLine('-', WIDTH * 3);
			displayMap(dest, HEIGHT, WIDTH, '#', '.', ' ', false);
			displayLine('-', WIDTH * 3);
			std::cout << "[Debug] Press enter to continue to the next step";
			std::cin.get();
		}
	}
}