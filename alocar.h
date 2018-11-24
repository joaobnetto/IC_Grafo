#ifndef ALOCAR_H
#define ALOCAR_H
#include <vector>
#include "sala.h"
#include "graph.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

class Alocar{
private:
	std::vector < Sala > salas;
	std::vector < Pedido > nao_alocados;
	struct Vector4D{
		std::vector < Pedido > p;
	};
	Vector4D pedidos[6][3][6];

public:
	void alocar();
	void lerPedidos();
	void lerSalas();
	void imprimirSalas();
	void imprimirNaoAlocados();
	void imprimirPedidos();
};

#endif