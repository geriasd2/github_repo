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
class Quadtree{
	struct node {


	    node* child_1,*child_2,*child_3,*child_4,*parent;
	    std::vector <points> key;
	    bool rect;
	    double x,y,x_length,y_length;
	    node (node*p,double a,double b,double c,double d): child_1(nullptr), child_2(nullptr),child_3(nullptr),child_4(nullptr),
	    		parent(p),rect(false),x(a),y(b),x_length(c),y_length(d){};
};



 	node* root;

 	std::ostream& _bejaras(std::ostream &o, const node*x);
 	std::vector<node*> _bejaras_2(std::vector<node*> &v, node* x);

public:
 	std::ostream&  bejaras(std::ostream &o);
    std::vector <node*> find_neighbors(const points &k);
    std::vector <points> find_nearest_neighbors(const points &k, unsigned int n );
    node* find_insert(const points &k);
    void insert(const points &k);





    std::vector<node*>  bejaras_2(std::vector<node*> &v);

   void robbantas(node* x);

   bool check(const node* x,const points k);


    Quadtree(double a,double b,double c,double d){


    	node* x=new node(nullptr,a,b,c,d);
    			root=x;
};



 //   ~Quadtree(){ _destroy(root);};



};






std::vector<points> Quadtree::find_nearest_neighbors(const points &k,unsigned int n){

std::vector<Quadtree::node*> v=find_neighbors(k);
std::vector<points> v_2;
std::vector<int> tmp;

for (unsigned int i=0;i<n;i++){
	int mintav=(k.x-v[0]->key[0].x*k.x-v[0]->key[0].x+k.y-v[0]->key[0].y*k.y-v[0]->key[0].y);
	int pos1=0;
	int pos2=0;
	for (unsigned int j=0;j<v.size();j++){
		for (unsigned int k=0;k<v[j]->key.size();k++){
			if (mintav>v[j]->key[k].x*v[j]->key[k].x+v[j]->key[k].y*v[j]->key[k].y){
				mintav=v[j]->key[k].x*v[j]->key[k].x+v[j]->key[k].y*v[j]->key[k].y;
				pos1=j;
				pos2=k;
			}
		}
	}

	v_2.push_back(v[pos1]->key[pos2]);
}




return v_2;
}








std::vector<Quadtree::node*> Quadtree::bejaras_2(std::vector<node*>&v){


	return _bejaras_2(v,root);
}


std::vector<Quadtree::node*> Quadtree::_bejaras_2(std::vector<node*>&v, node*x){



if (x->rect){
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




std::vector<Quadtree::node*> Quadtree::find_neighbors(const points &k){

	std::vector <node*> v;
	bejaras_2(v);


    std::vector<node*> v_3;
    v_3.push_back(find_insert(k));


    for (unsigned int i=0;i<v.size();i++){
       if (       (v_3[0]->x<v[i]->x && ((v_3[0]->x+v_3[0]->x_length)>v[i]->x )) || (v_3[0]->y<v[i]->y && ((v_3[0]->y+v_3[0]->y_length)>v[i]->y))){
    	   v_3.push_back(v[i]);
       }
    }







return v_3;
}






Quadtree::node* Quadtree::find_insert(const points &k){

	node* temp=root;

	while (temp->rect){

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









return temp;
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
//std::cout<<x->x<<" "<<x->y<<std::endl;

	node* new_child_1=new node(x,x->x,x->y,x->x_length/2,x->y_length/2);
	node* new_child_2=new node(x,x->x+x->x_length/2,x->y,x->x_length/2,x->y_length/2);
	node* new_child_3=new node(x,x->x,x->y+x->y_length/2,x->x_length/2,x->y_length/2);
	node* new_child_4=new node(x,x->x+x->x_length/2,x->y+x->y_length/2,x->x_length/2,x->y_length/2);



      //  std::cout<<new_child_1->x<<" "<<new_child_1->y<<"  "<<new_child_1->x_length<<" "<<new_child_1->y_length<<std::endl;

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
                	   robbantas(temp);

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
