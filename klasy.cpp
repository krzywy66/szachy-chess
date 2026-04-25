#include "klasy.h"
#include <iostream>

bool pozycja::czy_pop() {
	if (kolumna >= 0 && kolumna < 8 && wiersz >= 0 && wiersz < 8) return true;
	else {
		std::cout << "Bledne dane " << std::endl;
		return false;
	}
}

void szachownica::start() {
	int i,j;

	for (i = 0; i <= 7; i++) {
		plansza[1][i] = 'P';
		plansza[6][i] = 'p';
	}
	plansza[0][0] = 'R';
	plansza[0][1] = 'N';
	plansza[0][2] = 'B';
	plansza[0][3] = 'Q';
	plansza[0][4] = 'K';
	plansza[0][5] = 'B';
	plansza[0][6] = 'N';
	plansza[0][7] = 'R';

	plansza[7][0] = 'r';
	plansza[7][1] = 'n';
	plansza[7][2] = 'b';
	plansza[7][3] = 'q';
	plansza[7][4] = 'k';
	plansza[7][5] = 'b';
	plansza[7][6] = 'n';
	plansza[7][7] = 'r';
	
	for (i = 2; i <= 5; i++) {
		for (j = 0; j <= 7; j++) plansza[i][j] = ' ';
	}
}

void szachownica::wyswietl() {
	int wiersz, kolumna, pod_wiersz, pod_kolumna;
	
	std::cout << " A  B  C  D  E  F  G  H" << std::endl;

	for (wiersz=8; wiersz >= 1; wiersz--) {
		if (wiersz % 2 == 0) {
			for (kolumna = 1; kolumna <= 8; kolumna++) {
				if (kolumna % 2 != 0) {
					for(pod_wiersz=0;pod_wiersz<=2;pod_wiersz++)
						for (pod_kolumna = 1; pod_kolumna < 2; pod_kolumna++) {
							if (pod_wiersz == 1 && pod_kolumna == 1) {
								if (plansza[wiersz - 1][kolumna - 1] == ' ') std::cout << char(0xB0);
								else std::cout << plansza[wiersz - 1][kolumna - 1];
							}
							else std::cout << char(0xB0);
						}
				}
				else {
					for (pod_wiersz = 0; pod_wiersz <= 2; pod_wiersz++)
						for (pod_kolumna = 1; pod_kolumna < 2; pod_kolumna++) {
							if (pod_wiersz == 1 && pod_kolumna == 1) {
								if (plansza[wiersz - 1][kolumna - 1] == ' ') std::cout << char(0xDB);
								else std::cout << plansza[wiersz - 1][kolumna - 1];
							}
							else std::cout << char(0xDB);
						}
				}
			}
		}
		else {
			for (kolumna = 1; kolumna <= 8; kolumna++) {
				if (kolumna % 2 != 0) {
					for (pod_wiersz = 0; pod_wiersz <= 2; pod_wiersz++)
						for (pod_kolumna = 1; pod_kolumna < 2; pod_kolumna++) {
							if (pod_wiersz == 1 && pod_kolumna == 1) {
								if (plansza[wiersz - 1][kolumna - 1] == ' ') std::cout << char(0xDB);
								else std::cout << plansza[wiersz - 1][kolumna - 1];
							}
							else std::cout << char(0xDB);
						}
				}
				else {
					for (pod_wiersz = 0; pod_wiersz <= 2; pod_wiersz++)
						for (pod_kolumna = 1; pod_kolumna < 2; pod_kolumna++) {
							if (pod_wiersz == 1 && pod_kolumna == 1) {
								if (plansza[wiersz - 1][kolumna - 1] == ' ') std::cout << char(0xB0);
								else std::cout << plansza[wiersz - 1][kolumna - 1];
							}
							else std::cout << char(0xB0);
						}
				}
			}
		}
		std::cout << "  " << wiersz << std::endl;
	}
}


void szachownica::wykonaj_ruch(ruch r) {
	plansza[r.cel.wiersz][r.cel.kolumna] = plansza[r.start.wiersz][r.start.kolumna];
	plansza[r.start.wiersz][r.start.kolumna] = ' ';
	//historia.push_back(r);
}

krol krol::k_temp;
hetman hetman::h_temp;
wieza wieza::w_temp;
goniec goniec::g_temp;
skoczek skoczek::s_temp;
pionek pionek::p_temp;


bool krol::poprawny_ruch(ruch r,szachownica s) {
	char cel=s.get_pole(r.cel.wiersz,r.cel.kolumna);
	int dx = abs(r.cel.wiersz - r.start.wiersz);
	int dy = abs(r.cel.kolumna - r.start.kolumna);
	
	if (dx <= 1 && dy <= 1) {
		if (cel == ' ') return true;
		else if (r.gracz == 'B' && isupper(cel)) return false;
		else if (r.gracz == 'C' && islower(cel)) return false;
		else return false;
	}
	else return false;
}

bool hetman::poprawny_ruch(ruch r, szachownica s) {
	int dx = r.cel.wiersz - r.start.wiersz;
	int dy = r.cel.kolumna - r.start.kolumna;
	bool czy_skos = (abs(dx) == abs(dy));
	bool czy_pion = (dx != 0 && dy == 0);
	bool czy_poziom = (dx == 0 && dy != 0);

	if (!czy_skos && !czy_pion && !czy_poziom) return false;

	int krok_w = (dx != 0) ? dx / abs(dx) : 0;
	int krok_k = (dy != 0) ? dy / abs(dy) : 0;
	int w = r.start.wiersz + krok_w;
	int k = r.start.kolumna + krok_k;
	while (w != r.cel.wiersz || k != r.cel.kolumna) {
		if (s.get_pole(w, k) != ' ') return false;
		w += krok_w;
		k += krok_k;
	}
	
	char cel = s.get_pole(r.cel.wiersz, r.cel.kolumna);
	if (r.gracz == 'B' && isupper(cel)) return false;
	else if (r.gracz == 'C' && islower(cel)) return false;
	else return true;
}

bool wieza::poprawny_ruch(ruch r, szachownica s) {
	int dx = r.cel.wiersz - r.start.wiersz;
	int dy = r.cel.kolumna - r.start.kolumna;
	bool czy_pion = (dx != 0 && dy == 0);
	bool czy_poziom = (dx == 0 && dy != 0);

	if (!czy_pion && !czy_poziom) return false;
	
	int krok_w = (dx != 0) ? dx / abs(dx) : 0;
	int krok_k = (dy != 0) ? dy / abs(dy) : 0;
	int w = r.start.wiersz + krok_w;
	int k = r.start.kolumna + krok_k;
	while (w != r.cel.wiersz || k != r.cel.kolumna) {
		if (s.get_pole(w, k) != ' ') return false;
		w += krok_w;
		k += krok_k;
	}

	char cel = s.get_pole(r.cel.wiersz, r.cel.kolumna);
	if (r.gracz == 'B' && isupper(cel)) return false;
	else if (r.gracz == 'C' && islower(cel)) return false;
	else return true;
}

bool goniec::poprawny_ruch(ruch r, szachownica s) {
	int dx = r.cel.wiersz - r.start.wiersz;
	int dy = r.cel.kolumna - r.start.kolumna;
	bool czy_skos = (abs(dx) == abs(dy));

	if (!czy_skos) return false;

	int krok_w = (dx > 0) ? 1 : -1;
	int krok_k = (dy > 0) ? 1 : -1;
	int w = r.start.wiersz + krok_w;
	int k = r.start.kolumna + krok_k;
	while (w != r.cel.wiersz || k != r.cel.kolumna) {
		if (s.get_pole(w, k) != ' ') return false;
		w += krok_w;
		k += krok_k;
	}

	char cel = s.get_pole(r.cel.wiersz, r.cel.kolumna);
	if (r.gracz == 'B' && isupper(cel)) return false;
	else if (r.gracz == 'C' && islower(cel)) return false;
	else return true;
}

bool skoczek::poprawny_ruch(ruch r, szachownica s) {
	int dx = r.cel.wiersz - r.start.wiersz;
	int dy = r.cel.kolumna - r.start.kolumna;
	bool czy_l = (abs(dy) == 2 && abs(dx) == 1) || (abs(dx) == 2 && abs(dy) == 1);
	if (!czy_l) return false;

	char cel = s.get_pole(r.cel.wiersz, r.cel.kolumna);
	if (r.gracz == 'B' && isupper(cel)) return false;
	else if (r.gracz == 'C' && islower(cel)) return false;
	else return true; 
}

bool pionek::poprawny_ruch(ruch r, szachownica s) {
	int dx = r.cel.wiersz - r.start.wiersz;
	int dy = abs(r.cel.kolumna - r.start.kolumna);
	if (r.gracz == 'B') {
		if (dy == 0) {
			if (r.start.wiersz == 1) {
				if (dx == 1 && s.get_pole(r.cel.wiersz, r.cel.kolumna) == ' ') return true;
				else if (dx == 2 && s.get_pole(r.cel.wiersz, r.cel.kolumna) == ' ' && s.get_pole(r.cel.wiersz - 1, r.cel.kolumna) == ' ') return true;
				else return false;
			}
			else if (dx == 1 && s.get_pole(r.cel.wiersz, r.cel.kolumna) == ' ') return true;
			else return false;
		}
		else if (dy == 1 && dx == 1 && islower(s.get_pole(r.cel.wiersz, r.cel.kolumna))) return true;
		else return false;
	}
	else {
		if (dy == 0) {
			if (r.start.wiersz == 6) {
				if (dx == -1 && s.get_pole(r.cel.wiersz, r.cel.kolumna) == ' ') return true;
				if (dx == -2 && s.get_pole(r.cel.wiersz, r.cel.kolumna) == ' ' && s.get_pole(r.cel.wiersz + 1, r.cel.kolumna) == ' ') return true;
				else return false;
			}
			else if (dx == -1 && s.get_pole(r.cel.wiersz, r.cel.kolumna) == ' ') return true;
			else return false;
		}
		else if (dy == 1 && dx == -1 && isupper(s.get_pole(r.cel.wiersz, r.cel.kolumna))) return true;
		else return false;
	}

}

bool kontrola_gry::czy_ruch_legalny(ruch r, szachownica s) {
	if (r.start.wiersz == r.cel.wiersz && r.start.kolumna == r.cel.kolumna) return false;

	char figura_symbol = s.get_pole(r.start.wiersz, r.start.kolumna);
	if (figura_symbol == ' ') return false;
	if (aktualny_gracz == 'B' && islower(figura_symbol)) {
		return false;
	}
	if (aktualny_gracz == 'C' && isupper(figura_symbol)) {
			return false;
		}
	
	figura* f;
	switch (tolower(figura_symbol)) {
		case 'k': f = &krol::k_temp; break;
		case 'q': f = &hetman::h_temp; break;
		case 'r': f = &wieza::w_temp; break;
		case 'b': f = &goniec::g_temp; break;
		case 'n': f = &skoczek::s_temp; break;
		case 'p': f = &pionek::p_temp; break;
		default: return false;
	}
	if (!f->poprawny_ruch(r,s)) {
		return false;
	}

	szachownica kopia = s;
	kopia.wykonaj_ruch(r);
	if (czy_szach(kopia)) {
		std::cout << "Jest szach po tym ruchu " << std::endl;
		return false;
	}
	std::cout << "Poprawny ruch " << std::endl;
	return true;
}

bool kontrola_gry::czy_szach(szachownica s) {
	char figura_symbol, krol_symbol = (aktualny_gracz == 'B') ? 'K' : 'k';
	pozycja krol_pos;
	int w, k, i, dw, dk;
	bool znaleziono = false;

	if (krol_symbol == 'K') {
		for (w = 0; w < 8 && !znaleziono; w++)
			for (k = 0; k < 8; k++) {
				if (s.get_pole(w, k) == krol_symbol) {
					krol_pos = { k, w };
					znaleziono = true;
					break;
				}
			}
	}
	else {
		for (w = 0; w < 8 && !znaleziono; w++)
			for (k = 0; k < 8; k++) {
				if (s.get_pole(w, k) == krol_symbol) {
					krol_pos = { k, w };
					znaleziono = true;
					break;
				}
			}
	}

	int skosy[4][2] = { {-1,-1},{-1,1},{1,-1},{1,1} };
	for (i = 0; i < 4; i++) {
		dw = skosy[i][0];
		dk = skosy[i][1];
		w = krol_pos.wiersz + dw;
		k = krol_pos.kolumna + dk;
		
		while (w >= 0 && w < 8 && k >= 0 && k < 8) {
			figura_symbol = s.get_pole(w, k);
			if (figura_symbol != ' ') {
				if ((aktualny_gracz == 'B' && (figura_symbol == 'q' || figura_symbol == 'b')) || (aktualny_gracz == 'C' && (figura_symbol == 'Q' || figura_symbol == 'B'))) return true;
				break;
			}
			w += dw;
			k += dk;
		}
	}

	int pion_poziom[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
	for (i = 0; i < 4; i++) {
		dw = pion_poziom[i][0];
		dk = pion_poziom[i][1];
		w = krol_pos.wiersz + dw;
		k = krol_pos.kolumna + dk;
		while (w >= 0 && w < 8 && k >= 0 && k < 8) {
			figura_symbol = s.get_pole(w, k);
			if (figura_symbol != ' ') {
				if ((aktualny_gracz == 'B' && (figura_symbol == 'q' || figura_symbol == 'r')) || (aktualny_gracz == 'C' && (figura_symbol == 'Q' || figura_symbol == 'R'))) return true;
				break;
			}
			w += dw;
			k += dk;
		}
	}

	int skoczki[8][2] = { {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},{1, -2}, {1, 2}, {2, -1}, {2, 1} };
	for (i = 0; i < 8; i++) {
		dw = skoczki[i][0];
		dk = skoczki[i][1];
		w = krol_pos.wiersz + dw;
		k = krol_pos.kolumna + dk;
		if (w >= 0 && w < 8 && k >= 0 && k < 8) {
			figura_symbol = s.get_pole(w, k);
			if (figura_symbol != ' ') {
				if ((aktualny_gracz == 'B' && figura_symbol == 'n') || (aktualny_gracz == 'C' && figura_symbol == 'N')) return true;
			}
		}
	}

	int pionki_kierunek = (aktualny_gracz == 'B') ? 1 : -1;
	int pionki[2][2] = { {pionki_kierunek,-1},{pionki_kierunek,1} };
	for (i = 0; i < 2; i++) {
		dw = pionki[i][0];
		dk = pionki[i][1];
		w = krol_pos.wiersz + dw;
		k = krol_pos.kolumna + dk;
		if (w >= 0 && w < 8 && k >= 0 && k < 8) {
			figura_symbol = s.get_pole(w, k);
			if (figura_symbol != ' ') {
				if ((aktualny_gracz == 'B' && figura_symbol == 'p' && dw==1) || (aktualny_gracz == 'C' && figura_symbol == 'P' && dw==-1)) return true;
			}
		}
	}
	return false;
}

bool kontrola_gry::czy_mat(szachownica s) {
	std::cout << "Ruch gracza " << aktualny_gracz << std::endl;
	if (!czy_szach(s)) {
		return false;
	}
	std::cout << "Krol jest w szachu" << std::endl;
	int cel_w, cel_k, w, k;
	for (w = 0; w < 8; w++) {
		for (k = 0; k < 8; k++) {
			char figura = s.get_pole(w, k);

			if ((aktualny_gracz == 'B' && isupper(figura)) || (aktualny_gracz == 'C' && islower(figura))) {
				for (cel_w = 0; cel_w < 8; cel_w++) {
					for (cel_k = 0; cel_k < 8; cel_k++) {
						ruch r{ {w, k}, {cel_w, cel_k}, aktualny_gracz };
						if (czy_ruch_legalny(r, s)) {
							szachownica kopia = s;
							kopia.wykonaj_ruch(r);
							if(!czy_szach(kopia)) return false;
						}
					}
				}
			}
		}
	}
	return true;
}

ruch kontrola_gry::pobierz_ruch(ruch r) {
	char kolumna;

	do {
		std::cout << "Podaj pozycje figury ktora chcesz sie ruszyc (format najpierw kolumna pozniej wiersz np. A5, d4, G8): " << std::endl;
		std::cin >> kolumna >> r.start.wiersz;
		r.start.kolumna = tolower(kolumna) - 'a';
		r.start.wiersz--;

		if (!r.start.czy_pop()) std::cout << "Niepoprawna pozycja! Wpisz np. A2, g7." << std::endl;
	} while (!r.start.czy_pop());
	do {
		std::cout << "Podaj pozycje na ktora chcesz ruszyc ta figure (format najpierw kolumna pozniej wiersz np. A5, d4, G8): " << std::endl;
		std::cin >> kolumna >> r.cel.wiersz;
		r.cel.kolumna = tolower(kolumna) - 'a';
		r.cel.wiersz--;

		if (!r.cel.czy_pop()) std::cout << "Niepoprawna pozycja! Wpisz np. A2, g7." << std::endl;
	} while (!r.cel.czy_pop());
	r.gracz = this->aktualny_gracz;
	return r;
}

void kontrola_gry::zmien_gracza() {
	if (aktualny_gracz == 'B') aktualny_gracz = 'C';
	else aktualny_gracz = 'B';
}
