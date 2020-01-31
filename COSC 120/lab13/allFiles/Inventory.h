#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory {

public:
  void getId(int item);
  void getAmount(int num);
  void display();

private:
  int itemNumber;
  int numOfItem;

};

#endif
