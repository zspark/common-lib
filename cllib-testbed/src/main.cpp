#include <iostream>
#include "clHierarchicalStructure.h"
#include "Log.h"
#include "clTypeUtil.h"

using namespace cl;
void TestHS() {
  typedef clHierarchicalStructureNode_T<int> NodeInt;
  typedef clHierarchicalStructure_T<NodeInt> SHInt;

  SHInt sh;
  NodeInt* node=sh.CreateNode();
  node->mCustomObject = 10.0f;
  sh.InsertNode(nullptr, node, clHierarchicalStructureNodeRelation::R_FIRST_CHILD);

  NodeInt* node2 = sh.CreateNode();
  node2->mCustomObject = 1010;
  sh.InsertNode(node, node2, clHierarchicalStructureNodeRelation::R_FIRST_CHILD);


  sh.Print();
  
}


class A {
public:
  A() {}
  ~A() {}

  void Method() {
	 std::cout << "Method in A." << std::endl;
  };

};

class B:public A {
public:
  B(){}
  ~B(){}

  void Method(){
	 std::cout << "Method in B." << std::endl;
  };

};


void TestClass() {
  A* b=new B();
  //static_cast<A>(b).Method();
  b->Method();
}


void TestLog() {
	_LOGSYNCON
		_LOGWITHSYNC("Hello World!")
		Log(Log::LL_ERROR,"lalala");
}




void TestClType() {
	clInt2 int2_1,int2_2;
	int2_1.Set(30);
	clTypeUtil::SetTo<clInt2,clInt>(int2_1,2,3);
	clTypeUtil::CopyAtoB(int2_2,int2_1);
	//clTypeUtil::SetToaa<clInt2,clInt>(int2_1,2,3);
	std::cout<<int2_2.x<<" "<<int2_2.y<<std::endl;

	clFloat3 f1,f2,f3;
	clTypeUtil::SetTo<clFloat3,clFloat>(f1,2.1f,3.0f,4.0f);
	clTypeUtil::CopyAtoB(f3,f1);
	std::cout<<f3.x<<" "<<f3.y<<" "<<f3.z<<std::endl;
	std::cout<<f1.x<<" "<<f1.y<<" "<<f1.z<<std::endl;

	/*
	clInt2 int2;
	clFloat2 float2;
	float2.Set(1.0f,2.4f);
	int2.Copy(float2);
*/
}











int main() {
  std::cout << "Hello World! testbed begin." << std::endl;
  //TestHS();
  //TestClass();
  //TestLog();
	TestClType();
  std::cout << "Hello World! testbed end." << std::endl;
  system("PAUSE");
  return 0;
}