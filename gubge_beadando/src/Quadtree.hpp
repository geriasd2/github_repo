/*
 * Quadtree.hpp
 *
 *  Created on: 2015. nov. 9.
 *      Author: Gerike
 */

#ifndef QUADTREE_HPP_
#define QUADTREE_HPP_
#include <vector>
#include "points.hpp"
#include "stdlib.h"
#include "pqueue.hpp"
#include "gyakorlatilag_felesleges.hpp"


class Quadtree{
	struct node {


	    node* child_1,*child_2,*child_3,*child_4,*parent;
	    std::vector <points> key;
	    unsigned int osztodas;
	    bool rect;
	    double x,y,x_length,y_length;
	    node (node*p,double a,double b,double c,double d): child_1(nullptr), child_2(nullptr),child_3(nullptr),child_4(nullptr),
	    		parent(p),osztodas(0),rect(false),x(a),y(b),x_length(c),y_length(d){};
};



 	node* root;

 	std::ostream& _bejaras(std::ostream &o, const node*x);
 	std::vector<node*> _bejaras_2(std::vector<node*> &v, node* x);
 	double distance (const points k,const node* n);
 	double distance (const points k,const points k1);
 	double meroleges(const points k,const node*n);
    std::vector <rect> _bejaras_3(std::vector <rect> &v ,  node *x);  //gyakorlatilag semmi értelme csak a kimeneti rect miatt

public:

 	std::ostream&  bejaras(std::ostream &o);
    void insert(const points &k);
    std::vector<points> kFind(const points k,int  i);
    std::vector<rect> bejaras_3(std::vector <rect> &v);     //gyakorlatilag semmi értelme csak a kimeneti rect miatt






   void robbantas(node* x);

   bool check(const node* x,const points k);


    Quadtree(double a,double b,double c,double d){


    	node* x=new node(nullptr,a,b,c,d);
    			root=x;
};







};



// program működésében nem játszik szerepet innentől

std::vector<rect> Quadtree:: bejaras_3(std::vector<rect>& v){
	v=_bejaras_3(v,root);
	return v;
}



std::vector <rect>Quadtree:: _bejaras_3(std::vector<rect>& v,node* x){
	rect tmp;
	tmp.pont.x=x->x;
	tmp.pont.y=x->y;
	tmp.height=tmp.width=x->x_length;

		v.push_back(tmp);



	if (x->child_1!=0){
	_bejaras_3(v,x->child_1);
	}
	if (x->child_2!=0){
	_bejaras_3(v,x->child_2);
	}
	if (x->child_3!=0){
	_bejaras_3(v,x->child_3);
	}
	if (x->child_4!=0){
	_bejaras_3(v,x->child_4);
	}






	return v;
}



// idáig






std::vector<Quadtree::node*> Quadtree::_bejaras_2(std::vector<node*>&v, node*x){

if (x->key.size()!=0){
	v.push_back(x);
}


if (x->child_1!=0){
_bejaras_2(v,x->child_1);
}
if (x->child_2!=0){
_bejaras_2(v,x->child_2);
}
if (x->child_3!=0){
_bejaras_2(v,x->child_3);
}
if (x->child_4!=0){
_bejaras_2(v,x->child_4);
}






return v;
}




double Quadtree::meroleges (const points k,const node*n){

	if (n->x<k.x && n->x+n->x_length>k.x && n->y<k.y && n->y+n->y_length> k.y){
		return 0;
	}



	if (n->x<k.x && n->x+n->x_length>k.x){
		if (k.y>n->y){
			return k.y-n->y-n->y_length;
		}
		if (k.y<n->y){
			return n->y-k.y;
		}
	}

	if (n->y<k.y && n->y+n->y_length>k.y){
		if (k.x>n->x){
			return k.x-n->x-n->x_length;
		}
		if (k.x<n->x){
			return n->x-k.x;
		}
	}


return 0;



}




double Quadtree::distance (const points k1,const points k2){



	return sqrt((k1.x-k2.x)*(k1.x-k2.x)+(k1.y-k2.y)*(k1.y-k2.y));
}




double Quadtree::distance (const points k,const node* n){
	if (meroleges(k,n)){
		return meroleges(k,n);
	}
	else if (n->x<k.x && n->x+n->x_length>k.x && n->y<k.y && n->y+n->y_length> k.y){
			return 0;
		}

	else{

		points tmp0,tmp1,tmp2,tmp3;
		tmp0.x=n->x;
		tmp0.y=n->y;
		tmp1.x=n->x+n->x_length;
		tmp1.y=n->y;
		tmp2.x=n->x;
		tmp2.y=n->y+n->y_length;
		tmp3.x=n->x+n->x_length;
		tmp3.y=n->y+n->y_length;
		std::vector <double>dist;
		dist.push_back(distance(k,tmp0));
		dist.push_back(distance(k,tmp1));
		dist.push_back(distance(k,tmp2));
		dist.push_back(distance(k,tmp3));

		double min=dist[0];
		unsigned int pos=0;
		for (unsigned int i=1;i<4;i++){
			if (dist[i]<min){
				min=dist[i];
				pos=i;
			}
		}

return dist[pos];
	}


}








std::vector<points>Quadtree::kFind(const points p, int k){



	std::vector <points> solution;

	PriorityQueue <points> q;

	std::vector <node*> leafs;


	leafs=_bejaras_2(leafs,root);


	for (unsigned int i=0;i<leafs.size();i++){
		points sign(i,100);
		q.push(sign,-distance(p,leafs[i]));
	}




	while (0<k){
		points sign=q.top();
		q.pop();
		if (sign.y==100){
			for (unsigned int j=0;j<leafs[sign.x]->key.size();j++){
				points sign_2(sign.x,j);
				q.push(sign_2,-distance(p,leafs[sign.x]->key[j]));
			}




		}


			else {
				solution.push_back(leafs[sign.x]->key[sign.y]);
				k--;
			}

		}

	return solution;
	}



























bool Quadtree::check (const node* temp,const points k){




	 for (unsigned int i=0;i<temp->key.size();i++){
	        			 if (temp->key[i].x==k.x && temp->key[i].y==k.y){

	        				 return false;

	        			 }
	 }

		return true;
}











std::ostream& Quadtree::_bejaras(std::ostream& o, const node* x){

		o<<x->x<<" "<<x->y<<" "<<x->x_length<<" "<<x->y_length<<" ";





o<<std::endl;


if (x->child_1!=0){
	_bejaras(o,x->child_1);
}
if (x->child_2!=0){
	_bejaras(o,x->child_2);
}
if (x->child_3!=0){
	_bejaras(o,x->child_3);
}
if (x->child_4!=0){
	_bejaras(o,x->child_4);
}



return o;
}

std::ostream& Quadtree::bejaras(std::ostream &o){
	return (_bejaras(o,root));
}







void Quadtree::robbantas(node *x){
	x->rect=true;


	node* new_child_1=new node(x,x->x,x->y,x->x_length/2,x->y_length/2);
	node* new_child_2=new node(x,x->x+x->x_length/2,x->y,x->x_length/2,x->y_length/2);
	node* new_child_3=new node(x,x->x,x->y+x->y_length/2,x->x_length/2,x->y_length/2);
	node* new_child_4=new node(x,x->x+x->x_length/2,x->y+x->y_length/2,x->x_length/2,x->y_length/2);
	  new_child_1->osztodas=x->osztodas+1;
	  new_child_2->osztodas=x->osztodas+1;
	  new_child_3->osztodas=x->osztodas+1;
	  new_child_4->osztodas=x->osztodas+1;





	x->child_1=new_child_1;
	x->child_2=new_child_2;
	x->child_3=new_child_3;
	x->child_4=new_child_4;


	for (unsigned int i=0;i<x->key.size();i++){
		if (x->key[i].x<x->x+x->x_length/2 && x->key[i].y<x->y+x->y_length/2){
			x->child_1->key.push_back(x->key[i]);
		}

		else if (x->key[i].x<x->x+x->x_length && x->key[i].y<x->y+x->y_length/2){
			x->child_2->key.push_back(x->key[i]);
		}

		else if (x->key[i].x<x->x+x->x_length/2 && x->key[i].y<x->y+x->y_length){
			x->child_3->key.push_back(x->key[i]);
		}
		else {
			x->child_4->key.push_back(x->key[i]);
		}
	}

	x->key.clear();



}





















void Quadtree::insert(const points &k){

	node* temp=root;
	bool z=true;
	while (z){
         if (!(temp->rect)){
        	 if (temp->key.size()<20){
        		 if (check(temp,k)){
        		 temp->key.push_back(k);


        		 }
        		 else {return;}

        		 z=false;


        	 }


        	 else {
                   if (check(temp,k)){
                	   if (temp->osztodas<20){
                	   robbantas(temp);}
                	   else {
                		   temp->key.push_back(k);
                		   return;
                	   }

                   }
                   else {return;}


        	 }
         }



         else {


        	 if (k.x<(temp->x+temp->x_length/2) && k.y<(temp->y+temp->y_length/2)){
        		 temp=temp->child_1;
        	 }
        	 else if (k.x<(temp->x+temp->x_length) && k.y<(temp->y+temp->y_length/2)){
        		 temp=temp->child_2;
        	 }
        	 else if (k.x<(temp->x+temp->x_length/2) && k.y<(temp->y+temp->y_length)){
        		 temp=temp->child_3;

        	 }
        	 else  {
        		 temp=temp->child_4;

        	 }
         }



	}


}











#endif /* QUADTREE_HPP_ */
