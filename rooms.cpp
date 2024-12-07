#include "rooms.hpp"
const char O = '.';
const char X = '#';
std::unordered_map<char, std::vector<char>> rooms =
{
    {0,{
        O,O,O,
        O,O,O,
        O,O,O,
    }},    // 0000
    {1,{
        X, X, X,
        O, O, O,
        O, O, O,
    }},     //0001
    {2,{
        O, O, X,
        O, O, X,
        O, O, X,
    }},     //0010
    {4,{
        O, O, O,
        O, O, O,
        X, X, X,
    }},     //0100
    {8,{
        X, O, O,
        X, O, O,
        X, O, O,
    }},     //1000
    {3,{
        X, X, X,
        O, O, X,
        O, O, X,
    }},     //0011
    {6,{
        O, O, X,
        O, O, X,
        X, X, X,
    }},     //0110
    {12,{
        X, O, O,
        X, O, O,
        X, X, X,
    }},     //1100
    {9,{
        X, X, X,
        X, O, O,
        X, O, O,
    }},     //1001
    {5,{
        X, X, X,
        O, O, O,
        X, X, X,
    }},     //0101
    {10,{
        X, O, X,
        X, O, X,
        X, O, X,
    }},     //1010
    {11,{
        X, X, X,
        X, O, X,
        X, O, X,
    }},     //1011
    {7,{
        X, X, X,
        O, O, X,
        X, X, X,
    }},     //0111
    {14,{
        X, O, X,
        X, O, X,
        X, X, X,
    }},     //1110
    {13,{
        X, X, X,
        X, O, O,
        X, X, X,
    }},     //1101
    {16,{
        '+', '+', '+',
        '+', 'X', '+',
        '+', '+', '+',
    }}      //1111 // in case of errors
};