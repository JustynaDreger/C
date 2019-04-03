//SO2 IS1 221B LAB05
//Justyna Dreger
//dj39254@zut.edu.pl

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
//
//flagi do przelacznikow
int czy_d=0,czy_l=0,czy_f=0;
int l_w=0,g=0;
//liczniki do katalogów i plików
int ile_kat=0,ile_pl=0;
//funkcja do przegladania i wyswietlania zawartosci katalogow
//dep - wciecia
void f(char *str,int dep)
{
	 DIR *str1;
	struct dirent *s;	

	if((str1=opendir(str))==NULL) 
	{
		printf("nie otwarto katalogu!!\n");
		return ;
	}
	if(l_w<g) g=0;
	while((s=readdir(str1))) {    
	//sprawdzenie, czy jest katalogiem i zliczenie
	
	if(s->d_type==DT_DIR){
		//sprawdzenie czy nie jest . lub ..
		if((strcmp(s->d_name,".")==0)||(strcmp(s->d_name,"..")==0)) continue;
		else{
			//wypisanie nazwy
			//f
			if(czy_f==1)		printf("%*s%s%s\n",dep,"",str,s->d_name);
			else 	printf("%*s%s\n",dep,"",s->d_name);
			//rekurencja
			
			char *sciezka=calloc(strlen(str)+strlen(s->d_name)+2,sizeof(char));
			strcat(sciezka,str);
			strcat(sciezka,s->d_name);
			strcat(sciezka,"/");
			if(l_w!=1) {f(sciezka,dep+4);g++;}
			
			free(sciezka);			
		}
		ile_kat++;
	}
	
	//sprawdzenie, czy jest plikiem i zliczenie
		//je¿eli podano d to wywietla tylko katalogi
		//d
		if(czy_d!=1){
			if(s->d_type==DT_REG) {
				ile_pl++;
				if(czy_f==1)		printf("%*s%s%s\n",dep,"",str,s->d_name);
				else 	printf("%*s%s\n",dep,"",s->d_name);
			}
		}
	}
	
	closedir(str1);
	//free(s);
}
int main(int ile_arg,char** tab_arg){
int ret;
char *s=NULL,*opt_L=NULL;
//pobranie argumentów
while ((ret=getopt(ile_arg,tab_arg,"dlfL:"))!=-1)
	switch (ret){
	case 'd':czy_d=1; break;
	case 'l':czy_l=1;break;
	case 'f':czy_f=1;break;
	//liczba poziomów katalogów do których wejdzie
	case 'L':opt_L=optarg;l_w=atol(opt_L);break;
	default:break;
}

if(tab_arg[optind]==NULL){
	s="./";
	printf("%s\n",s);
	f(s,4);
//free(s);
}
else{
//¿eby nie bra³o jako nazwê katalogu prze³¹cznika
	s=calloc(strlen(tab_arg[optind])+3,sizeof(char));
	strcat(s,tab_arg[optind]);
	strcat(s,"/");
	printf("%s\n",s);
        f(s,4);
        free(s);
}

printf("\nLiczba katalogow = %d 	Liczba plikow = %d\n\n",ile_kat,ile_pl);
//free(opt_L);
//free(s);
return 0;
}
