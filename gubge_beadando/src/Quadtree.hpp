/*
 * Quadtree.hpp
 *
 *  Created on: 2015. nov. 6.
 *      Author: Gerike
 */

#ifndef QUADTREE_HPP_
#define QUADTREE_HPP_
#include <vector>

class Quadtree{
	struct node {


	    node* child_1,*child_2,*child_3,*child_4,*parent;
	    points key;
	    node (const points &k,node*p): child_1(0), child_2(0),child_3(0),child_4(0),
	    		parent(p),key(k){};
	    node ():child_1(0), child_2(0),child_3(0),child_4(0),parent(0),key(){};


	};

 	node* root;
 	void _destroy (node* x);
public:
 	std::vector<points> get_next(const points key);
    void insert(const points &key);

    Quadtree(int a,int b,int c,int d){
    	points k(a,b,c,d);

    	node* x=new node(k,nullptr);
    			root=x;



    set_children(x);



    			/*

    			points p;
    			node* r_1=new node(p,x);
    			x->child_1=r_1;
    			node* r_2=new node(p,x);
    			x->child_2=r_2;
    			node* r_3=new node(p,x);
    			x->child_3=r_3;
    			node* r_4=new node(p,x);
    			x->child_4=r_4;

    			        x->child_1->key.set_first(x->key.x_from,x->key.x_to,x->key.y_from,x->key.y_to);
    					x->child_2->key.set_second(x->key.x_to,x->key.y_from,x->key.y_to);
    					x->child_3->key.set_third(x->key.x_from,x->key.x_to,x->key.y_to);
    					x->child_4->key.set_fourth(x->key.x_to,x->key.y_to);
   */
    };
    ~Quadtree(){ _destroy(root);};
     void set_children(node* x);
     void _insert(const points &k, node* x);

};







void Quadtree::set_children(node* x){
	                points p;
	    			node* r_1=new node(p,x);
	    			x->child_1=r_1;
	    			node* r_2=new node(p,x);
	    			x->child_2=r_2;
	    			node* r_3=new node(p,x);
	    			x->child_3=r_3;
	    			node* r_4=new node(p,x);
	    			x->child_4=r_4;

	    			        x->child_1->key.set_first(x->key.x_from,x->key.x_to,x->key.y_from,x->key.y_to);
	    					x->child_2->key.set_second(x->key.x_to,x->key.y_from,x->key.y_to);
	    					x->child_3->key.set_third(x->key.x_from,x->key.x_to,x->key.y_to);
	    					x->child_4->key.set_fourth(x->key.x_to,x->key.y_to);

}



void Quadtree::insert(const points & k){
	_insert(k,root);
}












void Quadtree::_insert(const points & k, node * n){
	bool z=true;



	node* temp=n;




	while (z){
		if (!temp->child_1->key && !(temp->child_1->key<k)){         //1. ures,2.nal kisebb

			temp->child_1->key.shape=points::point;
			temp->child_1->key.x=k.x;
			temp->child_1->key.y=k.y;
			z=false;
			//std::cout<<"itt vok1"<<"pont: "<<k.x<<" - "<<k.y<<std::endl;

		}


		else if (!temp->child_2->key && !(temp->child_2->key<k) && temp->child_1->key<k){
			            temp->child_2->key.shape=points::point;
						temp->child_2->key.x=k.x;
						temp->child_2->key.y=k.y;
					z=false;
					//std::cout<<"itt vok2"<<std::endl;
				}

		else if (!temp->child_3->key && !(temp->child_3->key<k) && temp->child_2->key<k){
						temp->child_3->key.shape=points::point;
						temp->child_3->key.x=k.x;
						temp->child_3->key.y=k.y;

							z=false;
						//	std::cout<<"itt vok3"<<std::endl;
						}
		else if (!temp->child_4->key &&  temp->child_3->key<k){
						temp->child_4->key.shape=points::point;
						temp->child_4->key.x=k.x;
						temp->child_4->key.y=k.y;
							z=false;


						}                                               //ures helyre bekotes lerendezve


		else if (temp->child_1->key==k){
			temp=temp->child_1;
			//std::cout<<"itt vok5"<<std::endl;
		}



		else if (temp->child_2->key==k){
					temp=temp->child_2;
				//	std::cout<<"itt vok6"<<std::endl;
				}

		else if (temp->child_3->key==k){
					temp=temp->child_3;
			//		std::cout<<"itt vok7"<<std::endl;
				}


		else if (temp->child_4->key==k){
					temp=temp->child_4;
				//	std::cout<<"itt vok8"<<std::endl;
				}

                                              //tovabbmentem rect menten

		else if (!(temp->child_1->key<k) && temp->child_1->key.shape==points::point){            //1.re kellene illeszteni de az pont a.eset
		//	std::cout<<"itt vok9"<<std::endl;
			points p=temp->child_1->key;


			temp->child_1->key=temp->child_1->key++;
            set_children(temp->child_1);
            _insert(p,temp->child_1);

			temp=temp->child_1;
		//	std::cout<<temp->key.x_to<<" - "<<temp->key.y_to<<std::endl;

		}


		else if (temp->child_1->key<k && !(temp->child_2->key<k && temp->child_2->key.shape==points::point)){  //2.ra kellene de az pont

			points p=temp->child_2->key;

			        temp->child_2->key=temp->child_2->key++;
					set_children(temp->child_2);
			        _insert(p,temp->child_2);
			        temp=temp->child_2;
				//	std::cout<<"itt vok10"<<std::endl;
				}

		else if (temp->child_2->key<k && !(temp->child_3->key<k) && temp->child_3->key.shape==points::point){  //3.ra kellene

			points p=temp->child_3->key;

							temp->child_3->key=temp->child_3->key++;
							set_children(temp->child_3);
							_insert(p,temp->child_3);
							temp=temp->child_3;
					//		std::cout<<"itt vok11"<<std::endl;
						}

		else if (temp->child_3->key<k && temp->child_4->key.shape==points::point){              //4.re kellene

			points p=temp->child_4->key;

							temp->child_4->key=temp->child_4->key++;
							set_children(temp->child_4);
							_insert(p,temp->child_4);
							temp=temp->child_4;
					//		std::cout<<"itt vok12"<<std::endl;
						}


	}


}



void Quadtree:: _destroy(node * x){
delete x;
	/*
 if (x!=x->child_1 && x){
	 _destroy (x->child_1);
	 _destroy (x->child_2);
	 _destroy (x->child_3);
	 _destroy (x->child_4);
	 delete x;
 }
*/
}





#endif /* QUADTREE_HPP_ */
