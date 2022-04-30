/* Citation and Sources...
Final Project Milestone ?
Module: Time
Filename: IOAble.cpp
Version 1.0
Author  Yiou(Anna) Wang
Revision History
-----------------------------------------------------------
Date        Reason
2020/11/14  Preliminary release
2020/11/30  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR -----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#include <iostream>
#include "IOAble.h"
using namespace std;
namespace sdds {
	std::ostream& operator<<(std::ostream& ostr, const IOAble& IOA)
	{
		IOA.write(ostr);
		return ostr;
	}
	std::istream& operator>>(std::istream& istr, IOAble& IOA)
	{
		IOA.read(istr);
		return istr;
	}
}