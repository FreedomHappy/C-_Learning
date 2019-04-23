#ifndef LinkedQueue_h_
#define LinkedQueue_h_ 
#include<iostream>
using namespace std;
#include<string>

template<class T>
class LinkNode{
public:
	T data;
	LinkNode<T> *link;
	LinkNode(LinkNode<T> *ptr=NULL):link(ptr){}
	LinkNode(const T& item,LinkNode<T> *ptr=NULL):data(item),link(ptr){}
};

template<class T>
class LinkedQueue{
public:
	LinkedQueue():rear(NULL),front(NULL){}
	~LinkedQueue(){makeEmpty();}
	void makeEmpty();
	bool EnQueue(const T& x);
	bool DeQueue(T& x);
	bool getFront(T& x)const;
	bool IsEmpty()const{return(front==NULL)?true:false;}
	int getSize()const;
  template<class K> friend ostream& operator<<(ostream& os,LinkedQueue<K>& q);
protected:
    LinkNode<T> *front,*rear;		
};

struct Position{
	int row;
	int col;
    Position& operator=(Position& p1);
	friend ostream& operator<<(ostream& os,Position& po);
    
};

bool FindPath(Position start,Position finish,int& PathLen,Position* & path);

template<class T>
void LinkedQueue<T>::makeEmpty(){
	  LinkNode<T> *p=front; 
	  while(p!=NULL){
			front=front->link;
			delete p;
			p=front;
	  }
}

template<class T>
bool LinkedQueue<T>::EnQueue(const T& x){
	if(front==NULL){
	  	     front=new LinkNode<T>(x);
	  	     if(front==NULL) return false;
	  	     rear=front;
	}
	else{
	 	    rear->link=new LinkNode<T>(x);
	        if(rear->link==NULL) return false;
			rear=rear->link; 
	}
	return true;
}

template<class T>
bool LinkedQueue<T>::DeQueue(T& x){
	if(IsEmpty()==true) return false;
	LinkNode<T> *p=front;
	x=p->data;
	front=front->link;
	delete p;
	return true;
}


template<class T>
bool LinkedQueue<T>::getFront(T& x)const{
	if(front==NULL) return false;
	x=front->data;
	return true;
} 
 
template<class T>
int LinkedQueue<T>::getSize()const{
	LinkNode<T> *p=front;
	int a=0;
	while(p!=NULL){
		a++;
		p=p->link;
	}
	return a;
}

template<class K>
ostream& operator<<(ostream& os,LinkedQueue<K>& q){
		K x;
		while(q.DeQueue(x)){
			os<<x<<endl;
		}    
		return os;
}

 ostream& operator<<(ostream& os,Position& po){
        os<<"("<<po.row<<","<<po.col<<")";
		return os;	
}

Position& Position::operator=(Position& p1){
	row=p1.row;col=p1.col;
	return (*this);
}


bool FindPath(int m,Position start,Position finish,int& PathLen,Position* & path,int **grid){
	//一开始就是终点 
	if(start.row==finish.row&&start.col==finish.col){PathLen=0;return 0;}
	
	//初始化 
	int  i,j;
	int NumOfNbrs=4;
	
	for(i=0;i<=m+1;i++){
		grid[0][i]=grid[m+1][i]=1;
		grid[i][0]=grid[i][m+1]=1;
	} 
	
	Position offset[4];
	offset[0].row=-1;offset[0].col=0;
	offset[1].row=0; offset[1].col=1;
	offset[2].row=1; offset[2].col=0;
	offset[3].row=0; offset[3].col=-1;
	
	Position here,nbr;
	here=start;
	grid[start.row][start.col]=2;
	
	//网格距离标记 
	LinkedQueue<Position>  Q;
	do{
	    for(i=0; i<NumOfNbrs; i++){
            nbr.row=here.row+offset[i].row;
            nbr.col=here.col+offset[i].col;
            
			if(grid[nbr.row][nbr.col]==0){
            	grid[nbr.row][nbr.col]=grid[here.row][here.col]+1;
            	if(nbr.row==finish.row&&nbr.col==finish.col)break;
            	Q.EnQueue(nbr);
				}
		}
			
			if(nbr.row==finish.row&&nbr.col==finish.col)break;
		    
			if(Q.IsEmpty()==true) return false;
		    Q.DeQueue(here); 
		
	}while(true);
	
	//构造路径 
	PathLen=grid[finish.row][finish.col]-2;
	path=new Position[PathLen];
	here=finish;
	for(j=PathLen-1; j>=0; j--){
		path[j]=here;
		for(i=0; i<NumOfNbrs; i++){
			nbr.row=here.row+offset[i].row;
			nbr.col=here.col+offset[i].col;
			if(grid[nbr.row][nbr.col]==j+2) break;
		}
		
		here=nbr;
	}
	
	
	cout<<"PL:"<<PathLen<<endl;
	for(i=0; i<PathLen; i++){
		cout<<path[i]<<endl;
	}
	return true;
}

#endif

