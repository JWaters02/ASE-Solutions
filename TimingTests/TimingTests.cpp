#include <iostream>
#include <chrono>
#include <utility>
#include <map>
#include <fstream>
#include <unordered_map>

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include "KeyItemGenerator.h"
#include "../BST/Dictionary.h"

template <typename T>
std::chrono::nanoseconds timingTest(unsigned long long int mapSize, unsigned long long int numberOfLookups, T dict)
{
    KeyItemGenerator gen = KeyItemGenerator();

    for (unsigned long long int i = 0; i < mapSize; ++i) {
        if (std::is_same<T, Dictionary<int, std::string>>::value)
        {
            auto* dict_cast = (Dictionary<int, std::string>*)& dict;
            dict_cast->insert(gen.randomKey(), gen.randomItem());
        }
        else if (std::is_same<T, std::map<int, std::string>>::value)
        {
            auto* dict_cast = (std::map<int, std::string>*)& dict;
            dict_cast->insert({gen.randomKey(), gen.randomItem()});
        }
        else if (std::is_same<T, std::unordered_map<int, std::string>>::value)
        {
            auto* dict_cast = (std::unordered_map<int, std::string>*)& dict;
            dict_cast->insert({gen.randomKey(), gen.randomItem()});
        }
    }

    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    for (unsigned long long int i = 0; i < numberOfLookups; ++i) {
        if (std::is_same<T, Dictionary<int, std::string>>::value)
        {
            auto* dict_cast = (Dictionary<int, std::string>*)& dict;
            dict_cast->lookup(gen.randomKey());
        }
        else if (std::is_same<T, std::map<int, std::string>>::value)
        {
            auto* dict_cast = (std::map<int, std::string>*)& dict;
            dict_cast->find(gen.randomKey());
        }
        else if (std::is_same<T, std::unordered_map<int, std::string>>::value)
        {
            auto* dict_cast = (std::unordered_map<int, std::string>*)& dict;
            dict_cast->find(gen.randomKey());
        }
    }

    std::chrono::steady_clock::time_point finishTime = std::chrono::steady_clock::now();

    auto timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(finishTime - startTime);

    std::chrono::nanoseconds meanTimePerLookup = timeTaken / numberOfLookups;

    return meanTimePerLookup;
}

void iterateTests()
{
    std::vector<unsigned long long int> mapSizes = {1, 10, 100, 1000, 10000, 100000, 1000000};
    const unsigned long long int numberOfLookups = 10000;
    std::vector<std::chrono::nanoseconds> times_map;
    std::vector<std::chrono::nanoseconds> times_unordered_map;
    std::vector<std::chrono::nanoseconds> times_bst;

    for (unsigned long long mapSize : mapSizes)
    {
        times_map.push_back(timingTest(mapSize, numberOfLookups, std::map<int, std::string>()));
        times_unordered_map.push_back(timingTest(mapSize, numberOfLookups, std::unordered_map<int, std::string>()));
        times_bst.push_back(timingTest(mapSize, numberOfLookups, Dictionary<int, std::string>()));
    }

    std::ofstream file;
    file.open("mapTimes.csv");
    file << "size,mapTime,unorderedMapTime,bstTime\n";
    for (unsigned long long int i = 0; i < times_map.size(); ++i)
    {
        file << mapSizes[i] << ","
            << times_map[i].count() << ","
            << times_unordered_map[i].count()
            << "," << times_bst[i].count()
            << "\n";
    }
    file.close();
}


int main()
{
    iterateTests();

    Py_Initialize();
    PyRun_SimpleString("exec(open(\"timingGraphGen.py\").read())");
    Py_Finalize();

    return 0;
}
