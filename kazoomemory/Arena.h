#pragma once
#include <cstddef>

typedef size_t SizeType;

struct MemoryArena;
MemoryArena* ConstructArena(const SizeType Size);
char* Push(MemoryArena* Arena, const SizeType Size);

template <typename T>
T* PushStruct(MemoryArena* Arena)
{
	return (T*) Push(Arena, sizeof(T));
}

void DestroyArena(MemoryArena* Arena);
unsigned long GetBlockCount(MemoryArena* Arena);

struct MemoryArena
{
	SizeType Size;
	char* Memory;
	char* Top;
	MemoryArena* NextArena;
};
