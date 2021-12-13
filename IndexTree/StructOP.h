#pragma once
#include"Struct.h"
#include<iostream>

string inline person_name(persondata& node)
{
	return node.name;
}
string inline person_ID(persondata& node)
{
	return node.ID;
}
int inline person_age(persondata& node)
{
	return node.age;
}
int inline person_income(persondata& node)
{
	return node.income;
}
long long inline person_phone(persondata& node)
{
	return node.phone;
}

string inline record_ID(record& node)
{
	return node.ID;
}

string inline record_date(record& node)
{
	return node.date;
}

int inline record_time(record& node)
{
	return node.time;
}