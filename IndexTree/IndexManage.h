#pragma once
#include"File.h"
#include"Index.h"
#include"Index_s.h"
#include"StructOP.h"
#include"Filter.h"
#include"Printer.h"
#include"DataManage.h"
using namespace std;

Index<fstring<33>> PersonName_mi;
Index<fstring<19>> PersonID_mi;
Index<int> PersonAge_mi;
Index<int> PersonIncome_mi;
Index<long long> PersonPhone_mi;

Index<Date> RecordDate_mi;
Index<int> RecordCategory_mi;
Index<int> RecordTime_mi;
Index<int> Recordscore_add_mi;
Index<int> Recordscore_remain_mi;
Index<int> Recordscore_sub_mi;
Index<int> Recordscore_sub_t_mi;


Index_s<fstring<33>> PersonName_si;
Index_s<fstring<19>> PersonID_si;
Index_s<int> PersonAge_si;
Index_s<int> PersonIncome_si;
Index_s<long long> PersonPhone_si;

Index_s<Date> RecordDate_si;
Index_s<int> RecordCategory_si;
Index_s<int> RecordTime_si;
Index_s<int> Recordscore_add_si;
Index_s<int> Recordscore_remain_si;
Index_s<int> Recordscore_sub_si;
Index_s<int> Recordscore_sub_t_si;

Index_s<Date> Record_si;
namespace mode
{
    int normal = 1;
    int range = 2;
}
namespace object
{
    int name = 1;
    int id = 2;
    int age = 4;
    int income = 8;
    int phone = 16;
    int Date = 32;
    int Category = 64;
    int Time = 128;
};
class IndexManage
{
    bool memorymode = false;

    template<class ST, class DT>
    void IndexConstruct(fmanage<ST>& file, Index< DT >& index, DT(*opfunc)(ST&))
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

    void BuildIndex()
    {
        IndexConstruct(personfile, PersonName_mi, person_name);
        IndexConstruct(personfile, PersonID_mi, person_ID);
        IndexConstruct(personfile, PersonAge_mi, person_age);
        IndexConstruct(personfile, PersonIncome_mi, person_income);
        IndexConstruct(personfile, PersonPhone_mi, person_phone);

        IndexConstruct(recordfile.file_m, RecordDate_mi, record_date);
        IndexConstruct(recordfile.file_m, RecordCategory_mi, record_category);
        IndexConstruct(recordfile.file_m, RecordTime_mi, record_time);
        IndexConstruct(recordfile.file_m, Recordscore_add_mi, record_score_add);
        IndexConstruct(recordfile.file_m, Recordscore_remain_mi, record_score_remain);
        IndexConstruct(recordfile.file_m, Recordscore_sub_mi, record_score_sub);
        IndexConstruct(recordfile.file_m, Recordscore_sub_t_mi, record_score_sub_t);

    }

    void SaveIndex()
    {
        PersonName_mi.SaveIndex("person_name");
        PersonID_mi.SaveIndex("person_id");
        PersonAge_mi.SaveIndex("perosn_age");
        PersonIncome_mi.SaveIndex("person_income");
        PersonPhone_mi.SaveIndex("person_phone");

        RecordDate_mi.SaveIndex("record_date");
        RecordCategory_mi.SaveIndex("record_category");
        RecordTime_mi.SaveIndex("record_time");
        Recordscore_add_mi.SaveIndex("record_score_add");
        Recordscore_remain_mi.SaveIndex("record_score_remain");
        Recordscore_sub_mi.SaveIndex("record_score_sub");
        Recordscore_sub_t_mi.SaveIndex("record_score_sub_t");
    }

    static const int index_num = 12;
    string index_name[index_num] =
    { "person_name","person_id","perosn_age","person_income","person_phone",
        "record_date" ,"record_category","record_time","record_score_add","record_score_remain","record_score_sub","record_score_sub_t"};

    bool is_exi(string& name)
    {
        ifstream test;
        string path[3];
        path[0] = "Index/" + name + "LayerN.bin";
        path[1] = "Index/" + name + "LayerData.bin";
        path[2] = "Index/" + name + "info.bin";
        for (int i = 0; i < 3; i++)
        {
            test.open(path[i]);
            if (!test.is_open())
            {
                return false;
                cout << "Fail to import index , building index...." << endl;
            }
            test.close();
        }
        return true;
    }

    void ImportIndex_p()
    {
        bool error = false;
        for (int i = 0; i < index_num; i++)
        {
            if (!is_exi(index_name[i]))
            {
                error = true;
                memorymode = true;
            }
        }
        if (error)
        {
            BuildIndex();
        }
        else
        {
            PersonName_si.Import("person_name");
            PersonID_si.Import("person_id");
            PersonAge_si.Import("perosn_age");
            PersonIncome_si.Import("person_income");
            PersonPhone_si.Import("person_phone");

            RecordDate_si.Import("record_date");
            RecordCategory_si.Import("record_category");
            RecordTime_si.Import("record_time");
            Recordscore_add_si.Import("record_score_add");
            Recordscore_remain_si.Import("record_score_remain");
            Recordscore_sub_si.Import("record_score_sub");
            Recordscore_sub_t_si.Import("record_score_sub_t");
        }
    }

public:
    void ImportIndex()
    {
        ImportIndex_p();
    }
    void modeswitch(bool mode)
    {
        cout << "ModeSwitched, memorymode: " << memorymode << endl;
        if (memorymode == true && mode == false)
        {
            memorymode = false;
            SaveIndex();
        }
    }
    void ReBuild()
    {
        BuildIndex();
        SaveIndex();
    }
    void search(int mode,int obj)
    {
        if (mode % 2)
        {
            cout << "percice search" << endl;
        }
        else
        {
            cout << "range search" << endl;
        }
        if (mode & 1)
        {

        }
    }
    void satistic(int mode, int obj)
    {

    }
};
