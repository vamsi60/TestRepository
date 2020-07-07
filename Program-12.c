#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

void insertatend(int val);

void display();

struct node *head = NULL;

void main()
{
    int N, val;
    scanf("%d", &N);
    
    for(int i=0; i<N; i++)
    {
        scanf("%d", &val);
        insertatend(val);
    }
    display();
}

void insertatend(int val)
{
    struct node *tmp = (struct node*)malloc(sizeof(struct node));
    tmp->data = val;
    tmp->next = NULL;
    
    if(head == NULL)
        head = tmp;
    else
    {
        struct node* cur = head;
        while(cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = tmp;
    }
}

void display()
{
    struct node *cur = head;
    while(cur != NULL)
    {
        printf("%d->", cur->data);
        cur = cur->next;
    }
    printf("\n");
}