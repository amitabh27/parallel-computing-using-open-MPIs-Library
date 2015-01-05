#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// structures declared globally so that they can be accessed in the functions.
/*
collection for taking input
cinfo for storing class names,count and probability
*/
struct collection
{

double att1;
char att2[30];
char att3[30];

char class[30];
};


struct cinfo
{
char cname[30];
double ccount;
double cprob;
};

/*functions calc2=for two attributes(height,gender)
calc3=for 3 attributes(height,gender,credit ratings)
all the attributes must contribute in classification; So name,city cant be entered as input.
*/

void calc2(int a,int n,int no_of_classes,struct collection input[],struct cinfo cfacts[]);
void calc3(int a,int n,int no_of_classes,struct collection input[],struct cinfo cfacts[]);

void main()
{
printf("Bayesian Classification \n");
int a=0,n=0,i=0,j=0,k=0;
printf("enter the number of attributes: \n");
scanf("%d",&a);


printf("enter the number of tuples: \n");
scanf("%d",&n);
struct collection input[n+1];
char tempo[30];
printf("enter the tuples with the tuple to be classified at last\n");

for(i=0;i<(n+1);i++)
{

if(a==2)
{
	if(i==n)
	{
	scanf("%lf",&input[i].att1);
	scanf("%s",tempo);
	strcpy(input[i].att2,tempo);
	}
	else
	{	
	scanf("%lf",&input[i].att1);
	scanf("%s",tempo);
	strcpy(input[i].att2,tempo);
	scanf("%s",tempo);
	strcpy(input[i].class,tempo);
	}	

}
if(a==3)
{

	if(i==n)
	{
	scanf("%lf",&input[i].att1);
	scanf("%s",tempo);
	strcpy(input[i].att2,tempo);
	scanf("%s",tempo);
	strcpy(input[i].att3,tempo);
	}
	else
	{
	scanf("%lf",&input[i].att1);
	scanf("%s",tempo);
	strcpy(input[i].att2,tempo);
	scanf("%s",tempo);
	strcpy(input[i].att3,tempo);
	scanf("%s",tempo);
	strcpy(input[i].class,tempo);
	}	
}

}




struct cinfo cfacts[n];

char temp[30];
double count=0;
k=0;
int pointer_c=0;
int flag=0;

for(j=0;j<n;j++)
{
flag=1;
count=0;

strcpy(temp,input[j].class);
        if(k>=1)
	{
	for(pointer_c=0;pointer_c<k;pointer_c++)
	if(strcmp(temp,cfacts[pointer_c].cname)==0)
	{
	flag=0;
	break;
	}
	}


if(flag==1)
{
	for(i=0;i<n;i++)
	{
	if(strcmp(temp,input[i].class)==0)
	count++;
	}

strcpy(cfacts[k].cname,temp);
cfacts[k].ccount=count;
cfacts[k].cprob=(double)count/n;
k++;
}


}//class names and their probabilities are determined

int no_of_classes=k;

if(a==2)
calc2(a,n,no_of_classes,input,cfacts);
if(a==3)
calc3(a,n,no_of_classes,input,cfacts);
}




void calc2(int a,int n,int no_of_classes,struct collection input[],struct cinfo cfacts[])
{


int i=0,j=0,k=0;
struct ainfo
{
char aname[30];
double acount;
double aprob;
};
struct ainfo afacts[n];

char temp1[30];
double count1=0;
k=0;
int pointer_a1=0;
int flag1=0;

for(j=0;j<n;j++)
{
flag1=1;
count1=0;

strcpy(temp1,input[j].att2);
        if(k>=1)
	{
	for(pointer_a1=0;pointer_a1<k;pointer_a1++)
	if(strcmp(temp1,afacts[pointer_a1].aname)==0)
	{
	flag1=0;
	break;
	}
	}


if(flag1==1)
{
	for(i=0;i<n;i++)
	{
	if(strcmp(temp1,input[i].att2)==0)
	count1++;
	}

strcpy(afacts[k].aname,temp1);
afacts[k].acount=count1;
k++;
}
}



int z=0;
count1=0.0;
int p=0;
printf("\n");

for(i=0;i<k;i++)
{
count1=0;         	   
	for(z=0;z<no_of_classes;z++)
	{       count1=0;
		for(j=0;j<n;j++)
		{
		if(strcmp(input[j].att2,afacts[i].aname)==0 && strcmp(input[j].class,cfacts[z].cname)==0)
		{
		count1++;
		}
		}
	
		afacts[p].aprob=(double)count1/cfacts[z].ccount;
		p++;
	}
}
// 2 nd attribute's distinct values,counts,probs are determined.


//determining the probabilities of distinct values of first attribute.
double hprob[no_of_classes];
double hcount=0.0;
if(input[n].att1 >0 && input[n].att1 <=1.6)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >0 && input[i].att1 <=1.6)&&strcmp(input[i].class,cfacts[j].cname)==0)
	hcount++;
	}
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}
if(input[n].att1 >1.6 && input[n].att1 <=1.7)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >1.6 && input[i].att1 <=1.7)&&strcmp(input[i].class,cfacts[j].cname)==0)
	hcount++;
	}
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}
if(input[n].att1 >1.7 && input[n].att1 <=1.8)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >1.7 && input[i].att1 <=1.8)&&strcmp(input[i].class,cfacts[j].cname)==0)
	hcount++;
	}
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}
if(input[n].att1 >1.8 && input[n].att1 <=1.9)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >1.8 && input[i].att1 <=1.9)&&strcmp(input[i].class,cfacts[j].cname)==0)
	hcount++;
	}
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}
if(input[n].att1 >1.9 && input[n].att1 <=2.0)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >1.9 && input[i].att1 <=2.0)&&strcmp(input[i].class,cfacts[j].cname)==0)
	hcount++;
	}
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}
if(input[n].att1 >2.0 && input[n].att1 <=100.0)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >2.0 && input[i].att1 <=100.0)&&strcmp(input[i].class,cfacts[j].cname)==0)
	hcount++;
	}
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}


double actual_probs[no_of_classes];
double calc=0.0;
int x=0;
for(i=0;i<no_of_classes;i++)
{
x=i;
calc=0.0;
calc=hprob[i]*cfacts[i].cprob;


	for(j=0;j<p;j++)
	{
	if(strcmp(afacts[j].aname,input[n].att2)==0)
	{
	
	calc=calc*afacts[x].aprob;
	break;
	}
	x=x+no_of_classes;
	}
actual_probs[i]=calc;	
}

double t;
char t2[30];
for(i=0;i<no_of_classes;i++)
{
for(j=i+1;j<no_of_classes;j++)
{
if(actual_probs[j]>actual_probs[i])
{
t=actual_probs[i];
actual_probs[i]=actual_probs[j];
actual_probs[j]=t;

strcpy(t2,cfacts[i].cname);
strcpy(cfacts[i].cname,cfacts[j].cname);
strcpy(cfacts[j].cname,t2);
}}}

printf("Tuple is classified into the class :  %s",cfacts[0].cname);


}



void calc3(int a,int n,int no_of_classes,struct collection input[],struct cinfo cfacts[])
{
int i=0,j=0,k=0;
struct ainfo
{
char aname[30];
double acount;
double aprob;
};
struct ainfo afacts[n];

char temp1[30];
double count1=0;
k=0;
int pointer_a1=0;
int flag1=0;

for(j=0;j<n;j++)
{
flag1=1;
count1=0;

strcpy(temp1,input[j].att2);
        if(k>=1)
	{
	for(pointer_a1=0;pointer_a1<k;pointer_a1++)
	if(strcmp(temp1,afacts[pointer_a1].aname)==0)
	{
	flag1=0;
	break;
	}
	}


if(flag1==1)
{
	for(i=0;i<n;i++)
	{
	if(strcmp(temp1,input[i].att2)==0)
	count1++;
	}

strcpy(afacts[k].aname,temp1);
afacts[k].acount=count1;
k++;
}
}



int z=0;
count1=0;
int p=0;
printf("\n");

for(i=0;i<k;i++)
{
count1=0;         	   
	for(z=0;z<no_of_classes;z++)
	{       count1=0;
		for(j=0;j<n;j++)
		{
		if(strcmp(input[j].att2,afacts[i].aname)==0 && strcmp(input[j].class,cfacts[z].cname)==0)
		{
		count1++;
		}
		}
	
		afacts[p].aprob=(double)count1/cfacts[z].ccount;
		p++;
	}
}
// 2 nd attribute's distinct values,counts,probs are determined.
//////////////////////////////////////////////////////////////////////////////
struct a3info
{
char aname[30];
double acount;
double aprob;
};
struct a3info a3facts[n];

char temp3[30];
double count3=0;
k=0;
int pointer_a3=0;
int flag3=0;

for(j=0;j<n;j++)
{
flag3=1;

count3=0;

strcpy(temp3,input[j].att3);
        if(k>=1)
	{
	for(pointer_a3=0;pointer_a3<k;pointer_a3++)
	if(strcmp(temp3,a3facts[pointer_a3].aname)==0)
	{
	flag3=0;
	break;
	}
	}


if(flag3==1)
{
	for(i=0;i<n;i++)
	{
	if(strcmp(temp3,input[i].att3)==0)
	count3++;
	}

strcpy(a3facts[k].aname,temp3);
a3facts[k].acount=count3;
k++;
}
}



z=0;
count3=0;
int p3=0;
printf("\n");

for(i=0;i<k;i++)
{
count3=0;         	   
	for(z=0;z<no_of_classes;z++)
	{       count3=0;
		for(j=0;j<n;j++)
		{
		if(strcmp(input[j].att3,a3facts[i].aname)==0 && strcmp(input[j].class,cfacts[z].cname)==0)
		{
		count3++;
		}
		}
	
		a3facts[p3].aprob=(double)count3/cfacts[z].ccount;
		p3++;
	}
}
// 3 rd attribute's distinct values,counts,probs are determined.
/////////////////////////////////////////////////////////////////////////////






//determining the probabilities of distinct values of first attribute
double hprob[no_of_classes];
double hcount=0.0;
if(input[n].att1 >0 && input[n].att1 <=1.6)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >0 && input[i].att1 <=1.6)&&strcmp(input[i].class,cfacts[j].cname)==0)
	hcount++;
	}
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}
if(input[n].att1 >1.6 && input[n].att1 <=1.7)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >1.6 && input[i].att1 <=1.7)&&(strcmp(input[i].class,cfacts[j].cname)==0))

	hcount++;
	}
	
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}

if(input[n].att1 >1.7 && input[n].att1 <=1.8)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >1.7 && input[i].att1 <=1.8)&&strcmp(input[i].class,cfacts[j].cname)==0)
	hcount++;
	}
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}
if(input[n].att1 >1.8 && input[n].att1 <=1.9)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >1.8 && input[i].att1 <=1.9)&&strcmp(input[i].class,cfacts[j].cname)==0)
	hcount++;
	}
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}
if(input[n].att1 >1.9 && input[n].att1 <=2.0)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >1.9 && input[i].att1 <=2.0)&&strcmp(input[i].class,cfacts[j].cname)==0)
	hcount++;
	}
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}
if(input[n].att1 >2.0 && input[n].att1 <=100.0)
{
	
	for(j=0;j<no_of_classes;j++)
	{hcount=0;
	for(i=0;i<n;i++)
	{
	if((input[i].att1 >2.0 && input[i].att1 <=100.0)&&strcmp(input[i].class,cfacts[j].cname)==0)
	hcount++;
	}
	hprob[j]=(double)hcount/cfacts[j].ccount;
	}
}


for(i=0;i<p3;i++)
printf("%f   ",a3facts[i].aprob);
printf("\n\n");
for(i=0;i<p;i++)
printf("%f   ",afacts[i].aprob);
printf("\n\n");
for(i=0;i<no_of_classes;i++)
printf("%f   ",hprob[i]);
printf("\n\n");
for(i=0;i<no_of_classes;i++)
printf("%f   ",cfacts[i].cprob);
printf("\n\n");



double actual_probs[no_of_classes];
double calc=0.0;
int x=0;
for(i=0;i<no_of_classes;i++)
{
x=i;
calc=0.0;
calc=hprob[i]*cfacts[i].cprob;


	for(j=0;j<p;j++)
	{
	if(strcmp(afacts[j].aname,input[n].att2)==0)
	{
	
	calc=calc*afacts[x].aprob;
	break;
	}
	x=x+no_of_classes;
	}
	x=i;
	for(j=0;j<p3;j++)
	{
	if(strcmp(a3facts[j].aname,input[n].att3)==0)
	{
	
	calc=calc*a3facts[x].aprob;
	break;
	}
	x=x+no_of_classes;
	}
	
actual_probs[i]=calc;	
}



double t;
char t2[30];
for(i=0;i<no_of_classes;i++)
{
for(j=i+1;j<no_of_classes;j++)
{
if(actual_probs[j]>actual_probs[i])
{
t=actual_probs[i];
actual_probs[i]=actual_probs[j];
actual_probs[j]=t;

strcpy(t2,cfacts[i].cname);
strcpy(cfacts[i].cname,cfacts[j].cname);
strcpy(cfacts[j].cname,t2);
}}}

for(i=0;i<no_of_classes;i++)
printf("%f  ",actual_probs[i]);

printf("Tuple is classified into the class :  %s",cfacts[0].cname);


}









