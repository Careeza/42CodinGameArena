#include "common.hpp"

std::mt19937 gen(std::random_device{}());
int random_index(int lower, int higher) {
    return std::uniform_int_distribution<int>(lower, higher)(gen);
}

Diag d[37] = { 
    { {6, 18, 36}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, } },
    { {6, 18, 29}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, } },
    { {6, 18, 29}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, } },
    { {6, 18, 29}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, } },
    { {6, 18, 29}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, } },
    { {6, 18, 29}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, } },
    { {6, 18, 29}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, } },
    { {6, 13, 22}, {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, } },
    { {6, 15, 23}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, } },
    { {6, 13, 22}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, } },
    { {6, 15, 23}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, } },
    { {6, 13, 22}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, } },
    { {6, 15, 23}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, } },
    { {6, 13, 22}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, } },
    { {6, 15, 23}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, } },
    { {6, 13, 22}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, } },
    { {6, 15, 23}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, } },
    { {6, 13, 22}, {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, } },
    { {6, 15, 23}, {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, } },
    { {3, 8, 15}, {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, } },
    { {4, 10, 17}, {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, } },
    { {4, 10, 17}, {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, } },
    { {3, 8, 15}, {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, } },
    { {4, 10, 17}, {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, } },
    { {4, 10, 17}, {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, } },
    { {3, 8, 15}, {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, } },
    { {4, 10, 17}, {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, } },
    { {4, 10, 17}, {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, } },
    { {3, 8, 15}, {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, } },
    { {4, 10, 17}, {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, } },
    { {4, 10, 17}, {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, } },
    { {3, 8, 15}, {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, } },
    { {4, 10, 17}, {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, } },
    { {4, 10, 17}, {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, } },
    { {3, 8, 15}, {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, } },
    { {4, 10, 17}, {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, } },
    { {4, 10, 17}, {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, } }
};

Shadow s[6] = {
{{{ {{4, 13, 28, }}, {{0, 4, 13, }}, {{3, 12, 27, }}, {{12, 27, -1, }}, {{13, 28, -1, }}, {{14, 29, -1, }}, {{5, 14, 29, }}, {{1, 0, 4, }}, {{2, 3, 12, }}, {{10, 11, 26, }}, {{11, 26, -1, }}, {{26, -1, -1, }}, {{27, -1, -1, }}, {{28, -1, -1, }}, {{29, -1, -1, }}, {{30, -1, -1, }}, {{15, 30, -1, }}, {{16, 15, 30, }}, {{6, 5, 14, }}, {{7, 1, 0, }}, {{8, 2, 3, }}, {{9, 10, 11, }}, {{23, 24, 25, }}, {{24, 25, -1, }}, {{25, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{31, -1, -1, }}, {{32, 31, -1, }}, {{33, 32, 31, }}, {{17, 16, 15, }}, {{18, 6, 5, }},   }}},
{{{ {{5, 15, 31, }}, {{6, 16, 32, }}, {{0, 5, 15, }}, {{4, 14, 30, }}, {{14, 30, -1, }}, {{15, 31, -1, }}, {{16, 32, -1, }}, {{18, 17, 33, }}, {{1, 6, 16, }}, {{2, 0, 5, }}, {{3, 4, 14, }}, {{12, 13, 29, }}, {{13, 29, -1, }}, {{29, -1, -1, }}, {{30, -1, -1, }}, {{31, -1, -1, }}, {{32, -1, -1, }}, {{33, -1, -1, }}, {{17, 33, -1, }}, {{36, 35, 34, }}, {{7, 18, 17, }}, {{8, 1, 6, }}, {{9, 2, 0, }}, {{10, 3, 4, }}, {{11, 12, 13, }}, {{26, 27, 28, }}, {{27, 28, -1, }}, {{28, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{34, -1, -1, }}, {{35, 34, -1, }},   }}},
{{{ {{6, 17, 34, }}, {{18, 35, -1, }}, {{1, 18, 35, }}, {{0, 6, 17, }}, {{5, 16, 33, }}, {{16, 33, -1, }}, {{17, 34, -1, }}, {{36, -1, -1, }}, {{7, 36, -1, }}, {{8, 7, 36, }}, {{2, 1, 18, }}, {{3, 0, 6, }}, {{4, 5, 16, }}, {{14, 15, 32, }}, {{15, 32, -1, }}, {{32, -1, -1, }}, {{33, -1, -1, }}, {{34, -1, -1, }}, {{35, -1, -1, }}, {{-1, -1, -1, }}, {{19, -1, -1, }}, {{20, 19, -1, }}, {{21, 20, 19, }}, {{9, 8, 7, }}, {{10, 2, 1, }}, {{11, 3, 0, }}, {{12, 4, 5, }}, {{13, 14, 15, }}, {{29, 30, 31, }}, {{30, 31, -1, }}, {{31, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }},   }}},
{{{ {{1, 7, 19, }}, {{7, 19, -1, }}, {{8, 20, -1, }}, {{2, 8, 20, }}, {{0, 1, 7, }}, {{6, 18, 36, }}, {{18, 36, -1, }}, {{19, -1, -1, }}, {{20, -1, -1, }}, {{21, -1, -1, }}, {{9, 21, -1, }}, {{10, 9, 21, }}, {{3, 2, 8, }}, {{4, 0, 1, }}, {{5, 6, 18, }}, {{16, 17, 35, }}, {{17, 35, -1, }}, {{35, -1, -1, }}, {{36, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{22, -1, -1, }}, {{23, 22, -1, }}, {{24, 23, 22, }}, {{11, 10, 9, }}, {{12, 3, 2, }}, {{13, 4, 0, }}, {{14, 5, 6, }}, {{15, 16, 17, }}, {{32, 33, 34, }}, {{33, 34, -1, }}, {{34, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }},   }}},
{{{ {{2, 9, 22, }}, {{8, 21, -1, }}, {{9, 22, -1, }}, {{10, 23, -1, }}, {{3, 10, 23, }}, {{0, 2, 9, }}, {{1, 8, 21, }}, {{20, -1, -1, }}, {{21, -1, -1, }}, {{22, -1, -1, }}, {{23, -1, -1, }}, {{24, -1, -1, }}, {{11, 24, -1, }}, {{12, 11, 24, }}, {{4, 3, 10, }}, {{5, 0, 2, }}, {{6, 1, 8, }}, {{18, 7, 20, }}, {{7, 20, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{25, -1, -1, }}, {{26, 25, -1, }}, {{27, 26, 25, }}, {{13, 12, 11, }}, {{14, 4, 3, }}, {{15, 5, 0, }}, {{16, 6, 1, }}, {{17, 18, 7, }}, {{35, 36, 19, }}, {{36, 19, -1, }}, {{19, -1, -1, }},   }}},
{{{ {{3, 11, 25, }}, {{2, 10, 24, }}, {{10, 24, -1, }}, {{11, 25, -1, }}, {{12, 26, -1, }}, {{4, 12, 26, }}, {{0, 3, 11, }}, {{8, 9, 23, }}, {{9, 23, -1, }}, {{23, -1, -1, }}, {{24, -1, -1, }}, {{25, -1, -1, }}, {{26, -1, -1, }}, {{27, -1, -1, }}, {{13, 27, -1, }}, {{14, 13, 27, }}, {{5, 4, 12, }}, {{6, 0, 3, }}, {{1, 2, 10, }}, {{20, 21, 22, }}, {{21, 22, -1, }}, {{22, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{-1, -1, -1, }}, {{28, -1, -1, }}, {{29, 28, -1, }}, {{30, 29, 28, }}, {{15, 14, 13, }}, {{16, 5, 4, }}, {{17, 6, 0, }}, {{18, 1, 2, }}, {{7, 8, 9, }},   }}},
};

Neigbours n[37] = {
        { {6, 18, 36}, {1, 2, 3, 4, 5, 6, 7, 8, 18, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 20, 36, 21, 35, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34} },
        { {6, 18, 29}, {7, 8, 2, 0, 6, 18, 19, 20, 36, 21, 9, 10, 3, 4, 5, 16, 17, 35, 22, 23, 24, 11, 12, 13, 14, 15, 32, 33, 34,} },
        { {6, 18, 29}, {8, 9, 10, 3, 0, 1, 20, 21, 7, 22, 23, 24, 11, 12, 4, 5, 6, 18, 19, 36, 25, 26, 27, 13, 14, 15, 16, 17, 35,} },
        { {6, 18, 29}, {2, 10, 11, 12, 4, 0, 8, 9, 1, 23, 24, 25, 26, 27, 13, 14, 5, 6, 20, 21, 7, 22, 18, 28, 29, 30, 15, 16, 17,} },
        { {6, 18, 29}, {0, 3, 12, 13, 14, 5, 1, 2, 6, 10, 11, 26, 27, 28, 29, 30, 15, 16, 7, 8, 18, 9, 17, 23, 24, 25, 31, 32, 33,} },
        { {6, 18, 29}, {6, 0, 4, 14, 15, 16, 18, 1, 17, 2, 3, 12, 13, 29, 30, 31, 32, 33, 36, 7, 35, 8, 34, 9, 10, 11, 26, 27, 28,} },
        { {6, 18, 29}, {18, 1, 0, 5, 16, 17, 36, 7, 35, 8, 2, 3, 4, 14, 15, 32, 33, 34, 19, 20, 21, 9, 10, 11, 12, 13, 29, 30, 31,} },
        { {6, 13, 22}, {19, 20, 8, 1, 18, 36, 21, 9, 2, 0, 6, 17, 35, 22, 23, 10, 3, 4, 5, 16, 33, 34} },
        { {6, 15, 23}, {20, 21, 9, 2, 1, 7, 19, 22, 23, 10, 3, 0, 6, 18, 36, 24, 11, 12, 4, 5, 16, 17, 35} },
        { {6, 13, 22}, {21, 22, 23, 10, 2, 8, 20, 24, 11, 3, 0, 1, 7, 19, 25, 26, 12, 4, 5, 6, 18, 36} },
        { {6, 15, 23}, {9, 23, 24, 11, 3, 2, 21, 22, 8, 25, 26, 12, 4, 0, 1, 20, 7, 27, 13, 14, 5, 6, 18} },
        { {6, 13, 22}, {10, 24, 25, 26, 12, 3, 9, 23, 2, 27, 13, 4, 0, 21, 22, 8, 1, 28, 29, 14, 5, 6} },
        { {6, 15, 23}, {3, 11, 26, 27, 13, 4, 2, 10, 0, 24, 25, 28, 29, 14, 5, 8, 9, 1, 23, 6, 30, 15, 16} },
        { {6, 13, 22}, {4, 12, 27, 28, 29, 14, 0, 3, 5, 11, 26, 30, 15, 1, 2, 6, 10, 16, 24, 25, 31, 32} },
        { {6, 15, 23}, {5, 4, 13, 29, 30, 15, 6, 0, 16, 3, 12, 27, 28, 31, 32, 18, 1, 17, 2, 33, 10, 11, 26} },
        { {6, 13, 22}, {16, 5, 14, 30, 31, 32, 17, 6, 33, 0, 4, 13, 29, 35, 18, 34, 1, 2, 3, 12, 27, 28} },
        { {6, 15, 23}, {17, 6, 5, 15, 32, 33, 35, 18, 34, 1, 0, 4, 14, 30, 31, 36, 7, 8, 2, 3, 12, 13, 29} },
        { {6, 13, 22}, {35, 18, 6, 16, 33, 34, 36, 7, 1, 0, 5, 15, 32, 19, 20, 8, 2, 3, 4, 14, 30, 31} },
        { {6, 15, 23}, {36, 7, 1, 6, 17, 35, 19, 20, 8, 2, 0, 5, 16, 33, 34, 21, 9, 10, 3, 4, 14, 15, 32} },
        { {3, 8, 15}, {20, 7, 36, 21, 8, 1, 18, 35, 22, 9, 2, 0, 6, 17, 34} },
        { {4, 10, 17}, {21, 8, 7, 19, 22, 9, 2, 1, 18, 36, 23, 10, 3, 0, 6, 17, 35} },
        { {4, 10, 17}, {22, 9, 8, 20, 23, 10, 2, 1, 7, 19, 24, 11, 3, 0, 6, 18, 36} },
        { {3, 8, 15}, {23, 9, 21, 24, 10, 2, 8, 20, 25, 11, 3, 0, 1, 7, 19} },
        { {4, 10, 17}, {22, 24, 10, 9, 21, 25, 11, 3, 2, 8, 20, 26, 12, 4, 0, 1, 7} },
        { {4, 10, 17}, {23, 25, 11, 10, 22, 9, 26, 12, 3, 2, 21, 8, 27, 13, 4, 0, 1} },
        { {3, 8, 15}, {24, 26, 11, 23, 10, 27, 12, 3, 22, 9, 2, 28, 13, 4, 0} },
        { {4, 10, 17}, {11, 25, 27, 12, 10, 24, 3, 28, 13, 4, 9, 23, 2, 0, 29, 14, 5} },
        { {4, 10, 17}, {12, 26, 28, 13, 3, 11, 4, 25, 29, 14, 2, 10, 0, 24, 5, 30, 15} },
        { {3, 8, 15}, {13, 27, 29, 4, 12, 14, 26, 30, 0, 3, 5, 11, 15, 25, 31} },
        { {4, 10, 17}, {14, 13, 28, 30, 5, 4, 15, 12, 27, 31, 6, 0, 16, 3, 32, 11, 26} },
        { {4, 10, 17}, {15, 14, 29, 31, 16, 5, 32, 4, 13, 28, 17, 6, 33, 0, 3, 12, 27} },
        { {3, 8, 15}, {32, 15, 30, 33, 16, 5, 14, 29, 34, 17, 6, 0, 4, 13, 28} },
        { {4, 10, 17}, {33, 16, 15, 31, 34, 17, 6, 5, 14, 30, 35, 18, 1, 0, 4, 13, 29} },
        { {4, 10, 17}, {34, 17, 16, 32, 35, 18, 6, 5, 15, 31, 36, 7, 1, 0, 4, 14, 30} },
        { {3, 8, 15}, {35, 17, 33, 36, 18, 6, 16, 32, 19, 7, 1, 0, 5, 15, 31} },
        { {4, 10, 17}, {36, 18, 17, 34, 19, 7, 1, 6, 16, 33, 20, 8, 2, 0, 5, 15, 32} },
        { {4, 10, 17}, {19, 7, 18, 35, 20, 8, 1, 6, 17, 34, 21, 9, 2, 0, 5, 16, 33} },
    };

std::ostream&   operator<<(std::ostream& f, Action_type a) {
    switch (a)
    {
    case Action_type::seed :
        f << "SEED";
        break;
    case Action_type::grow :
        f << "GROW";
        break;
    case Action_type::complete :
        f << "COMPLETE";
        break;
    case Action_type::wait :
        f << "WAIT";
        break;
    default:
        f << "Error in parser" << std::endl;
        break;
    }
    return f;
}
std::ostream&   operator<<(std::ostream& f, Action a) {
    switch (a.type)
    {
    case Action_type::seed :
        f << a.type << " " << static_cast<int>(a.from) << " " << static_cast<int>(a.to);
        break;
    case Action_type::grow :
        f << a.type << " " << static_cast<int>(a.from);
        break;
    case Action_type::complete :
        f << a.type << " " << static_cast<int>(a.from);
        break;
    case Action_type::wait :
        f << a.type;
        break;
    default:
        f << "Error in parser";
        break;
    }
    return f;
}

int     adjacent_trees(State& s, int index, int player) {
    int neigbours = 0;
    for (int i = 0; i < n[index].size[0]; i++) {
        if (!s.grid[n[index].neigbours[i]].empty and s.grid[n[index].neigbours[i]].player == player) {
            neigbours++;
        }
    }
    return neigbours;
}
bool    isDiagonal(int from, int to) {
    int start = n[from].size[0];
    int end = n[from].size[1];

    for (int i = start; i < end; i++) {
        if (n[from].neigbours[i] == to) {
            return d[from].diag[i];
        }
    }
    return false;
}
bool    inSecondLayer(int from, int to) {
    int start = n[from].size[0];
    int end = n[from].size[1];

    for (int i = start; i < end; i++) {
        if (n[from].neigbours[i] == to)
            return true;
    }
    return false;
}
bool    shadow_next_turn(State& state, int day, int id) {
    int orientaion = (day + 1) % 6;
    int size = state.grid[id].size;
    for (int j = 0; j < 3; j++) {
        int index_cell = s[orientaion].shadow[id][j];
        if (index_cell == -1 or state.grid[index_cell].empty) {
            continue;
        }
        if (state.grid[index_cell].size < size or j >= state.grid[index_cell].size) {
            continue;
        }
        return (true);
    }
    return false;
}

void	pass_day(State &state) {
	state.info.days++;
	if (state.info.days >= 24)
		return ;
	int orientaion = state.info.days % 6;

	state.info.wait[0] = false;
	state.info.wait[1] = false;
	for (int i = 0; i < state.grid.size(); i++) {
		int size = state.grid[i].size;
		state.grid[i].sleep = false;
		if (state.grid[i].empty or size == 0)
			continue;
		
		bool shadow = false;
		for (int j = 0; j < 3; j++) {
			int index_cell = s[orientaion].shadow[i][j];
			if (index_cell == -1 or state.grid[index_cell].empty) {
				continue;
			}

			if (state.grid[index_cell].size < size or j >= state.grid[index_cell].size) {
				continue;
			}
			shadow = true;
			break;
		}
		if (!shadow) {
			state.info.sun[state.grid[i].player] += size;
		}
	}

}
bool	seed_action(State &s, Action a, int player, int info) {
	(void)info;
    s.grid[a.from].sleep = true;
	if (!s.grid[a.to].empty) {
		s.grid[a.to].empty = true;
		return true;
	}
	s.grid[a.to].empty = false;
	s.grid[a.to].player = player;
	s.grid[a.to].size = 0;
	s.grid[a.to].sleep = true;
	s.info.trees_size[player][0]++;
    s.info.trees_richness[player][s.grid[a.to].richness - 1]++;

	return false;
}
bool	complete_action(State &s, Action a, int player, int info) {
	s.grid[a.from].empty = true;
	s.info.trees_size[player][3]--;

    //std::cerr << "COMPLETE !!!!! " << player << ", " << s.grid[a.from].richness - 1 << std::endl;
    //std::cerr <<  s.info.trees_richness[player][s.grid[a.from].richness - 1] << std::endl;

    s.info.trees_richness[player][s.grid[a.from].richness - 1]--;

    //std::cerr <<  s.info.trees_richness[player][s.grid[a.from].richness - 1] << std::endl;

	s.info.score[player] += (info + (s.grid[a.from].richness - 1) * 2);
    if (s.info.nutriments == 0)
        s.info.nutriments = 0;
	else
        s.info.nutriments--;

	return false;
}
bool	grow_action(State &s, Action a, int player, int info) {
    s.grid[a.from].sleep = true;
	s.info.trees_size[player][s.grid[a.from].size]--;
	s.grid[a.from].size += 1;
	s.info.trees_size[player][s.grid[a.from].size]++;
	return false;
}
bool	wait_action(State &s, Action a, int player, int info) {
	s.info.wait[player] = true;
	return false;
}

std::function<bool(State&, Action, int, int)> t[4] = {seed_action, grow_action, complete_action, wait_action};

void	State::simulate_action(State& new_s, Action a) {
    new_s = *this;
	int nutriments = this->info.nutriments;

    if (!this->info.player) {
        new_s.a = a;
    } else {
        new_s.info.sun[0] -= this->a.cost;
        new_s.info.sun[1] -= a.cost;
		t[static_cast<int>(this->a.type)](new_s, this->a, 0, nutriments);
		
		if (t[static_cast<int>(a.type)](new_s, a, 1, nutriments)) {
			new_s.info.sun[0] += this->a.cost;
        	new_s.info.sun[1] += a.cost;
            new_s.info.trees_size[0][0]--;
            new_s.info.trees_richness[0][new_s.grid[a.to].richness - 1]--;
		}

		if (new_s.info.wait[0] and new_s.info.wait[1]) {
			pass_day(new_s);
		}
	}

	new_s.info.player = !this->info.player;
}

void	State::do_action(Action a) {
	int nutriments = this->info.nutriments;

    if (!this->info.player) {
        this->a = a;
    } else {
        this->info.sun[0] -= this->a.cost;
        this->info.sun[1] -= a.cost;
		t[static_cast<int>(this->a.type)](*this, this->a, 0, nutriments);
		
		if (t[static_cast<int>(a.type)](*this, a, 1, nutriments)) {
			this->info.sun[0] += this->a.cost;
        	this->info.sun[1] += a.cost;
            this->info.trees_size[0][0]--;
            this->info.trees_richness[0][this->grid[a.to].richness - 1]--;
		}

		if (this->info.wait[0] and this->info.wait[1]) {
			pass_day(*this);
		}
	}
	this->info.player = !this->info.player;
}


double  score_action(State& s, Action a) {
    double score = 0;
    int player = s.info.player;

    switch (a.type)
    {
        case Action_type::seed : {
            Cell& c = s.grid[a.to];
            Cell& from = s.grid[a.from];
            if (c.richness == 2 || c.richness == 1) {
                score = c.richness == 2 ? 0.8 : 0.8;
                if (s.info.trees_richness[player][2] >= 1 && s.info.trees_richness[player][1] < 3 && (c.richness == 2 || s.info.trees_richness[player][0] < 3) && from.size > 1) {
                    score += 0.1 * (6 - adjacent_trees(s, a.to, player)); // adjacent_trees returns the number of trees (you own) surrounding a cell
                }
            } else if (c.richness == 3) {
                score = s.info.trees_richness[player][2] < 4 ? 2 : 0;
                score -= (s.info.days < 8 ? 0.6 : 0.6 ) * adjacent_trees(s, a.to, player);
                score += from.size == 3 ? 0.1 : 0; // sow_size is the size of the tree in the cell sow
            }
            if (isDiagonal(a.from, a.to)) // is the cell id diagonal to the cell sow ?
                score += 0.2;
            if (s.info.days > 18)
                score -= 2;
            //std::cerr << "SON SCORE EST DE " << score << std::endl;
            break;
        }
        case Action_type::grow : {
            Cell& c = s.grid[a.from];
            if (c.richness == 1)
                score = 4;
            else if (c.richness == 2)
                score = 2.5;
            else if (c.richness == 3)
                score = 3;
            if (shadow_next_turn(s, s.info.days, a.from))
                score -= 1;
            score += 0.1 * (c.size + 1);
            break;
        }
        case Action_type::complete : {
            Cell& c = s.grid[a.from];
            if (c.richness == 1)
                score = 0;
            else
                score = c.richness;
            if (s.info.days > 21)
                score += 21;
            if (!shadow_next_turn(s, s.info.days, a.from))
                score -= 2;
            break;
        }
        default: {
            score = 1.5;
            break;
        }
    }
    return score;
}

    // double  score_seed(Action& a, int player);
    // double  score_grow(Action& a);
    // double  score_complete(Action& a);



bool	State::final_state() const {
	if (info.days >= 24)
		return true;
	return false;
}

