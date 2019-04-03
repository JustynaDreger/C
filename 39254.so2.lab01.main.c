//SO2 IS1 221B LAB01
//Justyna Dreger
//dj39254@zut.edu.pl

#include<stdio.h>
#include<utmp.h>
#include<unistd.h>
#include<stdlib.h>
#include<pwd.h>
#include<grp.h>
//ile argumentów ,  tablica rgumentów
int main(int ile_arg, char **tab_arg){

//flagi do przełączników : p1=przełącznik 1	p2=przełącznik 2
int p1=0,p2=0,ret;

//ustawianie flag
while ((ret=getopt(ile_arg,tab_arg,"ab"))!=-1)
	switch (ret){
	case 'a': p1=1; break;
	case 'b':p2=1;break;
}

struct utmp *str;
str=getutent();

struct passwd *str1;

str1=getpwnam(str->ut_user);

struct group *gr;
gid_t *b;
int n=0;
if (p1==1) {
	if(p2==1) {
////p1=1 p2=1
	while(str!=NULL){
		
		if(str->ut_type==7){
			n=0;
			str1=getpwnam(str->ut_user);
			
			getgrouplist(str->ut_user,str1->pw_gid,b,&n);
			
			b=malloc(sizeof(*b)*(n));
			getgrouplist(str->ut_user,str1->pw_gid,b,&n);

		//wyświetla loginy, hosty, grupy
			printf("%s	",str->ut_user);
			
			printf("(%s)	[",str->ut_host);//wyswietla hosty
		int i=0;
		
		for(i=0;i<n;i++){	
			gr=getgrgid(b[i]);
			printf("%s ",gr->gr_name);		
		}
		free(b);
		printf("]\n");
		}
		str=getutent();
		
		}
	}
	else{
	//p1=1 p2=0 - wyświetla loginy i hosty - zrobione
		while(str!=NULL){
		if(str->ut_type==7){
			printf("%s	",str->ut_user);
			printf("(%s)	\n",str->ut_host);
		}
		str=getutent();
		
		}
	}
}
else{
	if(p2==1) {
//p1=0 p2=1	wyświetla login i grupy
	while(str!=NULL){
		
		if(str->ut_type==7){
			n=0;
			str1=getpwnam(str->ut_user);
			
			getgrouplist(str->ut_user,str1->pw_gid,b,&n);
			
			b=malloc(sizeof(*b)*(n));
			getgrouplist(str->ut_user,str1->pw_gid,b,&n);

		//wyświetla loginy, grupy
			printf("%s	[",str->ut_user);
		int i=0;
		
		for(i=0;i<n;i++){	
			gr=getgrgid(b[i]);
			printf("%s ",gr->gr_name);		
		}
		free(b);
		printf("]\n");
		}
		str=getutent();
		
		}
	}
	else{
//p1=0 p2=0	wyświetla sam login - zrobione

	while(str!=NULL){
		if(str->ut_type==7){
			printf("%s	\n",str->ut_user);
		}
		str=getutent();
		}
	}
}

	return 0;
}
