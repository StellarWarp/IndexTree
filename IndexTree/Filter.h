#pragma once
#include"Index.h"
#include"Support.h"
class Fliter
{
	unsigned long* SearchList;
	unsigned long* FlitList;
	int lenth;
	void BitAppend(unsigned long List[], unsigned long value)
	{
		unsigned long in = 1;
		unsigned int i = value % 8;
		for (i = value % 8; i > 0; i--)
		{
			in = in << 1;
		}
		List[value / 8] |= in;
	}
	void BitFlit(unsigned long List1[], unsigned long List2[])
	{
		unsigned long in = 1;
		for (unsigned int i = 0; i < lenth; i++)
		{
			List1[i] &= List2[i];
		}
		delete[] List2;
		List2 = new unsigned long[lenth] {0};
	}
public:
	Fliter(int maxnum)
	{
		lenth = maxnum % 8 == 0 ? maxnum / 8 : maxnum / 8 + 1;
		SearchList = new unsigned long[lenth] {0};
		FlitList = new unsigned long[lenth] {0};
	}
	Line<unsigned long>& Read()
	{
		Line<unsigned long> Result;
		unsigned long* p = SearchList;
		for (int i = 0; i < lenth; i++)
		{
			if (*p)
			{
				for (int j = 0; *p; j++)
				{
					if (*p % 2)
					{
						Result.IN(i * 8 + j);
					}
					*p = *p >> 1;
				}
			}
			p++;
		}
		return Result;
	}
	void Append(Line<unsigned long>& Result)
	{
		while (Result.Nempty())
		{
			BitAppend(SearchList, Result.OUT());
		}
	}
	void Flit(Line<unsigned long>& Result)
	{
		while (Result.Nempty())
		{
			BitAppend(FlitList, Result.OUT());
		}
		BitFlit(SearchList, FlitList);
	}
};
