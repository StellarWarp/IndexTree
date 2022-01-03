#pragma once
#include"File.h"
#include"Struct.h"
using namespace std;

RelevantInfoFile<record, recordindex> recordfile;
fmanage<persondata> personfile;
fmanage<scoredata> scorefile;
void Open()
{
    recordfile.OpenFile("Data/record.bin", "Data/FileManage/record_hole.bin",
        "Data/recordindex.bin", "Data/FileManage/recordindex_hole.bin");
    personfile.OpenFile("Data/person.bin", "Data/FileManage/person_hole.bin");
    scorefile.OpenFile("Data/score.bin", "Data/FileManage /score_hole.bin");
}
void Close()
{
    recordfile.CloseFile();
    personfile.CloseFile();
    scorefile.CloseFile();
}