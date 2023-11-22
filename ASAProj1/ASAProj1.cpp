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
bool tudo_arrumado = false;
int* n_tipos_na_gaveta;
int* vpa_da_gaveta;
int chapa_x, chapa_y, chapa_area, n_tipos, n_gavetas = 0;
int melhor_valor_ate_agora = 0;
int i_inicio, j_inicio;

void ler() {
	tipo tipo_info;
	int aux, i;

	scanf_s("%d %d", &chapa_x, &chapa_y);
	chapa_area = chapa_x * chapa_y;
	scanf_s("%d", &n_tipos);
	tipos_arrumados = (tipo**)malloc((n_tipos + 1) * sizeof(tipo*));
	n_tipos_na_gaveta = (int*)malloc((n_tipos + 1) * sizeof(int));
	vpa_da_gaveta = (int*)malloc((n_tipos + 1) * sizeof(int));
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

void arrumar_gaveta(float vpa){
	tipo* gaveta;
	int valor_max = 0, n_max = 0;
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
	n_tipos_na_gaveta[n_gavetas] = n_max;
	vpa_da_gaveta[n_gavetas++] = valor_max;
	if (n_max != 0) {
		return;
	}
	tudo_arrumado = true;
}

int cortar_com_um_tipo(tipo peca, list<tipo>* pecas_usadas) {
	int  n_pecas, area_sobra, valor_agora;
	int i;

	n_pecas = (chapa_x / peca.x) * (chapa_y / peca.y);
	area_sobra = chapa_area - peca.x * peca.y * n_pecas;
	valor_agora = peca.valor * n_pecas;
	if (melhor_valor_ate_agora < valor_agora) {
		melhor_valor_ate_agora = valor_agora;
	}
	for (i = 0; i < n_pecas; i++) {
		pecas_usadas->push_back(peca);
	}
	return area_sobra;
}

int montagem(list<tipo> pecas_usadas, tipo nova_peca) {
	//pecas usadas cabem 100% garantia
	//usar next bellow
	int i;

	if (chapa_x < nova_peca.x || chapa_y < nova_peca.y) {
		return -1;
	}
	if (!pecas_usadas.empty()) {
		for (i = 0; !pecas_usadas.empty(); i++) {
			if (i > 0) {

			}
		}
	}
	else {
		return (chapa_area - nova_peca.x * nova_peca.y);
	}
}

void cortar_tentar_preencher(list<tipo> pecas_usadas,tipo nova_peca, int area_sobra_ant, int valor_ant, int i, int j) {
	tipo teste;
	int area_sobra;

	pecas_usadas.push_back(nova_peca);
	for (i; area_sobra_ant * vpa_da_gaveta[i] > melhor_valor_ate_agora; i++) {
		for (j; j < n_tipos_na_gaveta[i]; j++) {
			teste = tipos_arrumados[i][j];
			area_sobra = montagem(pecas_usadas, teste);
			if (area_sobra > 0) {
				if (melhor_valor_ate_agora < valor_ant + teste.valor) {
					melhor_valor_ate_agora = valor_ant + teste.valor;
				}
				cortar_tentar_preencher(pecas_usadas, teste, area_sobra, valor_ant + teste.valor, i, j);
			}
			else if (area_sobra == 0) {
				if (melhor_valor_ate_agora < valor_ant + teste.valor) {
					melhor_valor_ate_agora = valor_ant + teste.valor;
				}
				return;
			}
		}
		if (i + 1 == n_gavetas) {
			if (!tudo_arrumado) {
				arrumar_gaveta(vpa_da_gaveta[i]);
			}
			else {
				return;
			}
		}
	}
}

void cortar_substituir(list<tipo> pecas_usadas, int area_sobra_ant, int valor_ant) {
	tipo teste;
	int area_sobra;
	int i, j;
	bool first_time = true;

	valor_ant -= pecas_usadas.back().valor;
	area_sobra_ant -= (pecas_usadas.back().x * pecas_usadas.back().y);
	pecas_usadas.pop_back();
	for (i = i_inicio; area_sobra_ant * vpa_da_gaveta[i] > melhor_valor_ate_agora; i++) {
		if (!first_time) { j = 0; }
		else { j = j_inicio + 1; first_time = false; }
		for (j; j < n_tipos_na_gaveta[i]; j++) {
			teste = tipos_arrumados[i][j];
			area_sobra = montagem(pecas_usadas, teste);
			if (area_sobra > 0) {
				if (melhor_valor_ate_agora < valor_ant + teste.valor) {
					melhor_valor_ate_agora = valor_ant + teste.valor;
				}
				cortar_tentar_preencher(pecas_usadas, teste, area_sobra, valor_ant + teste.valor, i, j);
			}
			else if (area_sobra == 0) {
				if (melhor_valor_ate_agora < valor_ant + teste.valor) {
					melhor_valor_ate_agora = valor_ant + teste.valor;
				}
			}
		}
		if (i + 1 == n_gavetas) {
			if (!tudo_arrumado) {
				arrumar_gaveta(vpa_da_gaveta[i]);
			}
			else {
				return;
			}
		}
	}
	if (!pecas_usadas.empty()) {
		cortar_substituir(pecas_usadas, area_sobra_ant, valor_ant);
	}
}

void cortar() {
	list<tipo> tipos_usados;
	int i, j;

	for (i = 0; melhor_valor_ate_agora == 0; i++) {
		for (j = 0; n_tipos_na_gaveta[i] > j && melhor_valor_ate_agora == 0; j++) {
			if (cortar_com_um_tipo(tipos_arrumados[i][j], &tipos_usados) == 0) {
				printf("%d\n", melhor_valor_ate_agora);
				return;
			}
		}
		if (melhor_valor_ate_agora == 0) {
			if (!tudo_arrumado) {
				arrumar_gaveta(vpa_da_gaveta[i]);
			}
			else {
				return;
			}
		}
	}
	i_inicio = i;
	j_inicio = j;
}

int main() {
	int i;

	ler();
	arrumar_gaveta(NULL);
}