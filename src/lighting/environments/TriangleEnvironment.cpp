

#include "lighting/environments/TriangleEnvironment.hpp"

using namespace Chroma;

EnvironmentLightDataT TriangleEnvironment::getEnvironmentLights() {
    return EnvironmentLightDataT(
        {
    {0, {
        {1, 3 },
        {2, 8 },
        {3, 5 },
        {4, 2 },
        {5, 7 },
        {6, 4 },
        {7, 1 },
        {8, 6 },
        {9, 0 },
        {10, 12 },
    }},
    {1, {
        {1, 4 },
        {2, 5 },
        {3, 6 },
        {4, 7 },
        {5, 8 },
        {6, 9 },
        {7, 10 },
        {8, 11 },
        {9, 12 },
        {10, 13 },
        {11, 14 },
        {12, 15 },
        {13, 16 },
        {14, 17 },
        {15, 18 },
        {16, 19 },
        {17, 20 },
        {18, 21 },
        {19, 22 },
        {20, 23 },
        {21, 24 },
        {22, 25 },
        {23, 26 },
        {24, 27 },
        {25, 28 },
        {26, 29 },
        {27, 30 },
        {28, 31 },
        {29, 32 },
        {30, 33 },
        {31, 34 },
        {32, 35 },
        {33, 36 },
        {34, 37 },
        {35, 38 },
        {36, 39 },
        {37, 40 },
        {38, 41 },
        {39, 42 },
        {40, 43 },
        {41, 44 },
        {42, 45 },
        {43, 46 },
        {44, 47 },
        {45, 48 },
        {46, 49 },
        {47, 50 },
        {48, 51 },
        {49, 52 },
        {50, 53 },
        {51, 54 },
        {52, 55 },
        {53, 56 },
        {54, 57 },
        {55, 58 },
        {56, 59 },
        {57, 60 },
        {58, 61 },
        {59, 62 },
        {60, 63 },
    }},
    {2, {
        {1, 10 },
        {2, 3 },
        {3, 2 },
        {4, 6 },
        {5, 7 },
        {6, 4 },
        {7, 5 },
        {8, 12 },
        {9, 9 },
        {10, 0 },
        {11, 13 },
    }},
    {3, {
        {1, 10 },
        {2, 4 },
        {3, 3 },
        {4, 7 },
        {5, 8 },
        {6, 5 },
        {7, 6 },
        {8, 12 },
        {9, 14 },
        {10, 0 },
        {11, 2 },
    }},
    {4, {
        {1, 6 },
        {2, 10 },
        {3, 13 },
        {4, 5 },
        {5, 9 },
        {6, 12 },
        {7, 7 },
        {8, 11 },
        {9, 8 },
        {10, 0 },
        {11, 14 },
        {12, 16 },
    }},
    {5, {
    }},
    {6, {
    }},
    {7, {
    }},
}
    );
}

ChromaInstallEnvironment(TriangleEnvironment)
