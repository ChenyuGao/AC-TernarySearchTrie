#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "time.h"

#define maxq 1000000
#define max_pattern 100
#define maxp_num 2000000

typedef struct 
{
	char P[max_pattern];
	int length;
}Pattern, *Pa;

Pa Patterns[maxp_num];

//ternarySearchTrie三叉树的结构
typedef struct TSNode 
{
	char data;                      //节点存储的字节数据
	struct TSNode* lchild, *rchild; //同级节点TSNode 
	struct TSNode* next;            //下一节点 
	struct TSNode* faillink;        //失效链接
	int ID;                         //状态id
} TSNode, *TSTree;


//AC自动机结构
typedef struct 
{
	TSTree root;          //三叉树根节点 
	long startPoint, strNum, currentPoint;   //文件位置起始点，搜索串长度 ,目前串位置 
	int pNum;             //模式串个数 
	char* searchStr;      //搜索串序列 
	TSTree currentNode;   //当前搜索到的节点
} AC_STRUCT;


//为AC自动机分配内存
AC_STRUCT *ac_alloc();              
//为AC自动机添加模式串
int ac_add_string(AC_STRUCT *node, char *P, int M, int id);   
//对trie树添加faillink，完成outputlink，实现自动机。出现错误返回0，否则返回1
int ac_implement(AC_STRUCT* node);  
//搜索之前对AC自动机初始化
void search_init(AC_STRUCT* node, long strNum, char* S);
//AC搜索
int ac_search(AC_STRUCT* node);



/****************************************************************************************************/
//队列结构
typedef struct
{
	TSTree queue[maxq];
	int head, tail;
} Queue;
//队列初始化 
Queue* que_init();
//入队，成功返回1，否则返回0 
int enqueue(Queue* q, TSTree node);
//出队操作 
TSTree dequeue(Queue* q);
//判空操作 
int empty(Queue* q);
//半角转为全角
//void half_to_full(char *sHalfStr, char *sFullStr);
//输出文件
void printResult(AC_STRUCT* node);

//先序遍历，做调试用
void preorder(TSTree node);