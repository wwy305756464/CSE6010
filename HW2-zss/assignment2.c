#include "assignment2.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) < (b)) ? (b) : (a))

LLQueue* LLQ_create(){
	LLQueue* prehead = (LLQueue*)malloc(sizeof(LLQueue));
	if(prehead == NULL){
		return NULL;
	}
	prehead->value = -100;
	prehead->next = NULL;
	return prehead;
}

int LLQ_insert(LLQueue *LLQ, double data){
	if(LLQ == NULL){
		return -100;
	}
	LLQueue *pre = LLQ;
	LLQueue *node = (LLQueue*)malloc(sizeof(LLQueue));
	node->value = data;
	while(pre){
		pre = pre->next;
	}
	// pre->next = node;
	// node->next = NULL;
	node->next = pre->next;
	pre->next = node;
	return 0;
}

double LLQ_delete(LLQueue *LLQ){
	if(LLQ == NULL || LLQ->next == NULL){
		return 0;
	}
	LLQueue *head = LLQ->next;
	double res = head->value;
	LLQ->next = head->next;
	free(head);
	return res;	
}

double* LLQ_Search(LLQueue *LLQ, double data){
	if(LLQ == NULL || LLQ->next == NULL){
		return NULL;
	}
	LLQueue* head = LLQ->next;
	while(head){
		if(head->value == data){
			return head;
		}
		head = head->next;
	}
	return NULL;
}

double LLQ_minimum(LLQueue *LLQ){
	if(LLQ == NULL || LLQ->next == NULL){
		return -100;
	}
	LLQueue *head = LLQ->next;
	double resmin = 100;
	while(head){
		resmin = min(resmin, head->value);
		head = head->next;
	}
	return resmin;
}

double LLQ_maximum(LLQueue *LLQ){
	if(LLQ == NULL || LLQ->next == NULL){
		return -100;
	}
	LLQueue *head = LLQ->next;
	double resmax = -99;
	while(head){
		resmax = max(resmax, head->value);
		head = head->next;
	}
	return resmax;
}

unsigned int LLQ_count(LLQueue *LLQ){
	if(LLQ == NULL || LLQ->next == NULL){
		return 0;
	}
	LLQueue *head = LLQ->next;
	int cnt = 0;
	while(head){
		++cnt;
		head = head->next;
	}
	return cnt;
}

void LLQ_print(LLQueue *LLQ){
	if(LLQ == NULL || LLQ->next == NULL){
		return;
	}
	LLQueue *head = LLQ->next;
	while(head){
		printf("%s\n", head->value);
		head = head->next;
	}
	return;
}

void LLQ_free(LLQueue *LLQ){
	if(LLQ == NULL || LLQ->next == NULL){
		return;
	}
	LLQueue *head = LLQ->next;
	LLQ->next = NULL;
	free(LLQ);
	LLQueue *p;
	while(head->next){
		p = head->next;
		head->next = p->next;
		free(p);
	}
	free(head);
}



