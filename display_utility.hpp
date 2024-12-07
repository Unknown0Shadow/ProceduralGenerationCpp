#pragma once
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

#ifndef DISPLAY_UTILITY_HPP
#define DISPLAY_UTILITY_HPP

void displayRoom(std::vector<char>);

void displayAllRooms();

template<typename T>
void displayArr(T arr[], int length);

void displayMapValues(char map[], int HEIGHT, int WIDTH);

void displayMap(std::vector<char> map, int HEIGHT, int WIDTH, char block, char path, char uncharted);

void displayLine(char c, int length);

#endif //DISPLAY_UTILITY_HPP