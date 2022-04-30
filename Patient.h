/* Citation and Sources...
Final Project Milestone ?
Module: Time
Filename: Patient.h
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
#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
namespace sdds {
	class Patient : public IOAble {
		char* m_name;
		int m_OHIP;
		Ticket m_ticket;
		bool m_flag;
	public:
		Patient(int ticketNum = 0, bool flag = false) :m_ticket(ticketNum) {
			m_name = nullptr;  m_flag = flag;
		};
		Patient(const Patient& patient) = delete;
		Patient& operator=(const Patient&) = delete;
		~Patient();
		virtual char type()const = 0;
		bool fileIO()const;
		void fileIO(const bool flag);
		void setArrivalTime();
		operator Time()const;
		int number()const;
		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);
		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);


	};
	bool operator ==(const Patient& patient, const char cha);
	bool operator ==(const Patient& A, const Patient& B);


}
#endif // !SDDS_PATIENT_H_


