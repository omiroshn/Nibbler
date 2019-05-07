#include <iostream>
#include "Graphics.hpp"
#include "gManager.hpp"

#include <vector>
#include <algorithm>
#include <thread>
#include <ctime>
#include <list>

void	print_bits(int num)
{
	int i = 7;

	while(i >= 0)
	{
		if(num & 1 << i)
			std::cout << 1;
		else
			std::cout << 0;
		--i;
	}
	std::cout << std::endl;
}

int	swapBits(int num, int pos1, int pos2)
{
	int bit1;
	int bit2;
	int x;
	int result;

	bit1 = (num >> pos1) & 1;
	bit2 = (num >> pos2) & 1;
	x = bit1 ^ bit2;
	x = (x << pos1) | (x << pos2);
	result = num ^ x;
	return result;
}

int main(int argc, char **argv)
{
	gManager *game;
	game = gManager::Instance();
	game->run();
	gManager::Release();
	game = nullptr;

	return (0);
}