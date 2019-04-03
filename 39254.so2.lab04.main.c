//SO2 IS1 221B LAB04
//Justyna Dreger
//dj39254@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

//flaga
int f;
pid_t proces,pid2;
//zmiana flagi
void fu(int s){f=0;}
//wypisanie tabulacji - obsluguje blokowane sygnaly
void fu2(int s){printf("\t");}
//ile argumentów podano, tablica podanych argumentów
int main(int liczba_arg, char **tab_arg)
{
	if (liczba_arg < 2)
	{
		printf("Nie ma wystarczajavej liczby argumentow!!!\n");
		return 0;
	}
	//ustawienie flagi
	f = 1;
	//zbiór sygnałów 1,2,3
	sigset_t s, s1, s2;
	//utworzenie struktury sigaction
	struct sigaction act, act2;
	//ustawienie pustego zbioru sygnałów
	sigemptyset(&s);
	sigemptyset(&s1);
	sigemptyset(&s2);
	//podanie funkcji jako akcji na sygnał
	act.sa_handler = &fu;
	act2.sa_handler = &fu2;
	//przypisanie maski sygnałów
	act.sa_mask = s;
	act2.sa_mask = s2;
	//przypisanie wartości flagi, na którą będzie reagować
	act.sa_flags = 0;
	act2.sa_flags = 0;

	sigaddset(&s1, SIGTSTP);
	//zmiana akcji - po odebraniu SIGINT brana jest akcja z act, nie przechowujemy poprzedniej akcji
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGTSTP, &act2, NULL);
	//zmiana akcji - po odebraniu SIG_BLOCK brana jest akcja z s1, nie przechowujemy poprzedniej akcji
	sigprocmask(SIG_BLOCK, &s1, NULL);	

	
	//sprawdzanie czy jest potegš 2
	int dlugosc = strlen(tab_arg[liczba_arg - 1]);
	int bit = 1, ile_j = 0;

	//32 bo int ma 32 bity!!
	//pętla porównuje z potęgami 2
	int i = 0;
	for (i; i<32; i++) {
		if (dlugosc == bit) {
			ile_j = 1;
			break;
		}
		else
		{
			ile_j++;
		}
		bit = bit << 1;
	}
	char *poczatkowy;
	if (ile_j != 1) {
		//zmiana długości - ponieważ nie jest potęgą 2
		poczatkowy = malloc((dlugosc + 1) * sizeof(char));
		//kopia parametrów
		strncpy(poczatkowy, tab_arg[liczba_arg - 1], dlugosc);
		//dodanie parametru
		poczatkowy[dlugosc] = 'z';
	}
	else {
		//bez zmian
		poczatkowy = calloc((dlugosc) , sizeof(char));
		//kopia parametrów
		strncpy(poczatkowy, tab_arg[liczba_arg - 1], dlugosc);
	}

	//warunek zaprzestania dzielenia
	if (dlugosc != 1)
	{
		char *lewy, *prawy;
		//wskaniki na podzielone parametry
		lewy = calloc(((strlen(poczatkowy) / 2) + 1), sizeof(char));
		prawy = calloc(((strlen(poczatkowy) / 2) + 1), sizeof(char));
		//przypisanie parametrów
		memcpy(lewy, tab_arg[1], (strlen(poczatkowy) / 2))
		memcpy(prawy, tab_arg[1] + (strlen(poczatkowy) / 2), (strlen(poczatkowy) / 2));
		//utworzenie tablic argumentów dla nowych procesów + nazwy procesu
		char **nowy = (char**)malloc((liczba_arg + 2) * sizeof(char*));
		int k = 0;
		while (k < liczba_arg) {
			nowy[k] = tab_arg[k];
			k++;
		}

		nowy[liczba_arg + 1] = NULL;
		//pierwszy proces potomny
		pid_t pid = -1;
		pid = fork();
		//		 pid_t pid2;
		if (pid == 0)
		{
			////zmiana grupy procesu bieżącego do nowej grupy, której liderem jest ten proces
			setpgid(0, 0);
			nowy[liczba_arg] = lewy;

			//wywołanie tego samego programu z połowš argumentów
			execvp("./a.out", nowy);
			//kończenie procesu
			exit(0);
		}
		else {
			//pid_t pid2;
			//drugi proces potomny
			pid2 = fork();
			if (pid2 == 0)
			{
				///
				//zmiana grupy procesu bieżącego do nowej grupy, której liderem jest ten proces
				setpgid(0, 0);
				nowy[liczba_arg] = prawy;
				//wywołanie tego samego programu z połowš argumentów
				execvp("./a.out", nowy);
				//kończenie procesu
				exit(0);

			}
		}
		//zwolnienie wskaników
		free(nowy);
		free(prawy);
		free(lewy);
		kill(pid, 2);
		kill(pid2, 2);
	}
	free(poczatkowy);
	while (f == 1) {
		//niekonczonca sie petla
	}
	if (dlugosc > 1) {
		kill(pid2, 2);
		kill(proces, 2);
	}
	//identyfikator procesu potomnego
	pid_t id;
	int licznik = 0;

	//czekanie na zakończenie procesów
	//2 bo 2 procesy potomne
	//wait zwróci identyfikator procesu potomnego
	//jeli ==0 to to jest id procesu głównego
	while ((id = wait(NULL)) > 0)
	{
		licznik++;
		if (licznik == 2) break;
	}

	//pobranie pid procesu głównego i wypisanie
	printf("%d ",getpid());

	//wypisanie parametrów wywołania
	int m = 1;
	while (m < liczba_arg) {
		printf("%s ", tab_arg[m]);
		m++;
	}
	printf("\n");
	//zbiór sygnałów 4
	sigset_t zablokowane;
	//pobranie zbioru sygnałów, które zostały przysłane i zablokowane
	sigpending(&zablokowane);
	//czy sygnał SIGTSTP jest w zbiorze przysłanych sygnałów
	if (sigismember(&zablokowane, SIGTSTP)) printf("\nByl sygnal!\n");
	//zmiana maski blokowanych sygnałów
	//usunięcie z aktualnej maski sygnału z zbioru 
	//sygnały sprzed zmiany nie są zapisywane
	sigprocmask(SIG_UNBLOCK, &s1, NULL);

	return 0;
}
