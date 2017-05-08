#include <iostream>
#include <string>
#include <vector>
#include "Bus.h"
#include "Driver.h"
#include "Line.h"
#include "Shift.h"
using namespace std;
// Extra Line for testing git hub

//************Variable declaration*************//

// These vectores are here while reading from file option isn't avalable
vector <Driver> condutores = {
			Driver(1, "Antonio Manuel", 4 * 60, 36 * 60, 2 * 60),	// É multiplicado por 60 pois o tempo é armazenado em minutos
			Driver(3, "Joaquim Belmiro", 8 * 60, 48 * 60, 4 * 60)
			};
vector <Line> linhas = {
			Line(201, 20, {"Paranhos", "Monte dos Burgos", "ISEP", "Hospital de Sao Joao"}, {10, 20, 45}), 
			Line(207, 10,{ "Aliados", "Carmo", "Galiza", "Rotunda da Boavista" },{ 5, 20, 20 }),
			Line(505, 30,{ "Matosinhos", "7 Bicas", "Rotunda dos Produtos Estrela", "Senhora da Hora" },{ 40, 30, 45 }),
			Line(505, 30,{ "Ribeira", "Alfandega", "Fluvial", "Foz" },{ 10, 25, 55 }),
			};


//***********Function Declaration**************//

// Temporary function for others that haven't been implemented
int outOfOrder();
// Adds a driver
int addDriver();
// Displays all driver's information
int seeAllDrivers();
// Removes a driver
int removeDriver();
// Checks for the existence of a driver using its name
bool existsDriver(string name);
// Displays driver's shifts
int seeDriverShifts();
// Edits driver'ID
int editDriverID(string name);
// Edits driver's name
int editDriverName(string name);
// Edits driver's shift max duration
int editDriverShiftMaxDuration(string name);
// Edits driver's max week working time
int editDriverMaxWeekWorkingTime(string name);
// Edits driver's min rest time
int editDriverMinRestTime(string name);
// See Drivers whose max hours per week haven't been reached
void seeDriverWhithoutFullScheduele();

// Menu Controls
int mainMenu();
int opcao1Menu();
int opcao1_1Menu();
int opcao1_1_2Menu();
// All Menu Displays
void mainMenuDisplay();
void opcao1MenuDisplay();
void opcao1_1MenuDisplay();
void opcao1_1_2MenuDisplay();


//*****************//
int main()
{
	mainMenu();
	return 0;
}
//*****************//


//**************Function Definition*************//

int outOfOrder()
{
	system("CLS");
	cout << "Funcao ainda nao implementada." << endl;
	cout << "Escreva 0 para voltar atras: ";
	string temps;
	cin >> temps;
	//Teste se o input é válido, caso contrário continua a pedir um novo até surgir um que seja
	while (cin.fail() || !(temps == "0" || temps == "zero"))
	{
		system("CLS");
		cout << "Input nao e valido." << endl << endl;
		cout << "Funcao ainda nao implementada." << endl;
		cout << "Escreva 0 para voltar atras: ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> temps;
	}
	return 0;
}
bool existsDriver(string name)
{
	for (unsigned int i = 0; i < condutores.size(); i++)
		if (condutores.at(i).getName() == name)
			return true;
	return false;
}
int addDriver()
{
	bool redo = false;
	string name;
	unsigned int id, Max_Horas_Turno, Max_Horas_Semana, Descanso;
	system("CLS");
	cout << "A adicionar um condutor" << endl;
	cout << "Escreva " << -1 << " a qualquer momento para voltar atras" << endl;
	cout << "Escreva o nome do condutor a adicionar: ";
	cin.clear();
	cin.ignore(1000, '\n');
	getline(cin, name);
	if (name == "-1")
		return 0;
	cout << "Escreva o Id do condutor: ";
	cin >> id;
	// Caso id já exista, é preciso inserir outro valor
	if (id == -1)
		return 0;
	cout << "Escreva o numero maximo de horas por turno do condutor: ";
	cin >> Max_Horas_Turno;
	if (Max_Horas_Turno == -1)
		return 0;
	cout << "Escreva o numero maximo de horas por semana do condutor: ";
	cin >> Max_Horas_Semana;
	if (Max_Horas_Semana == -1)
		return 0;
	cout << "Escreva as horas de descanso do condutor: ";
	cin >> Descanso;
	if (Descanso == -1)
		return 0;
	Driver temp = Driver(id, name, Max_Horas_Turno, Max_Horas_Semana, Descanso);
	condutores.push_back(temp);
	system("CLS");
	cout << "A introduzir o condutor:" << endl;
	temp.printAll();
	system("pause");
	return 0;
}
int seeAllDrivers()
{
	system("CLS");
	cout << "All Driver Information:" << endl << endl;
	for (unsigned int i = 0; i < condutores.size(); i++)
		condutores.at(i).printAll();
	system("pause");
	return 0;
}
int removeDriver()
{
	string name;
	bool continuar = false;
	system("CLS");
	cout << "Escreva o nome do condutor a remover (0 para voltar atras):" << endl;
	cin.clear();
	cin.ignore(1000, '\n');
	getline(cin, name);
	if (name == "0")
		return 0;
	continuar = existsDriver(name);
	// Ask for a new name if the first input isn't a driver
	while (!continuar)
	{
		system("CLS");
		cout << "Nome de condutor nao existe." << endl;
		cout << "Escreva o nome do condutor a remover:" << endl;
		cout << " (Escreva 0 para voltar atras) " << endl;
		getline(cin, name);
		continuar = existsDriver(name);
		if (name == "0")
			return 0;
	}
	system("cls");
	cout << "A remover o condutor: " << name;
	for (unsigned int i = 0; i < condutores.size(); i++)
		if (condutores.at(i).getName() == name)
		{
			condutores.at(i).printAll();
			condutores.erase(condutores.begin() + i);
		}
	system("pause");
	return 0;
}
int seeDriverShifts()
{
	string name;
	bool continuar = false;
	system("CLS");
	cout << "Escreva o nome do condutor cujos turnos pretende ver (0 para voltar atras):" << endl;
	cin.clear();
	cin.ignore(1000, '\n');
	getline(cin, name);
	if (name == "0")
		return 0;
	continuar = existsDriver(name);
	while (!continuar)
	{
		system("CLS");
		cout << "Nome de condutor nao existe." << endl;
		cout << "Escreva o nome do condutor cujos turnos pretende ver:" << endl;
		cout << " (Escreva 0 para voltar atras) " << endl;
		getline(cin, name);
		continuar = existsDriver(name);
		if (name == "0")
			return 0;
	}
	for (unsigned int i = 0; i < condutores.size(); i++)
		if (condutores.at(i).getName() == name)
			condutores.at(i).printShifts();
	system("pause");
	return 0;
}
int editDriverID(string name)
{
	int id;
	system("cls");
	cout << "Escreva o novo ID do condutor: " << name << endl;
	cout << " (Escreva -1 para voltar atras)" << endl;
	cout << "Novo ID: ";
	cin >> id;
	if (id == -1)
		return 0;
	for (unsigned int i = 0; i < condutores.size(); i++)
		if (condutores.at(i).getName() == name)
			condutores.at(i).setID(id);
	return 0;
}
int editDriverName(string name)
{
	string newName;
	system("cls");
	cout << "Escreva o novo nome do condutor: " << name << endl;
	cout << " (Escreva -1 para voltar atras)" << endl;
	cout << "Novo nome: ";
	cin >> newName;
	if (newName == "-1")
		return 0;
	for (unsigned int i = 0; i < condutores.size(); i++)
		if (condutores.at(i).getName() == name)
			condutores.at(i).setName(newName);
	return 0;
}
int editDriverShiftMaxDuration(string name)
{
	int ShiftMaxDuration;
	system("cls");
	cout << "Escreva a nova duracao maxima do turno do condutor: " << name << endl;
	cout << " (Escreva -1 para voltar atras)" << endl;
	cout << "Nova duracao: ";
	cin >> ShiftMaxDuration;
	if (ShiftMaxDuration == -1)
		return 0;
	for (unsigned int i = 0; i < condutores.size(); i++)
		if (condutores.at(i).getName() == name)
			condutores.at(i).setShiftMaxDuration(ShiftMaxDuration);
	return 0;
}
int editDriverMaxWeekWorkingTime(string name)
{
	int MaxWeekWorkingTime;
	system("cls");
	cout << "Escreva o novo maximo de horas por semana do condutor: " << name << endl;
	cout << " (Escreva -1 para voltar atras)" << endl;
	cout << "Novo maximo: ";
	cin >> MaxWeekWorkingTime;
	if (MaxWeekWorkingTime == -1)
		return 0;
	for (unsigned int i = 0; i < condutores.size(); i++)
		if (condutores.at(i).getName() == name)
			condutores.at(i).setMaxWeekWorkingTime(MaxWeekWorkingTime);
	return 0;
}
int editDriverMinRestTime(string name)
{
	int MinRestTime;
	system("cls");
	cout << "Escreva o novo minimo de horas de descanso do condutor: " << name << endl;
	cout << " (Escreva -1 para voltar atras)" << endl;
	cout << "Novo minimo: ";
	cin >> MinRestTime;
	if (MinRestTime == -1)
		return 0;
	for (unsigned int i = 0; i < condutores.size(); i++)
		if (condutores.at(i).getName() == name)
			condutores.at(i).setMinRestTime(MinRestTime);
	return 0;
}
void seeDriverWhithoutFullScheduele()
{
	unsigned int contagem; // Para guardar os minutos de trabalho de cada condutor
	system("cls");
	cout << "Listagem de todos condutores sem o servico completo atribuido:" << endl << endl;
	for (unsigned int i = 0; i < condutores.size(); i++)
	{
		// Test to check if driver has assigned shifts
		if (condutores.at(i).getShifts().size() == 0)
			cout << "O condutor " << condutores.at(i).getName() << " ainda nao tem nenhum turno atribuido." << endl;
		else
		{
			contagem = 0;
			for (unsigned int s = 0; condutores.at(i).getShifts().size(); s++)
				// To add how long a shift lasts to current amout of time
				contagem += condutores.at(i).getShifts().at(s).getShiftDuration();
			if (contagem < condutores.at(i).getMaxWeekWorkingTime())
				cout << "O condutor " << condutores.at(i).getName() << " ainda tem " << (condutores.at(i).getMaxWeekWorkingTime() - contagem) / 60 
					 << " horas e " << (condutores.at(i).getMaxWeekWorkingTime() - contagem) % 60 << "minutos por fazer." << endl;
		}
	}
	cout << endl;
	system("pause");
}

// Menu Function Definitions
int mainMenu()
{
	while (true)
	{
		system("CLS");
		mainMenuDisplay();
		int tempi;
		cin >> tempi;
		//Teste se o input é válido, caso contrário continua a pedir um novo até surgir um que seja
		while (cin.fail() || !(0 <= tempi && tempi <= 8))
		{
			system("CLS");
			cout << "Operacao nao existe ou input nao e valido." << endl << endl;
			mainMenuDisplay();
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> tempi;
		}
		if (tempi == 0)
			return 0;
		if (tempi == 1)
			opcao1Menu();
		if (tempi == 2)
			outOfOrder();
		if (tempi == 3)
			outOfOrder();
		if (tempi == 4)
			outOfOrder();
		if (tempi == 5)
			outOfOrder();
		if (tempi == 6)
			outOfOrder();
		if (tempi == 7)
			seeDriverWhithoutFullScheduele();
		if (tempi == 8)
			outOfOrder();
	}
}
int opcao1Menu()
{
	while (true)
	{
		system("CLS");
		opcao1MenuDisplay();
		int tempi;
		cin >> tempi;
		//Teste se o input é válido, caso contrário continua a pedir um novo até surgir um que seja
		while (cin.fail() || !(0 <= tempi && tempi <= 3))
		{
			system("CLS");
			cout << "Operacao nao existe ou input nao e valido." << endl << endl;
			opcao1MenuDisplay();
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> tempi;
		}
		if (tempi == 0)
			return 0;
		if (tempi == 1)
			opcao1_1Menu();
		if (tempi == 2)
			seeDriverShifts();
		if (tempi == 3)
			seeDriverWhithoutFullScheduele();
	}
}
int opcao1_1Menu()
{
	while (true)
	{
		system("CLS");
		opcao1_1MenuDisplay();
		int tempi;
		cin >> tempi;
		//Teste se o input é válido, caso contrário continua a pedir um novo até surgir um que seja
		while (cin.fail() || !(0 <= tempi && tempi <= 4))
		{
			system("CLS");
			cout << "Operacao nao existe ou input nao e valido." << endl << endl;
			opcao1_1MenuDisplay();
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> tempi;
		}
		if (tempi == 0)
			return 0;
		if (tempi == 1)
			addDriver();
		if (tempi == 2)
			opcao1_1_2Menu();
		if (tempi == 3)
			removeDriver();
		if (tempi == 4)
			seeAllDrivers();
	}
}
int opcao1_1_2Menu()
{
	string name;
	bool continuar = false;
	system("CLS");
	cout << "Escreva o nome do condutor a alterar (0 para voltar atras):" << endl;
	cin.clear();
	cin.ignore(1000, '\n');
	getline(cin, name);
	if (name == "0")
		return 0;
	continuar = existsDriver(name);
	while (!continuar)
			{
				system("CLS");
				cout << "Nome de condutor nao existe." << endl;
				cout << "Escreva o nome do condutor a remover:" << endl;
				cout << " (Escreva 0 para voltar atras) " << endl;
				getline(cin, name);
				continuar = existsDriver(name);
				if (name == "0")
					return 0;
			}
	system("cls");
	cout << "A alterar o condutor: " << name << endl << endl;
	opcao1_1_2MenuDisplay();
	int tempi;
	cin >> tempi;
	//Teste se o input é válido, caso contrário continua a pedir um novo até surgir um que seja
	while (cin.fail() || !(0 <= tempi && tempi <= 5))
			{
				system("CLS");
				cout << "Operacao nao existe ou input nao e valido." << endl << endl;
				opcao1_1_2MenuDisplay();
				cin.clear();
				cin.ignore(1000, '\n');
				cin >> tempi;
			}
	if (tempi == 0)
		return 0;
	if (tempi == 1)
		editDriverName(name);
	if (tempi == 2)
		editDriverID(name);
	if (tempi == 3)
		editDriverShiftMaxDuration(name);
	if (tempi == 4)
		editDriverMaxWeekWorkingTime(name);
	if (tempi == 5)
		editDriverMinRestTime(name);
	return 0;
}

// Display Menu's Function defination
void mainMenuDisplay()
{
	cout << "Operacoes disponiveis:" << endl;
	cout << " (Operacoes por implementar: 1, 2, 3, 4, 5, 6, 8)" << endl;
	cout << "[1] Gerir e ver informacao dos condutores." << endl;
	cout << "[2] Visualizar horarios de uma paragem." << endl;
	cout << "[3] Visualizar informacao de um autocarro." << endl;
	cout << "[4] Visualizar informacao de uma linha." << endl;
	cout << "[5] Calcular um percurso e tempo entre duas paragens." << endl;
	cout << "[6] Ver todos periodos de autocarro sem condutor atribuido." << endl;
	cout << "[7] Ver condutores sem servico completo. " << endl;
	cout << "[8] Atribuir turnos a um condutor." << endl;
	cout << "[0] Para sair do programa." << endl;
	cout << "Escreva o numero correspondente a operacao a realizar: ";
}
void opcao1MenuDisplay()
{
	cout << "Operacoes disponiveis:" << endl;
	cout << "[1] Gerir os condutores : criar, alterar e remover um condutor" << endl;
	cout << "[2] Visualizar o trabalho atribuido a um condutor" << endl;
	cout << "[3] Listar todos os periodos de condutores sem o servico completo atribuido." << endl;
	cout << "[0] Para voltar ao menu inicial." << endl;
	cout << "Escreva o numero correspondente a operacao a realizar: ";
}
void opcao1_1MenuDisplay()
{
	cout << "Operacoes disponiveis:" << endl;
	cout << "[1] Adicionar um condutor." << endl;
	cout << "[2] Alterar um condutor." << endl;
	cout << "[3] Remover um condutor." << endl;
	cout << "[4] Ver informacao de todos condutores." << endl;
	cout << "[0] Para voltar ao menu inicial." << endl;
	cout << "Escreva o numero correspondente a operacao a realizar: ";
}
void opcao1_1_2MenuDisplay()
{
	cout << "Operacoes disponiveis:" << endl;
	cout << " (Operacoes por implementar: 1, 2, 3, 4, 5)" << endl;
	cout << "[1] Alterar nome." << endl;
	cout << "[2] Alterar ID." << endl;
	cout << "[3] Alterar duracao maxima de turno." << endl;
	cout << "[4] Alterar maximo de horas que pode trabalhar por semana." << endl;
	cout << "[5] Alterar minimo de horas de descanso." << endl;
	cout << "[0] Para voltar ao menu inicial." << endl;
	cout << "Escreva o numero correspondente a operacao a realizar: ";
}