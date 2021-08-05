/*
	Spring 2021 Algorithm(Prof. Do-Gil Lee) Assignment
	
	Goal: make algorithm that calculate edit distacne (https://en.wikipedia.org/wiki/Edit_distance)
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INSERT_OP      0x01
#define DELETE_OP      0x02
#define SUBSTITUTE_OP  0x04
#define MATCH_OP       0x08
#define TRANSPOSE_OP   0x10

#define INSERT_COST	1
#define DELETE_COST	1
#define SUBSTITUTE_COST	1
#define TRANSPOSE_COST	1


static void backtrace_main( int *op_matrix, int col_size, char *str1, char *str2, int n, int m, int level, char align_str[][8]);
void print_matrix( int *op_matrix, int col_size, char *str1, char *str2, int n, int m);
int min_editdistance( char *str1, char *str2);
static int __GetMin3( int a, int b, int c)
static int __GetMin4( int a, int b, int c, int d)
void print_alignment( char align_str[][8], int level)
void backtrace( int *op_matrix, int col_size, char *str1, char *str2, int n, int m)

////////////////////////////////////////////////////////////////////////////////
static int __GetMin3( int a, int b, int c)
{
	int min = a;
	if (b < min)
		min = b;
	if(c < min)
		min = c;
	return min;
}

////////////////////////////////////////////////////////////////////////////////
static int __GetMin4( int a, int b, int c, int d)
{
	int min = __GetMin3( a, b, c);
	return (min > d) ? d : min;
}

////////////////////////////////////////////////////////////////////////////////
void print_alignment( char align_str[][8], int level)
{
	int i;
	
	for (i = level; i >= 0; i--)
	{
		printf( "%s\n", align_str[i]);
	}
}

////////////////////////////////////////////////////////////////////////////////
// wrapper fucntion that calls backtrace_main
// n : len of str1 
// m : len of str2 
void backtrace( int *op_matrix, int col_size, char *str1, char *str2, int n, int m)
{
	char align_str[n+m][8];
	
	backtrace_main( op_matrix, col_size, str1, str2, n, m, 0, align_str);
}

////////////////////////////////////////////////////////////////////////////////
int main()
{
	char str1[30];
	char str2[30];
	
	int distance;
	
	fprintf( stderr, "INSERT_COST = %d\n", INSERT_COST);
	fprintf( stderr, "DELETE_COST = %d\n", DELETE_COST);
	fprintf( stderr, "SUBSTITUTE_COST = %d\n", SUBSTITUTE_COST);
	fprintf( stderr, "TRANSPOSE_COST = %d\n", TRANSPOSE_COST);
	
	while( fscanf( stdin, "%s\t%s", str1, str2) != EOF)
	{
		printf( "\n==============================\n");
		printf( "%s vs. %s\n", str1, str2);
		printf( "==============================\n");
		
		distance = min_editdistance( str1, str2);
		
		printf("\nMinEdit(%s, %s) = %d\n", str1, str2, distance);
	}
	return 0;
}

// print op_matrix (Bottom Left(1,1) -> Top Right(n,m)) 
//  I: INSERT, D: DELETE, S: SUBSTITUTE, M: MATCH, T: TRANSPOSE
void print_matrix(int *op_matrix, int col_size, char *str1, char *str2, int n, int m)
{
	for(int i=0; i<n; i++) //row
	{
		printf("%c\t", str1[n-i-1]);
		for(int j=1; j<col_size; j++) //col
		{
			if((op_matrix[i*col_size+j] | SUBSTITUTE_OP) == op_matrix[i*col_size+j])
			{
				printf("S");
			}
			if((op_matrix[i*col_size+j] | MATCH_OP) == op_matrix[i*col_size+j])
			{
				printf("M");
			}						
			if((op_matrix[i*col_size+j] | INSERT_OP) == op_matrix[i*col_size+j])
			{
				printf("I");
			}
			if((op_matrix[i*col_size+j] | DELETE_OP) == op_matrix[i*col_size+j])
			{
				printf("D");
			}
			if((op_matrix[i*col_size+j] | TRANSPOSE_OP) == op_matrix[i*col_size+j])
			{
				printf("T");
			}
			printf("\t");
		}
		printf("\n");
	}
	printf("\t");
	for(int i=0; i<m;i++)
	{
		printf("%c\t",str2[i]);
	}
	printf("\n");	

}



// Calculate min edit distance of two strings(str1, str2)
// [output] min edit distance
int min_editdistance( char *str1, char *str2)
{
	int n = strlen(str1); //row
	int m = strlen(str2); //col

	int d[n+1][m+1]; //distance table
	int op_matrix[(n+1)*(m+1)]; //operator table
	int temp;

	int match,tran;

	for (int i=0; i<(n+1)*(m+1);i++)
	{
		op_matrix[i] = 0;
	}
	for (int i = 0; i<=n; i++)
	{
		d[i][0] = n-i;
		op_matrix[i*(m+1)] = DELETE_OP;
	}
	for (int i = 0; i<=m; i++)
	{
		d[n][i] = i;
		op_matrix[n*(m+1)+i] = INSERT_OP;
	}

	op_matrix[n*(m+1)] = 0;

	for (int i=n-1; i>=0; i--)	//str1 row
	{
		for (int j=1; j<=m; j++)	//str2 col
		{
			match = 1000;
			tran = 0;

			if(str1[n-i-1] == str2[j-1])	//MATCH
			{
				match = d[i+1][j-1];
			}

			if ((i<n-2 & j>=2) & (str1[n-i-1] == str2[j-2]) & (str1[n-i-2] == str2[j-1]) & (str1[n-i-1] != str1[n-i-2])) //TRAMPOSE
			{
				tran = 1;
				temp = __GetMin4(d[i][j-1] + INSERT_COST, d[i+1][j] + DELETE_COST, d[i+1][j-1] + SUBSTITUTE_COST, d[i+2][j-2] +TRANSPOSE_COST);
			}
			else
			{
				temp = __GetMin3(d[i][j-1] + INSERT_COST, d[i+1][j] + DELETE_COST, d[i+1][j-1] + SUBSTITUTE_COST);		
			}
			
			d[i][j] = temp < match? temp : match;


			if(tran & (d[i][j] == d[i+2][j-2] + TRANSPOSE_COST))
			{
				op_matrix[i*(m+1) + j] += TRANSPOSE_OP;
			}
			if((match != 1000) & (d[i][j] == d[i+1][j-1])) //MATCH_COST = 0
			{	
				op_matrix[i*(m+1) + j]+= MATCH_OP;
			}
			if(d[i][j] == d[i][j-1] + INSERT_COST)
			{	
				op_matrix[i*(m+1) + j]+= INSERT_OP;
			}
			if(d[i][j] == d[i+1][j] + DELETE_COST)
			{
				op_matrix[i*(m+1) + j]+= DELETE_OP;
			}
			if(d[i][j] == d[i+1][j-1] + SUBSTITUTE_COST)
			{
				op_matrix[i*(m+1) + j]+= SUBSTITUTE_OP;
			}
		}
	}

	print_matrix(op_matrix,m+1,str1,str2,n,m);

	backtrace(op_matrix,m+1,str1,str2,n,m);

	return d[0][m];
}

// print all possible alignment of two strings.
// work recursively 
// op_matrix : has former operator info
// col_size : col size of op_matrix
// n : len of str1 
// m : len of str2 
// level : level of recursive call (top:0)
// align_str ex) "a - a", "a - b", "* - b", "ab - ba"
static void backtrace_main(int *op_matrix, int col_size, char *str1, char *str2, int n, int m, int level, char align_str[][8])
{
	static int count = 0;

	int i=strlen(str1)-n;
	int j=m;

	//new string
	if (level == 0)
	{
		count = 0;
	}

	//MATCH OR SUB
	if(((op_matrix[i*col_size+j] | SUBSTITUTE_OP) == op_matrix[i*col_size+j]) || ((op_matrix[i*col_size+j] | MATCH_OP) == op_matrix[i*col_size+j]))
	{
		//str1 n - str2 m
		//n-1, m-1
		align_str[level][0] = str1[n-1];
		align_str[level][1] =' ';
		align_str[level][2] ='-';
		align_str[level][3] =' ';
		align_str[level][4] = str2[m-1];
		align_str[level][5] = '\0';
		backtrace_main(op_matrix, col_size, str1, str2, n-1, m-1, level+1, align_str);
	}				
	if((op_matrix[i*col_size+j] | INSERT_OP) == op_matrix[i*col_size+j])
	{
		//str1 n str2 *
		//n, m-1
		align_str[level][0] = '*';
		align_str[level][1] =' ';
		align_str[level][2] ='-';
		align_str[level][3] =' ';
		align_str[level][4] = str2[m-1];
		align_str[level][5] = '\0';

		backtrace_main(op_matrix, col_size, str1, str2, n, m-1, level+1, align_str);
	}
	if((op_matrix[i*col_size+j] | DELETE_OP) == op_matrix[i*col_size+j])
	{
		//str1 * str2 m
		//n-1, m
		align_str[level][0] = str1[n-1];
		align_str[level][1] =' ';
		align_str[level][2] ='-';
		align_str[level][3] =' ';
		align_str[level][4] = '*';
		align_str[level][5] = '\0';
		backtrace_main(op_matrix, col_size, str1, str2, n-1, m, level+1, align_str); 
	}

	if((op_matrix[i*col_size+j] | TRANSPOSE_OP) == op_matrix[i*col_size+j])
	{
		//str1[n] & str[n-1] - str2[m] str2[m-1]
		//n-2, m-2
		align_str[level][0] = str1[n-1];
		align_str[level][1] = str1[n-2];
		align_str[level][2] =' ';
		align_str[level][3] ='-';
		align_str[level][4] =' ';
		align_str[level][5] = str2[m-1];
		align_str[level][6] = str2[m-2];
		align_str[level][7] = '\0';

		backtrace_main(op_matrix, col_size, str1, str2, n-2, m-2, level+1, align_str); 
	}	


	if(i == strlen(str1) && (m==0))
	{
		printf("\n[%d] ==============================\n",++count);

		print_alignment(align_str,level-1);
		return;
	}
}