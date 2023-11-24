#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <vector>
#include <string>
#include <list>

using namespace std;

typedef struct tipo tipo;
typedef struct canto canto;

struct tipo {
	int x;
	int y;
	int valor;
	float valor_por_area;
};

struct canto {
	int x;
	int y;
	int lim_x;
	int lim_y;
};

tipo* todos_tipos;
tipo** tipos_arrumados;
bool tudo_arrumado = false;
int* n_tipos_na_gaveta;
int* vpa_da_gaveta;
float chapa_x, chapa_area;
int chapa_y, n_tipos, n_gavetas = 0;
int melhor_valor_ate_agora = 0;
int i_inicio, j_inicio;

void ler() {
	tipo tipo_info;
	int aux, i;

	scanf_s("%f %d", &chapa_x, &chapa_y);
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

canto criar_canto(int x, int y) {
	canto c;
	c.x = x;
	c.y = y;
	c.lim_x = chapa_x;
	c.lim_y = chapa_y;
	return c;
}

void arrumar_gaveta(float vpa){
	tipo* gaveta;
	int valor_max = 0, n_max = 0;
	int i, j;

	if (vpa == NULL) {
		for (i = 0; i < n_tipos; i += 2) {
			if (valor_max < todos_tipos[i].valor_por_area) {
				valor_max = todos_tipos[i].valor_por_area;
				n_max = 2;
			}
			else if (valor_max == todos_tipos[i].valor_por_area) {
				n_max+=2;
			}
		}
	}
	else {
		for (i = 0; i < n_tipos; i += 2) {
			if (valor_max < todos_tipos[i].valor_por_area && vpa > todos_tipos[i].valor_por_area) {
				valor_max = todos_tipos[i].valor_por_area;
				n_max = 2;
			}
			else if (valor_max == todos_tipos[i].valor_por_area) {
				n_max+=2;
			}
		}
	}
	gaveta = (tipo*)malloc(n_max * sizeof(tipo));
	for (i = 0, j = 0; i < n_tipos; i += 2) {
		if (todos_tipos[i].valor_por_area == valor_max) {
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
	int n_pecas, area_sobra, valor_agora;
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

bool por_nos_cantos(list<tipo> pecas_usadas, list<canto> cantos, canto canto_ant, int n_pos) {
	tipo peca;
	
	peca = pecas_usadas.front();
	if (canto_ant.x + peca.x > canto_ant.lim_x|| canto_ant.y + peca.y > canto_ant.lim_y) {
		return false;
	}
	pecas_usadas.pop_front();
	if (!pecas_usadas.empty()) {
		canto c1, c2;
		int i;
		auto canto_ant_pos = cantos.begin();
		for (i = 0; i < n_pos; i++) {
			canto_ant_pos++;
		}
		c1 = criar_canto(canto_ant.x + peca.x, canto_ant.y);
		c2 = criar_canto(canto_ant.x, canto_ant.y + peca.y);
		cantos.insert(canto_ant_pos, c1);
		cantos.insert(canto_ant_pos, c2);
		auto canto_aux_pos = canto_ant_pos;
		canto_ant_pos--;
		cantos.erase(canto_aux_pos);
		canto_aux_pos = --canto_ant_pos;
		//ajustar limites doutros cantos
		//proprios limites
		//mover o canto no sitio certo
		for (i/*= n_pos*/; i > 0; i--) {
			canto_aux_pos--;
			if (canto_aux_pos->x < c1.x) {
				canto_aux_pos->lim_y = c1.y;
				canto_ant_pos->y = canto_aux_pos->y;
			}
			else if (canto_aux_pos->x == c1.x) {
				cantos.erase(canto_aux_pos);
				break;
			}
			else {
				break;
			}
		}
		canto_aux_pos = ++canto_ant_pos;
		for (i = n_pos + 2; i < cantos.size(); i++) {
			canto_aux_pos++;
			if (canto_aux_pos->y < c2.y) {
				canto_aux_pos->lim_x = c2.x;
				canto_ant_pos->x = canto_aux_pos->x;
			}
			else if (canto_aux_pos->x == c2.x) {
				cantos.erase(canto_aux_pos);
				break;
			}
			else {
				break;
			}
		}
		//acho que funcemina
		n_pos = 0;
		for (canto c : cantos) {
			if (por_nos_cantos(pecas_usadas, cantos, c, n_pos)) {
				return true;
			}
			n_pos++;
		}
		return false;
	}
	return true;
}

int montagem(list<tipo> pecas_usadas, tipo nova_peca, int area_sobra_ant) {
	//pecas usadas cabem 100% garantia
	//usar next bellow
	list<canto> cantos;
	canto c = criar_canto(0, 0);
	int area_sobra;
	int i;

	if (chapa_x < nova_peca.x || chapa_y < nova_peca.y) {
		return -1;
	}
	if (nova_peca.x * nova_peca.y > area_sobra_ant) {
		return -1;
	}
	if (!pecas_usadas.empty()) {
		pecas_usadas.push_back(nova_peca);
		cantos.push_back(c);
		if (por_nos_cantos(pecas_usadas, cantos, c, 0)) {
			return area_sobra_ant - (nova_peca.x * nova_peca.y);
		}
		return -1;
	}
	return area_sobra_ant - (nova_peca.x * nova_peca.y);
}

void cortar_tentar_preencher(list<tipo> pecas_usadas,tipo nova_peca, int area_sobra_ant, int valor_ant, int i, int j) {
	tipo teste;
	int area_sobra;
	bool first_time = true;

	pecas_usadas.push_back(nova_peca);
	for (i; area_sobra_ant * vpa_da_gaveta[i] > melhor_valor_ate_agora - valor_ant; i++) {
		if (!first_time) { j = 0; }
		else { first_time = false; }
		for (j; j < n_tipos_na_gaveta[i]; j++) {
			teste = tipos_arrumados[i][j];
			area_sobra = montagem(pecas_usadas, teste, area_sobra_ant);
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
	for (i = i_inicio; area_sobra_ant * vpa_da_gaveta[i] > melhor_valor_ate_agora - valor_ant; i++) {
		if (!first_time) { j = 0; }
		else { j = j_inicio + 1; first_time = false; }
		for (j; j < n_tipos_na_gaveta[i]; j++) {
			teste = tipos_arrumados[i][j];
			area_sobra = montagem(pecas_usadas, teste, area_sobra_ant);
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
				break;
			}
		}
	}
	if (!pecas_usadas.empty()) {
		cortar_substituir(pecas_usadas, area_sobra_ant, valor_ant);
	}
}

void cortar() {
	list<tipo> tipos_usados;
	tipo teste;
	int area_sobra, valor_ant;
	bool first_time = true;
	int i, j;

	for (i = 0; melhor_valor_ate_agora == 0; i++) {
		for (j = 0; n_tipos_na_gaveta[i] > j && melhor_valor_ate_agora == 0; j++) {
			area_sobra = cortar_com_um_tipo(tipos_arrumados[i][j], &tipos_usados);
			if (area_sobra == 0) {
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
	i_inicio = i--;
	j_inicio = j--;
	valor_ant = melhor_valor_ate_agora;
	for (i = i_inicio; area_sobra * vpa_da_gaveta[i] > melhor_valor_ate_agora - valor_ant; i++) {
		if (!first_time) { j = 0; }
		else { j = j_inicio + 1; first_time = false; }
		for (j; j < n_tipos_na_gaveta[i]; j++) {
			teste = tipos_arrumados[i][j];
			area_sobra = montagem(tipos_usados, teste, area_sobra);
			if (area_sobra > 0) {
				if (melhor_valor_ate_agora < valor_ant + teste.valor) {
					melhor_valor_ate_agora = valor_ant + teste.valor;
				}
				cortar_tentar_preencher(tipos_usados, teste, area_sobra, valor_ant + teste.valor, i, j);
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
				break;
			}
		}
	}
	cortar_substituir(tipos_usados, area_sobra, valor_ant);

}

int main() {
	int i;

	ler();
	arrumar_gaveta(NULL);
	cortar();
	printf("%d", melhor_valor_ate_agora);
}