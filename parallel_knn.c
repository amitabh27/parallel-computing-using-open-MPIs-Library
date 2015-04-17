#include<stdio.h>
#include<string.h>
#include<mpi.h>

struct knnclassify
{
 double height;
 char gender[50];
 char outp[50];
};

void main(int argc,char *argv[])
{

  MPI_Init(&argc,&argv);


  int rank,size;

  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  int n=0;
  int i=0;
  int j=0;

  FILE *fp;
  fp=fopen("inputdata3.txt","r");


  // printf("enter the number of elements: ");
  // scanf("%d",&n);
  char testing[255];
  fscanf(fp,"%s",testing);
  n=atoi(testing);

  if(rank==0)
    printf("\n%d\n",n);



// printf("enter the tuples \n");
  MPI_Barrier(MPI_COMM_WORLD);

  char arr[50];
  struct knnclassify knns[n+1];
  for(i=0;i<n;i++)
  {
  
    fscanf(fp,"%lf",&knns[i].height);
    if(rank==0)
      printf("%lf ",knns[i].height);


  //  scanf("%f",&knns[i].height);  

  //  scanf("%s",arr);
    fscanf(fp,"%s",arr);
    strcpy(knns[i].gender,arr);


    fscanf(fp,"%s",arr);
  //  scanf("%s",arr);
    strcpy(knns[i].outp,arr);
  

  }
 



  //printf("\nenter the tuple to be classified: \n");
  MPI_Barrier(MPI_COMM_WORLD);

  fscanf(fp,"%lf",&knns[n].height);
  if(rank==0)
    printf("\n%s %lf\n",testing,knns[n].height);


  //scanf("%f",&knns[n].height);  

  MPI_Barrier(MPI_COMM_WORLD);

  //scanf("%s",arr);

  fscanf(fp,"%s",arr);
  strcpy(knns[n].gender,arr);
  


  int k=0;
  // printf("\nenter the value of k: ");
  
  fscanf(fp,"%s",arr);
  k=atoi(arr);
 //scanf("%d",&k);


  int index[n];
  
  int pointer;

  
  char temp;

  double distance[n];
  double diff,d;

  double td_rep[n];


  for(i=0;i<n;i++)
   {
      td_rep[i]=knns[i].height;
      if(rank==0)
         printf("%f\n",td_rep[i]);
      index[i]=i;
   }
  MPI_Barrier(MPI_COMM_WORLD);
     
  double tp_rep=knns[n].height;



  if(rank==0)
     printf("%f\n",tp_rep);
  MPI_Barrier(MPI_COMM_WORLD);



  int abc=n/size;
  int def=abc;

  double p_distance[abc];

double start=0,finish=0,timing=0;
//if(rank==0)
start=MPI_Wtime();



  for(i=rank*abc,j=0; (i<n && rank==size-1) || (j<abc); i++,j++)
   {
      diff=td_rep[i]-tp_rep;
 
      if(diff<0)
          diff=0-diff;

      p_distance[j]=diff;
//      printf("\nrank %d has %lf ",rank,p_distance[j]);
   
   }
finish=MPI_Wtime();
 // MPI_Barrier(MPI_COMM_WORLD);
  MPI_Gather(p_distance,abc,MPI_DOUBLE,distance,abc,MPI_DOUBLE,0,MPI_COMM_WORLD);

//if(rank==0)
//     finish=MPI_Wtime();


  if(rank==0)
      timing=timing+finish-start;



  if(rank==0)
   {

     for(i=0;i<n-1;i++)
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

   }
  MPI_Barrier(MPI_COMM_WORLD);

  char classes[n];
  if(rank==0)
   {
     for(i=0;i<k;i++)
      {
        pointer=index[i];
        classes[i]=*knns[pointer].outp;
        //printf("\ndisplaying classes value %s",&classes[i]);
      }
   }
  MPI_Barrier(MPI_COMM_WORLD);

  if(rank==0)
   {
  
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

    // for(i=0;classes[i]!='\0';i++)
      //   printf("%c	",classes[i]);
    // printf("\n");
     //System.out.print(classes[i]+"	");
     //System.out.println();

    // for(i=0;count_arr[i]!=0;i++)
      //   printf("%d	",count_arr[i]);
     //printf("\n");
     //System.out.print(count_arr[i]+"	   ");
     //System.out.println();
 
//     for(i=0;count_class[i]!='\0';i++)
  //       printf("%c	",count_class[i]);
     //System.out.print(count_class[i]+"	   ");


     int temp12=0;
     //String temp123;
     char temp123;
     for(i=0;i<count_arr_p-1;i++)
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

     printf("\nParallelization timing is %lf\n",timing);




   }//root end

MPI_Barrier(MPI_COMM_WORLD);
MPI_Finalize();

}
