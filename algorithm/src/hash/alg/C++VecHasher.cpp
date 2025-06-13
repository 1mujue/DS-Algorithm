#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Hasher
{
public:
    size_t operator()(const vector<uint32_t> &vec) const
    {
        size_t seed = vec.size();
        for (uint32_t i : vec)
        {
            seed ^= hash<uint32_t>{}(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};