/*
	Spring 2021 Algorithm(Professor: Do-Gil Lee) Assignment

	Goal: make algorithm that finds convex hull in bruteforce way!
*/

#include <stdlib.h> // atoi, rand, malloc, realloc
#include <stdio.h>
#include <time.h> //time

#define RANGE 10000

typedef struct
{
	int x;
	int y;
} t_point;

typedef struct
{
	t_point from;
	t_point to;
} t_line;

/////////////////////////////////////////////////////////////////
void print_header( char *filename)
{
	printf( "#! /usr/bin/env Rscript\n");
	printf( "png(\"%s\", width=700, height=700)\n", filename);
	
	printf( "plot(1:%d, 1:%d, type=\"n\")\n", RANGE, RANGE);
}
void print_footer( void)
{
	printf( "dev.off()\n");
}
////////////////////////////////////////////////////////////////

//print points like "points(xpos,ypos)"
void print_points( t_point *points, int num_point);

//print line segments like "segments(7107,2909,7107,2909)"
void print_line_segments( t_line *lines, int num_line);

// [input] points : set of points
// [input] num_point : number of points
// [output] num_line : number of line segments that forms the convex hull
// return value : set of line segments that forms the convex hull
t_line *convex_hull( t_point *points, int num_point, int *num_line);

int main( int argc, char **argv)
{
	int x, y;
	int num_point; // number of points
	int num_line; // number of lines
	
	if (argc != 2)
	{
		printf( "%s number_of_points\n", argv[0]);
		return 0;
	}

	num_point = atoi( argv[1]);
	if (num_point <= 0)
	{
		printf( "The number of points should be a positive integer!\n");
		return 0;
	}

	t_point *points = (t_point *) malloc( num_point * sizeof( t_point));
		
	t_line *lines;

	// making n points
	srand( time(NULL));
	for (int i = 0; i < num_point; i++)
	{
		x = rand() % RANGE + 1; // 1 ~ RANGE random number
		y = rand() % RANGE + 1;
		
		points[i].x = x;
		points[i].y = y;
 	}

	fprintf( stderr, "%d points created!\n", num_point);

	print_header( "convex.png");
	
	print_points( points, num_point);
	
	lines = convex_hull( points, num_point, &num_line);

	fprintf( stderr, "%d lines created!\n", num_line);

	print_line_segments( lines, num_line);
		
	print_footer();
	
	free( points);
	free( lines);
	
	return 0;
}

//print points like "points(xpos,ypos)"
void print_points( t_point *points, int num_point)
{
	for (int i=0; i<num_point; i++)
	{
		printf("points(%d,%d)\n", points[i].x,points[i].y);
	}
}


//print line segments like "segments(line.from.x,line.from.y,line.to.x,line.to.y)"
void print_line_segments( t_line *lines, int num_line)
{
	for (int i=0; i<num_line; i++)
	{
		printf("segments(%d,%d,%d,%d)\n", lines[i].from.x, lines[i].from.y, lines[i].to.x, lines[i].to.y);
	}
}

// [input] points : set of points
// [input] num_point : number of points
// [output] num_line : number of line segments that forms the convex hull
// return value : set of line segments that forms the convex hull
t_line *convex_hull( t_point *points, int num_point, int *num_line)
{
	int a,b,c;
	int res,p_cnt,m_cnt; //p:plus, m:minus
	int t_size = 10; //current size of lines in t_lines
	int t_idx = 0; //current # of lines in t_lines

	t_line * t_lines = (t_line *)malloc(sizeof(t_line)*t_size); //start with size 10 
	
	for (int i=0; i<num_point; i++)
	{
		for(int j=i+1; j<num_point;j++)
		{
			p_cnt=0;
			m_cnt=0;
			a = points[j].y - points[i].y;
			b = points[i].x - points[j].x;
			c = (points[i].x * points[j].y) - (points[i].y * points[j].x);
			for (int k=0; k<num_point; k++)
			{
				res = (a*points[k].x) + (b*points[k].y) - c;
				// judge if res is > , < or 0
				if (res >= 0)  
				{
					p_cnt++;
				}
				if(res <= 0)
				{
					m_cnt++;
				}
			}

			// if condition is satisfied, add current line to t_line 
			if((p_cnt == num_point) || (m_cnt == num_point))
			{
				if(t_idx == t_size) // t_lines is full! make it larger
				{
					t_size = t_size*2;
					t_lines = (t_line *)realloc(t_lines, sizeof(t_line) * t_size);
				}
				t_lines[t_idx].from.x = points[i].x;
				t_lines[t_idx].from.y = points[i].y;
				t_lines[t_idx].to.x = points[j].x;
				t_lines[t_idx].to.y = points[j].y;
				t_idx++;
			}
		}
	}
	*num_line = t_idx;
	return t_lines;
}