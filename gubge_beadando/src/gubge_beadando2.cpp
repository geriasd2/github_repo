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








void write (vector <points>&v, std::ofstream&f1,const points k){


	for (unsigned int i=0;i<v.size();i++){
	points temp=v[i];
		f1<<sqrt((k.x-temp.x)*(k.x-temp.x)+(k.y-temp.y)*(k.y-temp.y))<<endl;
	}
}







int main() {

	Quadtree tree(0,0,500,500);

	ifstream f("points.txt");
	vector <points> v=read(f);
	f.close();




	for (unsigned int i=0;i<v.size();i++){

		points p=v[i];
	tree.insert(p);




}

	ofstream f2("rect.txt",std::ofstream::out);

tree.bejaras(f2);

points tmp(30,50);
vector <points> v2;


v2=tree.kFind(tmp,10);


for (unsigned int i=0;i<v2.size();i++){
	cout<<v2[i].x<<" - "<<v2[i].y<<endl;
}





	return 0;
}
