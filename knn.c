#include<stdio.h>
#include<string.h>

struct knnclassify
{
 float height;
 char gender[50];
 char outp[50];
};

void main()
{
int n=0;
int i=0;
int j=0;

 printf("enter the number of elements: ");
 scanf("%d",&n);
 
 printf("enter the tuples \n");
 
 char arr[50];
 struct knnclassify knns[n+1];
 for(i=0;i<n;i++)
 {
  
  scanf("%f",&knns[i].height);  

  scanf("%s",arr);
  strcpy(knns[i].gender,arr);
  
  scanf("%s",arr);
  strcpy(knns[i].outp,arr);
  

 }
 

printf("\nenter the tuple to be classified: \n");

  scanf("%f",&knns[n].height);  

  scanf("%s",arr);
  strcpy(knns[n].gender,arr);
  
int k=0;

 printf("\nenter the value of k: ");
 scanf("%d",&k);


  int index[n];
  
  int pointer;

  
   char temp;

float distance[n];
float diff,d;

  float td_rep[n];

  for(i=0;i<n;i++)
   {  td_rep[i]=knns[i].height;
      printf("%f\n",td_rep[i]);
   }
     
   float tp_rep=knns[n].height;
printf("%f\n",tp_rep);

  for(i=0;i<n;i++)
  {
    diff=td_rep[i]-tp_rep;
 
   if(diff<0)
        diff=0-diff;

   distance[i]=diff;
   index[i]=i;
  }


  for(i=0;i<n;i++)
  {
    for(j=i+1;j<n;j++)
    {
      if(distance[j]<distance[i])
       {
         d=distance[i];
         distance[i]=distance[j];
         distance[j]=d;

         pointer=index[i];
         index[i]=index[j];
	 index[j]=pointer;
       }
    }
   }



  char classes[n];
  for(i=0;i<k;i++)
  {
    pointer=index[i];
    classes[i]=*knns[pointer].outp;
  }


  
  char start_with='\0';
  int z=0;

  int count;
  int count_arr[k];

  char count_class[k];
  int count_arr_p=0;

  for(j=0;j<k;j++)
  {
    count=0;

    for(z=0;z<k;z++)
    {
      if(classes[z]!='*')
      {
        start_with=classes[z];
             break;
      }
    }

    printf("%c		",start_with);

    if(start_with!='*' && start_with!='\0')
    {

      for(i=0;i<k;i++)
      {
  		char jay1[2];
                jay1[0]=start_with;
                jay1[1]='\0';							     //if(start_with.equals(classes[i]))
		char jay2[2];
                jay2[0]=classes[i];
                jay2[1]='\0';								 //if(start_with!=classes[i])
         if(strcmp(jay1,jay2)==0)
         {
	   count++;
	   classes[i]='*';
	 }
      }


     printf("%d\n",count);


     count_arr[count_arr_p]=count;
     count_class[count_arr_p]=start_with;
     start_with='\0';
     ++count_arr_p;
    }

  }//main for loop


//System.out.println();
printf("\n");

 for(i=0;classes[i]!='\0';i++)
   printf("%c	",classes[i]);
printf("\n");
 //System.out.print(classes[i]+"	");
//System.out.println();

 for(i=0;count_arr[i]!=0;i++)
   printf("%d	",count_arr[i]);
printf("\n");
//System.out.print(count_arr[i]+"	   ");
//System.out.println();
 for(i=0;count_class[i]!='\0';i++)
   printf("%c	",count_class[i]);
//System.out.print(count_class[i]+"	   ");


 int temp12=0;
//String temp123;
 char temp123;
 for(i=0;i<count_arr_p;i++)
  {
    for(j=i+1;j<count_arr_p;j++)
     {
       if(count_arr[j]>count_arr[i])
	{
	  temp12=count_arr[i];
   	  count_arr[i]=count_arr[j];
	  count_arr[j]=temp12;

          temp123=count_class[i];
	  count_class[i]=count_class[j];
	  count_class[j]=temp123;
        }
     }
   }

  printf("\nThe input is classified as : %c\n",count_class[0]);








}
