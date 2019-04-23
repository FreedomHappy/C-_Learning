#ifndef Graphmtx_h_
#define Graphmtx_h_

#include"Graph.h"
//邻接矩阵
template<typename T,typename E>
class Graphmtx:public Graph<T,E>{
	template<class K,class H>friend istream& operator>>(istream& in,Graphmtx<K,H>& G);
	template<class K,class H>friend ostream& operator<<(ostream& out,Graphmtx<K,H>& G);
	public:
		Graphmtx(int sz=DefaultVertices);
		~Graphmtx(){delete[]VerticesList;delete[]Edge;}
		
		T getValue(int i){ if(i>=0&&i<this->numVertices) return VerticesList[i]; //else return 0;
		}

		E getWeight(int v1,int v2){return v1!=-1&&v2!=-1?Edge[v1][v2]:0;}
		
		int getFirstNeighbor(int v);
		int getNextNeighbor(int v,int w);
		bool insertVertex(const T& vertex);
		bool insertEdge(int v1, int v2,E cost);
		bool removeVertex(int v);
		bool removeEdge(int v1,int v2);
		int getVertexPos(T vertex){
			for(int i=0;i<this->numVertices;i++)
			     if(VerticesList[i]==vertex) return i;
		    return -1;
		}
		
		
		
		ostream& print(ostream &);
	    istream& scan(istream  &);
		int search(string c){for(int i=0;i<this->numVertices;i++) if(T(c)==VerticesList[i])return i; return -1;}
	private:
		T *VerticesList;
		E* *Edge;
	
}; 

template<class T,class E>
Graphmtx<T,E>::Graphmtx(int sz){
//构造函数
             this->maxVertices=sz;this->numVertices=0;this->numEdges=0 ;
             int i,j;
            
			 VerticesList=new T[this->maxVertices];
            
			 Edge=(E* *)new E *[this->maxVertices];
             for(i=0; i<this->maxVertices; i++)
                  Edge[i]=new E[this->maxVertices];
            
			for(i=0;i<this->maxVertices;i++)
              for(j=0;  j<this->maxVertices; j++)
                     Edge[i][j]=(i==j)?0:this->maxWeight;          
}


template<class T,class E>
int Graphmtx<T,E>::getFirstNeighbor(int v){
	if(v!=-1){
		for(int col=0;col<this->numVertices;col++)
		   if(Edge[v][col]>0&&Edge[v][col]<this->maxWeight) return col;
	}
	return -1;
}

template<class T,class E>
int Graphmtx<T,E>::getNextNeighbor(int v,int w){
	if(v!=-1&&w!=-1){
		for(int col=w+1;col<this->numVertices;col++){
			if(Edge[v][col]>0&&Edge[v][col]<this->maxWeight) return col;
		}
	} 
	return -1;
}

template<class T,class  E>
bool Graphmtx<T,E>::insertVertex(const T& vertex){
	if(this->numVertices==this->maxVertices) return false;
	VerticesList[this->numVertices++]=vertex;
	return true;
}

template<class T,class E>
bool Graphmtx<T,E>::removeVertex(int v){
	if(v<0||v>=this->numVertices) return false;
	if(this->numVertices==1) return false;
	int i,j;
	VerticesList[v]=VerticesList[this->numVertices-1];
	for(i=0; i<this->numVertices;i++)
	   	if(Edge[i][v]>0&&Edge[i][v]<this->maxWeight) this->numEdges--;
	
	for(i=0;i<this->numVertices;i++)
	 	Edge[i][v]=Edge[i][this->numVertices-1];
	
	this->numVertices--;
	for(j=0;j<this->numVertices;j++)
	 	Edge[v][j]=Edge[this->numVertices][j];
	return true; 
}

template<class T,class E>
bool Graphmtx<T,E>::insertEdge(int v1,int v2,E cost){
	if(v1>-1&&v1<this->numVertices&&v2>-1&&v2<this->numVertices&&Edge[v1][v2]==this->maxWeight){
		Edge[v1][v2]=Edge[v2][v1]=cost;
		this->numEdges++;
		return true;	
	}
	else return false;
}
 template<class T,class E>
 bool Graphmtx<T,E>::removeEdge(int v1,int v2){
 	if(v1>-1&&v1<this->numVertices&&v2>-1&&v2<this->numVertices&&Edge[v1][v2]>0&&Edge[v1][v2]<this->maxWeight){
 		Edge[v1][v2]=Edge[v2][v1]=this->maxWeight;
 		this->numEdges--;
 		return true;
	 }
	 else return false;
 }
 template<class K,class H>
 ostream& Graphmtx<K,H>::print(ostream & out){
 	int i,j,n,m;K e1,e2;H w;
	n=this->NumberOfVertices();m=this->NumberOfEdges();
	out<<"numberVertices:"<<n<<","<<"numberEdges:"<<m<<endl;
	for(i=0; i<n; i++)
	   for(j=i+1; j<n;j++){
	   	w=this->getWeight(i,j);
	   	if(w>0&&w<this->maxWeight){
	   		e1=this->getValue(i);e2=this->getValue(j);
	   		out<<"("<<e1<<","<<e2<<","<<w<<")"<<endl;
		   }
	   }
	   return out;
 }
 template<class K,class H>
istream& Graphmtx<K,H>::scan(istream  &in){
	int i,j,k,n,m;K e1,e2;H weight;
 	cout<<"numVertices,numEdges:";
	 in>>n>>m;
	 for(i=0;i<n;i++){
	 	in>>e1;this->insertVertex(e1);
	 }
	 i=0;
	 
	 while(i<m){
	 	in>>e1>>e2>>weight;
	 	j=this->getVertexPos(e1);k=this->getVertexPos(e2);
	 	if(j==-1||k==-1)
	 	   cout<<"边两端信息有误，重新输入！"<<endl;
		else{
			this->insertEdge(j,k,weight);i++;
		} 
	 }
	 return in;
}
 
 
 template<class K,class H>
 istream& operator>>(istream& in, Graphmtx<K,H>& G){
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
ostream& operator<<(ostream& out,Graphmtx<K,H>& G){
	int i,j,n,m;K e1,e2;H w;
	n=G.NumberOfVertices();m=G.NumberOfEdges();
	out<<"numberVertices:"<<n<<","<<"numberEdges:"<<m<<endl;
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
void Components(Graph<T,E>& G){
	int i,n=G.NumberOfVertices();
	bool *visited=new bool[n];
	for(i=0;i<n;i++) visited[i]=false;
	for(i=0;i<n;i++)
	 if(visited[i]==false){
	 	DFS(G,i,visited);
	 	cout<<endl;
	 	}
}
template<class T,class E>
void DFS(Graph<T,E>& G,const T& v){
         int i,loc,n=G.NumberOfVertices();
         bool *visited=new bool[n];
         for(i=0; i<n;i++)visited[i]=false;
         loc=G.getVertexPos(v);
         DFS(G,loc,visited);
         delete []visited;
} 

template<class T,class E>
void DFS(Graph<T,E>& G,int v,bool visited[]){
	    cout<<G.getValue(v)<<"    ";//访问顶点
		visited[v]=true;
		int w=G.getFirstNeighbor(v);
		while(w!=-1){
		   if(visited[w]==false) DFS(G,w,visited);
		   w=G.getNextNeighbor(v,w);
		} 
}




#endif
