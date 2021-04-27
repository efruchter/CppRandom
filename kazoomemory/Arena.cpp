#include "Arena.h"
#include <stdlib.h>
#include <assert.h>

MemoryArena* ConstructArena(const SizeType Size)
{
	MemoryArena* Arena = (MemoryArena*) malloc(sizeof(MemoryArena));
	Arena->Size = Size;
	Arena->Memory = (char*) malloc((size_t) Size);
	Arena->Top = Arena->Memory;
	Arena->NextArena = nullptr;
	return Arena;
}

char* Push(MemoryArena* Arena, const SizeType Size)
{
	assert(Arena != nullptr);
	assert(Arena->Size >= Size); // Cannot fit struct into arena

	const SizeType UsedSize = reinterpret_cast<SizeType>((SizeType)Arena->Top - (SizeType)Arena->Memory);
	if ((UsedSize + Size) > Arena->Size)
	{
		if (Arena->NextArena == nullptr)
		{
			Arena->NextArena = ConstructArena(Arena->Size);
		}

		return Push(Arena->NextArena, Size);
	}

	char* Out = Arena->Top;
	Arena->Top += Size;
	return Out;
}

void DestroyArena(MemoryArena* Arena)
{
	if (Arena == nullptr)
	{
		return;
	}

	MemoryArena* Next = Arena->NextArena;

	free(Arena->Memory);
	free(Arena);

	if (Next != nullptr)
	{	
		DestroyArena(Arena->NextArena);
	}
}

unsigned long GetBlockCount(MemoryArena* Arena)
{
	unsigned long Count = 0;
	while (Arena != nullptr)
	{
		Count++;
		Arena = Arena->NextArena;
	}
	return Count;
}

