#include <bits/stdc++.h>

using namespace std;
// Representação do grafo, em termos de matriz. 
vector < int > g[110];

void bfs(int i){
	queue < int > q;
	q.push(i);
	bitset < 110 > vis;
	while(!q.empty()){
		int tmp = q.front();
		q.pop();
		if(vis[tmp]) continue;
		cout << tmp << " ";
		for(auto j : v[tmp]){
			q.push(j);
		}
	}
	cout << endl;
}

int main(){

	int n, m, x, y;

	// Leio n, número de vertices e m, numero de arestas.
	cin >> n >> m;

	// Ai aqui leio x e y, que quer dizer que tem uma ligação entre x e y; 
	for(int i = 0;i < m;++i){
		cin >> x >> y;
		// insiro a aresta y no vector na posição x;
		v[x].push_back(y);
		// Faco o mesmo pra y, pq é bidirecional.
		v[y].push_back(x);
	}
	// Imprimo todas as arestas de 1.
	
	bfs(1);
}