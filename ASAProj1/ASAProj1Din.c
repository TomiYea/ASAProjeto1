/*#include <stdio.h>
#include <stdlib.h>

#define peca todos_tipos[i]

typedef struct tipo tipo;

struct tipo {
	int x;
	int y;
	int valor;
};

tipo* todos_tipos;
int** matriz;
int chapa_x, chapa_y;
int n_tipos;

void ler() {
	tipo tipo_info;
	int i;

	if (scanf("%d %d", &chapa_x, &chapa_y) != 2) { exit(1); }
	if (scanf("%d", &n_tipos) != 1) { exit(1); }
	todos_tipos = (tipo*)malloc(n_tipos * sizeof(tipo));
	for (i = 0; i < n_tipos; i++) {
		if (scanf("%d %d %d", &tipo_info.x, &tipo_info.y, &tipo_info.valor) != 3) { exit(1); }
		todos_tipos[i] = tipo_info;
	}
}

int melhor_valor(int x, int y) {
	int valor_teste;
	int i, max = 0;

	for (i = 0; i < n_tipos; i++) {
		if (peca.x <= x && peca.y <= y) {
			valor_teste = peca.valor + matriz[x - peca.x][y] + matriz[peca.x][y - peca.y];
			if (max < valor_teste) {
				max = valor_teste;
			}
			valor_teste = peca.valor + matriz[x][y - peca.y] + matriz[x - peca.x][peca.y];
			if (max < valor_teste) {
				max = valor_teste;
			}
		}
		if (peca.y <= x && peca.x <= y) {
			valor_teste = peca.valor + matriz[x - peca.y][y] + matriz[peca.y][y - peca.x];
			if (max < valor_teste) {
				max = valor_teste;
			}
			valor_teste = peca.valor + matriz[x][y - peca.x] + matriz[x - peca.y][peca.x];
			if (max < valor_teste) {
				max = valor_teste;
			}
		}
	}
	return max;
}

void preenche_matriz() {
	int i, j;

	matriz = (int**)malloc((chapa_x + 1) * sizeof(int*));
	matriz[0] = (int*)malloc((chapa_y + 1) * sizeof(int));
	for (j = 0; j <= chapa_y; j++) {
		matriz[0][j] = 0;
	}
	for (i = 1; i <= chapa_x; i++) {
		matriz[i] = (int*)malloc((chapa_y + 1) * sizeof(int));
		matriz[i][0] = 0;
		for (j = 1; j <= chapa_y; j++) {
			matriz[i][j] = melhor_valor(i, j);
		}
	}
}

int main() {
	ler();
	preenche_matriz();
	printf("%d\n", matriz[chapa_x][chapa_y]);
	return 0;
}*/