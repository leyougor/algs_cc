#include <stdio.h>
#include <math.h>
#include <string.h>
#include "kTree.h"

/* Time meassuring */
double ticks;
struct tms t1,t2;

void start_clock() {
	times (&t1);
}

double stop_clock() {
	times (&t2);
	return (t2.tms_utime-t1.tms_utime)/ticks;
}
/* end Time meassuring */

int main(int argc, char* argv[]){

	if(argc<4){
		fprintf(stderr,"USAGE: %s <GRAPH> <query file> <repet>\n",argv[0]);
		return(-1);
	}

	//char *filename = (char *)malloc(sizeof(char)*20);
	

		TREP * rep = loadTreeRepresentation(argv[1]);
	
		char * list_file = argv[2];
		
		
		
	int repet = atoi(argv[3]);
	FILE * list_fp = fopen(list_file,"r");
	uint queries;
	uint nnodes= rep->numberOfNodes;
	fread(&queries, sizeof(uint), 1, list_fp);
	ulong recovered = 0;
	double t = 0;
  uint *qry = (uint *) malloc(sizeof(uint)*queries);
  fread(qry,sizeof(uint),queries,list_fp);

	fclose(list_fp);

  fprintf(stderr,"Processing %d queries\n",queries);
  ticks= (double)sysconf(_SC_CLK_TCK);
  
  

	uint i,j;
 //(584595,80)
  
  ///// SIN RANGOS
  recovered = 0;
	t = 0;
  fprintf(stderr,"Processing %d queries\n",queries);
  ticks= (double)sysconf(_SC_CLK_TCK);
	
	
	
  start_clock();
  for(j=0;j<repet;j++){
	  for(i=0;i<queries;i++) {
    //Comentar 2 lines o descomentar en funcion si se quieres comprobar tiempos 
    //usando rangos o no
    //uint *l  = compactAdjacencyList(rep, qry[i]);
    //recovered += l[0];
    //fprintf(stderr,"mirando %d %d\n",qry[i],j);
    	recovered +=  compactTreeCheckLinkQuery(rep, qry[j],qry[i]);
    }
  }
  t += stop_clock(); 
  t *= 1000; // to milliseconds

	fprintf(stderr,"Check Time: \n");


	fprintf(stderr,"Recovered Nodes: %d\n",recovered);
//	fprintf(stderr,"Queries: %d\n",queries);
	fprintf(stderr,"Total time(ms): %f",t);
//	fprintf(stderr,"Time per query: %f\n",t/queries);
	fprintf(stderr,"Time per query: %f\n",t/repet/queries);
//	fprintf(stderr,"Time per link: %f\n",t/recovered);


	t = 0;
	recovered = 0;
  start_clock();
  repet = repet;
//  for(j=0;j<nnodes;j++){
	//  for(i=0;i<queries;i++) {
	for(j=0;j<1000;j++){
	  for(i=0;i<repet;i++) {
    //Comentar 2 lines o descomentar en funcion si se quieres comprobar tiempos 
    //usando rangos o no
    //uint *l  = compactAdjacencyList(rep, qry[i]);
    //recovered += l[0];
    //fprintf(stderr,"mirando %d %d\n",qry[i],j);
    	uint *l  = compactTreeAdjacencyList(rep, qry[i]);
    	recovered += l[0];
    }
 // }
	}
  t += stop_clock(); 
  t *= 1000; // to milliseconds


	fprintf(stderr,"Adjacency Time: \n");
	fprintf(stderr,"Recovered Nodes: %d\n",recovered);
//	fprintf(stderr,"Queries: %d\n",queries);
	fprintf(stderr,"Total time(ms): %f",t);
//	fprintf(stderr,"Time per query: %f\n",t/queries);
	fprintf(stderr,"Time per query: %f\n",t/repet/1000);
	fprintf(stderr,"Time per link: %f\n",t/recovered);


  destroyTreeRepresentation(rep);

  
  return 0;
}


