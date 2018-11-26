#include <bits/stdc++.h>

using namespace std;

string hor[9] = {"24M23", "24M45", "35M23", "35M45", "6M2345", "23T23", "23T45", "45T2345", "6T23"};
string ho2[9] = {"246M23", "246M45", "35M23", "35M45", "23T23", "23T45", "45T2345", "6T23", "6T45"};
string predio[4] = {"CAA","CAB","CAC","INF"};
int cap[10] = {60,55,50,45,40,35,30,25,20,15};
string tipo[2] = {"S", "L"};

bool f(int c, string pre){
	if(pre == "INF") return 1;
	else if(c <= 24) return rand()%2;
}

bool p(string pr){
	if(pr == "INF") return 1;
	return 0;
}

int main(){
	cout << "{\n";
	srand(time(NULL));
	int i = 1, z = 1;
	string curso = "Curso";
	while(i < 500){
		int k = rand()%2;
		curso =  "Curso" + to_string(z++);
		for(int j = 1;j <= 8;++j){
			string info = "";
			for(int l = 0;l < 4;++l){
				info += "A";
				string pre = predio[rand()%4];
				int t = rand()%9;
				// cout << k << endl;
				int c = cap[rand()%10];
				cout << "\"Pedido" << to_string(i++) << "\": {\n";
				cout << "\"horario\": \"";
				if(k) cout << hor[t];
				else cout << ho2[t];
				cout << "\",\n";
				cout << "\"info\": \"" << info; cout << "\",\n";
				cout << "\"curso\": \"" << curso << "\",\n";
				cout << "\"capacidade\": \"";
				if(pre == "INF") cout << 24;
				else cout << c;
				cout << "\",\n";
				cout << "\"predio\": \"" << pre; cout << "\",\n";
				cout << "\"prioridade\": " << "0,\n";
				cout << "\"tipo\": \"";
				if(f(c, pre)) cout << "L";
				else cout << "S";
				cout << "\",\n";
				cout << "\"periodo\": " << j << "\n";
				cout << "},\n";
				// return 0;
			}
		}
	}

	cout << "}\n";
}
/*
"pedido1":{
		"horario": "2M12",
		"info": "Calculo 1A",
		"curso": "Ciencia da Computacao",
		"capacidade": "60",
		"predio": "CAB",
		"prioridade": 0,
        "tipo": "S",
	"periodo" : 1
},
*/