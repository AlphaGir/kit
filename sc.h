enum e_TockenCode
{
	//运算符以及分隔符
	TK_SEMICOLON,//;
	TK_EQ,// =
	TK_EOF,//文件结束符
	TK_BEGIN,//{
	TK_END,//}
        TK_COMMAND,//注释#
	//常量
        TK_CSTR,//字符串常量
	//关键字
	KW_HTTP,//http
	KW_INCLUDE,//include
	KW_DEFAULT_TYPE,//
	KW_SERVER,
	KW_LOCATION,
	KW_PRE,
	KW_ROOT,
	KW_HTTP_PROXY,
	KW_INDEX
};
typedef struct Dynstring
{
	int count;
	int capacity;
	char *data;
}Dynstring;

void dynstring_init(dynstring *pstr,int initsize)
{
	if(pstr!=NULL)
	{
		pstr->data=(char *)malloc(sizeof(char)*initsize);
		pstr->count=0;
		pstr->capacity=initsize;
	}
}
void dynstring_free(Dynstring *pstr)
{
	if(pstr!=NULL)
	{
		if(pstr->data)
			free(pstr->data);
		pstr->count=0;
		pstr->capacity=0;
	}
}
void dynstring_reset(Dynstring *pstr)
{
	dynstring_free(pstr);
	dystring_init(pstr,8);
}
void dynstring_realloc(Dynstring *pstr,int new_size)
{
	int capacity;
	char data;
	capacity=pstr->capacity;
	while(capacity<new_size)
		capacity=capacity*2;
	data=realloc(pstr->data,capacity);
	if(!data)
		perror("内存分配失败");
	pstr->capacity=capacity;
	pstr->data=data;
}
void dynstring_chacat(Dynstring *pstr,int ch)
{
	int count;
	count=pstr->count+1;
	if(count>pstr->capacity)
		dynstring_realloc(pstr,count);
	((char*)pstr->data)[count-1]=ch;
	pstr->count=count;
}
typedef struct DynArray
{
	int count;
	int capacity;
	void **data;
}Dynarray;
typedef sturct Tkword
{
	int tkcode;//单词编码
        struct Tkword *next;//指向哈希冲突的同义词
	char *spelling;//单词字符串
	struct Symbol *sym_struct;//指向单词所示的结构定义
	struct Symbol *sym_identifier;//指向单词所示的标识符
}Tkword;
#define MAXKEY 1024;
Tkword *tk_hashtable[MAXKEY];
Dynarray tktable;

void dynarray_realloc(Dynarray *parr,int new_size)
{
	int capacity;
	void *data;
	capacity=parr->capacity;
	while(capacity<new_size)
		capacity=capacity*2;
	data=realloc(parr->data,capacity);
	if(!data)
		parr->capacity=capacity;
	        parr->data=data;
}
void dynarray_add(Dynarray *parr,void *data)
{
	int count;
	count=parr->count+1;
	if(count*sizeof(void*) > parr->capacity)
		dynarray_realloc(parr,count*sizeof(void*));//sbwy 没有泛型 模板
	parr->data[count-1]=data;
	parr->count=count;
}
void dynarray_init(Dynarray *parr,int initsize)
{
	if(parr!=NULL)
	{
		parr->data=(void**)malloc(sizeof(char)*initsize);
		parr->count=0;
		parr->capacity=initsize;
	}
}
void dynarray_free(Dynarray *parr)
{
	void **p;
	for(p=parr->data;parr->count;++p;--parr->count)
		if(*p)
			free(*p);
	free(parr->data);
	parr->data=NULL;
}
int dynarray_search(Dynarray *parr,int key)
{
	int i;
	int **p;
	p=(int **)parr->data;
	for(i=0;i<parr->count;++i,p++)
		if(key==*p)
			return i;
		return -1;
}
int elf_hash(char *key)
{
        int h=0,g;
	while(*key)
	{
		h=(h<<4)+*key++;
		g=h&0xf0000000;
		if(g)
			h^=g>>24;
		h&=~g;
	}
	return h%MAXKEY;
}
TkWord *tkword_direct_insert(Tkword *tp)
{
	int keyno;
	dynarray_add(&tktable,tp);
	keyno=elf_hash(tp->spelling);
	tp->next=tk_hashtable[keyno];
	tk_hashtable[keyno]=tp;
	return tp;
}
Tkword *tkword_find(char *p,int keyno)
{
	Tkword *tp=NULL,*tp1;
	for(tp1=tk_hashtable[keyno];tp1;tp1=tp1->next)
	{
		if(!strcmp(p,tp1->spelling))
		{
			token=tp1->tkcode;
			tp=tp1;
		}
	}
	return tp;
}
Tkword *tkword_insert(char *p)
{
	Tkword *tp;
	int keyno;
	char *s;
	char *end;
	int length;
	keyno=elf_hash(p);
	tp=tkword_find(p,keyno);
	if(tp==NULL)
	{
		length=strlen(p);
		tp=(Tkword*)mallocz(sizeof(Tkword)+length+1);
		tp->next=tk_hashtable(keyno);
		tk_hashtable[keyno]=tp;
		dynarray_add(&tktable,tp);
		tp->tkcode=tltable.count-1;
		s=(char *)tp+sizoef(Tkword);
		tp->spelling=(char*)s;
		for(end=p+length;p<end;)
		{
			*s++=*p++;
		}
		*s=(char)'\0';
	}
	return tp;
}void *mallocz(int size)
{
	void *ptr;
	ptr=malloc(size);
	if(!ptr&&size)
	perror("内存分配失败");
	memset(ptr,0,size);
	return ptr;
}

void int_lex()
{
   Tkword *tp;
   static Tkword keyword[]={
	   {TK_EQ,NULL,"=",NULL,NULL},
	   {TK_BEGIN,NULL,"{",NULL,NULL},
	   {TK_END,NULL,"}",NULL,NULL},
	   {TK_SEMICOLON,NULL,";",NULL,NULL},
	   {TK_COMMAND,NULL,"#",NULL,NULL},
	   {TK_EOF,NULL,"END_OF_File",NULL,NULL},
	   {TK_CSTR,NULL,"字符串常量",NULL,NULL},
	   {KW_HTTP,NULL,"http",NULL,NULL},
	   {KW_INCLUDE,NULL,"include",NULL,NULL},
           {KW_DEFAULT_TYPE,NULL,"default_type",NULL,NULL},
           {KW_SERVER,NULL,"server",NULL,NULL},
           {KW_LOCATION,NULL,"location",NULL,NULL},
           {KW_PRE,NULL,"pre",NULL,NULL},
           {KW_ROOT,NULL,"root",NULL,NULL},
           {KW_HTTP_PROXY,NULL,"http_proxy",NULL,NULL},
           {KW_INDEX,NULL,"index",NULL,NULL}
   };
   dynarray_init(&tktable,8);
   for(tp=&keywords[0];tp->spelling!=NULL;tp++)
	   tkword_direct_insert(tp);
}
              
enum e_ErrorLevel
{
	LEVEL_WARNING,
	LEVEL_ERROR,
};
enum e_WorkStage
{
	STAGE_COMPILE,
	STAGE_LINK,
};
void handle_exception(int stage,int level,char *fmt,va_list ap)
{
	char buf[1024];
	vsprintf(buf,fmt,ap);
	if(stage==STAGE_COMPILE)
	{
		if(level==LEVEL_WARNING)
			printf("%s(第%d行):编译警告:%s!\n",filename,line_num,buf);
		else
		{
			printf("%s(第%d行):编译错误:%s!\n",filename,line_num,buf);
			exit(-1);
		}
	}
	else
	{
		printf("链接错误:%s!\n",buf);
		exit(-1);
	}
}


