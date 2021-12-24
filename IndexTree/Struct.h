#ifndef STRUCT_H
#define STRUCT_H
#include<iostream>
#include"TypeSupport.h"
using namespace std;

struct persondata
{
	char name[33];
	char ID[19];
	int age;
	char gender[7];
	long long phone;
	int income;
	char address[100];
	bool mark;
};

struct scoredata //仅用于读score//和person关联
{
	char name[33];
	char ID[19];
	Date date;
	int category;
	int time;
	int score_add;
	int score_remain;
	int score_sub;
	int score_sub_t;
	bool mark;
};

struct record //用于读record
{
	char name[33];
	char ID[19];
	Date date;
	int category;
	int time;
	int score_add;
	int score_remain;
	int score_sub;
	int score_sub_t;
	unsigned long next;
	unsigned long previous;
	bool mark;
};

struct recordindex
{
	char name[33];
	char ID[19];
	unsigned long record;
	unsigned long next;
	unsigned long previous;
	bool mark;
};

struct data
{
    struct persondata person;
};
#endif // !STRUCT_H

