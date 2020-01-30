

//we disregard my matrix multiplication calculator
//we only do matrix vector products here
//faster to just redo it
void matrixvectEigen(int matrix[], float vector[], float product[], int n){

  int i, j;

  for(i = 0; i < n; i++){

    product[i] = 0;

    for(j = 0; j < n; j++){
      float m = matrix[INDEX(n, i, j)], v = vector[j];
      //printf("Multiplying %.2f by %.2f\n", m, v);
      product[i] += (m * v);
    }
    //printf("%d sum: %.2f\n\n", i, product[i]);
  }

}

void matrixvect(int matrix[], int vector[], int product[], int n){

  int i, j;

  for(i = 0; i < n; i++){

    product[i] = 0;

    for(j = 0; j < n; j++){
      int m = matrix[INDEX(n, i, j)], v = vector[j];
      //printf("Multiplying %.2f by %.2f\n", m, v);
      product[i] += (m * v);
    }
    //printf("%d sum: %.2f\n\n", i, product[i]);
  }

}

float findmax(float a[], int msize){

  int i;
  float  maximum = a[0];
  for(i = 0; i < msize; i++){
    if(maximum < a[i]){
      maximum = a[i];
    }
  }

  return maximum;

}

int floatcomp(float a, float b){

  //small float comparison function
  //was not converging in some cases when original == was used

  double epsilon = .01f;
  if(fabs(a - b) < epsilon){
    return 1;
  }

  return 0;
}

int isEqual(float a[], float b[], int size){

  //we just want to see if these vectors are the same
  //no need to worry about indexing

  int i;

/*
  for(i = 0; i < size; i++){
    printf("%d  %.2f  %.2f\n",size, a[i], b[i]);
  }
  printf("\n\n");
*/

  for(i = 0; i < size; i++){
    if(floatcomp(a[i], b[i]) == 0){
      return 0;
    }
  }

  return 1;

}

void matrixeigen(int matrix[], float res[], int n){

  float vector[n];

  int i;

  //init vectors
  for(i = 0; i < n; i++){
    vector[i] = 1.0; //'let x be all 1 vector in appropriate dimmension'
    res[i] = 0.0;
  }

  while(1){

    //take matrix-vector product
    //matrix * vector --> res
    matrixvectEigen(matrix, vector, res, n);

    float eigenValue = findmax(res, n);
    for(i = 0; i < n; i++){
      res[i] /= eigenValue;
    }

    if(isEqual(vector, res, n) == 1){
      break;
    }

    for(i = 0; i < n; i++){
      vector[i] = res[i];
    }

  }

}

void hits(int matrix[], int auth[], int hub[], int n){

  //init vector of all 1's
  int vector[n];
  int i;

  for(i = 0; i < n; i++){
    vector[i] = 1;
  }

  matrixvect(matrix, vector, hub, n);
  transpose(matrix, n);
  matrixvect(matrix, hub, auth, n);

  //transpose again to get original matrix
  transpose(matrix, n);

}


/*

all further functions apply to the sparse matrix encoding
Compressed Sparse Row

*/


//sparse matrix multiplication
void sparsemult(struct CSRgraph csr, int vect[], int res[], int n){

  int i, j;
  for(i = 0; i < n; ++i){
    res[i] = 0;
    for(j = csr.dest_offsets[i]; j < csr.dest_offsets[i+1]; ++j){
      res[i] += 1 * vect[csr.source_indices[j]];
    }
  }
}

//sparse matrix mult with float arrs instead (for pagerank)
void sparsemult_f(struct CSRgraph csr, float vect[], float res[], int n){

  int i, j;
  for(i = 0; i < n; ++i){
    res[i] = 0;
    for(j = csr.dest_offsets[i]; j < csr.dest_offsets[i+1]; ++j){
      res[i] += 1 * vect[csr.source_indices[j]];
    }
  }
}

void sparsetranspose(struct CSRgraph *csr){

  int i, j, l;

  //we'll need to reset the csr after this
  int newvert[csr->nvertices+1];
  int newedge[csr->nedges];

  int currentEdge = 0;

  newvert[0] = 0;

  for(i = 0; i < csr->nvertices; i++){

    for(j = 0; j < csr->nvertices; j++){

      //iterate through current vertex
      int lowerBound = csr->dest_offsets[j];
      int upperBound = csr->dest_offsets[j+1];

      for(l = lowerBound; l < upperBound; l++){

        //we find a refernce
        if(csr->source_indices[l] == i){
          //record reference, increment edges
          newedge[currentEdge] = j;
          currentEdge++;
        }

      }

      newvert[i+1] = currentEdge;

    }

    if(i % 1000 == 0){
      printf("iterated through %d of %d\n", i, csr->nvertices);
    }

  }

  freegraph(csr);
  setgraph(csr, newvert, newedge, csr->nvertices, csr->nedges);

}

int sparsetransposeParallel(int lower, int upper, int tempv[], int tempe[], int offsets[], int sources[], int nv, int ne){

  int i, j, l;

  int currentEdge = 0;
  tempv[lower] = 0;

  for(i = lower; i < upper; i++){

    for(j = 0; j < nv; j++){

      //iterate through current vertex
      int lowerBound = offsets[j];
      int upperBound = offsets[j+1];

      for(l = lowerBound; l < upperBound; l++){

        //we find a refernce
        if(sources[l] == i){
          //record reference, increment edges
          tempe[currentEdge] = j;
          currentEdge++;
        }

      }

      tempv[i+1] = currentEdge;

    }

  }

  return currentEdge;

}

void mergeTransposeSectors(int masterV[], int masterE[], int workerV[], int workerE[], int currvert, int curredge, int workeredgetotal){

  int i;

  for(i = currvert; i < (currvert*2); i++){
    int workerindex = (currvert - i);
    masterV[i] = workerV[workerindex];
  }

  for(i = curredge; i < (curredge + workeredgetotal); i++){
    int workerindex = (workeredgetotal - i);
    masterE[i] = workerE[workerindex];
  }

}

//ensure roots nvertices and nedges are set to CSR's before calling
void paralleltransposeCSR(int rank, int wsize, int nvertices, int nedges, struct CSRgraph *csr){

  //bcast the number of vertices/edges we need
  MPI_Bcast(&nvertices, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&nedges, 1, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);

  //set number of operations per node

  int opspernode = (nvertices/wsize),
      lowerRange = rank * opspernode,
      upperRange = lowerRange + opspernode;

  //replicate CSR data on each node

  int offsets[nvertices+1];
  int sources[nedges];

  //copy from original CSR
  if(rank == 0){
    int i;
    for(i = 0; i < nvertices+1; i++){
      offsets[i] = csr->dest_offsets[i];
    }

    for(i = 0; i < nedges; i++){
      sources[i] = csr->source_indices[i];
    }

  }

  MPI_Bcast(offsets, nvertices+1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(sources, nedges, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);

  //these most likely will not have to hold this much
  //kind of like a buffer size
  int localV[nvertices], localE[nedges];

  //printf("rank %d will do vertex %d --> %d\n", rank, lowerRange, upperRange);

  int totalEdges = sparsetransposeParallel(lowerRange, upperRange, localV, localE, offsets, sources, nvertices, nedges);

  //each node individually sends its sources/offsets to 0
  if(rank != 0){
    MPI_Send(&totalEdges, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(localV, nvertices, MPI_INT, 0, 1, MPI_COMM_WORLD);
    MPI_Send(localE, nedges, MPI_INT, 0, 2, MPI_COMM_WORLD);
  } else {
    int i;

    int vbuffer[nvertices], ebuffer[nedges];
    int tempsources;
    int totalsources = totalEdges; //init number of all sources to roots find for sources in range 0

    for(i = 1; i < wsize; i++){

      int lowerRange = i * opspernode;
      int upperRange = lowerRange + opspernode;

      MPI_Recv(&tempsources, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Recv(vbuffer, nvertices, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Recv(ebuffer, nedges, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      mergeTransposeSectors(localV, localE, vbuffer, ebuffer, opspernode * i, totalsources, tempsources);
    }

  }

}

void sparsehub(struct CSRgraph csr, int hub[], int n){

  //init vector of all 1's
  int vector[n];
  int i;

  for(i = 0; i < n; i++){
    vector[i] = 1;
    hub[i] = 0;
  }

  if(csr.nedges == 0) return;

  sparsemult(csr, vector, hub, n); //get hub score

}

void sparseauth(struct CSRgraph csr, int auth[], int hub[], int n){

  int i, j;
  for(i = 0; i < n; i++){
    auth[i] = 0;
  }

  if(csr.nedges == 0) return;
  for(i = 0; i < csr.nvertices; i++){

    int lowerBound = csr.dest_offsets[i];
    int upperBound = csr.dest_offsets[i+1];

    for(j = lowerBound; j < upperBound; j++){
      auth[csr.source_indices[j]] += hub[i];
    }

  }

}


void sparsehit(struct CSRgraph *csr, int hub[], int auth[], int n){

  sparsehub(*csr, hub, n);
  sparseauth(*csr, auth, hub, n);

}

void sparsepagerank(struct CSRgraph csr, float res[]){

  int n = csr.nvertices;

  if(csr.nedges == 0) return;
  float vector[n];
  int i;

  //init vectors
  for(i = 0; i < n; i++){
    vector[i] = 1.0; //'let x be all 1 vector in appropriate dimmension'
    res[i] = 0.0;
  }

  while(1){

    sparsemult_f(csr, vector, res, n);

    float eigenValue = findmax(res, n);
    for(i = 0; i < n; i++){
      res[i] /= eigenValue;
    }

    if(isEqual(vector, res, n) == 1){
      break;
    }

    for(i = 0; i < n; i++){
      vector[i] = res[i];
    }

  }

}
/*
int shortestpath(int start, int target, struct CSRgraph *csr){

  int dist = searchVertex(start, target, csr);

  return dist;

}

int searchVertex(int start, int target, struct CSRgraph *csr){

  int i, j;

  //iterate through current vertex
  int lowerBound = csr->dest_offsets[start];
  int upperBound = csr->dest_offsets[start+1];

  for(i = lowerBound; i < upperBound; i++){

    printf("checking connection %d --> %d\n", start, csr->source_indices[i]);

    if(csr->source_indices[i] == target) return 0;
    //return searchVertex(csr->source_indices[i], target, csr) + 1;

  }

  return upperBound-lowerBound;

  //if we could not find any path, return the number of vertices (to denote that path does not exist)
  //return csr->nvertices;

}
*/
