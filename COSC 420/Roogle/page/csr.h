
#include "matrix.h"

//inspiration for Compressed Sparse Row encoding from
//NVIDIA CUDA nvGRAPH library
//https://docs.nvidia.com/cuda/nvgraph/index.html

//how it works is we essentially have two strided arrays
//one corresponds to the indices in the other
//e.g. - destination offsets

struct CSRgraph {
  int *dest_offsets;
  int *source_indices;
  int nvertices;
  int nedges;
};

void copygraph(struct CSRgraph *original, struct CSRgraph *copy){

  copy->nvertices = original->nvertices;
  copy->nedges = original->nedges;
  copy->dest_offsets = malloc((original->nvertices+1)*sizeof(int));
  copy->source_indices = malloc((original->nedges+1)*sizeof(int));

  int i;
  for(i = 0; i < copy->nvertices+1; i++){
    copy->dest_offsets[i] = original->dest_offsets[i];
  }

  for(i = 0; i < copy->nedges; i++){
    copy->source_indices[i] = original->source_indices[i];
  }

}

void setgraph(struct CSRgraph *g,
              int dest_offsets[],
              int source_indices[],
              int nv,
              int ne){

  g->nvertices = nv;
  g->nedges = ne;
  g->dest_offsets = malloc((nv+1)*sizeof(int));
  g->source_indices = malloc((ne+1)*sizeof(int));

  int i;
  for(i = 0; i < nv+1; i++){
    g->dest_offsets[i] = dest_offsets[i];
  }

  for(i = 0; i < ne; i++){
    g->source_indices[i] = source_indices[i];
  }

}

int comparegraph(struct CSRgraph *g1, struct CSRgraph *g2){

  int i;
  if(g1->nvertices != g2->nvertices){
    printf("NOT vs\n");
    return 0;
  }

  if(g1->nedges != g2->nedges){
    printf("NOT e\n");
    return 0;
  }

  for(i = 0; i < g1->nvertices; i++){
    if(g1->dest_offsets[i] != g2->dest_offsets[i]){
      printf("noo do %d %d\n", g1->dest_offsets[i], g2->dest_offsets[i]);
      continue; //return 0;
    } else {
      printf("%d - %d\n", g1->dest_offsets[i], g2->dest_offsets[i]);
    }
  }

  for(i = 0; i < g1->nedges; i++){
    if(g1->source_indices[i] != g2->source_indices[i]){
      printf("noo si %d %d\n",g1->source_indices[i], g2->source_indices[i]);
      return 0;
    } else {
      printf("%d - %d\n", g1->source_indices[i], g2->source_indices[i]);
    }
  }

  printf("matched\n");
  return 1;

}

void freegraph(struct CSRgraph *g){
  free(g->dest_offsets);
  free(g->source_indices);
}

void debugprint(struct CSRgraph g){

  int i, j;
  for(i = 0; i < g.nvertices; i++){
    int lowerBound = g.dest_offsets[i];
    int upperBound = g.dest_offsets[i+1];
    for(j = lowerBound; j < upperBound; j++){
      printf("vertex %d --> %d\n", i, g.source_indices[j]);
    }
  }
}

void finalconnprint(struct CSRgraph g){

  //print final connection for csr encoded graph
  //for debugging

  int i, j;
  int nv = g.nvertices, ne = g.nedges;

  int lowerBound = g.dest_offsets[nv-1];
  int upperBound = g.dest_offsets[nv];
  printf("\n\n%d, %d\n", nv, lowerBound);
  for(j = lowerBound; j < upperBound; j++){
    printf("vertex %d (%d) --> %d\n", nv, g.dest_offsets[nv], g.source_indices[j]);
  }
}

void offsetprint(struct CSRgraph g){

  int i, j;
  for(i = 0; i < g.nvertices+1; i++){
    printf("%d, ", g.dest_offsets[i]);
  }
  printf("\n\n");
  for(i = 0; i < g.nedges; i++){
    printf("%d, ", g.source_indices[i]);
  }
  printf("\n");
}

void statprint(struct CSRgraph g){
  printf("\ngraph stats (Compressed Sparse Row)\n v: %d e: %d\n", g.nvertices, g.nedges);
  int graphdata = ((g.nvertices + g.nedges) * 4)+8;
  float inMb = graphdata;
  inMb /= 1024; //kb
  inMb /= 1024; //mb
  printf("total data used for CSR: %.2fMb\n\n", inMb);
}


//convert an adjacency matrix to
//compressed sparse row

void matrixtocsr(int matrix[], int n, struct CSRgraph *graph){

  int dest_offsets[n+1];
  int source_indices[(n * n)+1]; //max edges is n*n
  int nv = n, ne = 0;

  int i, j;
  dest_offsets[0] = 0;
  for(i = 0; i < n; i++){

    for(j = 0; j < n; j++){
      int index = INDEX(n,i,j);
      if(matrix[index] != 0){
        source_indices[ne] = j; //hold index of which connected node
        ne++;
      }
    }

    dest_offsets[i+1] = ne;

  }

  setgraph(graph, dest_offsets, source_indices, nv, ne);

}

void savetofile(struct CSRgraph csr, char *filename){

  //open the file to write graph data to
  FILE *fp;
  fp = fopen(filename, "w+");

  fprintf(fp, "%d\n", csr.nvertices);
  fprintf(fp, "%d\n", csr.nedges);

  int i;
  for(i = 0; i < csr.nvertices+1; i++){
    fprintf(fp, "%d\n", csr.dest_offsets[i]);
  }

  for(i = 0; i < csr.nedges; i++){
    fprintf(fp, "%d\n", csr.source_indices[i]);
  }

  fclose(fp);

}

void savearraytofile(float array[], int size, char *file){

  FILE* fp = fopen(file, "r");

  int i;
  for(i = 0; i < size; i++){
    fprintf(fp, "%.3f\n", array[i]);
  }

  fclose(fp);

}

void readfromfile(struct CSRgraph *csr, char *file){

  FILE* fp = fopen(file, "r");

  int nv, ne;

  fscanf(fp, "%d", &nv); //read in vertex count
  fscanf(fp, "%d", &ne); //read in edge count

  int offsets[nv+1];
  int sources[ne];

  int i = 0;
  int curr;

  while (!feof(fp)){
    fscanf(fp, "%d", &curr);
    if(i <= nv){
      offsets[i] = curr;
    } else {
      sources[i] = curr;
    }
    i++;
  }

  setgraph(csr, offsets, sources, nv, ne);
  fclose(fp);

}

void readarrayfromfile(float arr[], char *file){

  FILE* fp = fopen (file, "r");

  int i = 0;
  int curr;

  while (!feof(fp)){
    fscanf (fp, "%.3f", &curr);
    arr[i] = curr;
    i++;
  }

  fclose(fp);

}
