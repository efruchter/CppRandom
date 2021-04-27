#include <iostream>
#include "Arena.h"

struct ABC
{
	int A;
	int B;
	int C;
};

int main()
{
	std::cout << "hello World" << std::endl;
	MemoryArena* Arena = ConstructArena(512);
	
	ABC* A = PushStruct<ABC>(Arena);
	A->A = 1;
	A->B = 2;
	A->C = 3;

	std::cout << A->A << std::endl;
	std::cout << A->B << std::endl;
	std::cout << A->C << std::endl;

	ABC* B = PushStruct<ABC>(Arena);
	B->A = 10;
	B->B = 20;
	B->C = 30;

	std::cout << B->A << std::endl;
	std::cout << B->B << std::endl;
	std::cout << B->C << std::endl;

	float* V = PushStruct<float>(Arena);
	*V = 36;

	std::cout << *V << std::endl;
	std::cout << "Count: " << GetBlockCount(Arena) << std::endl;

	DestroyArena(Arena);
	return 0;
}
