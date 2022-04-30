/* Citation and Sources...
Final Project Milestone ?
Module: Time
Filename: Patient.cpp
Version 1.0
Author  Yiou(Anna) Wang
Revision History
-----------------------------------------------------------
Date        Reason
2020/11/17  Preliminary release
2020/11/30  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR ----------------------------------------------------c-------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "utils.h"
using namespace std;
namespace sdds {
	Patient::~Patient()
	{
		delete[] m_name;
	}
	bool Patient::fileIO() const
	{
		return m_flag;
	}
	void Patient::fileIO(const bool flag)
	{
		m_flag = flag;
	}

	void Patient::setArrivalTime()
	{
		m_ticket.resetTime();
	}

	Patient::operator Time() const
	{
		return Time(m_ticket);
		//return m_ticket.operator sdds::Time();
	}

	int Patient::number() const
	{
		return m_ticket.number();
	}

	std::ostream& Patient::csvWrite(std::ostream& ostr) const
	{
		ostr << type() << "," << m_name << "," << m_OHIP << ",";
		m_ticket.csvWrite(ostr);
		return ostr;
	}

	std::istream& Patient::csvRead(std::istream& istr)
	{
		char name[51]{};
		istr.get(name, 51, ',');
		if (name[0] != '\0') {
			delete[] m_name;
			m_name = new char[strlen(name) + 1];
			strcpy(m_name, name);
			istr.ignore(100, ',');
			istr >> m_OHIP;
			istr.ignore(100, ',');
			m_ticket.csvRead(istr);
		}
		return istr;
	}

	std::ostream& Patient::write(std::ostream& ostr) const
	{
		m_ticket.write(ostr);
		ostr << endl;
		ostr << m_name << ", OHIP: " << m_OHIP;
		return ostr;
	}

	std::istream& Patient::read(std::istream& istr)
	{
		char name[51]{ 0 };
		int temp = -1;
		cout << "Name: ";
		istr.get(name, '\n');
		delete[] m_name;
		m_name = nullptr;
		m_name = new char[strlen(name) + 1];
		strcpy(m_name, name);
		istr.ignore(100, '\n');
		cout << "OHIP: ";
		istr >> temp;
		istr.ignore(100, '\n');
		if (temp >= 100000000 && temp <= 999999999)
			m_OHIP = temp;
		else {
			do {
				if (istr.fail()) {
					cout << "Bad integer value, try again: ";
					istr.clear();
					istr.ignore(200, '\n');
					istr >> m_OHIP;
				}
				else {
					cout << "Invalid value enterd, retry [100000000 <= value <= 999999999]: ";
					istr >> m_OHIP;
				}
			} while (m_OHIP <= 100000000 || m_OHIP >= 999999999);
		};
		return istr;
	}



	bool operator==(const Patient& patient, const char cha)
	{
		bool ok = false;
		if (patient.type() == cha)
			ok = true;
		return ok;
	}

	bool operator==(const Patient& A, const Patient& B)
	{
		bool ok = false;
		if (A.type() == B.type())
			ok = true;
		return ok;
	}

}