#include "alocar.h"
std::string dia[6] = {"Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};

// Leio os pedidos e os armazeno.

void Alocar::lerPedidos(){
	// Abro o arquivo Json e coloco ele num documento pra ser utilizado depois
	int j = 0, i = 0;
	FILE *fp = fopen("pedidos.json", "r");
	char readBuffer[1000010];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	rapidjson::Document d;
	d.ParseStream(is);

	// Coloco ele numa variavel pra ser iterada.
	const rapidjson::Value& pedido = d;

	for(rapidjson::Value::ConstMemberIterator itr = pedido.MemberBegin();itr != pedido.MemberEnd();++itr){
		std::vector < int > dias;
		int turno;
		const rapidjson::Value& membro = itr->value;
		Pedido tmp;
		i = j = 0;

		// Pego as variaveis necessarias do pedido.
		std::string horario = membro["horario"].GetString();
		tmp.info = membro["info"].GetString();
		tmp.predio = membro["predio"].GetString();
		tmp.tipo = membro["tipo"].GetString();
		tmp.capacidade = std::stoi(membro["capacidade"].GetString());
		tmp.prioridade = membro["prioridade"].GetInt();
		tmp.curso = membro["curso"].GetString();
		tmp.periodo = membro["periodo"].GetInt();

		// Pego os dias que tem a aula, quando comeca, termina e o turno
		j = 0;
		
		while(horario[j] <= '9' && horario[j] >= '0'){
			dias.push_back(horario[j++] - '0' - 2);
		}
		if(horario[j] == 'M') turno = 0;
		else if(horario[j] == 'T') turno = 1;
		else turno = 2;

		j++;

		for(;j < horario.size();++j){
			for(auto k : dias){
				pedidos[k][turno][horario[j]-'0'-1].p.push_back(tmp);
			}
		}
	} 
	
	// sort(pedidos.begin(),pedidos.end());
	fclose(fp);
}

// Leio as salas e as armazeno num vetor só. 

void Alocar::lerSalas(){
	// Variaveis que serão utilizadas depois
	int i = 0, capacidade = 0;

	// Abro o arquivo Json e coloco ele num documento pra ser utilizado depois
	FILE *fp = fopen("salas.json", "r");
	if(fp == NULL){
		std::cout << "Não há arquivo de salas\n";
		return;
	}
	char readBuffer[1000010];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	rapidjson::Document d;
	d.ParseStream(is);

	// Declaro uma variavel para iterar pelo meu documento.	
	const rapidjson::Value& predio = d;

	// Começo iterar pelos predios.
	for(rapidjson::Value::ConstMemberIterator iter = predio.MemberBegin();iter != predio.MemberEnd();++iter){
		const rapidjson::Value& tipo = iter->value;
		// Como cada predio tem 3 tipos de sala, itero pelos tipos.
		for(rapidjson::Value::ConstMemberIterator tipos = tipo.MemberBegin();tipos != tipo.MemberEnd();++tipos){

			// Comeco iterar pelas salas dentro desse predio.
			const rapidjson::Value& sala = tipos->value;


			for(rapidjson::Value::ConstMemberIterator itr = sala.MemberBegin();itr != sala.MemberEnd();++itr){

				// Pego a capacidade das salas, e a lista de salas com aquela capacidade.
				capacidade = std::stoi(itr->name.GetString());
				for(auto& array : itr->value.GetArray()){
					// E coloco essa sala na minha lista de salas 
					salas.push_back(Sala(capacidade, iter->name.GetString(), array.GetString(), tipos->name.GetString()));
					// std::cout << capacidade << " " << iter->name.GetString () << " " << array.GetString() << " " << tipos->name.GetString() << "\n";
				}
			}
		}

	}
	sort(salas.begin(), salas.end());
	fclose(fp);
}

// Imprimo minhas salas após a alocação.

void Alocar::imprimirSalas(){
	for(auto z : salas){
		Sala tmp = z;
		std::cout << "Sala: " <<  z.getNome() << ",Predio: " << z.getPredio() << ",Capacidade: " << z.getCapacidade() << std::endl;
		for(int j = 0;j < 3;++j){
			for(int k = 0;k < 6;++k){
				for(int i = 0;i < 6;++i){
					z.imprimeHorario(i, j, k);
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
}

// Imprimo os pedidos que li

void Alocar::imprimirPedidos(){
	for(int i = 0;i < 6;++i){
		std::cout << dia[i] << ":\n";
		for(int j = 0;j < 3;++j){
			for(int k = 0;k < 6;++k){
				std::vector < Pedido > tmp = pedidos[i][j][k].p;
				std::cout << tmp.size() << std::endl;
				std::map < int , int > m;
				for(int l = 0;l < tmp.size();++l){
					m[tmp[l].capacidade]++;
				}
				for(auto i = m.begin();i != m.end();++i){
					std::cout << i->first << ": " << i->second << std::endl; 
				}
				return;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
}

// Imprimo o que não foi alocado.

void Alocar::imprimirNaoAlocados(){
	std::cout << nao_alocados.size() << std::endl;
	for(auto i : nao_alocados){
		std::cout << i.info << " " << i.curso << " " << i.tipo << " " << i.predio << " " << i.capacidade << std::endl;
	}
}

// Aloco os pedidos, usando o min-cost max-flow, para cada horário crio um grafo e faço isso.
void Alocar::alocar(){
	for(int i = 0;i < 6;++i){
		// std::cout << dia[i] << ":\n";
		for(int j = 0;j < 3;++j){
			for(int k = 0;k < 6;++k){
				Graph aloc;
				std::vector < Pedido > tmp = pedidos[i][j][k].p;
				aloc.criaArestas(tmp, salas);
				// aloc.imprimeArestas();
				// std::cout << tmp.size() << " ";
				aloc.min_cost_flow(tmp.size() + salas.size() + 2, INT_MAX, 0, tmp.size() + salas.size() + 1);
				// std::cout << tmp.size() + salas.size() + 1 << std::endl;
				aloc.iterarArestas(tmp, salas,i,j,k, nao_alocados);
				// return;
			}
		}
	}
}
