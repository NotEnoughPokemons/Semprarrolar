#pragma once

#include <iostream>
#include <vector>

using namespace std;


class Shift{

 public:
	Shift();
	Shift(unsigned int lineId, unsigned int driverId, unsigned int busNumber, unsigned int startTime, unsigned int endTime);

	// get methdos
	unsigned int getLineId() const;
	unsigned int getDriverId() const;
	unsigned int getBusOrderNumber() const;
	unsigned int getStartTime() const;
	unsigned int getEndTime() const;
	unsigned int getShiftDuration() const;
	bool isShiftEqualTo(Shift turno) const;
	void print() const;

	// set methods
	void setLineId(unsigned int i);
	void setDriverId(unsigned int i);
	void setBusOrderNumber(unsigned int i);
	void setStartTime(unsigned int i);
	void setEndTime(unsigned int i);


 private:
	unsigned int LineId;
	unsigned int DriverId;  
	unsigned int BusOrderNumber; 
	unsigned int StartTime; 
	unsigned int EndTime;   
};

// Default constructor
Shift::Shift()
{
	LineId = 0;
	DriverId = 0;
	BusOrderNumber = 0;
	StartTime = 0;
	EndTime = 0;
}

// Constructor
Shift::Shift(unsigned int lineID, unsigned int driverID, unsigned int busOrderNumber, unsigned int startTime, unsigned int endTime)
{
	LineId = lineID;
	DriverId = driverID;
	BusOrderNumber = busOrderNumber;
	StartTime = startTime;
	EndTime = endTime;
}

// get methods defenition
unsigned int Shift::getLineId() const
{
	return LineId;
}

unsigned int Shift::getDriverId() const
{
	return DriverId;
}

unsigned int Shift::getBusOrderNumber() const
{
	return BusOrderNumber;
}

unsigned int Shift::getStartTime() const
{
	return StartTime;
}

unsigned int Shift::getEndTime() const
{
	return EndTime;
}

unsigned int Shift::getShiftDuration() const
{
	return EndTime - StartTime;
}

bool Shift::isShiftEqualTo(Shift turno) const
{
	if (
		LineId == turno.LineId &&
		BusOrderNumber == turno.BusOrderNumber &&
		DriverId == turno.DriverId &&
		StartTime == turno.StartTime &&
		EndTime == turno.EndTime 
		)
			return true;
	else
			return false;

}

 void Shift::print() const
{
	cout << " -BusLineId = " << LineId << endl;
	cout << " -DriverId = " << DriverId << endl;
	cout << " -BusOrderNumber = " << BusOrderNumber << endl;
	cout << " -StartTime = dia " << StartTime / 1440 << ", " << (StartTime / 60) % 24 << " horas e " << StartTime % 60 << " minutos" << endl;
	cout << " -EndTime = dia " << EndTime / 1440 << ", " << (EndTime / 60) % 24 << " horas e " << EndTime % 60 << " minutos" << endl;
}

// set methods defenition
void Shift::setLineId(unsigned int i)
{
	LineId = i;
}

void Shift::setDriverId(unsigned int i)
{
	DriverId = i;
}

void Shift::setBusOrderNumber(unsigned int i)
{
	BusOrderNumber = i;
}

void Shift::setStartTime(unsigned int i)
{
	StartTime = i;
}

void Shift::setEndTime(unsigned int i)
{
	EndTime = i;
}