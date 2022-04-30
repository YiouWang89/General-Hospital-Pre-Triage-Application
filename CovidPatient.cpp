/* Citation and Sources...
Final Project Milestone ?
Module: Time
Filename: CovidPatient.cpp
Version 1.0
Author  Yiou(Anna) Wang
Revision History
-----------------------------------------------------------
Date        Reason
2020/11/23  Preliminary release
2020/11/30  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR -----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/

#include "CovidPatient.h"
using namespace std;
namespace sdds {
	int nextCovidTicket = 1;

	CovidPatient::CovidPatient() : Patient(nextCovidTicket)
	{
		nextCovidTicket++;
	}

	char CovidPatient::type() const
	{
		return 'C';
	}

	std::ostream& CovidPatient::csvWrite(std::ostream& ostr) const
	{
		return Patient::csvWrite(ostr);
	}

	std::istream& CovidPatient::csvRead(std::istream& istr)
	{
		Patient::csvRead(istr);
		nextCovidTicket = Patient::number() + 1;
		return istr;
	}

	std::ostream& CovidPatient::write(std::ostream& ostr) const
	{
		bool ok = Patient::fileIO();
		if (ok)
			csvWrite(ostr);
		else {
			ostr << "COVID TEST" << endl;
			Patient::write(ostr);
			ostr << endl;
		}
		return ostr;
	}

	std::istream& CovidPatient::read(std::istream& istr)
	{
		bool ok = Patient::fileIO();
		if (ok)
			csvRead(istr);
		else
			Patient::read(istr);
		return istr;
	}

}