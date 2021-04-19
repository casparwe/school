#include "matris.h"

#include <algorithm>

int main() {

  Matris<int> Matris0;

  Matris<int> Matris01(3);

  std::cout<<"expecting 3x3 with (2,0)=3"<<std::endl;

  Matris0 = Matris01;

  Matris01(1,0) = 2;

  Matris0(2,0) = 3;

  Matris0.print();
  std::cout<<"-------------------"<<std::endl;

  std::cout<<"expecting 3x3 with (1,0) = 2"<<std::endl;

  Matris01.print();

  std::cout<<"-------------------"<<std::endl;

  Matris<int> Matris1(3);

  std::cout<<"expecting empty 3x3"<<std::endl;

  Matris1.print();

  std::cout<<"-------------------"<<std::endl;

  Matris<int> Matris2 = Matris1;

  std::cout<<"expecting empty 3x3"<<std::endl;

  Matris2.print();

  std::cout<<"-------------------"<<std::endl;

  Matris<int> Matris3(Matris2);

  std::cout<<"expecting empty 3x3"<<std::endl;

  Matris3.print();

  std::cout<<"-------------------"<<std::endl;

  Matris1(0,0) = 2;
  Matris1(1,0) = 2;
  Matris1(2,0) = 2;

  Matris2(0,0) = 2;
  Matris2(0,1) = 2;
  Matris2(0,2) = 2;

  Matris1.print();

  Matris2.print();

  std::cout<<"expecting previous added"<<std::endl;

  Matris3 = Matris1 + Matris2;

  Matris1 += Matris2;

  Matris1.print();

  Matris3.print();

  std::cout<<"-------------------"<<std::endl;

  Matris2(1,1) = 3;
  Matris2(2,1) = 3;

  Matris3.print();

  Matris2.print();

  std::cout<<"expecting previous added"<<std::endl;

  Matris1 = Matris3 + Matris2;

  Matris3 += Matris2;

  Matris1.print();

  Matris3.print();

  std::cout<<"-------------------"<<std::endl;

  Matris3.print();

  Matris2.print();

  std::cout<<"expecting previous multiplied in given order"<<std::endl;

  Matris<int> Matris4 = Matris3 * Matris2;

  Matris3 *= Matris2;

  Matris3.print();

  Matris4.print();

  Matris3.reset();

  std::cout<<"-------------------"<<std::endl;

  Matris4.print();

  Matris2(0,0) = 5;
  Matris2(0,1) = 22;
  Matris2(0,2) = 5;

  Matris2.print();

  std::cout<<"expecting 2 subtracted from 1"<<std::endl;

  Matris <int> Matris5 = Matris4 - Matris2;

  Matris4 -= Matris2;

  Matris4.print();

  Matris5.print();

  std::cout<<"-------------------"<<std::endl;

  std::cout<<"expecting previous sorted"<<std::endl;

  std::sort(Matris4.begin(),Matris4.end());

  Matris4.print();

  std::cout<<"-------------------"<<std::endl;

  Matris1.print();

  std::cout<<std::endl;

  std::cout<< Matris1;

  std::cout<<std::endl;

  Matris5.print();

  std::cout<<std::endl;

  std::cout<< Matris5;

  std::cout<<std::endl;

  std::cout<<"-------------------"<<std::endl;

  Matris1.print();

  std::cout<<"expecting empty at row 1"<<std::endl;

  Matris1.insert_row(1);

  Matris1.print();

  std::cout<<"-------------------"<<std::endl;

  Matris1.print();

  std::cout<<"expecting empty at column 1"<<std::endl;

  Matris1.insert_column(1);

  Matris1.print();

  std::cout<<"-------------------"<<std::endl;

  Matris2.print();

  std::cout<<"expecting empty at row 2"<<std::endl;

  Matris2.append_row(1);

  Matris2.print();

  std::cout<<"-------------------"<<std::endl;

  Matris2.print();

  std::cout<<"expecting empty at column 2"<<std::endl;

  Matris2.append_column(1);

  Matris2.print();

  std::cout<<"-------------------"<<std::endl;


  Matris5.print();

  std::cout<<"expecting remove column 1"<<std::endl;

  Matris5.remove_column(1);

  Matris5.print();

  std::cout<<"-------------------"<<std::endl;


  Matris5.print();

  std::cout<<"expecting remove row 0"<<std::endl;

  Matris5.remove_row(0);

  Matris5.print();

  std::cout<<"-------------------"<<std::endl;


  Matris<int> Matris6({1,2,3,4,5,6,7,8,9});

  Matris6.print();

  std::cout<<"-------------------"<<std::endl;

  Matris<int>::iterator itBegin = Matris4.begin(); //int not T

  Matris<int>::iterator itEnd = Matris4.end();

  for (unsigned int i = 0; itBegin + i < itEnd; i ++){
    std::cout<<*(itBegin + i)<<std::endl;
  }

  std::cout<<"-------------------"<<std::endl;

  Matris2.remove_column(2);

    Matris2.print();

    std::cout<<"expecting transpose"<<std::endl;

    Matris2.transpose();

    Matris2.print();

    std::cout<<"-------------------"<<std::endl;

  Matris<int> Matris8;

  std::cin>>Matris8;
  std::cout<<Matris8;

  Matris8.print();

  return 0;
}
