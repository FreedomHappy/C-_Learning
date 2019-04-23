#ifndef Graphlnk_h_
#define Graphlnk_h_ 

#if 1



#include"Graph.h"
#include"LinkedQueue.h"
template<class T,class E>
struct Edge{
	int dest;
	E cost;
    Edge<T,E> *link;
    Edge(){}
    Edge(int num,E weight):dest(num),cost(weight),link(NULL){}
    bool operator!=(Edge<T,E>& R)const{return(dest!=R.dest)?true:false;}
};

template<class T,class E>
struct Vertex{
	T data;
	Edge<T,E> *adj;
};

template<class T,class E>
class Graphlnk:public Graph<T,E>{
	template <class K,class H>friend istream& operator>>(istream& in,Graphlnk<K,H>& G);
	template <class K,class H>friend ostream& operator<<(ostream& out,Graphlnk<K,H>& G);
	public:
		Graphlnk(int sz=DefaultVertices);
        ~Graphlnk();
        T getValue(int i)
		{return (i>=0&&i<this->numVertices)?NodeTable[i].data:0;}  
        E getWeight(int v1,int v2);
		bool insertVertex(const T& vertex);
		bool removeVertex(int v);
		bool insertEdge(int v1,int v2,E weight);
		bool removeEdge(int v1,int v2);
		int getFirstNeighbor(int v);
		int getNextNeighbor(int v,int w);
		int getVertexPos(const T vertex){
	  	for(int i=0;i<this->numVertices;i++)
	  	  if(NodeTable[i].data==vertex) return i;
	   return -1;
	  } 
private:
      Vertex<T,E> *NodeTable;

};

template<class T,class E>
Graphlnk<T,E>::Graphlnk(int sz){
	//建立空邻接表
	this->maxVertices=sz;this->numVertices=0;this->numEdges=0;
	NodeTable=new Vertex<T,E>[this->maxVertices];//顶点表
	if(NodeTable==NULL){cerr<<"存储分配错!"<<endl;exit(1);}
	for(int i=0;i<this->maxVertices;i++)
	NodeTable[i].adj=NULL;  //顶点表的边链表各头边节点置为空 
}

template<class T,class E>
Graphlnk<T,E>::~Graphlnk(){
	for(int i=0;i<this->numVertices;i++)
	 {
	 Edge<T,E> *p=NodeTable[i].adj;
	   while(p!=NULL){
	   	NodeTable[i].adj=p->link;
	   	delete p;p=NodeTable[i].adj;
	   }
	}
	
	delete[]NodeTable;
} 

template<class T,class E>
int Graphlnk<T,E>::getFirstNeighbor(int v){
	
	if(v!=-1){
		Edge<T,E> *p=NodeTable[v].adj;
		if(p!=NULL)return p->dest;
	} 
	return -1;
}

template<class T,class E>
int Graphlnk<T,E>::getNextNeighbor(int v,int w){
	if(v!=-1){
		Edge<T,E> *p=NodeTable[v].adj;
		while(p!=NULL&&p->dest!=w)
		    p=p->link;
		    if(p!=NULL&&p->link!=NULL)
		       return p->link->dest; 
	}
	return -1;
}


template<class T,class E>
E Graphlnk<T,E>::getWeight(int v1,int v2){
          if(v1!=-1&&v2!=-1){
          	Edge<T,E> *p=NodeTable[v1].adj;
          	while(p!=NULL&&p->dest!=v2)
          	     p=p->link;
            if(p!=NULL) return p->cost;
		  }
		  return 0;
}

template<class T,class E>
bool Graphlnk<T,E>::insertVertex(const T& vertex){
	if(this->numVertices==this->maxVertices) return false;
	NodeTable[this->numVertices].data=vertex;
	this->numVertices++;return true;
}

template<class T,class E>
bool Graphlnk<T,E>::removeVertex(int v){
	if(this->numVertices==1||v<0||v>=this->numVertices)return false;
	
	Edge<T,E> *p,*s,*t;int i,k;
	while(NodeTable[v].adj!=NULL){
		p=NodeTable[v].adj;k=p->dest;
		s=NodeTable[k].adj;t=NULL;         //t指向上一个节点 
		while(s!=NULL&&s->dest!=v){
			t=s;s=s->link;
		}
		if(s!=NULL){
			if(t==NULL)NodeTable[k].adj=s->link;
			else t->link=s->link;
			delete s;
		}
		NodeTable[v].adj=p->link;
		delete p;this->numEdges--; 
	}
	
	this->numVertices--;                    //图的顶点数减一 
	NodeTable[v].data=NodeTable[this->numVertices].data;//填补 
	p=NodeTable[v].adj=NodeTable[this->numVertices].adj;
	while(p!=NULL){
		s=NodeTable[p->dest].adj;
		while(s!=NULL)
		       if(s->dest==this->numVertices){
			       s->dest=v;break;
			   }
			   else s=s->link;
	}
	return true;
}

template<class T,class E>
bool Graphlnk<T,E>::insertEdge(int v1,int v2,E weight){
	if(v1>=0&&v1<this->numVertices&&v2>=0&&v2<this->numVertices){
		Edge<T,E> *q,*p=NodeTable[v1].adj;
		while(p!=NULL&&p->dest!=v2)
		           p=p->link;
		if(p!=NULL) return false;
		p=new Edge<T,E>; q=new Edge<T,E>;
		p->dest=v2; p->cost=weight;
		p->link=NodeTable[v1].adj;
		NodeTable[v1].adj=p;
		q->dest=v1;q->cost=weight;
		q->link=NodeTable[v2].adj;
		NodeTable[v2].adj=q;
		this->numEdges++;return true;
		}
		
		return 0;
} 

template<class T,class E>
bool Graphlnk<T,E>::removeEdge(int v1,int v2){
	if(v1!=-1&&v2!=-1){
	
			Edge<T,E> *p=NodeTable[v1].adj,*q=NULL,*s=p;
			while(p!=NULL&&p->dest!=v2)
	        {p=q;p=p->link;}
			 
			if(p!=NULL){
			 	
			 	if(p==s)NodeTable[v1].adj=p->link;
			 	else q->link=p->link;
			 	delete p;
			}
			else return false;
			
			p=NodeTable[v2].adj; q=NULL,s=p;
			while(p->dest!=v1){q=p;p=p->link;}
			if(p==s) NodeTable[v2].adj=p->link;
			else q->link=p->link;
			delete p;
			return true;			    
		}
		return false;
} 


template<class K,class H>
 istream& operator>>(istream& in, Graphlnk<K,H>& G){
 	int i,j,k,n,m;K e1,e2;H weight;
 	cout<<"numVertices,numEdges:";
	 in>>n>>m;
	 for(i=0;i<n;i++){
	 	in>>e1;G.insertVertex(e1);
	 }
	 i=0;
	 
	 while(i<m){
	 	in>>e1>>e2>>weight;
	 	j=G.getVertexPos(e1);k=G.getVertexPos(e2);
	 	if(j==-1||k==-1)
	 	   cout<<"边两端信息有误，重新输入！"<<endl;
		else{
			G.insertEdge(j,k,weight);i++;
		} 
	 }
	 return in;
}

template<class K,class H>
ostream& operator<<(ostream& out,Graphlnk<K,H>& G){
	int i,j,n,m;K e1,e2;H w;
	n=G.NumberOfVertices();m=G.NumberOfEdges();
	out<<n<<","<<m<<endl;
	for(i=0; i<n; i++)
	   for(j=i+1; j<n;j++){
	   	w=G.getWeight(i,j);
	   	if(w>0&&w<G.maxWeight){
	   		e1=G.getValue(i);e2=G.getValue(j);
	   		out<<"("<<e1<<","<<e2<<","<<w<<")"<<endl;
		   }
	   }
	   return out;
}

template<class T,class E>
void BFS(Graph<T,E>& G,const T& v){
	int i,w ,n=G.NumberOfVertices();
	bool * visited=new bool[n];
	for(i=0; i<n; i++) visited[i]=false;
	int loc=G.getVertexPos(v);
	cout<<G.getValue(loc)<<"  ";
	visited[loc]=true;
	LinkedQueue<int> Q;  Q.EnQueue(loc);
	while(!Q.IsEmpty()){
		Q.DeQueue(loc);
		w=G.getFirstNeighbor(loc);
		while(w!=-1){
			if(visited[w]==false){
				cout<<G.getValue(w)<<" ";
				visited[w]=true;
				Q.EnQueue(w);
			}
			w=G.getNextNeighbor(loc,w);
		}
	}
	delete[]visited;
}


#endif 
#endif
