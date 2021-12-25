#include"File.h"
#include"Index.h"
#include"Index_s.h"
#include"StructOP.h"
#include"Filter.h"
#include"Printer.h"
using namespace std;

template<class ST,class DT>
void IndexConstruct(fmanage<ST>& file, Index< DT >& index, DT (*opfunc)(ST&))
{
    Line<unsigned long>& DataLine = file.FileTraversal_i();
    ST data;
    DT key;
    unsigned long DataPointer;
    while (DataLine.Nempty())
    {
        DataPointer = DataLine.OUT();
        file.ReadFile_i(DataPointer, data);
        key = opfunc(data);
        index.data_insert(DataPointer, key);
    }
}
template<class T>
struct keyandp
{
    unsigned long DataIndex;
    T DataKey;
};

typedef  Line<unsigned long> Search;

int main()
{

    RelevantInfoFile<record, recordindex> recordfile;
    recordfile.OpenFile("Data/record.bin", "Data/FileManage/record_hole.bin",
        "Data/recordindex.bin", "Data/FileManage/recordindex_hole.bin");
    record recorddata;
    recordfile.ReadLatestRecord(1, recorddata);

    fmanage<persondata> personfile;
    personfile.OpenFile("Data/person.bin", "Data/FileManage/person_hole.bin");
   
    Index<fstring<33>> PersonName_i;
    Index<fstring<19>> PersonID_i;
    Index<int> PersonAge_i;
    Index<int> PersonIncome_i;
    Index<long long> PersonPhone_i;
    IndexConstruct(personfile, PersonName_i, person_name);
    IndexConstruct(personfile, PersonID_i, person_ID);
    IndexConstruct(personfile, PersonAge_i, person_age);
    IndexConstruct(personfile, PersonIncome_i, person_income);
    IndexConstruct(personfile, PersonPhone_i, person_phone);
    Index<Date> Record_i;
    IndexConstruct(recordfile.file_m, Record_i, record_date);

    Search list1;
    Search list2;
    PersonAge_i.data_rangefind(list1, 20, 30);
    PersonIncome_i.data_rangefind(list2, 2900, 3000);
    Fliter mixer(1000000);
    mixer.Append(list1);
    mixer.Flit(list2);
    Search list3 = mixer.Read();
    personfile.PrintFile(list3, Print_s_person);

    const int lenth = 1000;
    int X[lenth] = {};
    int Y[lenth] = {};
    PersonAge_i.data_satistic(X, 10, 50, Y);
    cout << endl;
    PrintXY(X, Y, 20);
    cout << endl;
    PersonIncome_i.data_satistic_range(X, 2000, 20000, 1000, Y);
    PrintXY(X, Y, 20);
    cout << endl;
    Date X1[lenth] = {};
    Date t1, t2, gt;
    t1 = "2024.01.01";
    t2 = "2035.06.05";
    gt += 60;
    Record_i.data_satistic_range(X1, t1, t2, gt, Y);
    PrintXY(X1, Y, 40);

    recordfile.CloseFile();
    personfile.CloseFile();

    PersonName_i.SaveIndex("person_name");
    Index_s<fstring<33>> PersonName_is("person_name");
    PersonName_is.data_find(list1, fstring < 33>("阿果果"));
}


