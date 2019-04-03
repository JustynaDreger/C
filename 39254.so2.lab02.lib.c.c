// SO2 IS1 221B LAB02
//Justyna Dreger
//dj39254@zut.edu.pl

#include<grp.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<pwd.h>
char *grupy(char *login){
int ile_gr=0;
gid_t *gr_id=NULL;
struct group *gr;
struct passwd *uuid=getpwnam(login);
int i=0;
char *lista_gr=malloc(sizeof(char)*2);
lista_gr[0]=0;
getgrouplist(login, uuid->pw_gid,gr_id,&ile_gr);
gr_id=(gid_t*)malloc(sizeof(gid_t)*ile_gr);
getgrouplist(login, uuid->pw_gid,gr_id,&ile_gr);
//skopiowanie znaku do chara
if(1) strcpy(lista_gr,"[");
for(i=0;i<ile_gr;++i){
	gr=getgrgid(gr_id[i]);
	//zmiana rozmiaru chara -> dł. wsk_ch+dł. nazwy nowej grupy
	lista_gr=realloc(lista_gr, strlen(lista_gr)+strlen(gr->gr_name)+3);
	//wstawienie nazwy grupy do chara
	strcat(lista_gr,gr->gr_name);
	strcat(lista_gr," ");
	}
if(1) strcat(lista_gr,"]");
free(gr_id);
return lista_gr;
}
