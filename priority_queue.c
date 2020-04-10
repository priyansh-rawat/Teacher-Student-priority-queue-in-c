#include<stdio.h>
#include<stdlib.h>

int ip1(int a[],int total)
{
	a[total]=total;
	total++;	
	return total;
}

void op1(int point,int total,float a[], int x)
{
	int i;
	for(i=point;i<total;i++)
	{
		a[i]=a[i]+x;
	}
}

int priority_t(int t_point,int t_total,float tw[],float tb[],int t[],int s_point,int s_total,float sw[])
{
	int i,x,count=0;
	for(i=t_point;i<t_total;i++)
	{
		if((int)tw[t_point]>100)
		{
			printf("Teacher%d will be served.\t",t[t_point]+1);
			printf("Waiting time: %f\n",tw[t_point]);
			x=tb[t_point];
			t_point++;
		
			op1(t_point,t_total,tw,x);
			op1(s_point,s_total,sw,x);	
			count++;
		}
		else break;
	}
	return count;
}
	
int priority_s(int t_point,int t_total,float tw[],int s_point,int s_total,float sw[],int s[],float sb[])
{	
	int i,x,count=0;
	for(i=s_point;i<s_total;i++)
	{
		if((int)sw[s_point]>100)
		{
			printf("Student%d will be served.\t",s[s_point]+1);
			printf("Waiting time: %f\n",sw[s_point]);
			x=sb[s_point];
			s_point++;
			op1(t_point,t_total,tw,x);
			op1(s_point,s_total,sw,x);	
			count++;
		}
		else break;
	}
	return count;
}

int main()
{
	int s[25],t[25];
	float sb[25],tb[25],*sw,*tw;	
	int s_total=0,t_total=0,s_point=0,t_point=0;
	char c;
	int choice,i,x,check=0,y;
	
	sw=(float*)calloc(25,sizeof(float));
	tw=(float*)calloc(25,sizeof(float));
	
	printf("WELCOME\n");
	while(check==0)
	{
		printf("Would you like to take input?(y/n) ");
		scanf("%s",&c);
		while(c=='y')
		{
			printf("Enter the details:\n"); 
			printf("Student/Teacher? (0/1) :");
			scanf("%d",&choice);
			switch(choice)
			{
				case 0 :	s_total=ip1(s,s_total);
							printf("Enter burst time: ");
							scanf("%f",&sb[s_total-1]);
							break;
							
				case 1 : 	t_total=ip1(t,t_total);
							printf("Enter burst time");
							scanf("%f",&tb[t_total-1]);
							break;		
						
				default: printf("wrong input\n");	
			}
			printf("would you like to take more inputs:(y/n) ");
			scanf("%s",&c);			
		}
		
		if(t_point<t_total)
		{
			if((int)tw[t_point]>100)
			{
				y=priority_t(t_point,t_total,tw,tb,t,s_point,s_total,sw);	
				t_point=t_point+y;
			}
		}
		if(s_point<s_total)
		{
			if((int)sw[s_point]>100)
			{
				y=priority_s(t_point,t_total,tw,s_point,s_total,sw,s,sb);	
				s_point=s_point+y;
			}
		}
		
		if(t_point<t_total)	
		{
			printf("Teacher%d will be served.\t",t[t_point]+1);
			printf("Waiting time: %f\n",tw[t_point]);
			x=tb[t_point];
			t_point++;
			
			op1(t_point,t_total,tw,x);
			op1(s_point,s_total,sw,x);	
		}
		else if(t_point==t_total && s_point<s_total)
		{
			printf("Student%d will be served.\t",s[s_point]+1);
			printf("Waiting time: %f\n",sw[s_point]);
			x=sb[s_point];
			s_point++;
			op1(s_point,s_total,sw,x);
		}
		else
		{
			printf("\nmess empty\n");
			check=1;
		}
		c='y';	
	}

	free(sw);	
	free(tw);
return 0;
}
