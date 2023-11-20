#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <vector>
#include <string>
#include <list>

using namespace std;

typedef struct tipo tipo;

struct tipo {
	int x;
	int y;
	int valor;
	float valor_por_area;
};

tipo* todos_tipos;
tipo** tipos_arrumados;
int* tipos_na_gaveta;
int* vpa_da_gaveta;
int chapa_x, chapa_y, n_tipos, n_gavetas = 0;
int melhor_valor_ate_agora;

void ler() {
	tipo tipo_info;
	int aux, i;

	scanf_s("%d %d", &chapa_x, &chapa_y);
	scanf_s("%d", &n_tipos);
	tipos_arrumados = (tipo**)malloc(n_tipos * sizeof(tipo*));
	tipos_na_gaveta = (int*)malloc(n_tipos * sizeof(int));
	vpa_da_gaveta = (int*)malloc(n_tipos * sizeof(int));
	n_tipos *= 2;
	todos_tipos = (tipo*)malloc(n_tipos * sizeof(tipo));
	for (i = 0; i < n_tipos; i++) {
		scanf_s("%d %d %d", &tipo_info.x, &tipo_info.y, &tipo_info.valor);
		tipo_info.valor_por_area = tipo_info.valor / (tipo_info.x * tipo_info.y); //Calcular o valor_por_area
		todos_tipos[i] = tipo_info;
		todos_tipos[++i] = tipo_info;
		aux = todos_tipos[i].x;
		todos_tipos[i].x = todos_tipos[i].y;
		todos_tipos[i].y = aux;
	}
}

int arrumar_gaveta(float vpa){
	/*
	Retorna o valor_por_area das pecas na gaveta
	*/
	tipo* gaveta;
	int valor_max = 0, n_max = 0, valor_next = 0;
	int i, j;

	if (vpa == NULL) {
		for (i = 0; i < n_tipos; i += 2) {
			if (valor_max < todos_tipos[i].valor_por_area) {
				valor_max = todos_tipos[i].valor_por_area;
				n_max = 1;
			}
			else if (valor_max = todos_tipos[i].valor_por_area) {
				n_max++;
			}
		}
	}
	else {
		for (i = 0; i < n_tipos; i += 2) {
			if (valor_max < todos_tipos[i].valor_por_area && vpa > todos_tipos[i].valor_por_area) {
				valor_max = todos_tipos[i].valor_por_area;
				n_max = 1;
			}
			else if (valor_max = todos_tipos[i].valor_por_area) {
				n_max++;
			}
		}
	}
	gaveta = (tipo*)malloc(n_max * sizeof(tipo));
	for (i = 0, j = 0; i < n_tipos; i += 2) {
		if (todos_tipos[i].valor_por_area = valor_max) {
			gaveta[j++] = todos_tipos[i];
			gaveta[j++] = todos_tipos[i + 1];
		}
	}
	tipos_arrumados[n_gavetas] = gaveta;
	tipos_na_gaveta[n_gavetas] = n_max;
	vpa_da_gaveta[n_gavetas] = valor_max;
	tipos_na_gaveta[++n_gavetas] = 0;
	return valor_max;
}

int cortar() {}

int main() {
	ler();
	
}