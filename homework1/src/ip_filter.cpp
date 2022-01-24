#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

void trim(std::string& str) {
    std::string::size_type stop = str.find_first_of('\t');
    str = str.substr(0, stop);
}


unsigned split(const std::string& str, char d)
{
    unsigned r = 0;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        unsigned v = std::stoi(str.substr(start, stop - start));
        r += v;
        r = r << 8;

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    unsigned v = std::stoi(str.substr(start));
    r += v;
    return r;
}

int main(int argc, char const* argv[])
{
    try
    {
        std::vector<unsigned> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            trim(line);
            int v = split(line, '.');
            ip_pool.push_back(v);
        }

        // TODO reverse lexicographically sort

        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<unsigned>());

        for (auto ip : ip_pool) {
            int a = (ip >> 24) & 255;
            int b = (ip >> 16) & 255;
            int c = (ip >> 8) & 255;
            int d = ip & 255;
            std::cout << a << '.' << b << '.' << c << '.' << d << '\n';
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}