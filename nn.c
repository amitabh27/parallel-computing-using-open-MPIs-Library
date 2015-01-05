#include <stdio.h>
#include<string.h>
#include<stdlib.h>

void main()
{

    int n;
    int i,j,k;
    int th;
    int actual_op=0,insertion_row=0;
FILE *fp;
fp=fopen("/home/jay/jaycprogram/nnio","r");
char ch[10];
fscanf(fp,"%s",ch);
n=atoi(ch);
   // printf("enter the number of elements:\n");
   // scanf("%d",&n);
fscanf(fp,"%s",ch);
th=atoi(ch);

  //  printf("enter the threshold value:");
   // scanf("%d",&th);

    int elements[n];

   // printf("enter the elements:");
    for(i=0;i<n;i++)
    {
     fscanf(fp,"%s",ch);
     elements[i]=atoi(ch);

     //scanf("%d",&elements[i]);
    }

    int distance[n][n];
 
    //printf("enter the distance rowwise:");
    for(i=0;i<n;i++)
    {fscanf(fp,"%s",ch);// neglecting 1st i/p of the row
      for(j=0;j<n;j++)
      {
       fscanf(fp,"%s",ch);
       distance[i][j]=atoi(ch);

	//scanf("%d",&distance[i][j]);
      }
    }

    int clusters[n][n];
 
    for(i=0;i<n;i++)
    {
      for(j=0;j<n;j++)
       {
         clusters[i][j]=0;
       }
    }
/*
clusters is a nXn array keeping in mind that the worst case can be tht each element is in its owm cluster.
fisrt element is issigned to first cluster(i.e first row).
ele_dist is an array tht stores the distances of an element that is to be assigned to a cluster with the elements tht already hv been.
smallest_dist=smallest of ele_dist.
ecount=pointer to elements.
edcount=pointer to ele_dist
*/

     clusters[0][0]=elements[0];
     int c=n;
     int operands[n];
     int op=0;
     int ele_dist[c];
     for(i=0;i<c;i++)
       ele_dist[i]=0;
     int smallest_dist=0;
     int a,b;
     int apos=0;int bpos=0;
     int elem;
     int ecount=1;
     int edcount=0;

     for(ecount=1;ecount<n;ecount++)
     {
       edcount=op=actual_op=smallest_dist=0;
       
       for(i=0;i<n;i++)
       {
         for(j=0;j<n;j++)
	  {
	    a=b=apos=bpos=elem=0;

	    if(clusters[i][j]!=0)
	     {
		a=clusters[i][j];
		b=elements[ecount];

		for(elem=0;elem<n;elem++)
		{
		  if(elements[elem]==a)
  			break;
		  apos++;
		}

		for(elem=0;elem<n;elem++)
		{
		  if(elements[elem]==b)
			break;
		  bpos++;
		}

		ele_dist[edcount]=distance[apos][bpos];
		operands[op]=a;
		op++;
		edcount++;
	      }
           }
         }




         smallest_dist=ele_dist[0];
         actual_op=operands[0];

         //for(i=1;i<ele_dist.length;i++)
         //for(i=1;i<c;i++)
for(i=1;i<c;i++)
         {
	   if(ele_dist[i]<smallest_dist && ele_dist[i]!=0)
	    {
		smallest_dist=ele_dist[i];
		actual_op=operands[i];
	    }
	 }
//System.out.println("***************"+smallest_dist+","+actual_op);

	 if(smallest_dist<=th)
	 {
	   for(i=0;i<n;i++)
	   {
	     for(j=0;j<n;j++)
	     {
		if(clusters[i][j]==actual_op)
		{
		  insertion_row=i;
		   break;
		}
	      }
	    }

	    for(k=0;k<n;k++)
	    {
	      if(clusters[insertion_row][k]==0)
	      {
		clusters[insertion_row][k]=elements[ecount];
		break;
	      }
	     }

	  }

	  else
	  {
	    for(i=1;i<n;i++)
	    {
		j=0;

		if(clusters[i][j]==0)
		 {
		   clusters[i][j]=elements[ecount];
		   break;
		 }
	     }
	   }
	}//elements


        printf("Clusters:");

	for(i=0;i<n;i++)
	{
	  for(j=0;j<n;j++)
	  {
	    if(clusters[i][j]!=0)
		printf("%d %d %d \t",i,j,clusters[i][j]);
	  }

	  printf("\n");
	}
}
