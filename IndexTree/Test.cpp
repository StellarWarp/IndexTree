#include"Support.h"
#include"Index.h"
#include"Index_s.h"
#include"Filter.h"
#include"TypeSupport.h"
#include"VisualTree.h"
#include<vector>
int main()
{
	init();
	Index<int> Test;
	vector<int> testdata;
	vector<unsigned long> testid;
	int n = 3000;
	for (int i = 0; i < n; i++)
	{
		testid.push_back(i);
		testdata.push_back(((sin(testid[i])+1)*10));
		Test.append(testid[i], testdata[i]);
	}
	Test.SaveIndex("testindex");
	Index_s<int> Test1;
	Test1.Import("testindex");
	for (int i = 0; i < n; i++)
	{
		Test1.data_delete(testid[i], testdata[i]);
		//Test.data_delete(testid[i], testdata[i]);
	}
}