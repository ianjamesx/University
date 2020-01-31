
// FILE:  Zoo.cpp
// IMPLEMENTATION FILE FOR CLASS Zoo


#include "Zoo.h"

// Pre: none
// Post: owner's name has been initialized to "Nobody".
//       count is set to 0.
//       cage pointer is set to NULL.

Zoo :: Zoo(){

     owner = "Nobody";
     count = 0;
     cage = NULL;

}

// Pre: none
// Post: owner's name has been initialized to the string you give it.
//       count is set to 0.
//       cage pointer is set to NULL.
Zoo :: Zoo( string n ){

  owner = n;
  count = 0;
  cage = NULL;

}


// Pre: none
// Post: returns owner's name

string Zoo :: name(){

  return owner;

}


// Pre: none
// Post: Zoo Object has been initialized as an exact copy of z.

Zoo :: Zoo(const Zoo& z) {

  owner = z.owner;
  count = z.count;
  cage = new string[count];

  int i;

  for(i = 0; i < count; i++){

    cage[i] = z.cage[i];

  }

}

// Pre: none
// Post: Copied all animals to self. Does not change owner.
void Zoo :: operator=(const Zoo& z){

  count = z.count;
  cage = new string[count];

  int i;

  for(i = 0; i < count; i++){

    cage[i] = z.cage[i];

  }

}

// Pre: none
// Post: returns an object of Zoo with same owner and animals of z,
//       animal a added to the end.

Zoo operator+(const Zoo& z, string a){ // FRIEND FUNCTION

  Zoo tempZoo(z.owner);

  //we will be adding one animal to the end

  tempZoo.count = z.count + 1;
  tempZoo.cage = new string[tempZoo.count];

  int i;

  for(i = 0; i < z.count; i++){

    //copy last array

    tempZoo.cage[i] = z.cage[i];

  }

  //add param a to the last index
  //last index will be the length of the cage array of the previous object (the z.count member)

  tempZoo.cage[z.count] = a;

  return tempZoo;

}

// Pre: none
// Post: prints out z's contents (animal1, animal2, etc.),
//       and returns out stream.
ostream& operator<<(ostream& out, const Zoo& z){ // FRIEND FUNCTION

   out << z.owner << "'s" << " Zoo " << '(' << z.count << " animals "
       << ')' << ':' <<endl;

   for(int i = 0; i < z.count; i++){

      out<< z.cage[i];
      out<< endl;

   }

   return out;

}


//Pre: none
//Post: the memory of cage has been released.
Zoo :: ~Zoo(){

  delete [] cage;

}

// Pre: none
// Post: returns true if animal a is in Zoo z.
//       the owner does not count as an animal.

bool operator<=(string a, const Zoo& z){ // FRIEND FUNCTION

  int i;

  for(i = 0; i < z.count; i++){

    if(z.cage[i] == a){

      return true;

    }

  }

  return false;

 }

//Pre:  none
//Post: returns an object of Zoo with same owner and animals of z,
//      animal a added to the end.

Zoo operator+(string a, const Zoo& z){ // NONMEMBER FUNCTION

  //since we cant access the z object's members directly (this is a nonmember function)
  //just switch the order of the operands to call the friend function

  return z + a;

}

//Pre: none
//Modifies: z
//Post: z has same animals and owner, animal a added to the end.
void operator+=(Zoo& z, string a){ // NONMEMBER FUNCTION

    z = z + a;

}
