// huffman编码
#include <stdio.h>
#include <malloc.h>

#define MAXWEIGHT  1000

typedef struct
{
	int weight;
	int parent;
	int lchild;
	int rchild;
	int vale;
}HNodeType;   /* hfm节点结构体 */

/*
实现功能：
	构造Huffman树。
*/
void CreateHuffmanTree(HNodeType *pNodeArr, int n)
{
	// 初始化
	int i, j;
	for(i=0; i<2*n-1; i++)
	{
		pNodeArr[i].weight = 0;
		pNodeArr[i].parent = -1;
		pNodeArr[i].lchild = -1;
		pNodeArr[i].rchild = -1;
		pNodeArr[i].vale = i;
	}
	
	printf("Input n hNode weights(MAXWEIGHT=1000):");
	for(i=0; i<n; i++)
	{
		scanf("%d", &pNodeArr[i].weight);
	}
	
	int m1, m2;
	int pos1, pos2;
	// 循环构造hfm树
	for (i=0; i<n; i++)
	{
		m1 = m2 = MAXWEIGHT;
		pos1 = pos2 = 0;
		// 找出权值最小，且无父节点的两个节点
		for (j=0; j<n+i; j++)
		{
			if(pNodeArr[j].weight < m1 && pNodeArr[j].parent == -1)
			{
				m2 = m1;
				pos2 = pos1;
				m1 = pNodeArr[j].weight;
				pos1 = j;
			}
			else if(pNodeArr[j].weight < m2 && pNodeArr[j].parent == -1)
			{
				m2 = pNodeArr[j].weight;
				pos2 = j;
			}
		}
		// 合并pos1, pos2两个节点
		pNodeArr[pos1].parent = n+i;
		pNodeArr[pos2].parent = n+i;
		pNodeArr[n+i].weight = pNodeArr[pos1].weight + pNodeArr[pos2].weight;
		pNodeArr[n+i].lchild = pos1;
		pNodeArr[n+i].rchild = pos2;
	}
}

// 前序遍历 hfm树
void printTree(HNodeType *pNodeArr, int pos)
{
	if (pos < 0)
		return;
	printf("%d, %d;\n", pos, pNodeArr[pos].weight);
	printTree(pNodeArr, pNodeArr[pos].lchild);
	printTree(pNodeArr, pNodeArr[pos].rchild);
}

int main()
{
	int n;
	printf("Input the hfm node numbers: ");
	scanf("%d", &n);
	int num = 2*n - 1; // hfm树总的节点数num = 叶子节点n*2 - 1
	// 分配内存空间
	HNodeType *pNodeArr = (HNodeType*)malloc(num*sizeof(HNodeType));
	if(pNodeArr==0)
	{
		printf("out of memory,press any key to quit...\n");
		exit(0);
	}
	CreateHuffmanTree(pNodeArr, n);

	printTree(pNodeArr, num-1);
}

/*
Input the hfm node numbers: 7
Input n hNode weights:5 8 12 25 30 33 40
12, 153;
10, 63;
4, 30;
5, 33;
11, 90;
6, 40;
9, 50;
3, 25;
8, 25;
2, 12;
7, 13;
0, 5;
1, 8;

--------------------------------
Process exited after 12.33 seconds with return value 4294967295
*/

