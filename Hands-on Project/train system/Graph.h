#ifndef Graph_h_
#define Graph_h_


#include<iostream>
using namespace std;

#ifndef MAX_WEIGHT
#define MAX_WEIGHT 1000000  
#endif
const int DefaultVertices=30;


template<class T,class E>
class Graph{
	public:
		const E maxWeight;
		
		Graph(int sz=DefaultVertices):maxWeight(MAX_WEIGHT){}
		~Graph(){}
		bool GraphEmpty()const{
		   if(numEdges==0)return true;
		   else return false;
		}
		bool GraphFull()const{
		       if(numVertices==maxVertices||numEdges==maxVertices*(maxVertices-1)/2)return true;
		       else return false;
		}
		
		int NumberOfVertices(){return numVertices;}
		int NumberOfEdges(){return  numEdges;}
		virtual T getValue(int i){};
		virtual E getValue(int v1,int v2){};
		virtual int getFirstNeighbor(int v)=0;
		virtual int getNextNeighbor(int v,int w)=0;
		virtual bool insertVertex(const T& vertex)=0;
		virtual bool insertEdge(int v1,int v2,E cost)=0;
		virtual bool removeVertex(int v)=0;
		virtual bool removeEdge(int v1,int v2)=0;
        virtual int getVertexPos(T vertex)=0;
        
        //ÐÂÌí¼Ó 
		virtual int search(string c){};
		virtual E getWeight(int v1,int v2){};
		virtual ostream& print(ostream &){}
		virtual istream& scan(istream  &){}
template<class K,class H>friend ostream& operator<<(ostream& os,Graph<K,H>& t){return t.print(os);}
template<class K,class H>friend istream& operator>>(istream& is,Graph<K,H>& t){return t.scan(is);}
	protected:
    	int  maxVertices;
    	int  numEdges;
    	int  numVertices;
    	
};

#endif

