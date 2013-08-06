#include <stdio.h>
#include <math.h>
#include <string.h>
#include "kTree.h"



int main(int argc, char* argv[]){
	FILE *f;
	uint nodes; uint edges;
	register uint i;
	
	if(argc<6){
		fprintf(stderr,"USAGE: %s <GRAPH> <node> <name> <K1> <K2> [<max level K1>] <S>\n",argv[0]);
		return(-1);
	}

	//char *filename = (char *)malloc(sizeof(char)*20);
	
	f = fopen(argv[1],"r");
  fread(&nodes,sizeof(uint),1,f);
 // printf("nodes: %d\n",nodes);  
  //nodes = 11;
  //nodes = 40;
  int _K1 = atoi(argv[4]);
  int _K2 = atoi(argv[5]);

	uint s=20;
  if(argc>7)
  	s =  (atoi(argv[7]));

	uint tamSubm = 1<<s;
  
  //177147; //3^11
	uint part;
	part = nodes/tamSubm+1;
	printf("nodes:%d , tamSubm= %d , part= %d",nodes , tamSubm , part);

	uint nodesOrig = nodes;
	nodes= tamSubm; 

  
  
  printf("nodos: %d, K1: %d K2: %d, s: %d\n",nodes,_K1,_K2,s); 

  int max_level1;
  int max_real_level1;
  max_real_level1 = ceil(log(nodes)/log(_K1))-1;
  if(argc<7)
  	max_level1 = ceil(log(nodes)/log(_K1))-1;
  else
  	max_level1 = atoi(argv[6]);
 printf("nodos: %d, maximo nivel1: %d max real 1: %d\n",nodes,max_level1,max_real_level1);
 
	int nodes2 = 1;
	for(i=0;i<max_real_level1+1;i++){
		nodes2 *=_K1;
		}
	fprintf(stderr,"nodes2 %d\n",nodes2);

	
	for(i=0;i<max_level1;i++)
		nodes2 = ceil((double)nodes2/_K1);
	fprintf(stderr,"nodes2 %d\n",nodes2);


  int	max_level2 = ceil(log(nodes2)/log(_K2))-1;  
  printf("nodos: %d, maximo nivel1: %d max real 1: %d maximo nivel2: %d opr: %d\n",nodes,max_level1,max_real_level1,max_level2,nodes2);
  

  fread(&edges,sizeof(uint),1,f);
	printf("aristas: %d\n",edges);
	
	//edges = 12;
	//edges = 101;
	uint nodes_read=0;
	
	uint algo;
	ulong algo2;
	int id1, id2;
	NODE * tree;
	MREP * rep;
	TREP * trep;
	int fila,columna;

	trep = createTreeRep(nodesOrig,edges,part,tamSubm, max_real_level1, max_level1, max_level2,_K1,_K2);
	fclose(f);
	uint edges_read=0;
	//printf("part= %d",part);
	for(fila=0;fila<part;fila++){

		for(columna=0;columna<part;columna++){
				uint edges_sub=0;

				numberNodes=0;
				numberLeaves=0;
				numberTotalLeaves=0;

				fprintf(stderr,"fila= %d, columna=%d, aristas desde %d y desde %d, (%2.2f\%)\n",fila,columna,fila*tamSubm, columna*tamSubm,(float)(fila*part+columna)*100/part/part);
				f = fopen(argv[1],"r");
  			
  			fread(&algo,sizeof(uint),1,f);
				fread(&algo,sizeof(uint),1,f);

				tree = createKTree(_K1,_K2,max_real_level1,max_level1,max_level2);
			  
			  nodes_read=0;
				edges_read=0;
			
			  for(i=0;i<nodesOrig+edges;i++) {
			  	//fprintf(stderr,"---i: %d, limite: %d\n",i,nodes+edges);
			    int k;
			    fread(&k,sizeof(uint),1,f);
			    if(k<0) {
			    //	fprintf(stderr,"Nodo nuevo: %d, nodos %d hojas %d\n",nodes_read, numberNodes, numberLeaves);
			      nodes_read++;
			    }
			    else {
			    	k--;
						//if(k<40){
			    	//fprintf(stderr,"Introduciendo %d %d\n",nodes_read-1,k);
			     	
			     	
			     	id1=nodes_read-1;
			     	id2=k;
			     	
			     	if((id1>=fila*tamSubm)&&(id1<(fila+1)*tamSubm)&&(id2>=columna*tamSubm)&&(id2<(columna+1)*tamSubm)){

				     	insertNode(tree,id1-fila*tamSubm,id2-columna*tamSubm);
				     	edges_sub++;
				    }
				    edges_read++;
						    // 	insertNode(tree,nodes_read-1,k);
			    	//}
			    	//else
			    	//	i--;
			    }
			   }
			  printf("Number of Nodes: %d, number of leaves :%d, number of total leaves: %d\n",numberNodes,numberLeaves,numberTotalLeaves);
			  
			//  adjacencyList(tree,atoi(argv[2]));
		   	fclose(f);

			  MREP * rep;
			  rep = createRepresentation(tree,nodes,edges_sub);
   			fprintf(stderr,"edges in this submatrix: %d\n",edges_sub);

				insertIntoTreeRep(trep, rep, fila, columna);	
		}
	}
	
	compressInformationLeaves(trep);

  //fprintf(stderr,"LLEGO\n");
// 
//  	rep->element = (uint *)malloc(sizeof(uint)*MAX_INFO);	
//	rep->basex = (uint *)malloc(sizeof(uint)*MAX_INFO);
//	rep->basey = (uint *)malloc(sizeof(uint)*MAX_INFO);
//	rep->iniq = -1;
//	rep->finq =-1;
//	rep->div_level_table1 = (uint *)malloc(sizeof(uint)*rep->maxLevel1);
//	for(i=0;i<rep->maxLevel1;i++)
//		rep->div_level_table1[i]=exp_pow(K1,rep->maxRealLevel1-i);
//	
//	rep->div_level_table2 = (uint *)malloc(sizeof(uint)*rep->maxLevel2);
//	for(i=0;i<rep->maxLevel2;i++)
//		rep->div_level_table2[i]=exp_pow(K2,rep->maxLevel2-i);
// 	rep->info = (uint *)malloc(sizeof(uint)*MAX_INFO);
// 	fprintf(stderr,"calculando lista para %d\n",atoi(argv[2]));
//  uint * listady = compactAdjacencyList(rep,atoi(argv[2]));
//  fprintf(stderr,"Number of neighbours: %d\n",listady[0]);
//  for(i=0;i<listady[0];i++)
//  	fprintf(stderr,"%d\n",listady[i+1]);
//  
//  char *filename = (char *) malloc(sizeof(char)*(strlen(argv[3])+4));
//  strcpy(filename,argv[3]);
//  strcat(filename,".tr");
//  FILE * ft = fopen(filename,"w");
//  save(rep->bt,ft);
//  fclose(ft);
//
//  
//  strcpy(filename,argv[3]);
//  strcat(filename,".lv");
//  FILE * fn = fopen(filename,"w");
//  save(rep->bn,fn);
//  fclose(fn);  
//
//  
//  strcpy(filename,argv[3]);
//  strcat(filename,".il");
//  FILE * fi = fopen(filename,"w");
//  fwrite(&(rep->numberOfNodes),sizeof(uint),1,fi);
//  fwrite(&(rep->numberOfEdges),sizeof(uint),1,fi);
//  fwrite(&(rep->K1),sizeof(uint),1,fi);
//  fwrite(&(rep->K2),sizeof(uint),1,fi);
//  fwrite(&(rep->maxRealLevel1),sizeof(uint),1,fi);
//  fwrite(&(rep->maxLevel1),sizeof(uint),1,fi);
//  fwrite(&(rep->maxLevel2),sizeof(uint),1,fi);
//  fwrite(&(rep->cutBt),sizeof(uint),1,fi);
//  fwrite(&(rep->lastBt1_len),sizeof(uint),1,fi);
//  fwrite(&(rep->nleaves),sizeof(uint),1,fi);
//  fwrite (rep->leavesInf,sizeof(uint),rep->nleaves*K2*K2/W+1,fi);
//  fclose(fi);   
//  
//  
//	free(filename);
//	destroyRepresentation(rep);
//  

	
  uint * listady = compactTreeAdjacencyList(trep, atoi(argv[2]));
  //fprintf(stderr,"llego\n");
  
  fprintf(stderr,"Number of neighbours: %d\n",listady[0]);
  for(i=0;i<listady[0];i++)
  	fprintf(stderr,"%d\n",listady[i+1]);
	fprintf(stderr,"\n");

	saveTreeRep(trep,argv[3]);

	destroyTreeRepresentation(trep);
  return 0;
}


