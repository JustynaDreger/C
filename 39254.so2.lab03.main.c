//SO2 IS1 221B LAB03
//Justyna Dreger
//dj39254@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


//ile argument�w podano, tablica podanych argument�w
int main(int liczba_arg,char **tab_arg)
{
	if(liczba_arg<2)
	{
		printf("Nie ma wystarczajavej liczby argumentow!!!\n");
		return 0;
	}
	//sprawdzanie czy jest poteg� 2
        int dlugosc=strlen(tab_arg[liczba_arg-1]);
		int bit=1, ile_j=0;

		//32 bo int ma 32 bity!!
		//p�tla por�wnuje z pot�gami 2
		int i = 0;
		for(i;i<32;i++){
			if(dlugosc==bit){
				ile_j=1;
				break;
			}
			else
			{
				ile_j++;
			}
			bit=bit<<1;
		}
		char *poczatkowy;
		if(ile_j!=1){
			//zmiana d�ugo�ci - poniewa� nie jest pot�g� 2
			poczatkowy = calloc((dlugosc+1)*sizeof(char));
			//kopia parametr�w
			strncpy(poczatkowy,tab_arg[liczba_arg-1],dlugosc);
			//dodanie parametru
			poczatkowy[dlugosc] ='z';
		}
		else{
			//bez zmian
			poczatkowy = calloc((dlugosc)*sizeof(char));
			//kopia parametr�w
			strncpy(poczatkowy,tab_arg[liczba_arg-1],dlugosc);
		}
     
		//warunek zaprzestania dzielenia
 	if((dlugosc) != 1)
	{	
		char *lewy,*prawy;
		//wska�niki na podzielone parametry
		lewy =calloc((strlen(poczatkowy)/2+1),sizeof(char));			
		prawy =calloc((strlen(poczatkowy)/2+1),sizeof(char));
		//przypisanie parametr�w
		memcpy(lewy, tab_arg[1], (strlen(poczatkowy) / 2))
		memcpy(prawy, tab_arg[1] + (strlen(poczatkowy) / 2), (strlen(poczatkowy) / 2));
	
		//utworzenie tablic argument�w dla nowych proces�w + nazwy procesu
		char **nowy = (char**) calloc ((liczba_arg + 2), sizeof(char*));
		int k = 0;
		while (k < liczba_arg) {
			nowy[k] = tab_arg[k];
			k++;
		}
		
		nowy[liczba_arg +1]=NULL;
		//pierwszy proces potomny
		pid_t pid = fork();
		 
		if(pid == 0)
		{			
			nowy[liczba_arg]=lewy;
			
			//wywo�anie tego samego programu z po�ow� argument�w
			execvp("./a.out",nowy);	
			//ko�czenie procesu
           	exit(0);	
		}
	   	 free(lewy);
		//drugi proces potomny
		pid = fork();
		if(pid == 0)
		{			
			nowy[liczba_arg]=prawy;
			//wywo�anie tego samego programu z po�ow� argument�w
			execvp("./a.out",nowy);		
			//ko�czenie procesu
			exit(0);	
			 
                }		
		//zwolnienie wska�nik�w
                free(nowy);
                free(prawy);
    }
free(poczatkowy);	
	 
	//identyfikator procesu potomnego
	pid_t id;
	int licznik = 0;
        
	//czekanie na zako�czenie proces�w
	//2 bo 2 procesy potomne
	//wait zwr�ci identyfikator procesu potomnego
	//je�li ==0 to to jest id procesu g��wnego
	while((id = wait(NULL))>0)
	{
		licznik++;
		if(licznik==2) break;
	}
	
	//pobranie pid procesu g��wnego i wypisanie

    	printf("%d ", getpid());
        
	//wypisanie parametr�w wywo�ania
		int m = 1;
		while (m < liczba_arg) {
			printf("%s ",tab_arg[m]);
			m++;
		}
		printf( "\n");

return 0;
}
