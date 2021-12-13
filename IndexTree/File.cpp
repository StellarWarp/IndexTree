#include<iostream>
#include<fstream>
#include"File.h"
using namespace std;

void test()
{
	cout << "hi" << endl;
}

unsigned long getinfo()
{
    ifstream infofile;
    infofile.open("Data/info.bin");
    unsigned long  lenth;
    infofile >> lenth;
    return lenth;
    infofile.close();
};

unsigned long* ImportIndex(unsigned long lenth)
{
    unsigned long* indexlist = new unsigned long[lenth];
    ifstream indexfile;
    indexfile.open("Data/index_p.bin");
    for (unsigned long i = 0; i < lenth; i++)
    {
        indexfile >> indexlist[i];
    }
    return indexlist;
};



