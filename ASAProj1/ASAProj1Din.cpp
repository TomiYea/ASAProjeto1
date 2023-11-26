#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define peca todos_tipos.at(i)

using namespace std;

typedef struct tipo tipo;

struct tipo {
	int x;
	int y;
	int valor;
};

vector<tipo> todos_tipos;
vector<vector<int>> matriz;
int chapa_x, chapa_y;
int n_tipos;

void ler() {
	tipo tipo_info;
	int i;

	if (scanf("%d %d", &chapa_x, &chapa_y) != 2) { exit(1); }
	if (scanf("%d", &n_tipos) != 1) { exit(1); }
	todos_tipos.resize(n_tipos);
	for (i = 0; i < n_tipos; i++) {
		if (scanf("%d %d %d", &tipo_info.x, &tipo_info.y, &tipo_info.valor) != 3) { exit(1); }
		todos_tipos.at(i) = tipo_info;
	}
}

int melhor_valor(int x, int y) {
	int valor_teste;
	int i, max = 0;

	for (i = 0; i < n_tipos; i++) {
		if (peca.x <= x && peca.y <= y) {
			valor_teste = peca.valor + matriz.at(x - peca.x).at(y) + matriz.at(peca.x).at(y - peca.y);
			if (max < valor_teste) {
				max = valor_teste;
			}
			valor_teste = peca.valor + matriz.at(x).at(y-peca.y) + matriz.at(x - peca.x).at(peca.y);
			if (max < valor_teste) {
				max = valor_teste;
			}
		}
		if (peca.y <= x && peca.x <= y) {
			valor_teste = peca.valor + matriz.at(x - peca.y).at(y) + matriz.at(peca.y).at(y - peca.x);
			if (max < valor_teste) {
				max = valor_teste;
			}
			valor_teste = peca.valor + matriz.at(x).at(y - peca.x) + matriz.at(x - peca.y).at(peca.x);
			if (max < valor_teste) {
				max = valor_teste;
			}
		}
	}
	return max;
}

void preenche_matriz() {
	int i, j;
	matriz.resize(chapa_x + 1, vector<int>(chapa_y + 1, 0));
	for (i = 1; i <= chapa_x; i++) {
		for (j = 1; j <= chapa_y; j++) {
			matriz.at(i).at(j) = melhor_valor(i, j);
		}
	}
}

int main() {
	ler();
	preenche_matriz();
	printf("%d\n", matriz.at(chapa_x).at(chapa_y));
	return 0;
}