

#include <iostream>
#include "Jscpp.h"

using namespace std;
using namespace jc;

void FunctionDemo(void){

	deque<string> path = PathDeque("fei", "ji", "da", "pao", ":");
	for (int i = 0; i < path.size(); i++){
		cout << path[i] << endl;
	}
}