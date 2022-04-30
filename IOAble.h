/* Citation and Sources...
Final Project Milestone ?
Module: Time
Filename: IOAble.h
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
OR ----------------------------------------------------c-------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SDDS_IOABLE_H_
#define SDDS_IOABLE_H_
#include <iostream>
namespace sdds {
	class IOAble {
	public:
		virtual std::ostream& csvWrite(std::ostream& ostr)const = 0;
		virtual std::istream& csvRead(std::istream& istr) = 0;
		virtual std::ostream& write(std::ostream& ostr)const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual ~IOAble() {};
	};
	std::ostream& operator<<(std::ostream& ostr, const IOAble& IOA);
	std::istream& operator>>(std::istream& istr, IOAble& IOA);
}
#endif // !SDDS_IOABLE_H_
