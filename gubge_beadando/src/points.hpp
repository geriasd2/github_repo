/*
 * points.hpp
 *
 *  Created on: 2015. nov. 7.
 *      Author: Gerike
 */
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#ifndef POINTS_HPP_
#define POINTS_HPP_
struct points{

	int x,y,x_from,x_to,y_from,y_to;
	enum _shape {rect,point,free};
	_shape shape;
public:
	points (int a,int b,int c,int d,int e,int f): x(a),y(b),x_from(c),x_to(d),y_from(e),y_to(f),shape(point){};
    points (): x(0),y(0),x_from(0),x_to(0),y_from(0),y_to(0),shape(free){};
    points (int a,int b,int c,int d): x(0),y(0),x_from(a),x_to(b),y_from(c),y_to(d),shape(rect){};



	points &operator ++(int){

		shape=rect;
		return *this;
	}

	inline bool operator <(const points &p){
		if (x_to<p.x || y_to<p.y){
			return true;
		}
		else
			return false;
	}

    inline bool operator !(){
    	if (shape==free){
    		return true;
    	}
    	else
    		return false;
    }

   inline bool operator ==(const points p){
          if (shape==rect && x_from<=p.x && p.x<=x_to && y_from<=p.y    && p.y<=y_to){
        	  return true;
          }
          else
        	  return false;
   }




void set_first(int a,int b,int c,int d){
    x_from=a;
	x_to=b/2;
	y_from=c;
	y_to=d/2;

}




void set_second(int a,int b,int c){
	x_from=a/2;
	x_to=a;
	y_from=b;
	y_to=c/2;
}



void set_third(int a,int b,int c){
x_from=a;
x_to=b/2;
y_from=c/2;
y_to=c;
}

void set_fourth(int a,int b){
	x_from=a/2;
	x_to=a;
	y_from=b/2;
	y_to=b;
}






};




#endif /* POINTS_HPP_ */
