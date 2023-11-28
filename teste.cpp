#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

string cidades[1000];
string moeda = "Real";

// Criando um atalho para um par de inteiros
typedef pair<int, int> iPair;

// Estrutura para representar um grafo
struct Graph {
  int V;                          // Número de vértices
  vector<pair<int, iPair>> edges; // Lista de arestas com peso

  // Construtor
  Graph(int V) { this->V = V; }

  // Função utilitária para adicionar uma aresta
  void addEdge(int u, int v, int w) { edges.push_back({w, {u, v}}); }

  // Função para encontrar a MST usando o algoritmo de Kruskal
  int kruskalMST();
};

// Para representar Conjuntos Disjuntos
struct DisjointSets {
  int *parent, *rnk;
  int n;

  // Construtor
  DisjointSets(int n) {
    // Alocando memória
    this->n = n;
    parent = new int[n + 1];
    rnk = new int[n + 1];

    // Inicialmente, todos os vértices estão em conjuntos diferentes e têm rank
    // 0
    for (int i = 0; i <= n; i++) {
      rnk[i] = 0;
      parent[i] = i; // cada elemento é pai de si mesmo
    }
  }

  // Encontrar o pai de um nó 'u' (Compressão de Caminho)
  int find(int u) {
    if (u != parent[u])
      parent[u] = find(parent[u]); // faz o pai dos nós no caminho de u -->
                                   // parent[u] apontar para parent[u]
    return parent[u];
  }

  // União por rank
  void merge(int x, int y) {
    x = find(x), y = find(y);

    // Faz a árvore com altura menor ser uma subárvore da outra
    if (rnk[x] > rnk[y])
      parent[y] = x;
    else if (rnk[x] < rnk[y])
      parent[x] = y;
    else // Se rnk[x] == rnk[y], escolha qualquer árvore e aumente a altura
    {
      parent[y] = x;
      rnk[x]++;
    }
  }
};

// Função para calcular o peso da MST
int Graph::kruskalMST() {
  int mst_wt = 0; // Inicializa o peso resultante da MST

  // Ordena as arestas em ordem crescente com base no custo
  sort(edges.begin(), edges.end());

  // Cria conjuntos disjuntos
  DisjointSets ds(V);

  // Itera por todas as arestas ordenadas
  vector<pair<int, iPair>>::iterator it;
  for (it = edges.begin(); it != edges.end(); it++) {
    int u = it->second.first;
    int v = it->second.second;

    int set_u = ds.find(u);
    int set_v = ds.find(v);

    // Verifica se a aresta selecionada está criando um ciclo
    if (set_u != set_v) {
      // A aresta atual estará na MST, então imprima
      cout << "Construa ferrovia entre " << cidades[u] << " e " << cidades[v]
           << ", custo: $" << it->first << " milhoes de " << moeda << endl;

      // Atualiza o peso da MST
      mst_wt += it->first;

      // Une os dois conjuntos
      ds.merge(set_u, set_v);
    }
  }

  return mst_wt;
}

int main() {

  int quantC, preco;
  string cidade;
	map<int,map <int, int>> visitados;
  cout << "Analisador de Custos de Ferrovias" << endl;
  cout << "Insira a moeda: ";
  getline(cin, moeda);
  cout << "Insira a quantidade de cidades: ";
  cin >> quantC;

  Graph g(quantC);
	cin.ignore();
  for (int i = 0; i < quantC; i++) {
    cout << "Insira a cidade " << i << ": ";
    getline(cin, cidade);
    cidades[i] = cidade;
  }
	for (int i = 0; i < quantC; i++) {
		for (int j = 1; j < quantC; j++) {
			visitados[i][j] = visitados[j][i] = 0;
		}
	}

  for (int i = 0; i < quantC; i++) {
    for (int j = 1; j < quantC; j++) {
			if(i != j && visitados[i][j] == 0) {
				cout << "Insira o preco de producao da ferrovia\nentre " 
					<< cidades[i] << " e " << cidades[j] << ": $";
				cin >>preco;
				g.addEdge(i, j, preco);
				visitados[i][j] = visitados[j][i] = 1;
			}
    }
  }

  cout << "Construcao da MST:\n";
  int mst_wt = g.kruskalMST();

  cout << "\nCusto total da MST: $" << mst_wt << " milhoes de "<< moeda << endl;

  return 0;
}

/* entrada:
Euro
9
Paris
Nimes
Montpellier
Avignon
Lyon
Marseille
Nice
Cannes
Toulon
15
25
30
20
40
50
45
35
5
10
20
15
30
20
25
15
10
20
35
25
30
25
10
20
5
15
30
45
35
40
25
20
10
10
30
15
*/
