#pragma once
#include "stdafx.h"
union type
{
	int intval;
	double doubleval;
	char* charval = nullptr;
};
class var
{
	int id;
	type val;
public:
	var() = default;
	var(int i) :id(1) { val.intval = i; }
	var(double d) :id(2) { val.doubleval = d; }
	var(char*);
	var(const var&);
	var& operator=(const var&);
	var operator+(var &);
	var operator-(var &);
	var operator*(var &);
	var operator/(var &);
	var& operator+=(var &);
	var& operator-=(var &);
	var& operator*=(var &);
	var& operator/=(var &);
	bool operator>(const var &);
	bool operator<(const var &ob) { return (!(*this > ob) && !(*this == ob)); }
	bool operator>=(const var &ob) { return !(*this < ob); }
	bool operator<=(const var &ob) { return !(*this > ob); }
	bool operator==(const var &);
	bool operator!=(const var &ob) { return !(*this == ob); }
	operator int();
	operator double();
	operator char*();
	friend std::ostream & operator<<(std::ostream &, var);
	~var() { if (this->id == 3) free(this->val.charval); }
};