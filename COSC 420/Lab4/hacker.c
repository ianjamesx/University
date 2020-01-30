#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mpi.h>

int getbuffersize(){


}

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  //MPI_File fh;

  int buf[1000];
  //MPI_File_open(MPI_COMM_WORLD, "test", MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

  //MPI_File_read(comm, "test.ord", MPI_MODE_RDWR | MPI_MODE_CREATE | MPI_MODE_DELETE_ON_CLOSE, MPI_INFO_NULL, &fh);

  if (rank == 0){
    //MPI_File_write(fh, buf, 1000, MPI_INT, MPI_STATUS_IGNORE);
/*
    static const char filename[] = "file.txt";
   FILE *file = fopen ( filename, "r" );
   if ( file != NULL )
   {
      char line [ 128 ];// or other suitable maximum line size
      while ( fgets ( line, sizeof line, file ) != NULL ) // read a line
      {
         fputs ( line, stdout ); // write the line
      }
      fclose ( file );
   }
   else
   {
      perror ( filename ); //why didn't the file open?
   }

   */
  }

  //MPI_File_close(&fh);

/*
  if(argc < 2){
    printf("Usage: ./crypt [string]\n");
    return 0;
  }

  char* salt = "$5$cat";
  char* cypertext = crypt(argv[1], salt);
  printf("Hashed Passwd: %s\n", cypertext);

  */

  MPI_Finalize();

  return 0;

}
