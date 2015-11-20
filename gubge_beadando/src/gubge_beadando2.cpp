//============================================================================
// Name        : gubge_beadando2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Quadtree.hpp"
#include <fstream>
#include <sstream>
using namespace std;







std::vector <points> read (std::ifstream &f){
std::vector <points> v;
f.clear();
f.seekg(0, std::ios::beg);

while (f.good()){
std::string s;
f>>s;
std::stringstream ss;
ss<<s;
int temp_x,temp_y;
ss>>temp_x;
s.clear();ss.clear();
f>>s;
ss<<s;
ss>>temp_y;


points temp(temp_x,temp_y);
v.push_back(temp);
}


return v;
}













int main() {

	Quadtree tree(0,0,500,500);

	ifstream f("points.txt");
	vector <points> v=read(f);          //pontokat tartalmazo vektor
	f.close();




	for (unsigned int i=0;i<v.size();i++){

		points p=v[i];
	tree.insert(p);




}

	ofstream f2("rect.txt",std::ofstream::out);        //txt-be a rectek

tree.bejaras(f2);

points tmp(30,50);
vector <points> v2;


vector <rect> v4;
v4=tree.bejaras_3(v4);                 //recteket tartalmazo vektor....






v2=tree.kFind(tmp,10);             //knn pontokat tartalmazo vektor


for (unsigned int i=0;i<v2.size();i++){
	cout<<v2[i].x<<" - "<<v2[i].y<<endl;
}





	return 0;
}
