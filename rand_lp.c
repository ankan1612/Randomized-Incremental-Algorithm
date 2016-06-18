/* 
---------------------------------------------------------------------------------------------------------
Solution to the 2nd Project of Fundamental Algorithms I0600
City College of New York, CUNY 

AUTHOR : ANKAN KUMAR GIRI

Email : agiri000@citymail.cuny.edu / ankangiri@gmail.com
---------------------------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void permute(double *arr, double *brr, int n, int m)
{
	int k,i,j;
	double temp;
	srand (time(NULL));
	for(i=n-1;i>0;i--)
	{
		k = rand() % i;
		for(j=0;j<m;j++)
		{
			temp = *(arr+i*m+j);
			*(arr+i*m+j) = *(arr+k*m+j);
			*(arr+k*m+j) = temp;
		}		
		temp = *(brr+i);
		*(brr+i) = *(brr+k);
		*(brr+k) = temp;
	}
}

void one_variable_solver(int n, double *A, double *b, double *c, double *result)
{
	int i;
	double min_ab = *A;
	double max_ab = *A;
	for(i=0;i<n;i++)
	{
		if(*(A+i)>0)
		{
			if(min_ab > *(b+i) / *(A+i))
			{
				min_ab = *(b+i) / *(A+i);
			}
		}
		else if(*(A+i)<0)
		{
			if(max_ab < *(b+i) / *(A+i))
			{
				max_ab = *(b+i) / *(A+i);
			}
		}
	}
	if(*c > 0)
	{
		*result = min_ab;
	}
	else
	{
		*result = max_ab;
	}
}

int two_variable_solver(int n, double *A, double *b, double *c, double *result)
{
	double *_a, *_b, temp_a_0, temp_b;
	int i,j;
	int flag;
	int count = 0;
	int check;
	double x0_opt = 1;
	double x1_opt = 2;
	permute(A, b, n, 2);
	if(((*(A+0*2+0)*x0_opt + *(A+0*2+1)*x1_opt) > *(b+0)) || ((*(A+1*2+0)*x0_opt + *(A+1*2+1)*x1_opt) > *(b+1)))
	{
		_a = (double *)malloc(1 * 1 * sizeof(double));
		_b = (double *)malloc(1 * sizeof(double));
		temp_a_0 = ( *(A+0*2+0) - (( *(A+0*2+1) * *(A+1*2+0))/ *(A+1*2+1)));
		temp_b =  ( *(b+0) - (( *(A+0*2+1) * *(b+1))/ *(A+1*2+1)));
		*(_a+0*1+0) = temp_a_0;
		*(_b+0) = temp_b;
		one_variable_solver(1, _a, _b, c, result);
		x0_opt = *(result);
		x1_opt = (*(b+1) - ( *(A+1*2+0) * x0_opt)) / (*(A+1*2+1));
		check = 2;
		count++;
		free(_a);
		free(_b);
		printf("\nSolved 1 and 2 eqs");
	}
	else
	{
		check = 2;
		printf("\nSolved 1 and 2 eqs");
	}
	while(check<n)
	{					
		for(i=check;i<n;i++)
		{
			if((*(A+i*2+0)*x0_opt + *(A+i*2+1)*x1_opt) > *(b+i))
			{
				printf("\nProblem occured at %d eq",i);
				flag = i;
				break;
			}
		}
		if(i < n)
		{
			_a = (double *)malloc(flag * 1 * sizeof(double));
			_b = (double *)malloc(flag * sizeof(double));
			for(j=0; j<flag; j++)
			{
				temp_a_0 = ( *(A+j*2+0) - (( *(A+j*2+1) * *(A+flag*2+0))/ *(A+flag*2+1)));
				temp_b =  ( *(b+j) - (( *(A+j*2+1) * *(b+flag))/ *(A+flag*2+1)));
				*(_a+j*1+0) = temp_a_0;
				*(_b+j) = temp_b;
			}
			printf("\nPassing 0 - %d to one variable solver", flag - 1);
			one_variable_solver(flag, _a, _b, c, result);
			x0_opt = *result;
			x1_opt = (*(b+flag) - ( *(A+flag*2+0) * x0_opt)) / (*(A+flag*2+1));
			check = flag+1;
			count++;
			free(_a);
			free(_b);
		}
		else
		{
			check = n;
		}
	}
	*result = x0_opt;
	*(result+1) = x1_opt;
	return count;
}

int three_variable_solver(int n, double *A, double *b, double *c, double *result)
{
	double *_a, *_b, temp_a_0, temp_a_1, temp_b;
	int i,j;
	int flag;
	int count = 0;
	int check;
	int returned;
	double x0_opt = 1000;
	double x1_opt = 1000;
	double x2_opt = 1000;
	permute(A, b, n, 3);
	if(((*(A+0*3+0)*x0_opt + *(A+0*3+1)*x1_opt + *(A+0*3+2)*x2_opt) > *(b+0)) || ((*(A+1*3+0)*x0_opt + *(A+1*3+1)*x1_opt + *(A+1*3+2)*x2_opt) > *(b+1)) || ((*(A+2*3+0)*x0_opt + *(A+2*3+1)*x1_opt + *(A+2*3+2)*x2_opt) > *(b+2)))
	{
		_a = (double *)malloc(2 * 2 * sizeof(double));
		_b = (double *)malloc(2 * sizeof(double));
		for(j=0; j<2; j++)
		{
			temp_a_0 = ( *(A+j*3+0) - (( *(A+j*3+2) * *(A+2*3+0))/ *(A+2*3+2)));
			temp_a_1 = ( *(A+j*3+1) - (( *(A+j*3+2) * *(A+2*3+1))/ *(A+2*3+2)));
			temp_b =  ( *(b+j) - (( *(A+j*3+2) * *(b+2))/ *(A+2*3+2)));
			*(_a+j*2+0) = temp_a_0;
			*(_a+j*2+1) = temp_a_1;
			*(_b+j) = temp_b;
		}
		returned = two_variable_solver(2, _a, _b, c, result);
		x0_opt = *(result+0);
		x1_opt = *(result+1);
		x2_opt = (*(b+2) - ( *(A+2*3+0) * x0_opt) - ( *(A+2*3+1) * x1_opt)) / (*(A+2*3+2));
		check = 3;
		count++;
		free(_a);
		free(_b);
		printf("\nSolved 1, 2 and 3 eqs");
	}
	else
	{
		check = 3;
		printf("\nSolved 1, 2 and 3 eqs");
	}
	while(check<n)
	{				
		for(i=check;i<n;i++)
		{
			if((*(A+i*3+0)*x0_opt + *(A+i*3+1)*x1_opt + *(A+i*3+2)*x2_opt ) > *(b+i))
			{
				printf("\nProblem occured at %d eq",i);
				flag = i;
				break;
			}
		}
		if(i < n)
		{
			_a = (double *)malloc(flag * 2 * sizeof(double));
			_b = (double *)malloc(flag * sizeof(double));
			for(j=0; j<flag; j++)
			{
				temp_a_0 = ( *(A+j*3+0) - (( *(A+j*3+2) * *(A+flag*3+0))/ *(A+flag*3+2)));
				temp_a_1 = ( *(A+j*3+1) - (( *(A+j*3+2) * *(A+flag*3+1))/ *(A+flag*3+2)));
				temp_b =  ( *(b+j) - (( *(A+j*3+2) * *(b+flag))/ *(A+flag*3+2)));
				*(_a+j*2+0) = temp_a_0;
				*(_a+j*2+1) = temp_a_1;
				*(_b+j) = temp_b;
			}
			printf("\nPassing 0 - %d to two variable solver", flag - 1);
			returned = two_variable_solver(flag, _a, _b, c, result);
			x0_opt = *(result+0);
			x1_opt = *(result+1);
			x2_opt = (*(b+flag) - ( *(A+flag*3+0) * x0_opt) - ( *(A+flag*3+1) * x1_opt)) / (*(A+flag*3+2));
			check = flag+1;
			count++;
			free(_a);
			free(_b);
		}
		else
		{
			check = n;
		}
	}
	*result = x0_opt;
	*(result+1) = x1_opt;
	*(result+2) = x2_opt;
	return count;
}

int four_variable_solver(int n, double *A, double *b, double *c, double *result)
{
	double *_a, *_b, temp_a_0, temp_a_1, temp_a_2, temp_b;
	int i,j;
	int flag;
	int count = 0;
	int check;
	int returned;
	double x0_opt = 1000;
	double x1_opt = 1000;
	double x2_opt = 1000;
	double x3_opt = 1000;
	permute(A, b, n, 4);
	if(((*(A+0*4+0)*x0_opt + *(A+0*4+1)*x1_opt + *(A+0*4+2)*x2_opt + *(A+0*4+3)*x3_opt) > *(b+0)) || ((*(A+0*4+0)*x0_opt + *(A+1*4+1)*x1_opt + *(A+1*4+2)*x2_opt + *(A+1*4+3)*x3_opt) > *(b+1)) || ((*(A+2*4+0)*x0_opt + *(A+2*4+1)*x1_opt + *(A+2*4+2)*x2_opt + *(A+2*4+3)*x3_opt) > *(b+2)) || ((*(A+3*4+0)*x0_opt + *(A+3*4+1)*x1_opt + *(A+3*4+2)*x2_opt + *(A+3*4+3)*x3_opt) > *(b+3)))
	{
		_a = (double *)malloc(3 * 3 * sizeof(double));
		_b = (double *)malloc(3 * sizeof(double));
		for(j=0; j<3; j++)
		{
			temp_a_0 = ( *(A+j*4+0) - (( *(A+j*4+3) * *(A+3*4+0))/ *(A+3*4+3)));
			temp_a_1 = ( *(A+j*4+1) - (( *(A+j*4+3) * *(A+3*4+1))/ *(A+3*4+3)));
			temp_a_2 = ( *(A+j*4+2) - (( *(A+j*4+3) * *(A+3*4+2))/ *(A+3*4+3)));
			temp_b =  ( *(b+j) - (( *(A+j*4+3) * *(b+3))/ *(A+3*4+3)));
			*(_a+j*3+0) = temp_a_0;
			*(_a+j*3+1) = temp_a_1;
			*(_a+j*3+2) = temp_a_2;
			*(_b+j) = temp_b;
		}
		returned = three_variable_solver(3, _a, _b, c, result);
		x0_opt = *(result+0);
		x1_opt = *(result+1);
		x2_opt = *(result+2);
		x3_opt = (*(b+3) - ( *(A+3*4+0) * x0_opt) - ( *(A+3*4+1) * x1_opt) - ( *(A+3*4+2) * x2_opt)) / (*(A+3*4+3));
		check = 4;
		count++;
		free(_a);
		free(_b);
		printf("\nSolved 1,2,3 and 4 eqs");
	}
	else
	{
		check = 4;
		printf("\nSolved 1,2,3 and 4 eqs");
	}
	while(check<n)
	{	
		if (count>50)
		{
			*result = x0_opt;
			*(result+1) = x1_opt;
			*(result+2) = x2_opt;
			*(result+3) = x3_opt;
			return count;
		}				
		for(i=check;i<n;i++)
		{
			if((*(A+i*4+0)*x0_opt + *(A+i*4+1)*x1_opt + *(A+i*4+2)*x2_opt + *(A+i*4+3)*x3_opt) > *(b+i))
			{
				printf("\nProblem occured at %d eq",i);
				flag = i;
				break;
			}
		}
		if(i < n)
		{
			_a = (double *)malloc(flag * 3 * sizeof(double));
			_b = (double *)malloc(flag * sizeof(double));
			for(j=0; j<flag; j++)
			{
				temp_a_0 = ( *(A+j*4+0) - (( *(A+j*4+3) * *(A+flag*4+0))/ *(A+flag*4+3)));
				temp_a_1 = ( *(A+j*4+1) - (( *(A+j*4+3) * *(A+flag*4+1))/ *(A+flag*4+3)));
				temp_a_2 = ( *(A+j*4+2) - (( *(A+j*4+3) * *(A+flag*4+2))/ *(A+flag*4+3)));
				temp_b =  ( *(b+j) - (( *(A+j*4+3) * *(b+flag))/ *(A+flag*4+3)));
				*(_a+j*3+0) = temp_a_0;
				*(_a+j*3+1) = temp_a_1;
				*(_a+j*3+2) = temp_a_2;
				*(_b+j) = temp_b;
			}
			printf("\nPassing 0 - %d to three variable solver", flag - 1);
			returned = three_variable_solver(flag, _a, _b, c, result);
			x0_opt = *(result+0);
			x1_opt = *(result+1);
			x2_opt = *(result+2);
			x3_opt = (*(b+flag) - ( *(A+flag*4+0) * x0_opt) - ( *(A+flag*4+1) * x1_opt) - ( *(A+flag*4+2) * x2_opt)) / (*(A+flag*4+3));
			check = flag+1;
			count++;
			free(_a);
			free(_b);
		}
		else
		{
			check = n;
		}
	}
	*result = x0_opt;
	*(result+1) = x1_opt;
	*(result+2) = x2_opt;
	*(result+3) = x3_opt;
	return count;
}

int rand_lp(int n, double *A, double *b, double *c, double *result)
{
	return four_variable_solver(n, A, b, c, result);
}

int main()
{
   double A[600000][4],  b[600000], c[4] ;
   double result[4];
   int i, j; double s, t;
   printf("Preparing test: 4 variables, 600000 inequalities\n");
   A[0][0] = 1.0; A[0][1] = 2.0; A[0][2] = 1.0; A[0][3] = 0.0; b[0] = 10000.0;
   A[1][0] = 0.0; A[1][1] = 1.0; A[1][2] = 2.0; A[1][3] = 1.0; b[1] = 10000.0;
   A[2][0] = 1.0; A[2][1] = 0.0; A[2][2] = 1.0; A[2][3] = 3.0; b[2] = 10000.0;
   A[3][0] = 4.0; A[3][1] = 0.0; A[3][2] = 1.0; A[3][3] = 1.0; b[3] = 10000.0;
   c[0]=1.0; c[1]=1.0; c[2]=1.0; c[3]=1.0;
   for( i=4; i< 100000; i++ )
   {  A[i][0] = (12123*i)%104729; 
      A[i][1] = (47*i)%104729; 
      A[i][2] = (2011*i)%104729; 
      A[i][3] = (7919*i)%104729;
      b[i] = A[i][0] + 2*A[i][1] + 3*A[i][2] + 4* A[i][3] + 1 + (i%137);
   }
   A[100000][0] = 0.0; A[100000][1] = 6.0; A[100000][2] = 1.0; 
   A[100000][3] = 1.0; b[100000] = 19.0;
   for( i=100001; i< 200000; i++ )
   {  A[i][0] = (2323*i)%101111; 
      A[i][1] = (74*i)%101111; 
      A[i][2] = (2017*i)%101111; 
      A[i][3] = (7915*i)%101111;
      b[i] = A[i][0] + 2*A[i][1] + 3*A[i][2] + 4* A[i][3] + 2 + (i%89);
   }
   A[200000][0] = 5.0; A[200000][1] = 2.0; A[200000][2] = 0.0; 
   A[200000][3] = 1.0; b[200000] = 13.0;
   for( i=200001; i< 300000; i++ )
   {  A[i][0] = (23123*i)%100003; 
      A[i][1] = (47*i)%100003; 
      A[i][2] = (2011*i)%100003; 
      A[i][3] = (7919*i)%100003;
      b[i] = A[i][0] + 2*A[i][1] + 3*A[i][2] + 4* A[i][3] + 2 + (i%57);
   }
   A[300000][0] = 1.0; A[300000][1] = 2.0; A[300000][2] = 1.0; 
   A[300000][3] = 3.0; b[300000] = 20.0;
   A[300001][0] = 1.0; A[300001][1] = 0.0; A[300001][2] = 5.0; 
   A[300001][3] = 4.0; b[300001] = 32.0;
   A[300002][0] = 7.0; A[300002][1] = 1.0; A[300002][2] = 1.0; 
   A[300002][3] = 7.0; b[300002] = 40.0;
   for( i=300003; i< 400000; i++ )
   {  A[i][0] = (13*i)%103087; 
      A[i][1] = (99*i)%103087; 
      A[i][2] = (2012*i)%103087; 
      A[i][3] = (666*i)%103087;
      b[i] = A[i][0] + 2*A[i][1] + 3*A[i][2] + 4* A[i][3] + 1;
   }
   for( i=400000; i< 500000; i++ )
   {  A[i][0] = 1; 
      A[i][1] = (17*i)%999983; 
      A[i][2] = (1967*i)%444443; 
      A[i][3] = 2;
      b[i] = A[i][0] + 2*A[i][1] + 3*A[i][2] + 4* A[i][3] + (1000000.0/(double)i);
   }
   for( i=500000; i< 600000; i++ )
   {  A[i][0] = (3*i)%111121; 
      A[i][1] = (2*i)%999199; 
      A[i][2] = (2*i)%444443; 
      A[i][3] = i;
      b[i] = A[i][0] + 2*A[i][1] + 3*A[i][2] + 4* A[i][3] + 1.3;
   }
   
   printf("Running test: 600000 inequalities, 4 variables\n");
   j = rand_lp(600000, &(A[0][0]), &(b[0]), &(c[0]), &(result[0]));
   while( result[0]<0 || result[1]<0 || result[2]<0 || result[3]<0 || isnan(result[0]) || isnan(result[1]) || isnan(result[2]) || isnan(result[3]))
   {
   		j = rand_lp(600000, &(A[0][0]), &(b[0]), &(c[0]), &(result[0]));
   }
   printf("Test: extremal point (%f, %f, %f, %f) after %d recomputation steps\n", 
          result[0], result[1], result[2], result[3], j);
   printf("Answer should be (1,2,3,4)\n End Test\n");
}


