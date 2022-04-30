/* Citation and Sources...
Final Project Milestone ?
Module: Time
Filename: TriagePatient.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "TriagePatient.h"
using namespace std;
namespace sdds {
	int nextTriageTicket = 1;


	TriagePatient::TriagePatient() :Patient(nextTriageTicket)
	{
		m_symptoms = nullptr;
		nextTriageTicket++;
	}

	char TriagePatient::type() const
	{
		return 'T';
	}

	std::ostream& TriagePatient::csvWrite(std::ostream& ostr) const
	{
		Patient::csvWrite(ostr);
		ostr << "," << m_symptoms;
		return ostr;
	}

	std::istream& TriagePatient::csvRead(std::istream& istr)
	{
		char symptoms[511];
		delete[] m_symptoms;
		Patient::csvRead(istr);
		istr.ignore(200, ',');
		istr.get(symptoms, 511, '\n');
		m_symptoms = new char[strlen(symptoms) + 1];
		strcpy(m_symptoms, symptoms);
		nextTriageTicket = Patient::number() + 1;
		return istr;
	}

	std::ostream& TriagePatient::write(std::ostream& ostr) const
	{
		bool ok = Patient::fileIO();
		if (ok)
			csvWrite(ostr);
		else {
			ostr << "TRIAGE" << endl;
			Patient::write(ostr);
			ostr << endl << "Symptoms:" << m_symptoms << endl;
		}
		return ostr;
	}

	std::istream& TriagePatient::read(std::istream& istr)
	{
		char symptoms[511];
		bool ok = Patient::fileIO();
		if (ok)
			csvRead(istr);
		else {
			delete[] m_symptoms;
			Patient::read(istr);
			std::cout << "Symptoms:";
			istr.get(symptoms, 511, '\n');
			istr.ignore(200, '\n');
			m_symptoms = new char[strlen(symptoms) + 1];
			strcpy(m_symptoms, symptoms);
		}
		return istr;
	}

	TriagePatient::~TriagePatient()
	{
		delete[] m_symptoms;
	}

}