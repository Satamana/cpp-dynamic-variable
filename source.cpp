#include "stdafx.h"
#include "var.h"
void main()
{
	var a = 15;
	var b = "Hello";
	var c = 7.8;
	var d = "50";
	b = a + d;
	std::cout << b;
	if (a == b) std::cout << "Equal" << std::endl;
	else std::cout << "Not Equal" << std::endl;
	a = 10;
	b = "120";
	c = a + b;
	std::cout << c;
	c = b + a;
	std::cout << c;
	a = "Microsoft";
	b = "Windows";
	c = a * b;
	std::cout << c;
	c = a / b;
	std::cout << c;
}