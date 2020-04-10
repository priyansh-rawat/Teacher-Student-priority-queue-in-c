#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


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
			printf("\nTeacher%d will be served.\t",t[t_point]+1);
			printf("Waiting time: %.2f\n",tw[t_point]);
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
			printf("\nStudent%d will be served.\t",s[s_point]+1);
			printf("Waiting time: %.2f\n",sw[s_point]);
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
	char c[2];
	int choice,i,x,check=0,y;
	int z1;
	char buffer[10];	

	sw=(float*)calloc(25,sizeof(float));
	tw=(float*)calloc(25,sizeof(float));
	
	write(1,"WELCOME\n",strlen("WELCOME\n"));
	while(check==0)
	{
		write(1,"Would you like to take input?(y/n) ",strlen("Would you like to take input?(y/n) "));
		z1=read(0,c,sizeof(c));
		while(c[0]=='y')
		{		
			write(1,"Enter the details:\n",strlen("Enter the details:\n"));
			write(1,"Student/Teacher? (0/1) :",strlen("Student/Teacher? (0/1) :"));
			z1=read(0,buffer,sizeof(buffer));
			choice=atoi(buffer);
			switch(choice)
			{
				case 0 :	s_total=ip1(s,s_total);
						write(1,"Enter burst time: ",strlen("Enter burst time: "));
						scanf("%f",&sb[s_total-1]);
						break;

				case 1 : 	t_total=ip1(t,t_total);
						write(1,"Enter burst time: ",strlen("Enter burst time: "));
						scanf("%f",&tb[t_total-1]);
						break;
				default: printf("wrong input\n");	
			}
			write(1,"Would you like to take more input?(y/n) ",strlen("Would you like to take more input?(y/n) "));
			z1=read(0,c,sizeof(c));				
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
			printf("\nTeacher%d will be served.\t",t[t_point]+1);
			printf("Waiting time: %.2f\n",tw[t_point]);
			x=tb[t_point];
			t_point++;
			
			op1(t_point,t_total,tw,x);
			op1(s_point,s_total,sw,x);	
		}
		else if(t_point==t_total && s_point<s_total)
		{
			printf("\nStudent%d will be served.\t",s[s_point]+1);
			printf("Waiting time: %.0f\n",sw[s_point]);
			x=sb[s_point];
			s_point++;
			op1(s_point,s_total,sw,x);
		}
		else
		{
			write(1,"\nmess empty\n",strlen("\nmess empty\n"));	
			check=1;
		}
	}
	free(sw);	
	free(tw);
	return 0;
}