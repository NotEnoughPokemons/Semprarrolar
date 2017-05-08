#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Shift.h"
#include <algorithm>

using namespace std;


//********** Para pôr em source ou class de empresas
const int hora_inicio = 8 * 60;
const int hora_fim = 20 * 60;
const int dias_semana_trabalho = 5; //Tem de ser dias consecutivos



class Rest {
	Rest();
	Rest(unsigned int SrR, unsigned int StR);

public:
	// get methods
	unsigned int getStartRest() const;
	unsigned int getEndRest() const;
	void print() const;
	// set methods
	void setStartRest(unsigned int i);
	void setEndRest(unsigned int i);

private:
	unsigned int StartRest;
	unsigned int EndRest;
};

Rest::Rest()
{
	StartRest = 0;
	EndRest = 0;
}

Rest::Rest(unsigned int SrR, unsigned int StR)
{
	StartRest = SrR;
	EndRest = StR;
}

unsigned int Rest::getStartRest() const
{
	return StartRest;
}

unsigned int Rest::getEndRest() const
{
	return EndRest;
}

void Rest::print() const
{
	cout << " -StartTime = dia " << StartRest / 1440 << ", " << (StartRest / 60) % 24 << " horas e " << StartRest % 60 << " minutos" << endl;
	cout << " -EndTime = dia " << EndRest / 1440 << ", " << (EndRest / 60) % 24 << " horas e " << EndRest % 60 << " minutos" << endl;
}

void Rest::setStartRest(unsigned int startRest)
{
	StartRest = startRest;
}

void Rest::setEndRest(unsigned int endRest)
{
	EndRest = endRest;
}



class Driver{
 public:
	Driver(unsigned int iDCondutor, string name);
	Driver(unsigned int iDCondutor, string name, unsigned int shiftMaxDuration, unsigned int maxWeekWorkingTime, unsigned int minRestTime);
  
	// get methods
	unsigned int getID() const;
	string getName() const;
	unsigned int getShiftMaxDuration() const;
	unsigned int getMaxWeekWorkingTime() const;
	unsigned int getMinRestTime() const;
	vector<Shift> getShifts() const;
	vector<Rest> getRests() const;
	void printShifts() const;			// Mainly for debbuging
	void printRests() const;			// Mainly for debbuging
	void printAll() const;				// Mainly for debbuging

	// set methods
	void setName(string name);
	void setID(unsigned int iD);
	void setShiftMaxDuration(unsigned int shiftMaxDurationi);
	void setMaxWeekWorkingTime(unsigned int maxWeekWorkingTime);
	void setMinRestTime(unsigned int minRestTime);
	void addShift(Shift turno);
	void removeShift(Shift turno);


 private:
	unsigned int ID;	// Driver's ID
	string Name;	// Driver's name
	unsigned int ShiftMaxDuration;	// Driver's max amount of hours per shift
	unsigned int MaxWeekWorkingTime;	// Driver's max amount of hours per week
	unsigned int MinRestTime;	// Driver's min amout of hours of rest between shifts
	vector<Shift> Shifts;	// Driver's assigned shifts
	vector<Rest> Rests; // Driver's rests

};

// default constructor
Driver::Driver(unsigned int iDCondutor, string name)
{
	ID = iDCondutor;
	Name = name;
}

// class constructor
Driver::Driver(unsigned int iDCondutor, string name, unsigned int shiftMaxDuration, unsigned int maxWeekWorkingTime, unsigned int minRestTime)
{
	ID = iDCondutor;
	Name = name;
	ShiftMaxDuration = shiftMaxDuration;
	MaxWeekWorkingTime = maxWeekWorkingTime;
	MinRestTime = minRestTime;
}

	// get methods

unsigned int Driver::getID() const
{
	return ID;
}

string Driver::getName() const
{
	return Name;
}

unsigned int Driver::getShiftMaxDuration() const
{
	return ShiftMaxDuration;
}

unsigned int Driver::getMaxWeekWorkingTime() const
{
	return MaxWeekWorkingTime;
}

unsigned int Driver::getMinRestTime() const
{
	return MinRestTime;
}

vector <Shift> Driver::getShifts() const
{
	return Shifts;
}

vector <Rest> Driver::getRests() const
{
	return Rests;
}

void Driver::printShifts() const
{
	if (Shifts.size() == 0)
		cout << " -Sem turnos" << endl;
	else 
		for (unsigned int i = 0; i < Shifts.size(); i++)
		{
			cout << "-Turno[" << i + 1 << "]:" << endl;
			Shifts.at(i).print();
			cout << endl;
		}
}

void Driver::printRests() const
{
	if (Rests.size() == 0)
		cout << " -Sem descansos" << endl;
	else
		for (unsigned int i = 0; i < Shifts.size(); i++)
		{
			cout << "-Descanso[" << i + 1 << "]:" << endl;
			Rests.at(i).print();
			cout << endl;
		}
}

void Driver::printAll() const
{
	cout << "Name = " << Name << endl;
	cout << "DriverID = " << ID << endl;
	cout << "ShiftMaxDuration = " << ShiftMaxDuration << endl;
	cout << "MaxWeekWorkingTime = " << MaxWeekWorkingTime << endl;
	cout << "MinRestTime = " << MinRestTime << endl;
	cout << "Shifts = " << endl;
	printShifts();
	cout << "Rests = " << endl;
	printRests();
	cout << endl;
}

	// set methods

void Driver::setName(string name)
{
	Name = name;
}

void Driver::setID(unsigned int iD)
{
	ID = iD;
}

void Driver::setShiftMaxDuration(unsigned int shiftMaxDuration)
{
	ShiftMaxDuration = shiftMaxDuration;
}

void Driver::setMaxWeekWorkingTime(unsigned int maxWeekWorkingTime)
{
	MaxWeekWorkingTime = maxWeekWorkingTime;
}

void Driver::setMinRestTime(unsigned int minRestTime)
{
	MinRestTime = minRestTime;
}

//Nota: Esta função não testa se o condutor já tem outros turnos à mesma hora, se já passou o limite de horas consecutivas, etc..
void Driver::addShift(Shift turno)
{
	Shifts.push_back(turno);
}

void Driver::removeShift(Shift turno)
{
	for (unsigned int i = 0; i < Shifts.size(); i++)
		if (Shifts.at(i).isShiftEqualTo(turno))
			Shifts.erase(Shifts.begin() + i);
}