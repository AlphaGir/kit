#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct location
{
        char *pre;
        char *root;
        char *http_proxy;
        char *index;
}location,*loc;
typedef struct server
{
        int listen;
        char *server_name;
        loc* l ;
        int count;//location数量
}server,*ser;

char *include;
char *default_type;
ser *s;
int count;//server数量
loc *lo;
void getparamterinit(int length)
{
     s=(ser*)malloc(sizeof(ser)*length);
     ser s1=(ser)malloc(sizeof(ser));
     
}
int main()
{
    /*s=(ser*)malloc(sizeof(ser)*10);
    ser s1=(ser)malloc(sizeof(ser));
    int j=10;
    int i;

    s1->listen=80;
    s[0]=s1;
    
    s1->l=(loc*)malloc(sizeof(loc)*10);
    loc l1=(loc)malloc(sizeof(loc));
    l1->pre=(char*)malloc(sizeof(char)*25);
    l1->root=(char*)malloc(sizeof(char)*25);
    l1->http_proxy=(char*)malloc(sizeof(char)*25);
    l1->index=(char*)malloc(sizeof(char)*25);
    s1->l[0]=l1;
    strcpy(l1->pre,"ssss");
    strcpy(l1->http_proxy,"dddd");
    strcpy(l1->index,"ddeee");
    */
    char *ss=(char*)malloc(sizeof(char)*10);
    if(ss==NULL)
    printf("%s",ss);
    else
	    printf("not null\n");
}
