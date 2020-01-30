README

Matrix multiplication fix
Gauss Jordan Algorithm
Inverse Matrix Algorithm

Matrix multiplication fix)

As it turns out, the original approach for the matrix multiplication algorithm performed quite poorly (much more than that of a sequential implementation)
This, and matrix multiplication would block if the size of n was too large. These issues have been fixed.

The causes for these issues was the fact that the original implementation was not true parallel. Instead, the root node was not properly sending to the
other nodes, and as a result, was forced to do a majority of the work. This is because the amount of memory allocated for each node, which would hold a portion
of the matrix, was not of the correct size.

In the new implementation, all nodes allocate without permission of the node, ensuring that each node can properly store its section of the matrix. The results of the
new implementation have shown to be far superior.

Running the program is the same procedure as the last implementation.


Gauss Jordan Algorithm / Inverse)

The Gauss Jordan algorithm takes two inputs, the width and length of the randomly generated matrix that will be reduced to pivot positions. The algorithm works by distributing
the number of rows across the number of nodes, and collecting all the results of each operation after each row reduction operation. The root node then takes each reduced row,
and recombines it into a single, row reduced, augmented matrix

The Inverse matrix algorithm uses the Gauss Jordan implementation, however appends the identity matrix prior to utilizing Gauss Jordan.
