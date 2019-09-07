#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*配置文件解析(词法分析)
 *
 *
 *
 */
typedef struct conf
{
	char *type;
	struct *server;
}conf;
typedef struct server
{
	int listen;
	char *server_name;
	char *reg;
        char *root;
        char *index;
}server;	
int i;
int fd;
char buf[1024];
void resolve(char *path,conf *out)
{
	//int fd;
	i++;
	char c;
	if((fd==open(path,O_RDONLY))==-1)
		perror("open");
        while(read(fd,buf,1))
	{
		if(i==1)
	        {
			if(buf[i]=='h')
			{
				if(http(buf[i]))
				{
				}
				else
					return ;
			}
                        else if(buf[i]=='#')
			{

			}
			else
				printf("line 1 undefined word experinced:\n");
		}
		else

}
int http(char c)
{
	if(read(fd,buf,3))
	{
		i=i+3;
		if(buf[i-1]=='p'&&buf[i-2]=='t'&&buf[i-1]=='t')
		{
			return 1;
		}
		else
			printf("line 1 undefined word\n");
		        return 0;
	}
}


}
void command(char c)
{
       
}
int main()
{

