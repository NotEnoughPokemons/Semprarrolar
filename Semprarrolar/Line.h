#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Line
{
 public:
	Line();
	Line(unsigned int ID, unsigned int Freq);
	Line(unsigned int ID, unsigned int Freq, vector<string> BusStopList, vector<int> TimesList);

	// get methods
	unsigned int getId() const;
	vector<string> getBusStops() const;
	vector<int> getTimesList() const;
	unsigned int getFreq() const;
	// Shows all line's information
	void print() const;
	//set methods
	void setId(unsigned int i);
	void setFreq(unsigned int f);
	// @param stop: Stop's name 
	// @param t: Time from previous stop to the next one
	// @param p: Stop's order in line (starting from 1)
	// The functiont tests if stop already exists and, if so, adds it
	void addBusStop(string stop, unsigned int p, unsigned int t);
	// @param stop: Stop's name to remove
	void removeBusStop(string stop);

 private:
  unsigned int id, freq;
  vector<string> busStopList;
  vector<int> timesList;
};

// default constructor
Line::Line()
{
	id = 0;
	freq = 0;
}

//Test Construcor
Line::Line(unsigned int ID, unsigned int Freq)
{
	id = ID;
	freq = Freq;
}

// constructor
Line::Line(unsigned int ID, unsigned int Freq, vector<string> BusStopList, vector<int> TimesList)
{
	id = ID;
	freq = Freq;
	vector<string> busStopList = BusStopList;
	vector<int> timesList = TimesList;
}

// get methods
unsigned int Line::getId() const
{
	return id;
}

unsigned int Line::getFreq() const
{
	return freq;
}

vector<string> Line::getBusStops() const
{
	return busStopList;
}

vector<int> Line::getTimesList() const
{
	return timesList;
}

void Line::print() const
{
	cout << "Id = " << id << endl;
	cout << "Freq = " << freq << endl;
	cout << "BusStopList = ";
	for (unsigned int i = 0; i < busStopList.size(); i++)
	{
		cout << busStopList.at(i);
		if (i + 1 != busStopList.size())
			cout << ", ";
	}
	if (busStopList.size() == 0)
		cout << "Sem paragens atribuidas.";
	cout << endl;
	cout << "TimesList = ";
	for (unsigned int i = 0; i < timesList.size(); i++)
	{
		cout << timesList.at(i);
		if (i + 1 != timesList.size())
			cout << ", ";
	}
	if (timesList.size() == 0)
		cout << "Sem frequencias atribuidas.";
	cout << endl;
}

// set methods
void Line::setId(unsigned int i)
{
	id = i;
}

void Line::setFreq(unsigned int f)
{
	freq = f;
}

void Line::addBusStop(string stop, unsigned int p, unsigned int t)
{

	if (busStopList.size() == 0)
	{
		busStopList.push_back(stop);
	}
	else
	{
		vector <string> newVectorS;
		vector <int> newVectorI;
		// Adicionar linha
		for (unsigned int i = 0; i < p - 1; i++)
			newVectorS.push_back(busStopList.at(i));
		newVectorS.push_back(stop);
		for (unsigned int i = p - 1; i < busStopList.size(); i++)
			newVectorS.push_back(busStopList.at(i));
		// Adicionar tempo de espera
		for (unsigned int i = 0; i < p - 1; i++)
			newVectorI.push_back(timesList.at(i));
		newVectorI.push_back(t);
		for (unsigned int i = p - 1; i < timesList.size(); i++)
			newVectorI.push_back(timesList.at(i));


		busStopList = newVectorS;
		timesList = newVectorI;
	}
}

void Line::removeBusStop(string stop)
{
	bool canRemove = false;
	unsigned int p;
	// Testa se a paragem existe e se pode ser removida
	for (unsigned int i = 0; i < busStopList.size(); i++)
		if (busStopList.at(i) == stop)
		{
			canRemove = true;
			p = i;
			break;
		}
	// Remover a paragem
	if (canRemove)
	{
		if (busStopList.size() == 1)
			busStopList.pop_back();
		else
		{
			busStopList.erase(busStopList.begin() + p);
			timesList.erase(timesList.begin() + p - 1);
		}
		
	}
}