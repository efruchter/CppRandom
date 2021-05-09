/*
 * A VERY basic, in-place, non-stable quicksort.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Arr
{
	int* Ints;
	int Count;
} Arr;

Arr MakeRandomNums(int Count);
void QuickSort(int* Nums, int LowerIndex, int UpperIndex);

static inline void Swap(int* A, int* B)
{
	int T = *A;
	*A = *B;
	*B = T;
}

int main(void) {
	Arr Nums = MakeRandomNums(2048*2*2*2*2*2*2*2*2*2);
	QuickSort(Nums.Ints, 0, Nums.Count - 1);
	for (int i = 0; i < Nums.Count; i++)
	{
		printf("%d\n", Nums.Ints[i]);
	}
	return EXIT_SUCCESS;
}

Arr MakeRandomNums(int Count)
{
	Arr Out;
	Out.Count = Count;
	Out.Ints = (int*)malloc(sizeof(int)*Count);
	for (int i = 0; i < Count; i++)
	{
		Out.Ints[i] = rand();
	}
	return Out;
}

void QuickSort(int* Nums, int LowerIndex, int UpperIndex)
{
	if (LowerIndex >= UpperIndex)
	{
		return;
	}

	int Partition = Nums[(LowerIndex + UpperIndex) / 2];

	int Left = 0;
	int Right = 0;
	for (int i = LowerIndex; i <= (UpperIndex - Right); i++)
	{
		if (Nums[i] < Partition)
		{
			Swap(&Nums[i], &Nums[LowerIndex + Left]);
			Left++;
		}
		else if (Nums[i] > Partition)
		{
			Swap(&Nums[i], &Nums[UpperIndex - Right]);
			Right++;
			i--;
		}
	}

	if (LowerIndex < (LowerIndex + Left - 1))
	{
		QuickSort(Nums, LowerIndex, LowerIndex + Left - 1);
	}

	if ((LowerIndex + Left + 1) < UpperIndex)
	{
		QuickSort(Nums, LowerIndex + Left + 1, UpperIndex);
	}
}
