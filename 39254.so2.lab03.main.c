//SO2 IS1 221B LAB03
//Justyna Dreger
//dj39254@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


//ile argumentów podano, tablica podanych argumentów
int main(int liczba_arg,char **tab_arg)
{
	if(liczba_arg<2)
	{
		printf("Nie ma wystarczajavej liczby argumentow!!!\n");
		return 0;
	}
	//sprawdzanie czy jest poteg¹ 2
        int dlugosc=strlen(tab_arg[liczba_arg-1]);
		int bit=1, ile_j=0;

		//32 bo int ma 32 bity!!
		//pêtla porównuje z potêgami 2
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
			//zmiana d³ugoœci - poniewa¿ nie jest potêg¹ 2
			poczatkowy = calloc((dlugosc+1)*sizeof(char));
			//kopia parametrów
			strncpy(poczatkowy,tab_arg[liczba_arg-1],dlugosc);
			//dodanie parametru
			poczatkowy[dlugosc] ='z';
		}
		else{
			//bez zmian
			poczatkowy = calloc((dlugosc)*sizeof(char));
			//kopia parametrów
			strncpy(poczatkowy,tab_arg[liczba_arg-1],dlugosc);
		}
     
		//warunek zaprzestania dzielenia
 	if((dlugosc) != 1)
	{	
		char *lewy,*prawy;
		//wskaŸniki na podzielone parametry
		lewy =calloc((strlen(poczatkowy)/2+1),sizeof(char));			
		prawy =calloc((strlen(poczatkowy)/2+1),sizeof(char));
		//przypisanie parametrów
		memcpy(lewy, tab_arg[1], (strlen(poczatkowy) / 2))
		memcpy(prawy, tab_arg[1] + (strlen(poczatkowy) / 2), (strlen(poczatkowy) / 2));
	
		//utworzenie tablic argumentów dla nowych procesów + nazwy procesu
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
			
			//wywo³anie tego samego programu z po³ow¹ argumentów
			execvp("./a.out",nowy);	
			//koñczenie procesu
           	exit(0);	
		}
	   	 free(lewy);
		//drugi proces potomny
		pid = fork();
		if(pid == 0)
		{			
			nowy[liczba_arg]=prawy;
			//wywo³anie tego samego programu z po³ow¹ argumentów
			execvp("./a.out",nowy);		
			//koñczenie procesu
			exit(0);	
			 
                }		
		//zwolnienie wskaŸników
                free(nowy);
                free(prawy);
    }
free(poczatkowy);	
	 
	//identyfikator procesu potomnego
	pid_t id;
	int licznik = 0;
        
	//czekanie na zakoñczenie procesów
	//2 bo 2 procesy potomne
	//wait zwróci identyfikator procesu potomnego
	//jeœli ==0 to to jest id procesu g³ównego
	while((id = wait(NULL))>0)
	{
		licznik++;
		if(licznik==2) break;
	}
	
	//pobranie pid procesu g³ównego i wypisanie

    	printf("%d ", getpid());
        
	//wypisanie parametrów wywo³ania
		int m = 1;
		while (m < liczba_arg) {
			printf("%s ",tab_arg[m]);
			m++;
		}
		printf( "\n");

return 0;
}
