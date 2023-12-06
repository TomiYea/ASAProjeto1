#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

vector<vector<int>> matriz;
int chapa_x, chapa_y;
int n_tipos;

void ler() {
	int x, y, valor;
	int i;

	if (scanf("%d %d", &chapa_x, &chapa_y) != 2) { exit(1); }
	matriz.resize(chapa_x + 1, vector<int>(chapa_y + 1, 0));
	if (scanf("%d", &n_tipos) != 1) { exit(1); }
	for (i = 0; i < n_tipos; i++) {
		if (scanf("%d %d %d", &x, &y, &valor) != 3) { exit(1); }
		if (x <= chapa_x && y <= chapa_y) {
			if (matriz.at(x).at(y) < valor) {
				matriz.at(x).at(y) = valor;
				if (y <= chapa_x && x <= chapa_y) {
					matriz.at(y).at(x) = valor;
				}
			}
		}
		else if (y <= chapa_x && x <= chapa_y) {
			if (matriz.at(y).at(x) < valor) {
				matriz.at(y).at(x) = valor;
			}
		}
	}
}

int melhor_valor(int x, int y) {
	int valor_teste, max;
	int i, j;

	max = matriz.at(x).at(y);
	for (i = 1, j = x - 1; i <= j; i++, j--) {
		valor_teste = matriz.at(i).at(y) + matriz.at(j).at(y);
		if (max < valor_teste) {
			max = valor_teste;
		}
	}
	for (i = 1, j = y - 1; i <= j; i++, j--){
		valor_teste = matriz.at(x).at(i) + matriz.at(x).at(j);
		if (max < valor_teste) {
			max = valor_teste;
		}
	}
	return max;
}

void preenche_matriz() {
	int i, j;
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