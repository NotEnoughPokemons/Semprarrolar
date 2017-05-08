#pragma once

#include <iostream>
#include <vector>
#include "Shift.h"

using namespace std;


class Bus{
 public:
	Bus();
	Bus(unsigned int BusNumber, unsigned int DriverID, unsigned int LineID);
  // get methods
	unsigned int getBusNumber() const;
	unsigned int getDriverId() const;
	unsigned int getLineId() const;
	vector<Shift> getSchedule() const;
	void print() const;
  // set methods
    void setDriverId(unsigned int i);
    void setLineId(unsigned int i);
	void addShift(Shift turno);
	void removeShift(Shift turno);
  // other methods 

 private:
	unsigned int busNumber;
	unsigned int driverId;
	unsigned int lineId;
	vector<Shift> schedule;
};

	// default constructor
Bus::Bus()
{
	busNumber = 0;
	driverId = 0;
	lineId = 0;
}
	// class constructor
Bus::Bus(unsigned int BusNumber, unsigned int DriverID, unsigned int LineID)
{
	busNumber = BusNumber;
	driverId = DriverID;
	lineId = LineID;
}

	// get methods
unsigned int Bus::getBusNumber() const
{
	return busNumber;
}

unsigned int Bus::getDriverId() const
{
	return driverId;
}

unsigned int Bus::getLineId() const
{
	return lineId;
}

vector<Shift> Bus::getSchedule() const
{
	return schedule;
}

void Bus::print() const
{
	cout << "BusOrderInLine = " << busNumber << endl;
	cout << "DriverId = " << driverId << endl;
	cout << "lineId = " << lineId << endl;
	cout << "Schedule = " << endl;
	if (schedule.size() == 0)
		cout << "Sem horário";
	else
		for (unsigned int i = 0; i < schedule.size(); i++)
		{
			cout << "-Turno[" << i + 1 << "]:" << endl;
			schedule.at(i).print();
			cout << endl;
		}
}

	// set methods
void Bus::setDriverId(unsigned int i)
{
	driverId = i;
}

void Bus::setLineId(unsigned int i)
{
	lineId = i;
}

// Nota: Esta função não testa se o turno já existe no horário
void Bus::addShift(Shift turno)
{
	schedule.push_back(turno);
}

void Bus::removeShift(Shift turno)
{
	for (unsigned int i = 0; i < schedule.size(); i++)
	{
		if (schedule.at(i).isShiftEqualTo(turno))
		{
			schedule.erase(schedule.begin() + i);
		}
	}
}