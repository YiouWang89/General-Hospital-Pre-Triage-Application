/* Citation and Sources...
Final Project Milestone ?
Module: Time
Filename: Time.h
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
#ifndef SDDS_TIME_H
#define SDDS_TIME_H
#include <iostream>
namespace sdds {
    class Time {
        unsigned int m_minutes;
    public:
        Time& reset();
        Time(unsigned int min = 0);
        std::ostream& write(std::ostream& ostr) const;
        std::istream& read(std::istream& istr);
        operator int()const;
        Time& operator *= (int val);
        Time& operator-=(const Time& D);
        Time operator-(const Time& ROperand);
    };
    // helper operator << and >> prototypes
    std::ostream& operator<<(std::ostream& ostr, const Time& time);
    std::istream& operator>>(std::istream& istr, Time& time);

}

#endif // !SDDS_TIME_H

