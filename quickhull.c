/*
	Spring 2021 Algorithm(Prof. Do-Gil Lee) Assignment

	Goal: make algorithm that finds convex hull using divide and conquer!
		  => Quick hull!
*/

#include <stdlib.h> // atoi, rand, qsort, malloc
#include <stdio.h>
#include <assert.h> // assert
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

float distance( float a, float b, float c, t_point p);
t_line *upper_hull( t_point *points, int num_point, t_point p1, t_point pn, t_line *lines, int *num_line, int *capacity);
void separate_points( t_point *points, int num_point, t_point from, t_point to, t_point *s1, t_point *s2, int *n1, int *n2);


// finding upper hull (recursive)
// [output] lines: a set of lines that make convex hull
// [output] num_line: # of lines(t_line *lines)
// [output] capacity: # of lines that lines(t_line *lines) can handle (made by Dynamic Memory Allocation)
// return value: pointer of lines
t_line *upper_hull( t_point *points, int num_point, t_point p1, t_point pn, t_line *lines, int *num_line, int *capacity)
{

	//basecase
	if (num_point == 0)
	{	
		if (*num_line == *capacity)
		{
			*capacity = *capacity + 10;

			t_line * temp = (t_line *)malloc(*capacity * sizeof(t_line));
			for (int i=0; i<*num_line;i++)
			{
				temp[i] = lines[i];
			}			
			free(lines);
			lines = temp;
		}

		lines[*num_line].from = p1;
		lines[*num_line].to = pn;

		*num_line = *num_line + 1;

		return lines;
	}

	// find farthest point from the line made by p1 and pn
	int a = pn.y - p1.y;
	int b = p1.x - pn.x;
	int c = (p1.x * pn.y) - (p1.y * pn.x);
	float dis; // distance
	float max = -1;
	t_point pmax;
	t_line *p, *q;
	int n1, n2;

	for (int i = 0; i < num_point; i++)
	{
		dis = distance(a,b,c,points[i]);
		if ( dis > max)
		{
			max = dis;
			pmax.x = points[i].x;
			pmax.y = points[i].y;
		}
	}

	// s1: set of points
	t_point * s1 = (t_point *)malloc(sizeof(t_point) * num_point);
	assert(s1 != NULL);

	// s2: set of points
	t_point * s2 = (t_point *)malloc(sizeof(t_point) * num_point);
	assert(s2 != NULL);

	separate_points(points, num_point, p1, pmax, s1, s2, &n1, &n2);
	p = upper_hull(s1,n1, p1,pmax, lines, num_line, capacity);

	separate_points(points, num_point, pmax, pn, s1, s2, &n1, &n2);
	q = upper_hull(s1, n1, pmax, pn, p, num_line, capacity);
	
	free(s1);
	free(s2);
	
	return q;
}


// distance between line(ax+by-c=0) and given point p(x1, y1)
// distance = |ax1+by1-c| / sqrt(a^2 + b^2) 
// sqrt(a^2 + b^2): will be always same so doesn't have to be calcualted
// [output] result: distance
float distance( float a, float b, float c, t_point p)
{
	float result = (p.x * a + p.y * b - c);
	if (result > 0)
	{
		return result;
	}
	return -result;
}

// seperate s(set of points) into s1 and s2 by line (made by point from and point to) 
// [output] s1 : set of point belong to upper(left) (ax+by-c < 0)
// [output] s2 : set of point belong to lower(right) (ax+by-c > 0)
// [output] n1 : # of points in s1 
// [output] n2 : # of points in s2 
void separate_points( t_point *points, int num_point, t_point from, t_point to, t_point *s1, t_point *s2, int *n1, int *n2)
{
	int a = to.y - from.y;
	int b = from.x - to.x;
	int c = (from.x * to.y) - (from.y * to.x);

	int temp;

	*n1 = 0;
	*n2 = 0;
	
	for (int i=0; i<num_point; i++)
	{
		temp = points[i].x * a +  points[i].y * b - c;
		
		if (temp < 0)
		{
			s1[*n1] = points[i];
			*n1 = *n1 + 1;
		}

		if (temp > 0)
		{
			s2[*n2] = points[i];
			*n2 = *n2 + 1;
		}
	}

}

void print_header(char *filename)
{
	printf( "#! /usr/bin/env Rscript\n");
	printf( "png(\"%s\", width=700, height=700)\n", filename);
	
	printf( "plot(1:%d, 1:%d, type=\"n\")\n", RANGE, RANGE);
}
void print_footer(void)
{
	printf( "dev.off()\n");
}

// compare function for qsort
// sort by x coordinate to find left most and right most
int cmp_x( const void *p1, const void *p2)
{
	t_point *p = (t_point *)p1;
	t_point *q = (t_point *)p2;
	
	float diff = p->x - q->x;
	
    return ((diff >= 0.0) ? ((diff > 0.0) ? +1 : 0) : -1);
}

void print_points( t_point *points, int num_point)
{
	int i;
	printf( "\n#points\n");
	
	for (i = 0; i < num_point; i++)
		printf( "points(%d,%d)\n", points[i].x, points[i].y);
}
void print_line_segments( t_line *lines, int num_line)
{
	int i;

	printf( "\n#line segments\n");
	
	for (i = 0; i < num_line; i++)
		printf( "segments(%d,%d,%d,%d)\n", lines[i].from.x, lines[i].from.y, lines[i].to.x, lines[i].to.y);
}

// [input] points : set of points
// [input] num_point : # of points
// [output] num_line : # of lines
// return value : pointer of set of line segments that forms the convex hull
t_line *convex_hull( t_point *points, int num_point, int *num_line)
{
	int capacity = 10;

	t_line *lines = (t_line *) malloc( capacity * sizeof(t_line));
	*num_line = 0;

	// s1: set of points
	t_point *s1 = (t_point *)malloc(sizeof(t_point) * num_point);
	assert( s1 != NULL);

	// s2: set of points
	t_point *s2 = (t_point *)malloc(sizeof(t_point) * num_point);
	assert( s2 != NULL);

	int n1, n2; // number of points in s1, s2, respectively

	// points are sorted by x coordinate
	// points[0] : leftmost point (p1)
	// points[num_point-1] : rightmost point (pn)
	
	// seperate points by two extreme point
	separate_points( points, num_point, points[0], points[num_point-1], s1, s2, &n1, &n2);

	// find upper hull and lower hull
	lines = upper_hull( s1, n1, points[0], points[num_point-1], lines, num_line, &capacity);
	lines = upper_hull( s2, n2, points[num_point-1], points[0], lines, num_line, &capacity);
	
	free(s1);
	free(s2);

	return lines;
}

int main( int argc, char **argv)
{
	float x, y;
	int num_point; // number of points
	
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

	t_point *points;
	points = (t_point *)malloc( sizeof(t_point) * num_point);
	assert( points != NULL);
	
	// making points
	srand( time(NULL));
	for (int i = 0; i < num_point; i++)
	{
		x = rand() % RANGE + 1; // 1 ~ RANGE random number
		y = rand() % RANGE + 1;
	
		points[i].x = x;
		points[i].y = y;
 	}

	fprintf( stderr, "%d points created!\n", num_point);
	
	// sort the points by their x coordinate
	qsort( points, num_point, sizeof(t_point), cmp_x);

	print_header( "convex.png");
	
	print_points( points, num_point);
	
	// convex hull algorithm
	int num_line;
	t_line *lines = convex_hull( points, num_point, &num_line);
	
	fprintf( stderr, "%d lines created!\n", num_line);

	print_line_segments(lines, num_line);
	
	print_footer();
	
	free(points);
	free(lines);
	
	return 0;
}
