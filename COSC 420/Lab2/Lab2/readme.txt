Ian Thomas
COSC 420
Lab 2 README

Ian's Inner Product, Matrix Addition, Subtraction, and Multiplication

All of the programs take a single input from the command line, which will be the size
of the randomly generated square matrix

The matrix used for the computation will be randomly generated matrices (and vectors for the
innerproduct.c program), where m and n will be equal to whatever value the user inputs

NOTE: The makefile for this program is actually a shell script, run it as ./make.sh
      If you require executable permissions for the file, first run  chmod +x make.sh
Four files will be produced (all of which are executable by mpiexec):

inner (for innerproduct.c)
matrixaddsubtract (for matrixAddSubtract.c)
matrixtranspose (for matrixTranspose.c)
matrixmultiply (for matrixMultiply.c)

there are four files included:

innerproduct.c
matrixAddSubtract.c
matrixMultiply.c
matrixTranspose.c

innerproduct works as standard by dividing the vectors over the processors, it uses the MPI
scatter and gather methods in order to distribute then recollect the results

matrixAddSubtract works similarly, however uses the MPI send and receive methods in order to
distribute and recollect data. Only data relevant to each node is sent to each node

matrixTranspose works entirely sequential (however still uses the MPI compiler)

matrixMultiply works by sending a complete copy of the matrices being multiplied to each
node working on it. Results are recollected into a master array on the root node


Questions)

a) for innerproduct, the theoretical complexity would be n/p where n is the number of elements
  and p is the number of processors

  for matrixAddSubtract, it would take n^2/p as the matrix will contain n*n elements, again distributed
  over the processors

  for matrixTranspose, it would only be n, as it is fully sequential and only has to swap
  corresponding elements

  For matrixMultiply, it would take n^3/p as the dot product of each row and column needs to
  be calculated in order to calculate the element in each index

b) Adding more nodes does not perfectly divide the program, as the overhead from communication
typically overtakes some of the performance gain from using the nodes

c) Some real world applications would be, for example, biological research in order to track
predator prey models through matrix multiplication, they would greatly benefit from distributed
code due to the large amount of data that must be processed for accurate models

d) Overall, the code is very un-modular, it is not capable of functioning outside the context
  of the program it is currently running it. Once it is modularized then the program will be
  much more usable in other context rather than just testing time performance and theoretical
  usability
