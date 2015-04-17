#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mpi.h>

int* dsent=0;
int calc(int a,int unique[],int n);
int possible(int t,int n,int input[t][n],int spc,int arr1[],int arr2[],int grouping_similar,int k);
int determine(int t,int n,int input[t][n],int spc,int grouping_similar);

int prune(int t1[],int t2[],int k,int n);

void main(int argc,char *argv[])
{

  MPI_Init(&argc,&argv);

  int size,rank;

  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);


  int x,y,z;
  int xy=0;
  int pr=0;

  double start,finish;
  double actual_timing=0;

  int n=0,t=0,i,j;

  FILE *fp;
  char ch[10];
  fp=fopen("aprioriionew.txt","r");
 
  fscanf(fp,"%s",ch);
  n=atoi(ch);

  fscanf(fp,"%s",ch); 
  t=atoi(ch);


  //printf("enter the number of items: ");
  //////////////scanf("%d",&n);


  //printf("enter the number of transactions: ");
  /////////////scanf("%d",&t);

  int input[t][n];
  dsent=malloc(sizeof(int) * n);

  //printf("enter the input data:\n");

  int eachnode=t/size;

  start=MPI_Wtime();
  if(rank==0)
  {
    for(i=0;i<t;i++)
    {
       for(j=0;j<n;j++)
       {
         fscanf(fp,"%s",ch);
         input[i][j]=atoi(ch);
         ////////////scanf("%d",&input[i][j]);
       }
    }
  }
  MPI_Bcast(input,t*n,MPI_INT,0,MPI_COMM_WORLD);

  int spc=0;

  fscanf(fp,"%s",ch);
  spc=atoi(ch);

  //printf("enter the minimum support count:\n");
  ///////////scanf("%d",&spc);

  //int azx=(n*n-n)/2;

//  double start,finish;
//  double actual_timing=0;

  int azx=2000;
  struct frequent
  {
    int row[azx][n];
    int count[azx];
  };
  struct frequent fq[1];

  int duplic[azx][n];

  int azxnode=azx/size;
  int azx_count=0;
/*
  start=MPI_Wtime();
  for(i=rank*azxnode;azx_count<azxnode;i++,azx_count++)
  {
     for(j=0;j<n;j++)
     {
       fq[0].row[i][j]=0;
       duplic[i][j]=0;
     }
  }
  MPI_Gather(&fq[0].row,azxnode*n,MPI_INT,&fq[0].row,azxnode*n,MPI_INT,0,MPI_COMM_WORLD);
  finish=MPI_Wtime();
  actual_timing=finish-start;*/
  /////////////////////////////////////////////////////////////////////////

  int c=0;

  int r=0;
  int k=1;
  int unique[n];
  /*
  for(j=0;j<n;j++)
  {
    unique[j]=0;
    dsent[j]=0;
  }
  */


  ////////////////////can be parallelized
  if(rank==0)
  {
    for(i=0;i<t;i++)
    {
      for(j=0;j<n;j++)
      {
        if(calc(input[i][j],unique,n)==1)
        {
          unique[c]=input[i][j];
          c++;
        }
      }
    }
  }
  MPI_Bcast(unique,n,MPI_INT,0,MPI_COMM_WORLD);


  //uniques hv been calculated.
  ////////////////////////////////////////////////////////////////////////////

  //c=0;
  int ct=0;
  int tk=0;
  int pointer_unique=0;
  int ctnodes;

  int extra=t%size;

  //////////////////////////////can be parallelized

  int en_count;
  
  //start=MPI_Wtime();

  finish=MPI_Wtime();
  actual_timing=actual_timing+finish-start;  

  
  while(pointer_unique<n)
  { 
    //if(pointer_unique>0)
      start=MPI_Wtime();
    //printf("\nstart time is %f \n",start);
    en_count=0;
    for(i=rank*eachnode,ctnodes=0;en_count<eachnode;i++,en_count++)
    {
      for(j=0;j<n;j++)
      {
        if(unique[pointer_unique]==input[i][j])
	   ctnodes++;
      } 
    }
    if(extra!=0 && rank==0)
    {
      for(i=eachnode*size;i<t;i++)
         for(j=0;j<n;j++)
         {
           if(unique[pointer_unique]==input[i][j])
	      ctnodes++;
         } 
    }
    //MPI_Barrier(MPI_COMM_WORLD);
    MPI_Allreduce(&ctnodes,&ct,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    //  MPI_Gather(&ctnodes,1,MPI_INT,&ct,1,MPI_INT,0,MPI_COMM_WORLD);
    //finish=MPI_Wtime();
    //actual_timing=actual_timing+finish-start;
    /*
      for(i=0;i<t;i++)
      {
        for(j=0;j<n;j++)
        {
          if(unique[pointer_unique]==input[i][j])
	      ct++;
        } 
      }*/ 
      if(ct >= spc)
      {
        fq[0].row[tk][0]=unique[pointer_unique];
        fq[0].count[tk]=ct;
        tk++;
      }

    ct=0;
    pointer_unique++;
    finish=MPI_Wtime();
    actual_timing=actual_timing+finish-start;

  }



  if(rank==0)
  {

    printf("1-frequent itemset :\n");
    for(i=0;i<n && fq[0].row[i][0]!=0;i++)
    {
      printf("%d ",fq[0].row[i][0]);
      printf("  %d \n",fq[0].count[i]);
    }

  }


//1-frequent itemset has been calculated.
/////////////////////////////////////////////////////////////////////////////
  struct kfrequent
  {
    int krow[azx][n];
    int kcount[azx];
  };
  struct kfrequent kfq[1];

/*
  for(i=0;i<azx;i++)
    for(j=0;j<n;j++)
        kfq[0].krow[i][j]=0;

for(i=0;i<azx;i++)
kfq[0].kcount[i]=0;
*/


  int zero_not_found=0;

  ct=0;
  int flag=1;
  int grouping_similar=0;

  int a,b;
  int d=0;

  int arr1[n];
  int arr2[n];

  int t1[n];
  int t2[n];
/*
for(i=0;i<n;i++)
{
arr1[i]=arr2[i]=0;
t1[i]=t2[i]=0;
}*/
////////////////////////////////////////////////////////////////////////////
				//GAME BEGINS HERE

  int game_ends=0;
  int ge=0;
  int twodone=1;

  while(game_ends==0)
  {
    zero_not_found=0;

//calulating the k of n-C-k;k=zero_not_found
    for(i=0;i<1;i++)
    {
      for(j=0;j<n;j++)
      {
        if(fq[0].row[i][j]==0)
            break;

        zero_not_found++;
      }
    }


    grouping_similar=zero_not_found-1;
    //printf("\nj has value %d zero not found = %d \n",j,zero_not_found);


    //calculating 2-frequent itemsets.
    if(grouping_similar==0 && twodone==1)
    {
      start=MPI_Wtime();

      //all possible combinations generated,counts are determined,pruning is done.
      for(i=0;i<(azx-1);i++)
      {
        for(j=i+1;j<azx;j++)
        {
          a=fq[0].row[i][0];
          b=fq[0].row[j][0];
          if(a!=0 && b!=0)
          {
	    dsent[0]=a;
	    dsent[1]=b;
	  //  d=determine(t,n,input,spc,grouping_similar);

            //printf("\ngrouping=%d\n",grouping_similar);

  	    int i1;
	    int dspc=0;
	    int dspc1=0;
	    int j1,k1;
	    int gs=grouping_similar+2;
	    int gc_copy=0;
	    en_count=0;

	    for(i1=rank*eachnode;en_count<eachnode;i1++,en_count++)
	    {
	       for(j1=0;j1<n;j1++)
	        {
		
		  for(k1=0;k1<gs;k1++)
		   {	
			if(dsent[k1]==input[i1][j1] && dsent[k1]!=0)
			{
			gc_copy++;
			}

		   }
			
	        }
        
	      if(gc_copy==gs)
	       {
	         dspc1++;
	       }
	       gc_copy=0;
	    }

            MPI_Barrier(MPI_COMM_WORLD);
            MPI_Allreduce(&dspc1,&dspc,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);


            if(dspc>=spc)
	    {
	        //printf("%d ",dspc);
		//return dspc;
		kfq[0].krow[r][0]=a;
		kfq[0].krow[r][1]=b;
		kfq[0].kcount[r]=dspc;
		r++;
	    }


	/*	if(d>0)
		{
		
		kfq[0].krow[r][0]=a;
		kfq[0].krow[r][1]=b;
		kfq[0].kcount[r]=d;
		r++;
		
		}*/
	 }
      }
    }

    if(rank==0)
    {
      finish=MPI_Wtime(); 
      actual_timing=actual_timing+finish-start;
      printf("\nparallelization time period is %f \n",actual_timing);
    }

    k=2;

    if(rank==0)
    {

      //print stuff for 2-frequent itemset.
      if(kfq[0].krow[0][0] !=0)
           printf("%d-frequent itemset :\n",k);
      for(i=0;i<r;i++)
      {
         for(j=0;j<n  && kfq[0].krow[i][j]!=0;j++)
         {
           printf("%d ",kfq[0].krow[i][j]);
         }
         if(kfq[0].kcount[i]!=0)
             printf("  %d \n",kfq[0].kcount[i]);
      }

    }

//exchange of contents of structures.
azx_count=0;
    for(i=rank*azxnode;azx_count<azxnode;azx_count++,i++)//0;i<azx;i++)
      {start=MPI_Wtime();
         fq[0].count[azx_count]=kfq[0].kcount[i];

         for(j=0;j<n;j++)
           fq[0].row[azx_count][j]=kfq[0].krow[i][j];
      }

    MPI_Allgather(kfq[0].krow,azxnode*n,MPI_INT,fq[0].row,azxnode*n,MPI_INT,MPI_COMM_WORLD);
    MPI_Allgather(kfq[0].kcount,azxnode,MPI_INT,fq[0].count,azxnode,MPI_INT,MPI_COMM_WORLD);
/*
    for(i=0;i<azx;i++)
        fq[0].count[i]=kfq[0].kcount[i];*/

//Kfq copied into fq and Kfq is initialised with 0.
    for(i=0;i<azx;i++)
        for(j=0;j<n;j++)
            kfq[0].krow[i][j]=0;

    for(i=0;i<azx;i++)
        kfq[0].kcount[i]=0;

    twodone=0;
    
    finish=MPI_Wtime();
    actual_timing=actual_timing+finish-start;    

  }

//////////////////////////////////////////////////////////////////////////////
//calculating n-frequent itemsets.


  if(grouping_similar>=1)
  {

    k++;
    r=0;

    for(i=0;i<(azx-1);i++)
     {

	for(y=0;y<n && fq[0].row[i][y]!=0;y++)
	   arr1[y]=fq[0].row[i][y];

	for(j=i+1;j<azx;j++)
	{
		for(x=0;x<n && fq[0].row[j][x]!=0;x++)
	  	   arr2[x]=fq[0].row[j][x];
		
		xy=possible(t,n,input,spc,arr1,arr2,grouping_similar,k);

		if(xy==1)
		{	
			
//			d=determine(t,n,input,spc,grouping_similar);

                    
	  	    int i1;
		    int dspc=0;
		    int dspc1=0;
		    int j1,k1;
		    int gs=grouping_similar+2;
		    int gc_copy=0;
		    en_count=0;
		    
		    start=MPI_Wtime();		

		    for(i1=rank*eachnode;en_count<eachnode;i1++,en_count++)
		    {
		       for(j1=0;j1<n;j1++)
		        {
			
			  for(k1=0;k1<gs;k1++)
			   {	
				if(dsent[k1]==input[i1][j1] && dsent[k1]!=0)
				{
				gc_copy++;
				}

			   }
				
		        }
        
		      if(gc_copy==gs)
		       {
		         dspc1++;
		       }
		       gc_copy=0;
		    }

	            MPI_Barrier(MPI_COMM_WORLD);
	            MPI_Allreduce(&dspc1,&dspc,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);


	            if(dspc>=spc)
		    {
		        //printf("%d ",dspc);
			//return dspc;
			//kfq[0].krow[r][0]=a;
			//kfq[0].krow[r][1]=b;
			//kfq[0].kcount[r]=d;
			//r++;
			for(z=0;z<n && dsent[z]!=0;z++)
			  {
			     kfq[0].krow[r][z]=dsent[z];
			  }
			kfq[0].kcount[r]=dspc;
			r++;
			dspc=0;	
		    }

			/*if(d>0)
			{	
				
				for(z=0;z<n && dsent[z]!=0;z++)
				{
				//printf("%d  ",dsent[z]);
				kfq[0].krow[r][z]=dsent[z];
				}
				//printf("-->%d \n",r);
				kfq[0].kcount[r]=d;
				r++;
				//printf("%d ---------*-----------",r);
				d=0;				
			}*/
		 xy=0;
                 
		finish=MPI_Wtime();
		actual_timing=actual_timing+finish-start;

		}

	        for(c=0;c<n;c++)
		    arr2[c]=0;
		
	  }

          for(c=0;c<n;c++)
	     arr1[c]=0;
      }

//getting rid of tuples like a-b-c & c-a-b(say).



      int t1[n];				
      int t2[n];
      int dec=0;
				
/*      for(i=0;i<n;i++)
          t1[i]=t2[i]=0;*/

      for(i=0;i<(azx-1);i++)
      {

	for(y=0;y<n && kfq[0].krow[i][y]!=0;y++)
	    t1[y]=kfq[0].krow[i][y];

	for(j=i+1;j<azx;j++)
	  {
	     for(x=0;x<n && kfq[0].krow[j][x]!=0;x++)
		 t2[x]=kfq[0].krow[j][x];

	     if(t1[0]!=0 && t2[0]!=0)					
	         dec=prune(t1,t2,k,n);

             if(dec==1)
	      {
		 for(x=0;x<n;x++)
		     kfq[0].krow[j][x]=0;
					
		 kfq[0].kcount[j]=0;
	      }
	
	      dec=0;
	      for(x=0;x<n;x++)
		t2[x]=0;
	  }

				
        for(x=0;x<n;x++)
	   t1[x]=0;

      }
//pruning closed



      if(rank==0)
      {

	///////////////////////////////////////////////////////////////////////////
	//print stuff for k-frequent itemset.
        printf("%d-frequent itemset :\n",k);
        for(i=0;i<azx;i++)
        {
	   for(j=0;j<n && kfq[0].krow[i][j]!=0;j++)
	   {
		printf("%d ",kfq[0].krow[i][j]);
	   }
	   if(kfq[0].kcount[i]!=0)
		printf("    %d \n",kfq[0].kcount[i]);
	}


      }

//exchange of contents of structures.
      for(i=0;i<azx;i++)
	for(j=0;j<n;j++)
	    fq[0].row[i][j]=kfq[0].krow[i][j];

      for(i=0;i<azx;i++)
   	 fq[0].count[i]=kfq[0].kcount[i];
 
//Kfq copied into fq and Kfq is initialised with 0.
      for(i=0;i<azx;i++)
	for(j=0;j<n;j++)
	    kfq[0].krow[i][j]=0;

      for(i=0;i<azx;i++)
	  kfq[0].kcount[i]=0;

   }



//checking whether the game needs to be ended now.


   if(fq[0].row[0][0]==0)
   {
      game_ends=1;
      if(rank==0)
  	printf("No more frequent itemsets to display.\n");

      break;
   }


 }


 if(rank==0)
 {
   printf("\nTotal time of parallelized portion is %f \n",actual_timing);
 }
//end of while.


//return 0;

MPI_Finalize();
}





int calc(int a,int unique[],int n)
{
int i;

for(i=0;i<n;i++)
{
if(unique[i]==a)
return 0;
}
return 1;
}


int determine(int t,int n,int input[t][n],int spc,int grouping_similar)
{
int i;
int dspc=0;
int j,k;
int gs=grouping_similar+2;
int gc_copy=gs;


	for(i=0;i<t;i++)
	{
   	  for(j=0;j<n;j++)
	  {
		
		for(k=0;k<gs;k++)
		{	
			if(dsent[k]==input[i][j] && dsent[k]!=0)
			{
			gc_copy--;
			}

		}
			
	  }
	  if(gc_copy==0)
	  {
	    dspc++;
	  }
	  gc_copy=gs;
	}

if(dspc>=spc)
{
//printf("%d ",dspc);
return dspc;
}

return 0;




}

int possible(int t,int n,int input[t][n],int spc,int arr1[],int arr2[],int grouping_similar,int k)
{
int i,j;

int x,y,z;

for(i=0;i<n;i++)
dsent[i]=0;
int similar_count=k-2;

int a,b;

//finding the n(A intersection B) and if it matches the required value return 1.
for(i=0;i<(k-1) && arr1[i]!=0;i++)
{
a=arr1[i];
for(j=0;j<(k-1) && arr2[j]!=0;j++)
{
b=arr2[j];
if(a==b)
similar_count--;
}}

if(similar_count==0)
{

for(i=0;i<(k-1);i++)
dsent[i]=arr1[i];

int f=0;
for(j=0;j<(k-1);j++)
{
	for(i=0;i<(k-1);i++)
	if(arr2[j]==dsent[i])
	f=1;

	if(f==0)
	{
	dsent[i]=arr2[j];
	break;
	}
f=0;
}
//itemset has been generated and it is in dsent.


return 1;

}
//if closed



return 0;

}





int prune(int t1[],int t2[],int k,int n)
{
int count=k;

int i,j;

for(i=0;i<n;i++)
{

	for(j=0;j<n;j++)
	{
	if(t1[i]==t2[j] && t1[i]!=0 && t2[j]!=0)
	{
	count--;
	//printf("%d   %d\n",t1[i],t2[j]);
	}
	}
}



if(count==0)
{
return 1;
}
return 0;

}


