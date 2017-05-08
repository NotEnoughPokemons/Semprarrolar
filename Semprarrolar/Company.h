#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Bus.h"
#include "Driver.h"
#include "Line.h"
#include "Shift.h"

using namespace std;


class Empresa{
 public:
	 Empresa(string nome, string fichCondutores, string fichLinhas);
  // metodos get
  string getNome() const;
  // metodos set
  // outros metodos
  void distribuiServico(); // funcao que implementa a afectacao de servico

 private:
  string nome;
  vector<Driver> condutores;
  vector<Line> linhas;
};
