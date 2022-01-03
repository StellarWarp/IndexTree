#include"File.h"
#include"Index.h"
#include"Index_s.h"
#include"StructOP.h"
#include"Filter.h"
#include"Printer.h"
#include"DataManage.h"
#include"IndexManage.h"
using namespace std;

template<class T>
struct keyandp
{
    unsigned long DataIndex;
    T DataKey;
};

typedef  Line<unsigned long> Search;

int main()
{
    system("chcp 936");
    Open();
   
    IndexManage DataBase;
    DataBase.ImportIndex();

    Search list1;
    Search list2;
    PersonAge_si.data_rangefind(list1, 20, 30);
    PersonIncome_si.data_rangefind(list2, 2900, 3000);
    Fliter mixer(1000000);
    mixer.Append(list1);
    mixer.Flit(list2);
    Search list3 = mixer.Read();
    personfile.PrintFile(list3, Print_s_person);

    const int lenth = 1000;
    int X[lenth] = {};
    int Y[lenth] = {};
    PersonAge_si.data_satistic(X, 10, 50, Y);
    cout << endl;
    PrintXY(X, Y, 20);
    cout << endl;
    PersonIncome_si.data_satistic_range(X, 2000, 20000, 1000, Y);
    PrintXY(X, Y, 20);
    cout << endl;
    Date X1[lenth] = {};
    Date t1, t2, gt;
    t1 = "2024.01.01";
    t2 = "2035.06.05";
    gt += 60;
    RecordDate_si.data_satistic_range(X1, t1, t2, gt, Y);
    PrintXY(X1, Y, 40);

    recordfile.CloseFile();
    personfile.CloseFile();

    Close();
}


