/*
  Pointers.cpp
  COSC-220 Lab 9
  Based on a lab designed by Thomas Horseman

  Thomas Anastasio
  Created: April 8, 2001
  Current: March 20, 2003
*/

#include <iostream>
#include <stddef.h>     // for NULL definition

int main()
{
  using namespace std;

  int int1 = 1, int2 = 2, int3 = 3;
  double dub1 = 1.0, dub2 = 2.0, dub3 = 3.0;
  float flt1 = 1.0f;
  char chr1 = 'a', chr2 = 'b';

  //////////////////////////////////////////////////////////////////
  // 1. Experiment with storage sizes and addresses of various data
  // types.
  //////////////////////////////////////////////////////////////////
  //  A.  Add statements to print the addresses of each of the 9
  //  variables declared above and record the addresses.
  //  B.  Add statements to print the sizes (in bytes) of each of the
  //  9 variables  (use the sizeof operator).
  //  C.  Add statements to print the sizes of the addresses of the 9
  //  variables (again, use the sizeof operator).

  //  Write your code here:
  
  cout << "\n\n";

  cout << &int1 << " - " << &int2 << " - " << &int3 << endl;
  cout << &dub1 << " - " << &dub2 << " - " << &dub3 << endl;
  cout << &flt1 << " - " << &chr1 << " - " << &chr2 << endl;

  cout << "\n";

  cout << sizeof int1 << " - " << sizeof int2 << " - " << sizeof int3 << endl;
  cout << sizeof dub1 << " - " << sizeof dub2 << " - " << sizeof dub3 << endl;
  cout << sizeof flt1 << " - " << sizeof chr1 << " - " << sizeof chr2 << endl;

  cout << "\n";

  cout << sizeof &int1 << " - " << sizeof &int2 << " - " << sizeof &int3 << endl;
  cout << sizeof &dub1 << " - " << sizeof &dub2 << " - " << sizeof &dub3 << endl;
  cout << sizeof &flt1 << " - " << sizeof &chr1 << " - " << sizeof &chr2 << endl;

  cout << "-----------------------------------------" << endl << endl;

  // Record your results here:
  //
  //  Variable  Size   Address   Address-Size
  //   int1     4      0x7ffee2cd9a48     8
  //   int2     4      0x7ffee2cd9a44     8
  //   int3     4      0x7ffee2cd9a40     8
  //   dub1     8      0x7ffee2cd9a38     8
  //   dub2     8      0x7ffee2cd9a30     8
  //   dub3     8      0x7ffee2cd9a28     8
  //   flt1     4      0x7ffee2cd9a24     8
  //   chr1     1      a                  8
  //   chr2     1      b                  8


  // How many bytes of storage is allocated for each data type?  How
  // many bytes is allocated for each pointer (address). Notice that
  // the data types are not necessarily the same size, but the
  // pointers are.

  /*

    ints: 4 bytes
    doubles: 8 bytes
    floats: 4 bytes
    characters: 1 bytes

    pointers (addresses): 8 bytes

  */

  //
  // Did the address of the char variables print as you expected?  If
  // not, why not?   You can force the printed output to be
  // interpreted as a pointer by coercing it (casting) to void* like
  // this:
  //    cout << (void *) &chr1;
  //
  // Run the program again, using the coercion for the char
  // pointers. Record your data.

  // Write your modified code here:

  cout << "modifed code for char address coercion: \n" << endl;

  cout << &int1 << " - " << &int2 << " - " << &int3 << endl;
  cout << &dub1 << " - " << &dub2 << " - " << &dub3 << endl;
  cout << &flt1 << " - " << (void *) &chr1 << " - " << (void *) &chr2 << endl;


  cout << "-----------------------------------------" << endl << endl;


  // Record your results here:
  //
  //  Variable  Size   Address   Address-Size
  //     chr1   1      0x7ffee9714a23     8
  //     chr2   1      0x7ffee9714a22     8

  //////////////////////////////////////////////////////////////////
  // 2. Experiment with pointer variables.
  //////////////////////////////////////////////////////////////////
  //   A. Declare pointer vaiables intPtr1, intPtr2, intPtr3, dubPtr1,
  //   dubPtr2, dubPtr3, fltPtr1, chrPtr1, and chrPtr2 so that they
  //   can be used to point to the  appropriate variables.  Assign the
  //   address of the appropriate variable to them and print their
  //   values.  (The char pointers will have to be coerced as before
  //   for printing).

  //  Write your code here:

  int * intPtr1;
  int * intPtr2;
  int * intPtr3;
  double * dubPtr1;
  double * dubPtr2;
  double * dubPtr3;
  float * fltPtr1;
  char * chrPtr1;
  char * chrPtr2;

  intPtr1 = &int1;
  intPtr2 = &int2;
  intPtr3 = &int3;

  dubPtr1 = &dub1;
  dubPtr2 = &dub2;
  dubPtr3 = &dub3;

  fltPtr1 = &flt1;
  chrPtr1 = &chr1;
  chrPtr2 = &chr2;

  cout << intPtr1 << " - " << intPtr2 << " - " << intPtr3 << endl;
  cout << dubPtr1 << " - " << dubPtr2 << " - " << dubPtr3 << endl;
  cout << fltPtr1 << " - " << (void *)chrPtr1 << " - " << (void *)chrPtr2 << endl;

  cout << "\n";

  cout << "-----------------------------------------" << endl << endl;

  //  Report your results here:
  //
  //   Pointer  Printed
  //  Variable   Value
  //   intPtr1   0x7ffee8e6c9c0
  //   intPtr2   0x7ffee8e6c9bc
  //   intPtr3   0x7ffee8e6c9b8
  //   dubPtr1   0x7ffee8e6c9b0
  //   dubPtr2   0x7ffee8e6c9a8
  //   dubPtr3   0x7ffee8e6c9a0
  //   fltPtr1   0x7ffee8e6c99c
  //   chrPtr1   0x7fffa9e9ac53
  //   chrPtr2   0x7fffa9e9ac52

  // How do the values of the pointers compare to the values of the
  // addresses you got in the previous experiment?

  /*

  the pointers are the same as the addresses from the last experiment

  */

  //////////////////////////////////////////////////////////////////
  //  3. Experiments with NULL pointers and with dereferencing
  //////////////////////////////////////////////////////////////////
  //   A. Assign NULL to fltPtr1, then print the value of fltPtr1.
  //   B. Accessing the storage locations through the relevant
  //   pointers, assign the following values and print them.
  //       int1  12
  //       int2  22
  //       dub1  10.1
  //       dub2  20.2
  //       flt1  30.3

  // Write your code here:

  /*
   
    
  fltPtr1 = NULL;

  cout << fltPtr1 << endl;
  
  *intPtr1 = 12;
  *intPtr2 = 22;
  *dubPtr1 = 10.1;
  *dubPtr2 = 20.2;
  *fltPtr1 = 30.3;
  
  */

  // Your program should have terminated with a run-time error.
  // What error was reported?
  //
  // Segmentation fault (core dumped)
  //
  // Why did it occur?
  //
  // i do not have access to the memory of which it is pointing to in the fltPtr1 pointer
  // since it is pointing to a null

  //   C.  Fix the problem and repeat.
  
  //easy fix - comment out the null point
  //OR, you could create a pointee and assign that value to it
  //(doing easy fix for simplicity)

  // Write your code here:
  
  //fltPtr1 = NULL;
 
  cout << fltPtr1 << endl;
  
  *intPtr1 = 12;
  *intPtr2 = 22;
  *dubPtr1 = 10.1;
  *dubPtr2 = 20.2;
  *fltPtr1 = 30.3;

  cout << "-----------------------------------------" << endl << endl;

  //////////////////////////////////////////////////////////////////
  //  4. Experiments with pointer arithmetic
  //////////////////////////////////////////////////////////////////
  //    A.  Print the values of intPtr2, (intPtr2+1) and
  //    (intPtr2-1). Did you get what you expected?

  // Write your code here:

  cout << intPtr2 << endl;
  cout << (intPtr2 + 1) << endl;
  cout << (intPtr2 - 1) << endl;

  cout << "\n";

  // Write your explanation here:
  //
  //the addition to a pointer must
  //increment the memory address rather than the
  //value of which it is pointing to
  //
  //


  //   B. Print the value of intPtr1.
  //   C. Use the increment operator to increment intPtr1.
  //   D. Print the value of intPtr1 again.
  //   E. Print the value of the memory location pointed to by
  //   intPtr1.  Explain what is happening.

  // Write your code here:

  cout << intPtr1 << endl;
  intPtr1++;

  cout << intPtr1 << endl;

  cout << *intPtr1 << endl;


  // Write your explanation here.
  //
  //the memory address must be changing when incrementin
  //the value of the pointer, and points to a different
  //location

  cout << "-----------------------------------------" << endl << endl;


  //////////////////////////////////////////////////////////////////
  //  5. Experiments with dynamic allocation
  //////////////////////////////////////////////////////////////////
  //   A.  Use the new operator to dynamically allocate an integer.
  //   B.  Assign the number 6000 to the new location.
  //   C.  Print the address of this new location.
  //   D.  Print the value stored in the new location.
  //   E.  Comment on the address of the new location compared to the
  //   addresses seen in part 2.

  //  Write your code here:

  int * dynamicInt;

  dynamicInt = new int;

  *dynamicInt = 6000;

  cout << dynamicInt << endl;
  cout << *dynamicInt << endl;
  
  cout << "\n\n";

  //  Write your results and comments here:
  //
  //  new location address = 0x17f3010
  //  contents of new location = 6000

  //  Comment: address and contents of address are not the same
  //

  //  F.  Use the new operator to allocate an array of size 10 of
  //  doubles.  Fill the array with 10.0,20.0,...100.0 and print the array.

  // Write your code here:
  
   double * dynamicArr;
   
   dynamicArr = new double[10];
   
   int i;
   
   for(i = 0; i < 10; i++){
     
     dynamicArr[i] =  i * 10.0;
   
   }
   
   //printing array
   
   for(i = 0; i < 10; i++){
     
     cout << dynamicArr[i] << endl;
     
   }
   

  return 0;
}
