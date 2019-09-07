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
int token;
char ch;
int linenum;
int pos;//
int i;
int fd;
char buf[1024];
void getch()
{
	ch=getc(fd);
}
void init()
{
   token=0;
}
enum e_tkcode 
{
	TK_BEGIN,               // { 左大括号
        TK_END,                 // } 右大括号
        TK_SEMICOLON,           // ; 分号
	TK_EQ,                      // == 等于号
        TK_EOF,                 // 文件结束符

	KW_HTTP,         //关键字
	KW_SERVER,
	KW_LOCATION,
	KW_INCLUDE,
	KW_DEFAULT_TYPE,
	KW_LISTEN,
	KW_SERVER_NAME,
	KW_PRE,
	KW_ROOT,
	KW_HTTP_PROXY,
	KW_INDEX,
	KW_STR,

	  /* 常量 */
        TK_CINT,            // 整型常量
        TK_CSTR,            // 字符串常量

	
}
void resolve(char *path)//词法分析
{
	i++;
	if((fd==open(path,O_RDONLY))==-1)
		perror("open");
         getch();
	 do
	 {
            preprocess();

	 }while(token!=TK_EOF);
}
void error(char *s)
{
	printf("the %d line apperances %s\n",linenum,s);
	exit(1);
}
void get_tocken()
{
   switch(ch)
   {
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
    case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
    case 'o': case 'p': case 'q': case 'r': case 's': case 't':
    case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
    case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
    case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T':
    case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
    case '_':
	    parse_string();
 	    break;
    case '0': case '1': case '2': case '3':
    case '4': case '5': case '6': case '7':
    case '8': case '9':
                parse_num();
                token = TK_CINT;
                break;
    case '=':
                token = TK_EQ;
                getch();
		break;
    case '}':
                token = TK_END;
                getch();
                break;
    case '{':
                token = TK_BEGIN;
                getch();
                break;
    case '\"'://为米还能\"
                {
                        parse_string(ch);
                        token = TK_CSTR;
            break;
                }

    case EOF:
                token = TK_EOF;
                break;
    default:
                error("unkown character");

}
void parse_string()
{

}

void preprocess()//预处理 处理注释 换行 制表符
{
        if(ch==' '||ch=='\n'||ch=='\t'||ch=='#')
	{
		if(ch=='#')
		{
			while(ch!='\n')
			{
				getch();
			}
			if(ch=='\n')
			{
			getch();
			linenum++;
			}
		}
		else if(ch=='\n')
		{
			getch();
			linenum++;
		}
		else
			getch();
	}
	getch();

}

int main()
{
}
