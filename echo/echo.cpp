#include <iostream>

using namespace std;

int main(int argc, char *argv[]){

  if (argc <= 1){
    cout<< "Usage: echo  \"string to echo\" extra extra" << endl;
  }else{
    for (int i =1; i<argc;i++){
    	cout  << argv[i] << " ";
    }
    cout << endl;
  }

  //    https://www.eclipse.org/downloads/packages/
}
