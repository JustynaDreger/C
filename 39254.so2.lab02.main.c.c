// SO2 IS1 221B LAB02
//Justyna Dreger
//dj39254@zut.edu.pl

#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<pwd.h>
#include<sys/types.h>
#include<dlfcn.h>
#include<unistd.h>
int main(int ile_arg, char **tab_arg){

int pa=0,pb=0;
char ret;
char *(*grupy)(char * login);
void *handle=dlopen("./liblb2.so",RTLD_LAZY);

while((ret=getopt(ile_arg,tab_arg,"ab"))!=-1)
	switch (ret){
	case 'a': pa=1; break;
	case 'b': pb=1; break;
	}

if(handle==NULL){
	printf("Biblioteka nie załadowana!!\n");
	pa=0;
	pb=0;
}
grupy=dlsym(handle,"grupy");
if(grupy==NULL){
	printf("Nie ma funkcji\n");
	pa=0;
	pb=0;
}
struct utmp *uzytkownik=NULL;
char * lista_gr=NULL;
while((uzytkownik=getutent())!=NULL){
	if(uzytkownik->ut_type==7){
		printf("%s	",uzytkownik->ut_user);
		if(pa==1) printf("(%s)	",uzytkownik->ut_host);
		if(pb==1) {
			lista_gr=grupy(uzytkownik->ut_user);
			printf("%s",lista_gr);
			free(lista_gr);
			}
		printf("\n");
		}
	}
if(handle!=NULL) dlclose(handle);
}
