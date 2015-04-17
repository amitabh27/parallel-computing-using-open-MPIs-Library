#include <mpi.h>
#include <stdio.h>

void main(int argc,char *argv[])
{


MPI_Init(&argc,&argv);

int rank,size;
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);




int n,c,i,j;

FILE *fp;
fp=fopen("bigcensus4","r");

char testing[255];
fgets(testing,255,(FILE*)fp);
n=atoi(testing);

if(rank==0)
printf("The number of terms are : %d\n",n);


int a[n];


if(rank==0)
printf("\nThe terms are : ");
for(i=0;i<n;i++)
{
  fgets(testing,255,(FILE*)fp);
a[i]=atoi(testing);

if(rank==0)
printf("%d ",a[i]);

}

fgets(testing,255,(FILE*)fp);
c=atoi(testing);


if(rank==0)
printf("\nThe no.of clusters(k) are : %d ",c);



int flag=1;

double m[c];
double m1[c];
double ok[c][n];

int k[c][n];
int k1[size];
int count[c];
int count1[c];
int count2[c];



if(rank==0)
printf("\nInitially assigning first term to mean : ");

int abc=0;





for(i=0;i<c;i++)
{
  m[i]=a[i];m1[i]=a[i];
  
}


if(rank==0)
 for(i=0;i<c;i++)
    printf("m[%d]= %f",i,m[i]);


int no=n/size;


for(i=0;i<size;i++)
{
   k1[i]=i*n;
}

MPI_Barrier(MPI_COMM_WORLD);


int p=0;


int lk;
int ans[n];
int inc;
int n_ans[n*size];

double start=0,finish=0;




start=MPI_Wtime();



do
{

  for(i=0;i<c;i++)
     for(j=0;j<n;j++)
          k[i][j]=0;
    


  for(inc=0;inc<c;inc++)
   {
      for(i=0;i<n*size;i++)
	  n_ans[i]=0;

      for(i=0;i<n;i++)
          ans[i]=0;


      count1[inc]=0;

      for(i=rank*no,lk=0;(lk<no || rank==size-1) && i<n;i++,lk++)
       {        
          int min=0;

	  for(j=1;j<c;j++)
           {
	      double min1,min2;

	      if(m[min]<a[i])
		  min1=(double)(a[i]-m[min]);
	      else
		  min1=(double)(m[min]-a[i]);

	      if(m[j]<a[i])
 		  min2=(double)(a[i]-m[j]);
	      else
		  min2=(double)(m[j]-a[i]);

	      if(min1>min2)
		  min=j;


	  }

	 if(min==inc)
	  {
	     ans[count1[min]]=a[i];
	     count1[min]++;
	  }


		
      }

//      MPI_Barrier(MPI_COMM_WORLD);

      count2[inc]=n;
      MPI_Barrier(MPI_COMM_WORLD);



      MPI_Gather(ans,count2[inc],MPI_INT,n_ans,count2[inc],MPI_INT,0,MPI_COMM_WORLD);
  
      MPI_Reduce(&count1[inc],&count[inc],1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);



  //    MPI_Barrier(MPI_COMM_WORLD);

      if(rank==0)
       {
	 int min;

	 for(i=0,j=0,min=0;i<count[inc];i++,j++)
	 {
           if(n_ans[j]!=0)
            {
               k[inc][i]=n_ans[j];
               n_ans[j]=0;
            }

           else
            {
               j=n+min;
	       min=j;
               j--;
               i--;
            }
  	 }
	 	
       }
	
      MPI_Barrier(MPI_COMM_WORLD);//FOR SYNCHRONIZTION

   } 


  //MPI_Bcast(k,n*c,MPI_INT,0,MPI_COMM_WORLD); ////Broadcasting all k-means cluster 
//  MPI_Barrier(MPI_COMM_WORLD);




  if(rank==0)
   {       
      for(i=0;i<c;i++)
       {
	 double avg=0;

 	 for(j=0;j<n;j++)
	    avg+=k[i][j];

 	 avg=avg/count[i];
	 m[i]=avg;
       }
   }

   




  MPI_Bcast(m,c,MPI_DOUBLE,0,MPI_COMM_WORLD); ////Broadcasting new mean values
  //MPI_Barrier(MPI_COMM_WORLD);


  /*if(rank==0)
   {
      printf("\n");
	
      for(i=0;i<c;i++)
       {
	 printf("k[%d]=",i);

 	 for(j=0;j<count[i];j++)
    	     printf("%d\t",k[i][j]); /////Printing the members of each cluster

	 printf("\n");
       }
   }
  MPI_Barrier(MPI_COMM_WORLD);

  if(rank==0)
   {
      printf("\n");

      for(i=0;i<c;i++)
    	{
           printf("M[%d]= %f\t",i,m[i]); ////Printing new mean values
        }
   }
*/
  //MPI_Barrier(MPI_COMM_WORLD);

  if(rank==0)
   {
      flag=0;/////flag=0 means final step reached. flag=1 means continue the do-while loop

      for(i=0,abc=0;i<c;i++,abc++)////////// To check if new mean values are same as that in previous step.If false, then continue the process
       {
	  if(m[i]!=m1[i])
           {
             for(j=0;j<c;j++)
                m1[j]=m[j];
             break;
           }
		
       }
 
      if(abc!=c)/////abc=c only when new mean values are equal to those in previous step
         flag=1;
           
   }          

  MPI_Bcast(&flag,1,MPI_INT,0,MPI_COMM_WORLD);/////////BROADCASTING flag value for do-while looping condition    
  MPI_Barrier(MPI_COMM_WORLD);

  p=1;


}while(flag==1);


////////////////DISPLAYING THE FINAL ANSWER////////////

if(rank==0)
{
   printf("\nANSWER :\n");

   for(i=0;i<c;i++)
   {
	printf("k[%d]= ",i);
	
	for(j=0;j<count[i];j++)
    		printf("%d\t",k[i][j]);

	printf("\n");
   }
}

finish=MPI_Wtime();

if(rank==0)
{double timing=finish-start;printf("\nTiming is %f \n",timing);}

MPI_Barrier(MPI_COMM_WORLD);
MPI_Finalize();
}
