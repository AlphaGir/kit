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

int main()
{
    s=(ser*)malloc(sizeof(ser*));
    ser s1=(ser)malloc(sizeof(ser));
    int j=10;
    int i;
    for(i=0;i<j;i++)
    {
    scanf("%d",&(s1->listen));
    s[i]=s1;
   // s1=(ser)malloc(sizeof(ser));
 //   s1->server_name=(char*)malloc(20);
    }
   /* loc l1=(loc)malloc(sizeof(loc));
    s1->l=(loc*)malloc(sizeof(loc*));
    s1->l[0]=l1;
    strcpy("/sss/",l1->pre);
    strcpy("ddddd",l1->http_proxy);
    strcpy("/ss/d/",l1->index);
    */
    for(i=0;i<j;i++)
    printf("%d ",s[i]->listen);
}
