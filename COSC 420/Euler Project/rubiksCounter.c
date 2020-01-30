void bruteforceFV(struct Cubelet cube[][2][2], int &count){

  int i, j;
  for(i = 0; i < 3; i++){
    for(j = 0; j < 2; j++){
      moveFrontVertically(j, cube);
      count++;
      bruteforceSH(cube);
    }
  }

}

void bruteforceAllRubiks(struct Cubelet cube[][2][2], int &count){

  bruteforceFV(cube, count);

}

void bruteforceFC(struct Cubelet cube[][2][2], int &count){

  int i, j;
  for(i = 0; i < 3; i++){
    for(j = 0; j < 2; j++){
      moveFaceClockwise(j, cube);
      count++;
    }
  }

}

void bruteforceSH(struct Cubelet cube[][2][2], int &count){

  int i, j;
  for(i = 0; i < 3; i++){
    for(j = 0; j < 2; j++){
      moveSideHorizontally(j, cube);
      bruteforceFC(cube, count);
      count++;
    }
  }

}
