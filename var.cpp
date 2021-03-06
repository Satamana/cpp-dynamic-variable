#include "stdafx.h"
#include "var.h"
var::var(char* str) : id(3)
{
	this->val.charval = (char*)malloc(strlen(str) + 1);
	strcpy_s(this->val.charval, strlen(str) + 1, str);
}
var::var(const var&copy) : id(copy.id)
{
	if (this->id == 1) this->val.intval = copy.val.intval;
	else if (this->id == 2) this->val.doubleval = copy.val.doubleval;
	else if (this->id == 3)
	{
		this->val.charval = (char*)malloc(strlen(copy.val.charval) + 1);
		strcpy_s(this->val.charval, strlen(copy.val.charval) + 1, copy.val.charval);
	}
}
var& var::operator=(const var &copy)
{
	if (this->id == 3 && this->val.charval != nullptr) free(this->val.charval);
	this->id = copy.id;
	if (this->id == 1) this->val.intval = copy.val.intval;
	else if (this->id == 2) this->val.doubleval = copy.val.doubleval;
	else if (this->id == 3)
	{
		this->val.charval = (char*)malloc(strlen(copy.val.charval) + 1);
		strcpy_s(this->val.charval, strlen(copy.val.charval) + 1, copy.val.charval);
	}
	return *this;
}
var var::operator+(var &ob)
{
	if (this->id == 1) return var(this->val.intval + int(ob));
	else if (this->id == 2) return var(this->val.doubleval + double(ob));
	else if (this->id == 3)
	{
		char* tmp = (char*)malloc(strlen(this->val.charval) + strlen(ob));
		strcpy_s(tmp, strlen(this->val.charval) + 1, this->val.charval);
		strcat_s(tmp, strlen(this->val.charval) + strlen(ob) + 1, ob);
		return var(tmp);
	}
	else return var();
}
var var::operator-(var &ob)
{
	if (this->id == 1) return var(this->val.intval - int(ob));
	else if (this->id == 2) return var(this->val.doubleval - double(ob));
	else if (this->id == 3 && strlen(this->val.charval) > strlen(ob))
	{
		char* tmp = (char*)malloc(strlen(this->val.charval) - strlen(ob) + 1);
		for (size_t i = 0; i < strlen(this->val.charval) - strlen(ob); i++) tmp[i] = this->val.charval[i];
		tmp[strlen(this->val.charval) - strlen(ob)] = 0;
		return var(tmp);
	}
	else return var();
}
var var::operator*(var &ob)
{
	if (this->id == 1) return var(this->val.intval * int(ob));
	else if (this->id == 2) return var(this->val.doubleval * double(ob));
	else if (this->id == 3 && ob.id == 3)
	{
		size_t size = 0;
		char* tmp = nullptr;
		for (size_t i = 0; i < strlen(this->val.charval); i++)
		{
			if (strchr(ob,this->val.charval[i]))
			{
				tmp = (char*)realloc(tmp, size + 1);
				tmp[size++] = this->val.charval[i];
			}
		}
		tmp = (char*)realloc(tmp, size + 1);
		tmp[size] = 0;
		return var(tmp);
	}
	else return var();
}
var var::operator/(var &ob)
{
	if (this->id == 1) return var(this->val.intval / int(ob));
	else if (this->id == 2) return var(this->val.doubleval / double(ob));
	else if (this->id == 3)
	{
		size_t size = 0;
		char* tmp = nullptr;
		for (size_t i = 0; i < strlen(this->val.charval); i++)
		{
			if (!strchr(ob, this->val.charval[i]))
			{
				tmp = (char*)realloc(tmp, size + 1);
				tmp[size++] = this->val.charval[i];
			}
		}
		tmp = (char*)realloc(tmp, size + 1);
		tmp[size] = 0;
		return var(tmp);
	}
	else return var();
}
var& var::operator+=(var &ob)
{
	if (this->id == 1) this->val.intval += int(ob);
	else if (this->id == 2)this->val.doubleval += double(ob);
	else if (this->id == 3)
	{
		char* tmp = (char*)malloc(strlen(this->val.charval) + strlen(ob) + 1);
		strcpy_s(tmp, strlen(this->val.charval) + 1, this->val.charval);
		strcat_s(tmp, strlen(this->val.charval) + strlen(ob) + 1, ob);
		if (this->val.charval != nullptr) free(this->val.charval);
		this->val.charval = (char*)malloc(strlen(tmp) + 1);
		strcpy_s(this->val.charval, strlen(tmp) + 1, tmp);
	}
	return *this;
}
var& var::operator-=(var &ob)
{
	if (this->id == 1) this->val.intval -= int(ob);
	else if (this->id == 2) this->val.doubleval -= double(ob);
	else if (this->id == 3 && strlen(this->val.charval) > strlen(ob)) 
	{
		this->val.charval = (char*)realloc(this->val.charval, strlen(this->val.charval) - strlen(ob));

		this->val.charval[strlen(this->val.charval) - strlen(ob)] = 0;
	}
	else if (this->id == 3 && strlen(this->val.charval) <= strlen(ob))
	{
		this->val.charval = (char*)realloc(this->val.charval, 1);
		this->val.charval[0] = 0;
	}
	return *this;
}
var& var::operator*=(var &ob)
{
	if (this->id == 1) this->val.intval *= int(ob);
	else if (this->id == 2)this->val.doubleval *= double(ob);
	else if (this->id == 3)
	{
		size_t size = 0;
		char* tmp = nullptr;
		for (size_t i = 0; i < strlen(this->val.charval); i++)
		{
			if (strchr(ob, this->val.charval[i]))
			{
				tmp = (char*)realloc(tmp, size + 1);
				tmp[size++] = this->val.charval[i];
			}
		}
		tmp = (char*)realloc(tmp, size + 1);
		tmp[size] = 0;
		if (this->val.charval != nullptr) free(this->val.charval);
		this->val.charval = (char*)malloc(strlen(tmp) + 1);
		strcpy_s(this->val.charval, strlen(tmp) + 1, tmp);
	}
	return *this;
}
var& var::operator/=(var &ob)
{
	if (this->id == 1) this->val.intval /= int(ob);
	else if (this->id == 2)this->val.doubleval /= double(ob);
	else if (this->id == 3)
	{
		size_t size = 0;
		char* tmp = nullptr;
		for (size_t i = 0; i < strlen(this->val.charval); i++)
		{
			if (!strchr(ob, this->val.charval[i]))
			{
				tmp = (char*)realloc(tmp, size + 1);
				tmp[size++] = this->val.charval[i];
			}
		}
		tmp = (char*)realloc(tmp, size + 1);
		tmp[size] = 0;
		if (this->val.charval != nullptr) free(this->val.charval);
		this->val.charval = (char*)malloc(strlen(tmp) + 1);
		strcpy_s(this->val.charval, strlen(tmp) + 1, tmp);
	}
	return *this;
}
bool var::operator==(const var &ob)
{
	if (this->id == ob.id)
	{
		if (this->id == 1) return (this->val.intval == ob.val.intval);
		else if (this->id == 2) return (this->val.doubleval == ob.val.doubleval);
		else if (this->id == 3) return ((strcmp(this->val.charval, ob.val.charval) == 0) ? true : false);
	}
	return false;
}
bool var::operator>(const var &ob)
{
	if (this->id == ob.id)
	{
		if (this->id == 1) return (this->val.intval > ob.val.intval);
		else if (this->id == 2) return (this->val.doubleval > ob.val.doubleval);
		else if (this->id == 3) return ((strcmp(this->val.charval, ob.val.charval) == 1) ? true : false);
	}
	return false;
}
var::operator int()
{
	if (this->id == 1) return this->val.intval;
	else if (this->id == 2) return (int)this->val.doubleval;
	else if (this->id == 3) return atoi(this->val.charval);
	else return 0;
}
var::operator double()
{
	if (this->id == 1) return this->val.intval;
	else if (this->id == 2) return this->val.doubleval;
	else if (this->id == 3) return atof(this->val.charval);
	else return 0;
}
var::operator char*()
{
	char *tmp=(char*)malloc(21);
	if (this->id == 1) sprintf_s(tmp, sizeof(tmp), "%d", val.intval);
	else if (this->id == 2) sprintf_s(tmp, sizeof(tmp), "%lf", val.doubleval);
	else if (this->id == 3) return this->val.charval;
	return tmp;
}
std::ostream & operator<<(std::ostream &os, var ob)
{
	if (ob.id == 1) os << ob.val.intval << std::endl;
	else if (ob.id == 2) os << ob.val.doubleval << std::endl;
	else if (ob.id == 3) os << ob.val.charval << std::endl;
	return os;
}