#pragma once
#include <vector>
#include <iostream>
#include <string>

struct pozycja {
	int kolumna;
	int wiersz;
	bool czy_pop();
};

struct ruch {
	pozycja start;
	pozycja cel;
	char gracz;
};

class szachownica {
	char plansza[8][8];
	//std::vector<ruch> historia;
public:
	char get_pole(int wiersz, int kolumna) { return plansza[wiersz][kolumna]; }
	void start();
	void wyswietl();
	void wykonaj_ruch(ruch r);
};

class figura {
	std::string kolor;
	std::string nazwa;
public:
	virtual bool poprawny_ruch(ruch r, szachownica s) = 0;
};


class krol :public figura {
public:
	static krol k_temp;
	bool poprawny_ruch(ruch r, szachownica s);
};

class hetman :public figura {
public:
	static hetman h_temp;
	bool poprawny_ruch(ruch r, szachownica s);
};

class wieza :public figura {
public:
	static wieza w_temp;
	bool poprawny_ruch(ruch r, szachownica s);
};

class goniec :public figura {
public:
	static goniec g_temp;
	bool poprawny_ruch(ruch r, szachownica s);
};

class skoczek :public figura {
public:
	static skoczek s_temp;
	bool poprawny_ruch(ruch r, szachownica s);
};

class pionek :public figura {
public:
	static pionek p_temp;
	bool poprawny_ruch(ruch r, szachownica s);
};

class kontrola_gry {
	szachownica rozgrywka;
	char aktualny_gracz = 'B';
public:
	char get_aktualny_gracz() { return aktualny_gracz; }
	ruch pobierz_ruch(ruch r);
	bool czy_ruch_legalny(ruch r, szachownica s);
	bool czy_szach(szachownica s);
	bool czy_mat(szachownica s);
	void zmien_gracza();

};
