#pragma once
#ifndef MAP_n_VECTOR
#define MAP_n_VECTOR
#include <unordered_map>
#include <vector>
#endif //MAP_n_VECTOR

#ifndef ROOMS_HPP
#define ROOMS_HPP

//                  1 (0001) = up
// 8 (1000) = left                  2 (0010) = right
//                  4 (0100) = down

// all rooms are combinations of these 4 cardinal bits

extern std::unordered_map<char, std::vector<char>> rooms;

#endif //ROOMS_HPP