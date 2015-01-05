//#include "mpi.h"
#include <stdio.h>

void main()
{

int n,c,i,j;
FILE *fp;
fp=fopen("/home/jay/jaycprogram/census","r");

char testing[255];
fgets(testing,255,(FILE*)fp);
n=atoi(testing);

printf("The number of terms are : %d\n",n);


int a[n];

printf("\nThe terms are : ");
for(i=0;i<n;i++)
{
  fgets(testing,255,(FILE*)fp);
a[i]=atoi(testing);
printf("%d ",a[i]);

}

fgets(testing,255,(FILE*)fp);
c=atoi(testing);

printf("\nThe no.of clusters(k) are : %d ",c);



int flag=1;

double m[c];
double m1[c];
double ok[c][n];

int k[c][n];
int count[c];

printf("\nInitially assigning first term to mean : ");
int p=0;
int abc=0;

do
{
  for(i=0;i<c;i++)
	{
	 count[i]=0;
	 
	 for(j=0;j<n;j++)
    		ok[i][j]=k[i][j];
 	}

    for(i=0;i<c;i++)
       for(j=0;j<n;j++)
          k[i][j]=0;
    
    if(p==0)
    {
	for(i=0;i<c;i++)
          {m[i]=a[i];m1[i]=a[i];}

 	for(i=0;i<c;i++)
    		printf("m[%d]= %f",i,m[i]);

        p++;
    }

    else
    {
	for(i=0;i<n;i++)
	 {
		int min=0;

		for(j=1;j<c;j++)
               {
			double jay1,jay2;
			if(m[min]<a[i])
			  jay1=(double)(a[i]-m[min]);
			else
			  jay1=(double)(m[min]-a[i]);
			if(m[j]<a[i])
 			  jay2=(double)(a[i]-m[j]);
			else
			 jay2=(double)(m[j]-a[i]);
			if(jay1>jay2)
				min=j;


		}
		int temp=count[min]++;
		
		k[min][temp]=a[i];
	}

	for(i=0;i<c;i++)
	{
		double avg=0;

		for(j=0;j<n;j++)
		    avg+=k[i][j];

		avg=avg/count[i];
		m[i]=avg;
	}

	printf("\n");
	
	for(i=0;i<c;i++)
	{

	     printf("k[%d]=",i);

		for(j=0;j<count[i];j++)
    			printf("%d\t",k[i][j]);

		printf("\n");
	}

	printf("\n");

	int s=0;

	for(i=0;i<c;i++)
    		printf("M[%d]= %f\t",i,m[i]);

	flag=0;

	for(i=0,abc=0;i<c;i++,abc++)
	{
	  if(m[i]!=m1[i])
           {
             for(j=0;j<c;j++)
                m1[j]=m[j];
             break;
           }
		/*for(j=0;j<n;j++)
                  
			if(ok[i][j]!=k[i][j])
			{
				flag=1;
				break;
			}*/
	}
       if(abc!=c)
         flag=1;
    }

}while(flag==1);


   printf("\nANSWER :\n");

   for(i=0;i<c;i++)
   {
	printf("k[%d]= ",i);
	
	for(j=0;j<count[i];j++)
    		printf("%d\t",k[i][j]);

	printf("\n");
   }
}
