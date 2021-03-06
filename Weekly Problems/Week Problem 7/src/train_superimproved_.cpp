/*
A mess with the train timetable LPA 2013	

by Alexandre Pinto
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define NODES 500
#define FILESIZE 12000000

char input[FILESIZE];
char *ptr;
int edges[NODES][NODES];
int degrees[NODES];
int nVertices;
int nEdges;

int visited[NODES];
int colors[NODES];

int bi;

void dfs(int,int);
int getchar_unlocked(void);
int readLine(int * a, int * b);

int main(){

	register int i,j,z;
	char yes[9]={'N','O','T',' ','S','U','R','E','\n'};
	char no[3]={'N','O','\n'};

	struct stat filesize;
	fstat(STDIN_FILENO, &filesize);
	fread(input,1,filesize.st_size,stdin);			/*read entire file into memory*/
	ptr=input;
	while(readLine(&nVertices,&nEdges)!=-1){

		/*init graph*/
		memset(colors,0,nVertices*sizeof(int));
		memset(visited,0,nVertices*sizeof(int));
		memset(degrees,0,nVertices*sizeof(int));
		/*read graph*/
		for(z=0;z<nEdges;z++){
			readLine(&i,&j);
			edges[i-1][degrees[i-1]++]=j-1;			/*i-j*/
			edges[j-1][degrees[j-1]++]=i-1;			/*j-i*/
		}
		bi=1;											/*is bipartite*/
		dfs(0,0);										/*dfs search*/

		if(bi)
			fwrite_unlocked(yes,1,9,stdout);
		else
			fwrite_unlocked(no,1,3,stdout);
	}
	return 0;
}

void dfs(int node, int color){

	int i;

	visited[node]=1;
	colors[node]=color;

	if(bi){														
		for(i=(degrees[node]-1);i>=0;i--){
				if(visited[edges[node][i]]==0)
					dfs(edges[node][i],1-color);
				else if(colors[node]==colors[edges[node][i]]){	/*is not a bipartite graph*/
					bi=0;								
					return;
				}
		}
	}
}

/*parse the input buffer*/
inline int readLine(int * a, int * b)
{
    *a = 0;
    *b = 0;

    if (*ptr == 0) return -1;
    while ( *ptr!= ' ')
    {
        *a = *a*10 + (*ptr-48);
        ptr++;
    }
    ptr++;
    while (*ptr != '\n')
    {
         *b = *b*10 + (*ptr-48);
         ptr++;
    }
    ptr++;
    return 0;
}





