/* Citation and Sources...
Final Project Milestone ?
Module: Menu
Filename: Menu.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include <cstring> 
#include "utils.h"
#include "Menu.h"
using namespace std;
namespace sdds {
	Menu::Menu(const char* text, int NoOfSelections)
	{
		m_text = nullptr; //Initiallised
		m_text = new char[strlen(text) + 1];
		strcpy(m_text, text);
		m_noOfSel = NoOfSelections;
	}
	Menu::~Menu()
	{
		delete[] m_text;
	}
	std::ostream& Menu::display(std::ostream& ostr) const
	{
		ostr << m_text << endl;
		ostr << "0- Exit" << endl << "> ";
		return ostr;
	}
	int& Menu::operator>>(int& Selection)
	{
		int selec;
		display();
		cin >> selec;
		if (selec >= 0 && selec <= m_noOfSel)
			Selection = selec;
		else
			do {
				std::cout << "Invalid value enterd, retry [0 <= value <=" << m_noOfSel << "]: ";
				std::cin >> selec;
				Selection = selec;
				if (cin.fail())
					Selection = getInt();
			} while (Selection < 0 || Selection > m_noOfSel);

			return Selection;
	}
}