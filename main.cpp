#include <iostream>
#include <string>
#include <unordered_map>
#include <random>

#include <chrono>
using namespace std::chrono;

#define SIZE 100

int main()
{
	//unordered_set / unordered_map -> O(1) (avarage) or O(n) (worst)
	std::unordered_map <std::string, int> map;

	//fil random 
	for (int i = 0; i < SIZE; i++) {
		map[std::to_string(i)] = i;
	}

	srand(static_cast<long int> (time(NULL)));
	int j = 0, tmp = 0;

	for (int i = 0; i < SIZE; i++) {
		j = rand() % 100;
		tmp = map[std::to_string(i)];
		map[std::to_string(i)] = map[std::to_string(j)];
		map[std::to_string(j)] = tmp;
	}

	std::cout << "Container size: " << map.size() << std::endl;

	for (int i = 0; i < (map.size() - 1); i++) {
		std::cout << map[std::to_string(i)] << ", ";
	}
	std::cout << map[std::to_string(map.size() - 1)] << std::endl;

	//delete first element
	auto start = high_resolution_clock::now();
	map.erase(std::to_string(0));
	auto stop = high_resolution_clock::now();
	std::cout << "Time: " << duration_cast<microseconds>(stop - start).count() << std::endl;

	//delete laast element
	start = high_resolution_clock::now();
	map.erase(std::to_string(map.size() - 1));
	stop = high_resolution_clock::now();
	std::cout << "Time: " << duration_cast<microseconds>(stop - start).count() << std::endl;

	//delete random element
	start = high_resolution_clock::now();
	map.erase(std::to_string(rand() % 100));
	stop = high_resolution_clock::now();
	std::cout << "Time: " << duration_cast<microseconds>(stop - start).count() << std::endl;

	//delete 10 random element
	for (int i = 0; i < 10; i++) {
		start = high_resolution_clock::now();
		map.erase(std::to_string(rand() % 100));
		stop = high_resolution_clock::now();
		std::cout << "Time: " << duration_cast<microseconds>(stop - start).count() << std::endl;
	}

	//delete random element
	start = high_resolution_clock::now();
	map.erase(std::to_string(123));
	stop = high_resolution_clock::now();
	std::cout << "Time: " << duration_cast<microseconds>(stop - start).count() << std::endl;

	return 0;
}