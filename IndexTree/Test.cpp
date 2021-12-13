#include"Support.h"
#include"Index.h"
#include"Filter.h"

int main()
{

	const int max = 11;
	int sc1 = 5;
	int sc2 = 5;
	int a[max] = { 4,4,5,5,5,5,5,5,5,5,8 };
	int b[max];
	for (int i = 0; i < max; i++)
	{
		b[i] = i + 1;
	}
	int t = DilitarySearch_up(a, 0, max - 1, 5);
	int v = b[t];
}