#include <iostream>
#include "message.h"

int main(int argc, char *argv[]) {
  Message msg1("email"), msg2("book");
  Folder folder("private");

  msg1.saveTo(folder);
  msg2.saveTo(folder);

  Message msg3 = msg1;
  msg3 = msg2;

  return 0;
}