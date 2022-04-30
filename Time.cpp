/* Citation and Sources...
Final Project Milestone ?
Module: Time
Filename: Time.cpp
Version 1.0
Author  Yiou(Anna) Wang
Revision History
-----------------------------------------------------------
Date        Reason
2020/11/09  Preliminary release
2020/11/30  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR -----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds {

	Time& Time::reset()
	{
		m_minutes = getTime();
		return *this;
	}

	Time::Time(unsigned int min)
	{
		m_minutes = min;
	}

	std::ostream& Time::write(std::ostream& ostr) const
	{
		int h = m_minutes / 60;
		int min = m_minutes % 60;
		if (h < 10)
			ostr << "0" << h << ":";
		else
			ostr << h << ":";
		if (min < 10)
			ostr << "0" << min;
		else
			ostr << min;

		return ostr;
	}

	std::istream& Time::read(std::istream& istr)
	{
		int h, min;
		char c;
		istr >> h;
		c = istr.get();
		if (c != ':')
			istr.setstate(ios::failbit);
		istr >> min;
		m_minutes = h * 60 + min;
		return istr;
	}

	Time::operator int() const
	{
		return m_minutes;
	}

	Time& Time::operator*=(int val)
	{
		m_minutes = m_minutes * val;
		return *this;
	}

	Time& Time::operator-=(const Time& D)
	{
		int dif;
		dif = m_minutes - D.m_minutes;
		if (dif < 0)
			dif = m_minutes + 24 * 60 - D.m_minutes;
		m_minutes = dif;
		return *this;
	}

	Time Time::operator-(const Time& ROperand)
	{
		Time LOperand = *this;
		LOperand -= ROperand;
		return LOperand;
	}

	std::ostream& operator<<(std::ostream& ostr, const Time& time)
	{
		return time.write(ostr);
	}

	std::istream& operator>>(std::istream& istr, Time& time)
	{
		return time.read(istr);
	}

}