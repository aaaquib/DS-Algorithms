// MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
}Node;

void FrontBackSplit(Node* source, Node **frontRef, Node **backRef)
{
	if(source == NULL || source->next == NULL)
	{
		*frontRef = source;
		*backRef = NULL;
		return;
	}

	Node *i = source; 
	Node *j = source->next;

	while (j != NULL)
	{
		j = j->next;
		if (j != NULL)
		{
			i = i->next;
			j = j->next;
		}
	}
	*frontRef = source;
	*backRef = i->next;
	i->next = NULL;
}

Node* SortedMerge(Node *a,Node *b)
{
	Node *result;
	if (a==NULL)
	{
		return b;
	}
	else if (b==NULL)
	{
		return a;
	}
	
	if (a->data <= b->data)
	{
		result = a;
		result->next = SortedMerge(a->next,b);
	}
	else
	{
		result = b;
		result->next = SortedMerge(a,b->next);
	}

	return result;
}

void MergeSort(Node** headRef)
{
	Node* head = *headRef;
	Node *a,*b;

	if (head == NULL || head->next == NULL)
	{
		return;
	}

	FrontBackSplit(head,&a,&b);

	MergeSort(&a);
	MergeSort(&b);

	*headRef = SortedMerge(a,b);
}

/* Function to print nodes in a given linked list */
void printList(struct node *node)
{
  while(node!=NULL)
  {
   printf("%d ", node->data);
   node = node->next;
  }
}
 
/* Function to insert a node at the beginging of the linked list */
void push(struct node** head_ref, int new_data)
{
  /* allocate node */
  struct node* new_node =
            (struct node*) malloc(sizeof(struct node));
  
  /* put in the data  */
  new_node->data  = new_data;
  
  /* link the old list off the new node */
  new_node->next = (*head_ref);    
  
  /* move the head to point to the new node */
  (*head_ref)    = new_node;
} 

int _tmain(int argc, _TCHAR* argv[])
{
	Node* head = NULL;
	int i = 0;
	while (i<100)
	{
		push(&head,i);
		i++;
	}
	printList(head);
	printf("\n\n");
	MergeSort(&head);

	printList(head);

	i = getchar();

	return 0;
}

