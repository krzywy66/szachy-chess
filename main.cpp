#include "klasy.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

int main() {
	szachownica s;
	kontrola_gry gra;

	s.start();

    while (!gra.czy_mat(s)) {
        s.wyswietl();

        ruch aktualny_ruch;
        aktualny_ruch = gra.pobierz_ruch(ruch{});

        if (gra.czy_ruch_legalny(aktualny_ruch, s)) {
            s.wykonaj_ruch(aktualny_ruch);
            gra.zmien_gracza();
            system("cls");
        }
        else std::cout << "Nielegalny ruch! Sprobuj jeszcze raz." << std::endl;
    }
    s.wyswietl();
    std::cout << "Mat! wygrywa gracz " << gra.get_aktualny_gracz()<<std::endl;


	return 0;
}