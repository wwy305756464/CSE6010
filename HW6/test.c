#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <time.h>
#include <math.h>
#define Node_number 6
 
typedef struct List    //RingNetwork
{
	int link;    //redge
	struct List *next;     //
}C_List;
 
int k_value = 2;
int Link[Node_number][Node_number];
double C_value[Node_number];
int min_Length[Node_number][Node_number];
 
void Initial(void);
void OutputData(void);
void ReLink(double p);
void Caculate_min_Length(void);
void Caculate_C(void);

int main(void)
{
	//system("color 0A");
	printf("number of nodes is %d(ln(N)=%f)\nvalue of k is %d\n", Node_number, log(Node_number), k_value);
	printf("input value of p:");
	double p_value = 0;
	scanf("%lf", &p_value);
	Initial();

	for (int i = 0; i < Node_number; ++i){
        for(int j = 0; j < Node_number; ++j){
            printf("The value is: %d ", Link[i][j]);
        }
        printf("-----------\n");
    }

	//ReLink(p_value);
	//Caculate_min_Length();
	//Caculate_C();	
	//OutputData();
	return 0;
}

void Initial(void)
{
	for (int j = 0; j < Node_number; j++)
	{
		for (int i = 0; i < Node_number; i++)
			Link[i][j] = Node_number;
		
		for (int temp = -k_value/2; temp <= k_value/2; temp++)
			Link[(j + temp + Node_number)%Node_number][j] = 1;
		
		Link[j][j] = 0;
	}
	for (int i = 0; i < Node_number; i++)
		for (int j = 0; j < Node_number; j++)
			min_Length[i][j] = Link[i][j];

}

void ReLink(double p)
{
	srand((unsigned)time(NULL));
	for (int temp = 1; temp <= k_value/2; temp++)
	{
		for (int i = temp, j = 0; j < Node_number; i++,j++)
		{
			if((double)rand()/RAND_MAX < p)
			{
				int true = 1;
				while(true)
				{
					int temp_row = rand()%Node_number;
					if(Link[temp_row][j] == Node_number)
					{
						Link[temp_row][j] = Link[j][temp_row] = 1;
						true = 0;
					}
				}
				Link[(i+Node_number)%Node_number][j] = Node_number;
				Link[j][(i+Node_number)%Node_number] = Node_number;
			}
		}
	}
	for (int i = 0; i < Node_number; i++)
		for (int j = 0; j < Node_number; j++)
			min_Length[i][j] = Link[i][j];//之前一直忘了
}

void Caculate_min_Length(void)
{
	for (int Order = 0; Order < Node_number; Order++)
	{
		for (int i = 0; i < Node_number; i++)
		{
			for (int j = 0; j < Node_number; j++)
			{
				if (min_Length[i][Order] + min_Length[Order][j] < min_Length[i][j])
					min_Length[i][j] = min_Length[i][Order] + min_Length[Order][j];
			}
		}
	}
}

void Caculate_C(void)
{
	C_List *pHead = (C_List *)malloc(sizeof(C_List));
	pHead->link = -1;
	for (int j = 0; j < Node_number; j++)
	{
		C_List *pNext = pHead;
		C_List *pTail = NULL;
		C_List *pMove = NULL;
		int count = 0;
		for (int i = 0; i < Node_number; i++)
		{
			if (Link[i][j] == 1)
			{
				pTail = (C_List *)malloc(sizeof(C_List));
				pTail->link = i;
				pTail->next = NULL;
				pNext->next = pTail;
				pNext = pTail;
				count++;
			}
		}
		int actual_link = 0;
		pNext = pHead->next;
		while (pNext != NULL)
		{
			pMove = pHead->next;
			while (pMove != NULL)
			{
				if(Link[pNext->link][pMove->link] == 1)
					actual_link++;
				pMove = pMove->next;
			}
			pNext = pNext->next;
		}
		C_value[j] = (double)actual_link/(count*(count-1));
	}
	//内存就让他去吧
}

void OutputData(void)
{
	int sum = 0;
	double	total = 0;
	FILE *fp_link = fopen ("exam_Link.txt", "w");
	FILE *fp_length = fopen ("exam_min_Length.txt", "w");
	FILE *fp_C = fopen("C_value.txt", "w");
	for (int i = 0; i < Node_number; i++)
	{
		for (int j = 0; j < Node_number; j++)
		{
			sum += min_Length[i][j];
			fprintf(fp_link, "%d\t", Link[i][j]);
			fprintf(fp_length, "%d\t", min_Length[i][j]);
		}
		total += C_value[i];
		fprintf(fp_link, "\n");
		fprintf(fp_length, "\n");
		fprintf(fp_C, "%f\n", C_value[i]);
	}
	printf("C:%f\tmin_L:%f", total/Node_number, (double)sum/((Node_number-1)*Node_number));
	fclose(fp_link);
	fclose(fp_length);
	fclose(fp_C);
}