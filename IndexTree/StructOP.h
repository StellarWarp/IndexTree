#pragma once
#include"Struct.h"
#include"TypeSupport.h"
#include<iostream>

fstring<33> inline person_name(persondata& node)
{
	fstring<33> str;
	str = node.name;
	return str;
}
fstring<19> inline person_ID(persondata& node)
{
	fstring<19> str;
	str = node.name;
	return str;
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

Date inline record_date(record& node)
{
	return node.date;
}

int inline record_time(record& node)
{
	return node.time;
}