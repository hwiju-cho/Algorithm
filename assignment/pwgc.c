/*
	Spring 2021 Algorithm(Prof. Do-Gil Lee) Assignment
	
	Goal: make algorithm that solves river crossing puzzle (https://en.wikipedia.org/wiki/River_crossing_puzzle)
		  => Using DFS!
*/

#include <stdio.h>
#include <stdlib.h>

#define PEASANT 0x08 
#define WOLF	0x04
#define GOAT	0x02
#define CABBAGE	0x01

static int changeP(int state);
static int changePG( int state);
static int changePW(int state);
static int changePC(int state);
static void print_statename(int state);
static void get_pwgc( int state, int *p, int *w, int *g, int *c);
static int is_dead_end(int state);
static int is_possible_transition(int state1, int state2, int visited[]);
static int is_visited( int visited[], int state);
static void print_states( int visited[], int count);



// ex) if state == 7, print <0111>
//     7 == 0111 == PEASANT X, WOLF O, GOAT O, CABBAGE O
static void print_statename(int state) 
{
	printf("<");
	for (int i=4; i>0; i--)
	{
		printf("%d", ((state & ( 1<< i-1))? 1: 0));	
	}
	printf(">");
}

// get presence status of PEASANT,WOLF,GOAT,CABBAGE in given state and save them in p, w, g, c
// ex) state == 7(0111), p = 0, w = 1, g = 1, c = 1
static void get_pwgc( int state, int *p, int *w, int *g, int *c)
{
	*p = ((state & PEASANT)? 1:0);
	*w = ((state & WOLF)? 1:0);
	*g = ((state & GOAT)? 1:0);
	*c = ((state & CABBAGE)? 1:0);
}

// check if state is dead_end or not
// [output] 1: dead_end, 0: not dead_end
static int is_dead_end(int state)
{
	int p,w,g,c;
	get_pwgc(state, &p,&w,&g,&c);
	// WOLF and GOAT in same state without PEASANT or GOAT and CABBAGE in same state without PEASANT
	if ((w^g==0) & (p^w) | (g^c==0) & (p^g))
	{
		return 1;
	}
	return 0; 
}

// check if it is possible to move state1 to state2
// only allow state that moves (PEASANT) or (PEASANT and other one item) ---- see dfs_main
// [output] 1: possible transition, 0: impossible transition
static int is_possible_transition(int state1, int state2, int visited[])
{

	if(is_dead_end(state2))
	{
		printf("\tnext state ");
		print_statename(state2);
		printf(" is dead-end\n");		
		return 0;
	}
	if(is_visited(visited, state2))
	{
		printf("\tnext state ");
		print_statename(state2);
		printf(" has been visited\n");		
		return 0;
	}
	if (state2 == -1)
	{
		return 0;
	}
	return 1;
}

// change Position: move PEASANT
// [output] new state
static int changeP(int state)
{	
	int p,w,g,c;
	get_pwgc(state, &p,&w,&g,&c);
	
	return state^PEASANT;
}

// change Position: move PEASANT, WOLF 
// [output] if transition is not possible : -1, else: newstate
static int changePW( int state)
{
	int p,w,g,c;
	get_pwgc(state,&p,&w,&g,&c);
	if(!(p^w)) //only possible when they are in the same state
	{
		return (state^PEASANT^WOLF);
	}
	return -1;
}

// change Position: move PEASANT, GOAT
// [output] if transition is not possible : -1, else: newstate
static int changePG( int state)
{
	int p,w,g,c;
	get_pwgc(state,&p,&w,&g,&c);

	if (!(p^g)) //only possible when they are in the same state
	{
		return (state^PEASANT^GOAT);
	}
	return -1;
}

// change Position: move PEASANT, CABBAGE
// [output] if transition is not possible : -1, else: newstate
static int changePC(int state)
{
	int p,w,g,c;
	get_pwgc(state,&p,&w,&g,&c);

	if (!(p^c)) //only possible when they are in the same state
	{
		return (state^PEASANT^CABBAGE);
	}
	return -1;
}

// check if state is already visited
// [output] visited: 1, not visited: 0
static int is_visited( int visited[], int state)
{
	for (int i=0; i<16;i++)
	{
		if(visited[i] == state)
		{
			return 1;
		}
	}
	return 0;
}

// print visited states
static void print_states( int visited[], int count)
{	
	for (int i=0;i<count;i++)
	{
		print_statename(visited[i]);
		printf("\n");
	}
	printf("\n");
}

static void dfs_main( int state, int goal_state, int level, int visited[])
{
	visited[level] = state;

	printf("cur state is ");
	print_statename(state);
	printf(" (level %d)\n",level);
	
	if (state == goal_state)
	{
		printf("Goal-state found!\n");
		print_states(visited, level+1);
		return;
	}
	if(is_possible_transition(state,changeP(state),visited))
	{
		dfs_main(changeP(state), goal_state,level+1,visited);
		for (int i=level+1; i<16;i++)
		{
			visited[i]=0;
		}
		printf("back to ");
		print_statename(state);
		printf("(level %d)\n",level);			
	}
	if(is_possible_transition(state, changePW(state),visited))
	{
		dfs_main(changePW(state), goal_state, level+1, visited);
		for (int i=level+1; i<16;i++)
		{
			visited[i]=0;
		}
		printf("back to ");
		print_statename(state);
		printf("(level %d)\n",level);	
	}
	if(is_possible_transition(state, changePG(state),visited))
	{
		dfs_main(changePG(state), goal_state, level+1, visited);
		for (int i=level+1; i<16;i++)
		{
			visited[i]=0;
		}
		printf("back to ");
		print_statename(state);
		printf("(level %d)\n",level);	
	}
	if(is_possible_transition(state,changePC(state),visited))
	{	
		dfs_main(changePC(state), goal_state, level+1, visited);
		for (int i=level+1; i<16;i++)
		{
			visited[i]=0;
		}
		printf("back to ");
		print_statename(state);
		printf("(level %d)\n",level);	
	}
	
}

// get adjacency matrix of state
void make_adjacency_matrix( int graph[][16])
{
	for (int i=0; i<16; i++)
	{
		for (int j=0; j<16;j++)
		{
			graph[i][j] = 0;
			if (is_dead_end(j) | is_dead_end(i)) //check dead_end or not
			{
				continue;
			}
			if( (j == changeP(i))|(j==changePW(i))|(j==changePG(i))|(j==changePC(i))) //check transition possibility
			{
				graph[i][j]=1;
			}
			
		}
	}
}

// print adjacency matrix
void print_graph( int graph[][16], int num)
{
	for (int i=0; i<num; i++)
	{
		for (int j=0; j<num;j++)
		{
			printf("%d ", graph[i][j]);
		}
		printf("\n");
	}
}

// save given graph at .net file
void save_graph( char *filename, int graph[][16], int num)
{
	FILE * fp = fopen(filename,"w");
	if (fp==NULL)
	{
		return;
	}
	fprintf(fp, "*Vertices %d \n", num);
	for (int i=0;i<num;i++)
	{
		fprintf(fp, "%d \"<",i+1);
		for (int j=4; j>0; j--)
		{
			fprintf(fp, "%d", ((i & ( 1<< j-1))? 1: 0));	
		}
		fprintf(fp, ">\"\n");
	}
	fprintf(fp, "*Edges\n");
	{
		for (int i=0; i<num;i++)
		{
			for (int j=i; j<num;j++)
			{
				if (graph[i][j]==1)
				{
					fprintf(fp, "  %d  %d\n",i+1,j+1);
				}
			}
		}
	}
	fclose(fp);
}

// call dfs_main
void depth_first_search( int init_state, int goal_state)
{
	int level = 0;
	int visited[16] = {0,}; //save visited state
	
	dfs_main( init_state, goal_state, level, visited); 
}


int main( int argc, char **argv)
{
	int graph[16][16] = {0,};
	
	make_adjacency_matrix(graph);

	// print adjacency table (only for debugging)
	//print_graph(graph, 16); 
	
	save_graph("pwgc.net", graph, 16);

	depth_first_search( 0, 15); // initial state, goal state
	
	return 0;
}
