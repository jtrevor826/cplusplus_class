/*
 * main.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: Family
 */

#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char *argv[]){

  ifstream inFile;
  ofstream outFile;

  string originalFileName;
  string data;

  cout << "What file needs to be copied? ";
  cin >> originalFileName;
  cout <<endl;

  outFile.open("CopyOf.txt");
  if(outFile){
  	inFile.open(originalFileName.c_str(), std::fstream::in);
  	if (inFile){
    	inFile >> data;
  		while( !inFile.fail()){
    		cout << data <<endl;
        	inFile >> data;
            outFile << data;
  		}
  	}
  }
  inFile.close();
  outFile.flush();
  outFile.close();



}
