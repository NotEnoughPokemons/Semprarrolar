//Horario dos transportes: 8:00 às 20:00

#include <iostream>
#include <ios>
#include <limits>
#include <fstream>
#include <string>
#include <cstring>
#include <ctype.h>
#include <iomanip>
#include <sstream>
#include <vector>
#include <utility>
#include "Line.h"



using namespace std;

//usada para tamanho de arrays
const int TAMANHO = 10000;

struct linha {
	int id, freq;
	vector <string> paragens;
	vector <int> tempos;
};
struct condutor {
	int id, turno, h_semana, h_descanso;
	string nome;
};

//********** VERIFICAÇÃO DE INPUTS **********

//verifica se o caractere inserido e valido
//tem em atencao tipo de input (int) e limites
int verifica(int linf, int lsup) {
	int nr;
	cin >> nr;

	while (cin.fail() || nr > lsup || nr < linf) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Input invalido, tente outra vez: ";
		cin >> nr;
	}

	return nr;
}

//verifica se o caractere inserido e valido
//tem atencao ao tipo de input e apenas ao limite inferior
int verifica(int linf) {
	int nr;
	cin >> nr;

	while (cin.fail() || nr < linf) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Input invalido, tente outra vez: ";
		cin >> nr;
	}

	return nr;
}




//********** ABERTURA DOS FICHEIROS **********
//abre o ficheiro das linhas e devolve um vetor com as linhas existentes
vector<linha> abreLinhas(string nome) {
	ifstream infich;
	vector <linha> linhas;
	char str[TAMANHO], *pt;
	string exp1, exp2;

	infich.open(nome);

	//cria uma linha temporaria
	if (!infich.fail()) {
		while (getline(infich, nome)) {
			linha temp;
			strcpy_s(str, nome.c_str());
			pt = strtok_s(str, ";");
			temp.id = atoi(pt);
			pt = strtok_s(NULL, ";");
			temp.freq = atoi(pt);
			pt = strtok_s(NULL, ";");
			exp1 = pt;
			pt = strtok_s(NULL, ";");
			exp2 = pt;

			strcpy_s(str, exp1.c_str());
			pt = strtok_s(str, ",");
			while (pt != NULL) {
				temp.paragens.push_back(pt);
				pt = strtok(NULL, ",");
			}

			strcpy(str, exp2.c_str());
			pt = strtok(str, ",");
			while (pt != NULL) {
				temp.tempos.push_back(atoi(pt));
				pt = strtok(NULL, ",");
			}
			//adiciona a linha criada ao vetor
			linhas.push_back(temp);
		}
	}

	infich.close();
	return linhas;
}

//abre o ficheiro dos condutores e devolve um vetor com os condutores existentes
vector<condutor> abreCondutores(string nome) {
	ifstream infich;
	vector <condutor> condutores;
	char str[TAMANHO], *pt;

	infich.open(nome);

	//cria um condutor temporario
	if (!infich.fail()) {
		while (getline(infich, nome)) {
			condutor temp;
			strcpy(str, nome.c_str());
			pt = strtok(str, "; ");
			temp.id = atoi(pt);
			pt = strtok(NULL, "; ");
			temp.nome = pt;
			pt = strtok(NULL, " ");
			temp.nome = temp.nome + " " + pt;
			pt = strtok(NULL, ";");
			temp.turno = atoi(pt);
			pt = strtok(NULL, ";");
			temp.h_semana = atoi(pt);
			pt = strtok(NULL, ";");
			temp.h_descanso = atoi(pt);

			//adiciona o condutor ao vetor
			condutores.push_back(temp);
		}
	}

	return condutores;
}

//apaga tudo o que anteriormente esteve escrito nos ficheiros
// e escreve os vetores que foram criados pelo programa
void fecho(string nome_lin, string nome_cond, vector<linha> linhas, vector<condutor> condutores) {
	ofstream guarda;
	guarda.open(nome_lin, ios::out | ios::trunc);

	//guarda as informacoes no ficheiro das linhas
	for (int i = 0; i < linhas.size(); i++) {
		guarda << linhas.at(i).id << " ; " << linhas.at(i).freq << " ;";

		//permite que as virgulas fiquem no sitio certo
		guarda << linhas.at(i).paragens.at(0);

		for (int j = 1; j < linhas.at(i).paragens.size(); j++) {
			guarda << "," << linhas.at(i).paragens.at(j);
		}

		guarda << "; " << linhas.at(i).tempos.at(0);
		for (int j = 1; j < linhas.at(i).tempos.size(); j++) {
			guarda << ", " << linhas.at(i).tempos.at(j);
		}

		guarda << endl;
	}

	guarda.close();

	guarda.open(nome_cond, ios::out | ios::trunc);

	//guarda as informacoes no ficheiro dos condutores
	for (int i = 0; i < condutores.size(); i++) {
		guarda << condutores.at(i).id << " ; " << condutores.at(i).nome << " ; "
			<< condutores.at(i).turno << " ; " << condutores.at(i).h_semana
			<< " ; " << condutores.at(i).h_descanso << endl;
	}

	guarda.close();

}




//********** GESTÃO DE LINHAS **********

//cria uma linha nova verificando se o identificador unico ja existe
void criarLinha(vector<linha> &linhas) {

	//cria uma linha temporaria, adicionando-a no fim ao vetor

	linha temp;
	int nr, tempo, i;
	string nome;
	bool continuar = true;

	cout << "Numero da linha a criar: ";
	//verifica se o numero e positivo e nao repetido
	do {
		temp.id = verifica(0);

		for (i = 0; i < linhas.size(); i++) {
			if (linhas.at(i).id == temp.id) {
				cout << "Numero da linha repetido, tente outra vez: ";
				break;
			}
		}

		//condicao e verdadeira quando percorreu todas as linhas e nao parou
		if (i == linhas.size())
			continuar = false;

	} while (continuar);

	cout << "Frequencia: ";
	temp.freq = verifica(0);
	cout << "Numero de paragens: ";
	nr = verifica(0);


	cin.ignore();

	for (i = 0; i < nr; i++) {
		cout << "Nome da " << i + 1 << "a paragem: ";
		continuar = true;
		do {
			getline(cin, nome);

			//verifica que o primeiro caracter e alfabetico
			if (isalpha(nome[0]))
				continuar = false;
			else
				cout << "Nome invalido, tente outra vez: ";

		} while (continuar);

		//ao separar no ficheiro as paragens ficam com um espaço inicial a mais
		//somo para ficarem todas iguais
		nome = " " + nome;
		temp.paragens.push_back(nome);
	}

	//a ultima paragem nao tem tempo dai nr-1
	for (i = 0; i < nr - 1; i++) {
		cout << "Tempo desde" << temp.paragens.at(i) << " ate" << temp.paragens.at(i + 1) << ": ";
		tempo = verifica(0);
		temp.tempos.push_back(tempo);
	}

	linhas.push_back(temp);


	cout << "\nLinha criada com sucesso!\n";
}

//apaga uma linha nova verificando se o identificador unico existe
void apagarLinha(vector<linha> &linhas) {

	int id, i = 0;
	bool continuar = true, naoexiste = true;


	cout << "Numero da linha a apagar: ";

	//verifica se a linha existe
	do {
		id = verifica(0);

		for (i = 0; i < linhas.size(); i++) {
			if (linhas.at(i).id == id) {
				linhas.erase(linhas.begin() + i);
				naoexiste = false;
			}
		}


		if (naoexiste)
			cout << "Linha inexistente, tente outra vez: ";

		else {
			continuar = false;
			cout << "\nLinha apagada com sucesso!\n";
		}

	} while (continuar);
}

//edita todas as informacoes de uma linha nova exceto o identificador unico
void editarLinha(vector<linha> &linhas) {
	linha temp;
	int nr, tempo, i;
	string nome;
	bool continuar = true, naoexiste = true;;

	cout << "Numero da linha a editar: ";
	do {
		temp.id = verifica(0);

		for (i = 0; i < linhas.size(); i++) {
			if (linhas.at(i).id == temp.id) {
				naoexiste = false;
				break;
			}
		}

		if (naoexiste)
			cout << "Linha inexistente, tente outra vez: ";

		else
			continuar = false;

	} while (continuar);

	cout << "Frequencia: ";
	temp.freq = verifica(0);
	cout << "Numero de paragens: ";
	nr = verifica(0);

	cin.ignore();

	for (int j = 0; j < nr; j++) {
		cout << "Nome da " << j + 1 << "ª paragem: ";
		getline(cin, nome);
		//ao separar todas as paragens ficam com um espaco a mais no inicio
		//esta soma permite que tudo fique igual
		nome = " " + nome;
		temp.paragens.push_back(nome);
	}

	//a ultima paragem nao tem tempo dai nr-1
	for (int j = 0; j < nr - 1; j++) {
		cout << "Tempo desde" << temp.paragens.at(j) << " até" << temp.paragens.at(j + 1) << ": ";
		tempo = verifica(0);
		temp.tempos.push_back(tempo);
	}

	linhas.at(i) = temp;

	cout << "\nLinha editada com sucesso!\n";
}




//********** GESTÃO DE CONDUTORES **********
void criarCondutor(vector<condutor> &condutores) {

	condutor temp;
	int i;
	string nome;
	bool continuar = true;

	cout << "Identificador numerico: ";
	do {
		temp.id = verifica(0);

		for (i = 0; i < condutores.size(); i++) {
			if (condutores.at(i).id == temp.id) {
				cout << "Identificador repetido, tente outra vez: ";
				break;
			}
		}

		//condicao e verdadeira quando percorreu todas as linhas e nao parou
		if (i == condutores.size())
			continuar = false;

	} while (continuar);

	// permite usar o getline
	cin.ignore();

	cout << "Nome: ";
	getline(cin, temp.nome);
	cout << "Numero maximo de horas do turno: ";
	temp.turno = verifica(0);
	cout << "Numero maximo de horas que pode conduzir numa semana: ";
	temp.h_semana = verifica(0);
	cout << "Numero minimo de horas de descanso entre turnos: ";
	temp.h_descanso = verifica(0);


	condutores.push_back(temp);


	cout << "\nCondutor criado com sucesso!\n";
}

void apagarCondutor(vector<condutor> &condutores) {
	int id, i = 0;
	bool continuar = true, naoexiste = true;


	cout << "Identificador numerico do condutor a apagar: ";
	do {
		id = verifica(0);

		for (i = 0; i < condutores.size(); i++) {
			if (condutores.at(i).id == id) {
				condutores.erase(condutores.begin() + i);
				naoexiste = false;
			}
		}

		if (naoexiste)
			cout << "Condutor inexistente, tente outra vez: ";

		else {
			continuar = false;
			cout << "\nCondutor apagado com sucesso!\n";
		}

	} while (continuar);
}

void editarCondutor(vector<condutor> &condutores) {
	condutor temp;
	int i;
	string nome;
	bool continuar = true, naoexiste = true;;

	cout << "Numero da linha a editar: ";
	do {
		temp.id = verifica(0);

		for (i = 0; i < condutores.size(); i++) {
			if (condutores.at(i).id == temp.id) {
				naoexiste = false;
				break;
			}
		}

		if (naoexiste)
			cout << "Condutor inexistente, tente outra vez: ";

		else
			continuar = false;

	} while (continuar);

	cin.ignore();

	cout << "Nome: ";
	getline(cin, temp.nome);
	temp.nome = " " + temp.nome;
	cout << "Numero maximo de horas do turno: ";
	temp.turno = verifica(0);
	cout << "Numero maximo de horas que pode conduzir numa semana: ";
	temp.h_semana = verifica(0);
	cout << "Numero minimo de horas de descanso entre turnos: ";
	temp.h_descanso = verifica(0);

	condutores.at(i) = temp;

	cout << "\nCondutor editado com sucesso!\n";
}




//********** GESTÃO DE INFORMAÇÃO **********

//mostra o horario das linhas que passam numa determinada paragem
void horarioParagem(vector<linha> linhas) {
	string nome;
	//vetor onde sao guardadas as linhas com a paragem
	vector <linha> comParagem;
	int minutos, menor_freq = 720;
	bool naoexistetotal = true;

	cin.ignore();
	cout << "Nome da paragem: ";

	//verifica se a paragem existe
	do {

		getline(cin, nome);

		nome = " " + nome;

		//encontra as linhas que tem a paragem em questao

		//percorre todas as linhas existentes
		for (int i = 0; i < linhas.size(); i++) {


			//percorre todas as paragens de cada linha
			for (int j = 0; j < linhas.at(i).paragens.size(); j++) {

				//verifica se as linhas contem a paragem
				if (linhas.at(i).paragens.at(j) == nome) {

					//mostra o numero da linha
					cout << setfill(' ') << setw(11) << linhas.at(i).id;

					naoexistetotal = false;


					if (linhas.at(i).freq < menor_freq)
						menor_freq = linhas.at(i).freq;

					linhas.at(i).id = 0;

					//soma o tempo da 1a paragem ate a paragem em questao
					//visto que foi admitido que os autocarros comecam as 8 na paragem inicial e nao em cada paragem
					for (int k = 0; k < j; k++) {
						linhas.at(i).id = linhas.at(i).id + linhas.at(i).tempos.at(k);
						//o id nao e usado por isso pode ser alterado
					}

					comParagem.push_back(linhas.at(i));
					break;
				}
			}
		}

		if (naoexistetotal)
			cout << "Paragem inexistente, tente outra vez: ";


	} while (naoexistetotal);

	cout << endl;

	//mostra os horarios de todas as linhas em cada paragem
	//separados por colunas consoante a linha
	//720 = numero total de minutos entre 8 e 20
	//720/menor_freq e o numero maximo de linhas da "tabela"
	for (int k = 0; k <= 720 / menor_freq; k++) {

		for (int i = 0; i < comParagem.size(); i++) {
			//soma se ao tempo desde a 1a paragem a paragem em questao
			minutos = comParagem.at(i).id + comParagem.at(i).freq * k;
			if (minutos <= 720)
				cout << setfill(' ') << setw(8) << 8 + minutos / 60 << ":" << setfill('0') << setw(2) << minutos % 60;
			//pode haver linhas no qual ja se ultrapassou o limite e outras nao
			//e necessario assegurar espaço em branco para alinhamento
			else
				cout << setfill(' ') << setw(11) << " ";
		}

		cout << endl;
	}

}

//mostra o horario em que a linha passa nas respetivas paragens
void horarioLinha(vector<linha> linhas) {
	bool naoexiste = true;
	linha temp;
	int id, minutos = 0;

	cout << "Identificador numerico: ";

	do {
		id = verifica(0);

		for (int i = 0; i < linhas.size(); i++) {
			if (linhas.at(i).id == id) {
				naoexiste = false;
				temp = linhas.at(i);
				break;
			}
		}

	} while (naoexiste);

	cout << setfill(' ') << setw(10) << temp.paragens.at(0);
	for (int j = 1; j < temp.paragens.size(); j++) {
		cout << setw(25) << temp.paragens.at(j);
	}

	cout << endl;

	for (int i = 0; i < 720 / temp.freq; i++) {
		minutos = temp.freq*i;
		cout << setfill(' ') << setw(7) << 8 + minutos / 60 << ":" << setfill('0') << setw(2) << minutos % 60;
		for (int j = 0; j < temp.tempos.size(); j++) {
			minutos = minutos + temp.tempos.at(j);
			if (minutos <= 720)
				cout << setfill(' ') << setw(22) << 8 + minutos / 60 << ":" << setfill('0') << setw(2) << minutos % 60;
		}
		cout << endl;
	}
}

//mostra as linhas que passam numa determinada paragem
void linhasParagem(vector<linha> linhas) {
	string nome;
	int contador = 1;
	cin.ignore();
	cout << "Nome da paragem: ";

	do {
		getline(cin, nome);

		nome = " " + nome;

		//percorre todas as linhas existentes
		for (int i = 0; i < linhas.size(); i++) {

			//percorre todas as paragens de cada linha
			for (int j = 0; j < linhas.at(i).paragens.size(); j++) {

				if (linhas.at(i).paragens.at(j) == nome) {
					if (contador == 1) {
						cout << "\nLinhas que passam em" << nome << ": ";
						contador = 0;
					}
					cout << linhas.at(i).id;
					cout << "  ";
				}
			}
		}
		if (contador)
			cout << "Paragem inexistente, tente outra vez: ";

	} while (contador);

	cout << endl;
}

//mostra as linhas que o utilizador deve tomar, depois de indicadas as paragens de partida e de chegada
//apenas consegue calcular o percurso se as paragens estiverem na mesma linha ou se estiverem em linhas que se intersetam
bool percurso(vector<linha> linhas) {
	string partida, chegada;
	vector <linha> lin_partida, lin_chegada;
	bool naoexiste = true;

	cin.ignore();
	cout << "Nome da paragem de partida: ";

	do {
		getline(cin, partida);
		partida = " " + partida;

		for (int i = 0; i < linhas.size(); i++) {

			for (int j = 0; j < linhas.at(i).paragens.size(); j++) {

				if (linhas.at(i).paragens.at(j) == partida) {
					lin_partida.push_back(linhas.at(i));
					naoexiste = false;
					break;
				}
			}
		}

		if (naoexiste)
			cout << "Paragem inexistente, tente outra vez: ";

	} while (naoexiste);


	cout << "Nome da paragem de chegada: ";

	do {
		getline(cin, chegada);
		chegada = " " + chegada;

		for (int i = 0; i < linhas.size(); i++) {

			for (int j = 0; j < linhas.at(i).paragens.size(); j++) {

				if (linhas.at(i).paragens.at(j) == chegada) {
					lin_chegada.push_back(linhas.at(i));
					naoexiste = false;
					break;
				}
			}
		}

		if (naoexiste)
			cout << "Paragem inexistente, tente outra vez: ";

	} while (naoexiste);


	for (int i = 0; i < lin_partida.size(); i++) {

		for (int j = 0; j < lin_chegada.size(); j++) {
			if (lin_partida.at(i).id == lin_chegada.at(j).id) {
				cout << "\nDeve apanhar a linha " << lin_partida.at(i).id << endl;
				return true;
			}
		}
	}


	for (int i = 0; i < lin_partida.size(); i++) {

		for (int j = 0; j < lin_chegada.size(); j++) {

			for (int k = 0; k < lin_partida.at(i).paragens.size(); k++) {

				for (int l = 0; l < lin_chegada.at(j).paragens.size(); l++) {

					if (lin_partida.at(i).paragens.at(k) == lin_chegada.at(j).paragens.at(l)) {
						cout << "\nDeve apanhar a linha " << lin_partida.at(i).id << " trocar na paragem"
							<< lin_partida.at(i).paragens.at(k) << " e finalmente apanhar a linha "
							<< lin_chegada.at(j).id << " saindo no seu destino.\n";
						return true;
					}
				}
			}
		}
	}

	return false;
}

//mostra o numero de condutores necesarios para conduzir uma linha
//faz a distribuicao aos condutores de turnos de mais horas
void condutoresLinha(vector<linha> linhas, vector <condutor> condutores) {
	int nr_min, id, nr_turnos = 0, h_descanso;
	bool naoexiste = true;
	pair <int, int> max;

	cout << "Identificador numerico da linha: ";

	do {
		id = verifica(0);

		for (int i = 0; i < linhas.size(); i++) {
			if (linhas.at(i).id == id) {
				naoexiste = false;

				//calculo do total de minutos que a linha exige
				//calculo do tempo da 1a a ultima paragem
				for (int j = 0; j < linhas.at(i).tempos.size(); j++) {
					nr_min = nr_min + linhas.at(i).tempos.at(j);
				}
				//calculo da ultima vez q chega a ultima paragem
				while (nr_min <= 720)
					nr_min = nr_min + linhas.at(i).freq;
				//subtrai se pq na ultima iteracao ja ultrapassou os 720 min
				nr_min = nr_min - linhas.at(i).freq;
			}
		}
		if (naoexiste)
			cout << "Linha inexistente, tente outra vez: ";

	} while (naoexiste);

	cout << "Condutor(es) necessario(s): ";
	while (nr_min >= 0 && condutores.size() > 0) {
		max.first = condutores.at(0).turno;
		max.second = 0;

		// procura o condutor com o turno de mais horas
		for (int i = 1; i < condutores.size(); i++) {
			if (condutores.at(i).turno > max.first) {
				max.first = condutores.at(i).turno;
				max.second = i;
			}
		}

		if (nr_turnos == 0)
			cout << condutores.at(max.second).nome;
		else
			cout << ", " << condutores.at(max.second).nome;

		h_descanso = condutores.at(max.second).h_descanso;

		nr_turnos = nr_min / ((max.first + h_descanso) * 60);

		if (nr_turnos > nr_min % ((max.first + h_descanso) * 60))
			nr_turnos = nr_turnos + 1;

		nr_min = max.first*nr_turnos;

		//apaga o condutor para nao ser tido em consideracao na proxima iteracao
		condutores.erase(condutores.begin() + max.second);


	}

	cout << endl << endl;
}




//********** MENUS **********

//mostra o menu de gestao das linhas
//escolhe entre criar, apagar e editar uma linha
void gestaoLinhas(vector<linha> &linhas) {
	int escolha = 0;

	while (escolha != 4) {
		cout << setfill('*') << setw(24) << "\n";
		cout << "\n1 - Criar linha\n"
			<< "2 - Apagar linha\n"
			<< "3 - Editar linha\n"
			<< "4 - Voltar ao menu anterior\n\n";

		cout << setfill('*') << setw(24) << "\n";

		escolha = verifica(1, 4);

		switch (escolha) {
		case 1: criarLinha(linhas); break;
		case 2: apagarLinha(linhas); break;
		case 3: editarLinha(linhas); break;
		}
	}
}

//mostra o menu de gestao dos condutores
//escolhe entre criar, apagar e editar um condutor
void gestaoCondutores(vector<condutor> &condutores) {
	int escolha = 0;

	while (escolha != 4) {
		cout << setfill('*') << setw(24) << "\n";
		cout << "\n1 - Criar condutor\n"
			<< "2 - Apagar condutor\n"
			<< "3 - Editar condutor\n"
			<< "4 - Voltar ao menu anterior\n\n";

		cout << setfill('*') << setw(24) << "\n";

		escolha = verifica(1, 4);

		switch (escolha) {
		case 1: criarCondutor(condutores); break;
		case 2: apagarCondutor(condutores); break;
		case 3: editarCondutor(condutores); break;
		}
	}
}

//mostra o menu que inclui todas as outras hipoteses
//permite consultar horarios, calcular um percurso, ver as linhas que passam em determinada paragem
//e os condutores necesarios para uma linha
void gestaoInformacao(vector<linha> &linhas, vector<condutor> &condutores) {
	int escolha = 0;

	while (escolha != 8) {
		cout << setfill('*') << setw(24) << "\n";
		cout << "\n1 - Horario de uma paragem\n"
			<< "2 - Horario de uma linha\n"
			<< "3 - Linhas que passam numa paragem\n"
			<< "4 - Calcular percurso\n"
			<< "5 - Trabalho atribuido a um condutor\n"
			<< "6 - Condutores disponiveis\n"
			<< "7 - Condutores necessarios para uma linha\n"
			<< "8 - Voltar ao menu anterior\n\n";

		cout << setfill('*') << setw(24) << "\n";

		escolha = verifica(1, 8);

		switch (escolha) {
		case 1: horarioParagem(linhas); break;
		case 2: horarioLinha(linhas); break;
		case 3: linhasParagem(linhas); break;
		case 4: if (!percurso(linhas))
			cout << "Percurso indisponivel\n"; break;
		case 5: //trabalho pratico 2
			break;
		case 6: //trabalho pratico 2
			break;
		case 7: condutoresLinha(linhas, condutores); break;
		}
	}
}


void menu(string nome_lin, string nome_con, vector <linha> &linhas, vector<condutor> &condutores) {
	int escolha = 0;

	cout << endl << endl << setw(20) << "Semprarrolar\n\n";
	cout << setfill('*') << setw(14) << " Menu " << setfill('*') << setw(11) << " \n";

	while (escolha != 4) {
		cout << setfill('*') << setw(25) << "\n\n";
		cout << "1 - Gestão de linhas\n"
			<< "2 - Gestão de condutores\n"
			<< "3 - Visualização de informação\n"
			<< "4 - Sair\n\n";

		cout << setfill('*') << setw(24) << "\n";

		escolha = verifica(1, 8);

		switch (escolha) {
		case 1: gestaoLinhas(linhas); break;
		case 2: gestaoCondutores(condutores); break;
		case 3: gestaoInformacao(linhas, condutores); break;
		case 4: cout << "\n\n  Ate a proxima!\n\n"; break;
		}
	}

	fecho(nome_lin, nome_con, linhas, condutores);
}


//manda abrir os ficheiros e chama o menu
int main() {
	string nome_lin, nome_con;
	vector <linha> linhas;
	vector <condutor>  condutores;

	// FICHEIRO DAS LINHAS
	cout << "Ficheiro das linhas: ";
	cin >> nome_lin;

	//abre ficheiros mesmo sem a extensao .txt ter sido digitada
	size_t found = nome_lin.find(".txt");
	if (found == string::npos)
		nome_lin = nome_lin + ".txt";

	linhas = abreLinhas(nome_lin);


	// FICHEIRO DOS CONDUTORES
	cout << "Ficheiro dos condutores: ";
	cin >> nome_con;

	//abre ficheiros mesmo sem a extensao ter sido digitada
	found = nome_con.find(".txt");
	if (found == string::npos)
		nome_con = nome_con + ".txt";

	condutores = abreCondutores(nome_con);

	if (linhas.size() == 0 || condutores.size() == 0)
		cerr << "Erro ao abrir os ficheiros\n";
	else
		menu(nome_lin, nome_con, linhas, condutores);



	system("pause");
	return 0;
}
