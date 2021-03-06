#include <vector>
#include <iostream>
#include <map>
#include <math.h>
#include <deque>
#include <algorithm>
#include "sala.h"
const int INFI = 1e9;

class Group{
	private: 
		std::map < std::string , int > g;
	public:
		int getGroup(std::string predio){
			return g[predio];
		}
		Group(){
			g["CAA"] = g["CAB"] = g["CAC"] = g["INF"] = 1;
			g["IQ"] = 2;
			g["FEFD"] = 3;
			g["CAD"] = 4;
		}

};

class Graph{
private:
	struct Edge{
	    int from, to, capacity, cost;
	};
	std::vector<std::vector<int>> adj, cost, capacity;
	void shortest_paths(int n, int v0, std::vector<int>& d, std::vector<int>& p);
	std::vector < Edge > edges;
public:

	int min_cost_flow(int N, int K, int s, int t);
	void criaArestas(std::vector < Pedido > &pedidos, std::vector < Sala > &salas);
	void imprimeArestas();
	void iterarArestas(std::vector < Pedido > &pedidos, std::vector < Sala > &salas, int dia, int turno, int k, std::vector < Pedido > &nao_alocados);
};