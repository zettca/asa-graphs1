#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct vertex{
	int value, dist, color, prev;
	list_t *adj;
} vertex_t;

/* Breadth-First Search */
int BFS(vertex_t *vertices, int source){	
	list_t *queue = list_init();
	list_node_t *node;
	int v, w, big=0;
	vertices[source-1].dist = 0;

	list_push(queue, source);
	vertices[source-1].color = 1;
	
	while (!list_empty(queue)){
		v = list_peek(queue)->value;
		list_pop(queue);
		for(node=vertices[v-1].adj->head; node!=NULL ; node=node->next ){
			w = node->value;
			if (!vertices[w-1].color){
				vertices[w-1].color = 1;
				vertices[w-1].dist = vertices[v-1].dist+1;
				vertices[w-1].prev = v;
				
				big = (vertices[w-1].dist>big) ? vertices[w-1].dist : big;
				
				list_push(queue, w);
			}
		}
		vertices[v-1].color = 2;
	}
	
	return big;
}


int main(int argc, char const *argv[]){
	int N, C, PAUL;	// Authors, Collabs, Paul's Number
	int i, u, v, M, *distances;
	vertex_t *authors;

	scanf("%d %d", &N, &C); // Authors, Collabs
	scanf("%d", &PAUL); 	// PaulErdos
	
	authors = (vertex_t*) malloc(N*sizeof(vertex_t));
	
	for(i=0; i<N; i++){ // vertex init
		authors[i].value = i+1;
		authors[i].color = 0;	 // 0 White | 1 Gray | 2 Black 
		authors[i].dist = -1;
		authors[i].prev = 0;
		authors[i].adj = list_init();
	}
	
	for(i=0; i<C; i++){	// adds Collabs
		scanf("%d %d", &u, &v);
		list_push(authors[v-1].adj, u);
		list_push(authors[u-1].adj, v);
	}
	
	M = BFS(authors, PAUL);
	
	distances = (int*) malloc(M*sizeof(int));
	for (i=0; i<M; i++) distances[i] = 0; // distances init
	
	for (i=0; i<N; i++) // distances calc
		distances[authors[i].dist-1] += 1; 
	
	// OUTPUT
	printf("%d\n", M); 
	for (i=0; i<M; i++)
		printf("%d\n", distances[i]); 
	
	return 0;
}