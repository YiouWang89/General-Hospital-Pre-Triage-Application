/* Citation and Sources...
Final Project Milestone ?
Module: Time
Filename: PreTriage.cpp
Version 1.0
Author  Yiou(Anna) Wang
Revision History
-----------------------------------------------------------
Date        Reason
2020/11/30  Preliminary release
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
#include <fstream>
#include <cstring>
#include "PreTriage.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include "Menu.h"
#include "utils.h"
using namespace std;
namespace sdds {
	void PreTriage::removePatientFromLineup(int index)
	{
		removeDynamicElement(m_lineup, index, m_lineupSize);
	}
	void PreTriage::load()
	{
		Patient* p = nullptr;
		char type;
		bool ok = false;
		ifstream filein(m_dataFilename);
		cout << "Loading data..." << endl;
		if (filein) {
			filein >> m_averCovidWait;
			filein.ignore(200, ',');
			filein >> m_averTriageWait;
			filein.ignore(200, '\n');
			for (int i = 0; i < maxNoOfPatients; i++) {
				ok = false;
				type = filein.get();
				filein.ignore(200, ',');
				if (type == 'C') {
					p = new CovidPatient;
					ok = true;
				}
				if (type == 'T') {
					p = new TriagePatient;
					ok = true;
				}
				if (ok) {
					p->fileIO(true);
					p->read(filein);
					filein.ignore();
					p->fileIO(false);
					m_lineup[m_lineupSize] = p;
					m_lineupSize++;
				}
			}
			if (m_lineupSize >= 100) {
				cout << "Warning: number of records exceeded" << maxNoOfPatients << endl;
			}
			if (m_lineupSize <= 100) {
				cout << m_lineupSize << " Records imported..." << endl << endl;
			}
		}
		else {
			cout << "No data or bad data file!" << endl << endl;
		}

	}
	int PreTriage::indexOfFirstInLine(char type) const
	{
		int index = -1;
		for (int i = 0; i < m_lineupSize; i++) {
			if (m_lineup[i]->type() == type) {
				index = i;
				i += maxNoOfPatients;
			}
		}
		return index;
	}

	PreTriage::PreTriage(const char* dataFilename) : m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2) {
		m_averCovidWait = 15;
		m_averTriageWait = 5;
		m_dataFilename = new char[strlen(dataFilename) + 1];
		strcpy(m_dataFilename, dataFilename);
		load();
	}

	PreTriage::~PreTriage()
	{
		ofstream fileout(m_dataFilename);
		if (fileout) {
			cout << "Saving Average Wait Times," << endl;
			cout << "   COVID Test: ";
			cout << m_averCovidWait;
			fileout << m_averCovidWait;
			cout << endl << "   Triage: ";
			cout << m_averTriageWait;
			cout << endl;
			fileout << "," << m_averTriageWait << endl;
			cout << "Saving m_lineup..." << endl;
			for (int i = 0; i < m_lineupSize; i++) {
				cout << i + 1 << "- ";
				m_lineup[i]->csvWrite(cout);
				cout << endl;
				m_lineup[i]->csvWrite(fileout);
				fileout << endl;
			}
			for (int i = 0; i < m_lineupSize; i++) {
				delete m_lineup[i];
			}
		}
		delete[] m_dataFilename;
		cout << "done!" << endl;
	}

	void PreTriage::run(void)
	{
		int select;
		do {
			m_appMenu >> select;
			if (select == 1)
				reg();
			if (select == 2)
				admit();
		} while (select != 0);
	}

	void PreTriage::reg()
	{
		bool ok = false;
		int select;
		if (m_lineupSize < maxNoOfPatients) {
				m_pMenu >> select;
				ok = true;
				if (select == 1)
					m_lineup[m_lineupSize] = new CovidPatient;
				if (select == 2)
					m_lineup[m_lineupSize] = new TriagePatient;
			}
		else {
			cout << "Line up full!" << endl;
		}
		if (ok) {
			m_lineup[m_lineupSize]->setArrivalTime();
			cout << "Please enter patient information: " << endl;
			m_lineup[m_lineupSize]->read(cin);
			cout << endl << "******************************************" << endl;
			m_lineup[m_lineupSize]->write(cout);
			cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << endl;
			cout << "******************************************" << endl << endl;
			m_lineupSize++;
		}
	}

	void PreTriage::admit()
	{
		bool ok = false;
		bool go = false;
		char type;
		int select, index;
		m_pMenu >> select;
		if (select == 1) {
			type = 'C';
			ok = true;
		}
		if (select == 2) {
			type = 'T';
			ok = true;
		}

		if (ok) {
			index = indexOfFirstInLine(type);
			if (index >= 0)
				go = true;
		}
		if (go) {
				cout << endl << "******************************************" << endl;
				m_lineup[index]->fileIO(false);
				cout << "Calling for ";
				m_lineup[index]->write(cout);
				cout << "******************************************" << endl << endl;
				setAverageWaitTime(*m_lineup[index]);
				removePatientFromLineup(index);
			}
		

	}

	const Time PreTriage::getWaitTime(const Patient& p) const
	{
		int count=0;
		for (int i = 0; i < m_lineupSize; i++) {
			if (m_lineup[i]->type() == p.type()) {
				count++;
			}
		}
		return Time(count);
	}

	void PreTriage::setAverageWaitTime(const Patient& p)
	{
		int CT = getTime();
		int PTT = Time(p);
		int AWT;
		int PTN = p.number();
		if (p.type() == 'C') {
			AWT = m_averCovidWait;
			m_averCovidWait = ((CT - PTT) + (AWT * (PTN - 1))) / PTN;
		}
		if (p.type() == 'T') {
			AWT = m_averTriageWait;
			m_averTriageWait = ((CT - PTT) + (AWT * (PTN - 1))) / PTN;
		}
		
		
	}
}