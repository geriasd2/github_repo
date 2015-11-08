//============================================================================
// Name        : gubge_beadando.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "points.hpp"
#include "Quadtree.hpp"
#include <fstream>
#include <sstream>
using namespace std;








/*
struct points{
	enum _ures {igen,nem};
int a,b;
_ures ures;
points():a(1),b(2),ures(igen){};

points &operator +(const points &k){
	a+=k.a;
	b+=k.b;
	return *this;

}
void set_ures_true(){
	ures=igen;
}

void set_ures_false(){
	ures=nem;
}

inline bool operator <(const points &k){
if (a<k.a && b<k.b){
	return true;
}
else
	return false;}


inline bool operator !(){

if (ures==igen){
	return true;}
else{
	return false;}



}




};

int main() {


	points a,b;
a.set_ures_true();
b.set_ures_true();

a+b;
cout<<a.a<<endl<<a.b;
bool h=a<b;
cout<<endl<<h;


	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}





ifstream f("points.txt");
unsigned int sum=0;
unsigned int min=3;
unsigned int max=18;
while (f.good()){
	stringstream ss;
	string s;
	f>>s;
	ss<<s;
	unsigned int temp;
	ss>>temp;
	if (temp<min)
		min=temp;
	if (temp>max)
		max=temp;

	sum++;

}
cout<<"szumma: "<<sum/2<<endl<<"min: "<<min<<endl<<"max: "<<max;





*/

std::vector <points> read (std::ifstream &f,int a,int b,int c,int d){
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


points temp(temp_x,temp_y,a,b,c,d);
v.push_back(temp);
}







return v;
}



int main() {

Quadtree fa(0,500,0,500);

points p(32,100,0,500,0,500);

points c(10,15,0,500,0,500);

//c.set_first(10,20,30,40);

/*

fa.insert(p);
fa.insert(c);

*/


ifstream f("points.txt");
vector <points> v=read(f,0,500,0,500);






for (unsigned int i=0;i<v.size();i++){

	points p=v[i];
fa.insert(p);
cout<<i<<endl;
}



















	return 0;
}
