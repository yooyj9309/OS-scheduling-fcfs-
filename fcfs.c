#include <stdio.h>
#include <stdlib.h>

struct NODE
{
   struct NODE *next;
   int pid;
   int priority;
   int arrival;
   int burst;
}*head = NULL,*temp = NULL;

void scheduling(struct NODE*,int,int,int,int);
void output(struct NODE*,struct NODE*,FILE*);

int main()
{
   FILE *fp,*pp=NULL;// reading file , writing file
   int pd;
   int pri;
   int arr;
   int bur;
   printf("sdfdfdfs000f");/////////////////////////////////////////////////////////
   fp = fopen("input.txt","r");// read tree1.txt file
   if(fp == NULL)// error test
   {
      printf("File read error!");
      exit(1);
   }
   head = (struct NODE*)malloc(sizeof(struct NODE));
   head->next = NULL;

   while(fscanf(fp,"%d %d %d %d",&pd,&pri,&arr,&bur) != EOF)
   {
      scheduling(head,pd,pri,arr,bur);
   }
   temp = head;
   output(head,temp,pp);
}

void scheduling(struct NODE *head,int pd,int pri,int arr,int bur)
{
   struct NODE *now = head->next;// current node
   struct NODE *pre = head;// previos node
   struct NODE *node;// new node

   while(now)
   {
      if(now->arrival > arr)
         break;
      pre = now;
      now = now->next;
   }
   node = (struct NODE*)malloc(sizeof(struct NODE));
   node->pid = pd;
   node->priority = pri;
   node->arrival = arr;
   node->burst =  bur;

   pre->next = node;
   node->next = now;
}
void output(struct NODE *head,struct NODE *temp,FILE *pp)
{   
   int i,time=0;
   int resp=0,turn=0,wait=0,idle=0;

   pp = fopen("output.txt","w");
   if(pp == NULL)// error test
   {
      printf("File read error!");
      exit(1);
   }

   fprintf(pp,"scheduling : FCFS\n==============================================\n");
   while(head->next != NULL)
   {
      for(i=1;i<=head->next->burst;i++)
      {
         if(head->next->arrival > time)
         {
            printf("<time %d> --- system is idle ---\n",time);
            time++;
            idle++;
         }
		 if(temp->next!=NULL){
         if(temp->next->arrival == time)
         {
            printf("<time %d> [new arrival] process %d\n",time,temp->next->pid);
            temp=temp->next;
         }
		 }
         if(head->next->arrival <= time)
         {
            printf("<time %d> process %d is running\n",time,head->next->pid);
            time++;
         }

         if(i == head->next->burst)
         {
            if(head->next->next == NULL)
               printf("<time %d> All processes are finished!\n",time);
            else
               printf("<time %d> process %d is finished\n---------------------------(context - switch)\n",time,head->next->pid);
         }
      }
      head->next = head->next->next;
   }
}