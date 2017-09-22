#include <iostream>
#include <vector>

using namespace std;

typedef void Fn(int);
void A(int a){
  cout<<"A"<<endl;
}
void B(int a){
  cout<<"B"<<endl;
}

int main(int argc,char* argv[]){

  cout<<"Test clguiObject"<<endl;

  Fn* a=&A;
  a(10);
  a=&B;
  a(10);



  system("pause");
  return EXIT_SUCCESS;
}