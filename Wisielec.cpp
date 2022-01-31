#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <ctime>
#include <cctype>
#include <windows.h>
using namespace std;

struct statystyki
{
	double liczba_gier;
	int liczba_wygranych;
	int liczba_przegranych;
	double liczba_bledow;
	void wypisz()
	{
		cout << "liczba gier: " << liczba_gier << endl;
		cout << "liczba wygranych: " << liczba_wygranych << endl;
		cout << "liczba przegranych: " << liczba_przegranych << endl;
		cout << "procent wygranych: " << (liczba_wygranych * 100) / liczba_gier << "%" << endl;
		cout << "srednia ilosc bledow: " << liczba_bledow/liczba_gier << endl;
	}
};//struktura odpowiadajaca za statystkyi

statystyki statystyka;

statystyki zczytywanie_statystyk()//zczytanie z pliku aktualnych statystyk
{
	string linia;
	fstream plik;
	int i{};
	plik.open("statystyki.txt", ios::in);
	if (plik.is_open())
	{
		while (!plik.eof())
		{
			getline(plik, linia);
			if (i == 0)
				statystyka.liczba_gier = stod(linia);
			else if (i == 1)
				statystyka.liczba_wygranych = stoi(linia);
			else if (i == 2)
				statystyka.liczba_przegranych = stoi(linia);
			else if (i == 3)
				statystyka.liczba_bledow = stod(linia);
			i++;
		}
	}
	plik.close();
	return statystyka;
}

//funkcja odpowidajaca za najwazniejsza czesc programu czyli sama gre(wytlumaczenie na czym ona polega w dokumentacji)
void zgadywanie(string wylosowany_wyraz, int n)
{
	zczytywanie_statystyk();
	setlocale(LC_ALL, "");//nie wiem jak dokladnie dziala ale dzieki temu w konsoli pokazuja sie polskie znaki(przynajmniej u mnie tak to dziala jak widac na zrzutach w dokumentacji)
	char podane_litery[1024]{};
	string podana_litera;
	int ilosc_bledow{}, i_glowne{}, i{}, j{}, ile_pustych{};
	bool nie_ma, czy_pisac_spacje, graj = true; /*litera_byla = false;*/

	while (graj)
	{
		bool litera_byla = false;
		nie_ma = true;
		i_glowne = 0;
		ile_pustych = 0;
		cout << "podaj litere: ";
		cin >> podana_litera;
		if (i == 0)
			litera_byla = false;
		else
			litera_byla = true;
		while (!isalpha(podana_litera[0]) || podana_litera.length() > 1 || litera_byla)//sprawdzenie czy podano tylko jedna litere i nic innego
		{
			if (!isalpha(podana_litera[0]))
			{
				cout << "podales liczbe, prosze podaj liter© ";
				cin >> podana_litera;
			}
			else if (podana_litera.length() > 1)
			{
				cout << "nie wprowadziles jednej litery\npodaj tylko jedna litere prosze: ";
				cin >> podana_litera;
			}
			else if (i > 0)
			{
				j = 0;
				while (podane_litery[j] != 0)
				{
					if (podana_litera[0] == podane_litery[j])
					{
						litera_byla = true;
						j++;
						break;
					}
					else
						litera_byla = false;
					j++;
				}
				if (litera_byla)
				{
					cout << "ta litera juz byla, podaj inna: ";
					cin >> podana_litera;
				}
			}
		}

		podane_litery[i] = podana_litera[0];//gdy funkcja sie skonczy i podana litera jest prawidlowa dodaje ja do tabeli ktora bedzie zawierac wszystkie podane litery
		system("cls");
		cout << "-----------------------------------\n";
		while (wylosowany_wyraz[i_glowne] != 0)
		{
			if (podana_litera[0] == wylosowany_wyraz[i_glowne])//jesli podana litera w tym ruchu nie znajduje sie w wylosowanym wyrazie zmienna nie_ma = false bedzie pozniej uzyta do zliczenie bledow
				nie_ma = false;
			j = 0;
			czy_pisac_spacje = true;
			while (podane_litery[j] != 0)
			{
				if (wylosowany_wyraz[i_glowne] == podane_litery[j])//jesli podana byla juz litera znajdujaca sie w wyrazie wylosowanym bedzie ona wypisana
				{
					cout << " " << wylosowany_wyraz[i_glowne] << " ";
					Sleep(100);
					czy_pisac_spacje = false;//jesli tej litet nie ma w wyrazie bedziemy pozniej pisac spacje na podstawie tej zmiennej czy_pisac_spacje
				}
				j++;
			}
			if (wylosowany_wyraz[i_glowne] == 32)
			{
				cout << "\n";
			}
			else if (czy_pisac_spacje)
			{
				cout << " _ ";
				Sleep(100);
				ile_pustych++;//sprawdzenie czy byly bledy
			}
			i_glowne++;
		}
		i++;
		cout << endl;
		if (nie_ma)
			ilosc_bledow++;//zliczanie bledow jesli litery podanej przez uztykownika nie bylo w wyrazie
		if (ilosc_bledow >= n)//jesli liczba bledow jest wieksza niz dozwolona na ta gre przegrana
		{
			graj = false;
			cout << "niestety przegrałeś ;( powodzenia następnym razem!\n";
			cout << "wyraz do odgadniecia: " << wylosowany_wyraz << " " << endl;
			statystyka.liczba_gier++;
			statystyka.liczba_przegranych++;
			statystyka.liczba_bledow += ilosc_bledow;
		}
		if (ile_pustych == 0)//jesli caly wyraz zostal wypisany wygrana
		{
			graj = false;
			cout << "BRAWO WYGRAŁEŚ!!\n";
			statystyka.liczba_gier++;
			statystyka.liczba_wygranych++;
			statystyka.liczba_bledow += ilosc_bledow;
		}
		if (ilosc_bledow > 0)//wypisanie ile juz bledow w trakcie gry bylo popelnionych

		{
			int wisielec{};
			cout << "twoja ilość błędów: ";
			for (int i = 0; i < ilosc_bledow; i++)
			{
				cout << " * ";
				wisielec = i;
			}
			cout << endl;
			if (wisielec == 0)
			{
				cout << "\n\n\n\n\n";
				cout << "/ \\" << endl;
			}

			else if (wisielec == 1)
			{
				cout << "" << endl;
				cout << " |  " << endl;
				cout << " |    " << endl;
				cout << " |   " << endl;
				cout << " |   " << endl;
				cout << "/ \\" << endl;
			}

			else if (wisielec == 2)
			{
				cout << " ______" << endl;
				cout << " |/   " << endl;
				cout << " |    " << endl;
				cout << " |   " << endl;
				cout << " |   " << endl;
				cout << "/ \\" << endl;
			}

			else if (wisielec == 3)
			{
				cout << " ______" << endl;
				cout << " |/   |" << endl;
				cout << " |    O" << endl;
				cout << " |   " << endl;
				cout << " |   " << endl;
				cout << "/ \\" << endl;
			}

			else if (wisielec == 4)
			{
				cout << " ______" << endl;
				cout << " |/   |" << endl;
				cout << " |    O" << endl;
				cout << " |   /|\\" << endl;
				cout << " |   / \\" << endl;
				cout << "/ \\" << endl;
			}

			cout << endl;
		}
		cout << "-----------------------------------\n";
		int pod = 0;
		cout << "LISTA PODANYCH LITER: \n";
		while (podane_litery[pod] != 0)
		{
			cout << podane_litery[pod] << endl;
			pod++;
		}
	}
	ofstream plik;
	plik.open("statystyki.txt");
	if (plik.is_open())
	{
		plik << statystyka.liczba_gier << endl;
		plik << statystyka.liczba_wygranych << endl;
		plik << statystyka.liczba_przegranych << endl;
		plik << statystyka.liczba_bledow << endl;
	}
	plik.close();

}


//funkcja odpowiadajaca za losowanie wyrazu z pliku
string losowanie_wyrazu()
{
	string linia;
	string wylosowany_wyraz;
	string wylosowana_kategoria;
	int ile_wyrazow{};
	int numer_wyrazu{};
	int numer_kategorii{};
	fstream plik;
	plik.open("wyrazy.txt", ios::in);//zczytanie ile wyrazow znajduje sie w pliku
	if (plik.is_open())
	{
		while (!plik.eof())
		{
			getline(plik, linia);
			ile_wyrazow++;
		}
		plik.close();
	}
	else
		cout << "Blad";


	mt19937 generator(time(nullptr));//zainicjowanie losowania od 1 do ile jest wyrazow
	uniform_int_distribution<int>losowanie_lini(1, ile_wyrazow);
	numer_wyrazu = losowanie_lini(generator);
	if (numer_wyrazu % 2 == 0)//w pliku na liniach parzystych sa wyrazy a na nieparzystych kategorie(jesli liczba wylosowno linie na ktorej jest wyraz to to bedzie numer_wyrazu
		//a numer_kategorii to bedzie jedno wyzej
	{
		numer_kategorii = numer_wyrazu - 1;
	}
	else//w przeciwnym przypadku numer kategorii to wylosowana linia a numer_wyrazu to jedna linia dalej
	{
		numer_kategorii = numer_wyrazu;
		numer_wyrazu = numer_kategorii + 1;
	}

	plik.open("wyrazy.txt", ios::in);//wylosowanie wyrazu do zgadniecia przez uzytkownika
	if (plik.is_open())
	{
		for (int i = 0; i < numer_wyrazu; i++)
		{
			if (i == numer_kategorii)
			{
				wylosowana_kategoria = linia;//zczytanie kategorii wedlug ustalonego wczesniej numer_kategorii
			}
			getline(plik, linia);
		}
		cout << wylosowana_kategoria << "\n";
		wylosowany_wyraz = linia;//wylosowany wyraz to ostatnia linia zczytana z pliku poniewaz zczytywalismy do numeru linii wyrazu wczesniej ustalonego za pomoca zmiennej numer_wyrazu
		plik.close();
	}
	return wylosowany_wyraz;//zwrocenie wylosowanego_wyrazu;
}

void dopisywanie_do_pliku()
{
	int i{};
	bool zly_input = true;
	string kategoria;
	string slowo;
	int odp = 2;
	string kategoria_nowego_slowa;
	

	while (true)
	{
		
		cout << "Jakiej kategorii słowo chcesz dopisać do gry\n";
		cin>>kategoria;
		cout << "Jakie słowo chcesz dopisać do gry\n";
		cin.ignore();
		getline(cin, slowo);//zapisanie jakiej kategorii i jakie slowa chcemy dodac do przyslych gier
		do
		{
			cout << "Czy dane które chcesz dodać są prawidłowe(TAK-1/NIE-0/Wyjdź do menu-2):\nkategoria: " << kategoria << "\nslowo: " << slowo << "\n";
			cin >> odp;//zapytanie czy wprowadzono prawidlowe dane
			system("cls");
		} while (odp != 1 && odp != 0 && odp != 2);
		if (odp == 1 || odp == 2)
			break;
		
	}
	if (odp == 1)
	{
		fstream plik("wyrazy.txt", ios::app);
		plik << "\nkategoria:" + kategoria + "\n";
		plik << slowo;
		plik.close();
	}


}

void gra()
{
	while (true)
	{
		int z{};
		do
		{
			cout << "WISIELEC by Michał Bober" << endl;
			cout << "1.Graj\n2.Dodaj nowe słowa\n3.Statystyki\n0.Wyjdź" << endl;
			cin >> z;
			if (z == 1)//1 to gra 
			{
				bool graj_dalej = true;
				int odp = 2;
				while (graj_dalej)
				{
					system("cls");
					cout << "POWODZENIA";
					Sleep(1500);
					system("cls");
					zgadywanie(losowanie_wyrazu(), 5);
					cout << "chcesz grac dalej?(TAK-1,NIE-0) \n";
					cin >> odp;
					while (odp != 1 && odp != 0)
					{
						cout << "nie wprowadzilaes 0 ani 1\nchcesz grac dalej?(TAK-1,NIE-0) \n";
						cin >> odp;
					}
					if (odp == 0)
						graj_dalej = false;
					system("CLS");
				}
			}
			else if (z == 2)//2 to dodawanie nowego slowa do gry
			{
				int co_robic{};
				system("cls");
				dopisywanie_do_pliku();
			}
			else if (z == 3)//3 to sprawdzenie statystyk
			{
				int co_robic{};
				system("cls");
				zczytywanie_statystyk();
				statystyka.wypisz();
				cout << "POWRÓT DO MENU - 1/WYJDŹ - 0 " << endl;
				cin >> co_robic;
				if (co_robic == 0)
					exit(0);
				else if (co_robic == 1)
					system("cls");
			}
			else if (z == 0)
			{
				system("cls");
				exit(0);
			}
		} while (z > 3 || z < 0);
	}


}
   

int main()
{
	setlocale(LC_ALL, "");
	/*dopisywanie_do_pliku();*/

	gra();
	system("pause");
}



