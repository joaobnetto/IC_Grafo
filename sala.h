#ifndef SALA_H
#define SALA_H
#include <string>
#include <iostream>
#include <vector>

// Classe sala e estrututa pedido, com tudo que preciso.

struct Pedido{
	int capacidade, periodo, prioridade;
	std::string tipo, predio, curso, info;
	bool operator<(const Pedido b) const{
		return capacidade > b.capacidade;
	}
};

class Sala{
private:
	int capacidade;
	std::string predio, nome, tipo;
	struct Horario{
		int existe, capacidade, periodo;
		std::string info, curso, predio;
	};
	Horario horas[6][3][6];
public:
	Sala(int capacidade, std::string predio, std::string nome, std::string tipo){
		this->capacidade = capacidade;
		this->predio = predio;
		this->nome = nome;
		this->tipo = tipo;
		for(int i = 0;i < 6;++i)
			for(int j = 0;j < 3;++j)
				for(int k = 0;k < 6;++k) horas[i][j][k].existe = 0;
	}
	int getCapacidade() {return capacidade;};
	std::string getPredio(){return predio;};
	std::string getNome(){return nome;};
	std::string getTipo(){return tipo;};
	void setHorario(int i, int j, int k, int capacidade, int periodo, std::string info, std::string curso, std::string predio){
		Horario tmp = {1,capacidade,periodo, info,curso,predio};
		horas[i][j][k] = tmp;
	}
	bool existeHorario(int i, int j, int k) {return horas[i][j][k].existe;}

	bool mesmoHorario(int i, int j, int k, int capacidade, std::string info, std::string curso, std::string predio, int periodo){
		if(!existeHorario(i,j,k)) return 0;
		Horario tmp = horas[i][j][k];
		if(tmp.capacidade == capacidade && info == tmp.info 
			&& curso == tmp.curso && predio == tmp.predio && periodo == tmp.periodo) return true;
		return 0;
	}
	void imprimeHorario(int i, int j, int k){
		Horario tmp = horas[i][j][k];
		if(tmp.existe){
			std::cout << tmp.info << " Curso: " << tmp.curso << " Predio: " 
			<< tmp.predio << " Capacidade: " << tmp.capacidade << " Periodo: " << tmp.periodo << ",";
		}
		else std::cout << "VAZIO, ";
	}
	bool operator<(Sala B){
		int pr = predio.compare(B.getPredio()), nm = nome.compare(B.getNome()), tp = tipo.compare(B.getTipo());
		if(pr) return pr < 0;
		else if(tp) return tp > 0;
		else if(capacidade != B.getCapacidade()) return capacidade > B.getCapacidade();
		else if(nm) return nm < 0;
	};
};

#endif