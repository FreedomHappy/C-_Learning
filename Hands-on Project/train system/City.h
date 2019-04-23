#ifndef City_h_
#define City_h_
#include"head.h"

class City
{   
  friend ostream& operator<<(ostream& os,City& c);
   friend istream& operator>>(istream& is,City& c);
public:
    City(){}
	City(string n):name(n){}
    void setName(string n){name=n;}
   string getName(){return name;}
	int    key;
    bool operator==(City& c){ if(this->name==c.name) return true;else return false;}
    
	operator int(){return key;}  //������ ��������غ�����ͻ 
    operator string(){return name;}// 
private:
   string name;
};


 ostream& operator<<(ostream& os,City& c){//�˺���������ת��������ͻ 
	os<<c.name;
	return os;
} 


 istream& operator>>(istream& is,City& c){
	is>>c.name;
	return is;
}

template<class T,class E>
void initializeCity(Graph<T,E>& G){
	City city[6]={City("����"),City("�Ϻ�"),City("����"),City("����"),City("����"),City("����")};
	 for(int i=0;i<6;i++)
	{   city[i].key=i;
		 G.insertVertex(city[i]); 
     }
}
template<class T,class E>
void initializeTime(Graph<T,E>& G){
          G.insertEdge(0,2,356);G.insertEdge(0,3,260);G.insertEdge(1,2,693);
          G.insertEdge(1,3,450);G.insertEdge(1,4,264);G.insertEdge(1,5,484);
        G.insertEdge(2,3,591);G.insertEdge(2,5,222);G.insertEdge(2,3,652);
        G.insertEdge(4,5,110);
}


template<class T,class E>
void initializePrice(Graph<T,E>& G){
	G.insertEdge(0,2,590);G.insertEdge(0,3,515.5);G.insertEdge(1,2,588);
	G.insertEdge(1,3,699.5);G.insertEdge(1,4,309.5);G.insertEdge(1,5,388);
	G.insertEdge(2,3,888);G.insertEdge(2,5,180);G.insertEdge(2,3,824.5);
	G.insertEdge(4,5,88); 
}


template<class T,class E>
bool insertCity(Graph<T,E>& G,City &c){
	if(!G.insertVertex(c)) return false;
	else return true;
}

template<class T,class E>
bool removeCity(Graph<T,E>& G,string name){
	if(!G.removeVertex(G.search(name))) return false;
	else return true; 
}

template<class T,class E>
bool insertCityPT(Graph<T,E>& G,string c1,string c2,E pt){
	if(!G.insertEdge(G.search(c1),G.search(c2),pt)) return false;
	else return true;
}

template<class T,class E>
bool removeCityPT(Graph<T,E>& G,string c1,string c2){
	if(!G.removeEdge(G.search(c1),G.search(c2))) return false;
	else return true;
}

#ifndef maxValue
#define maxValue  MAX_WEIGHT
#endif

template<class T,class E>
void  ShortestPath(Graph<T,E>& G,int v,E dist[],int path[]){
	int n=G.NumberOfVertices();
	bool *S=new bool[n];
	int  i,j,k;E w,min;
	for(i=0;i<n;i++){
		dist[i]=G.getWeight(v,i);
		S[i]=false;
		if(i!=v&&dist[i]<maxValue)path[i]=v;
		else path[i]=-1;
	}
	S[v]=true; dist[v]=0;
	for(i=0;i<n-1;i++){
		min=maxValue;int u=v;
		for(j=0;j<n;j++)if(S[j]==false&&dist[j]<min){u=j;min=dist[j];}
		S[u]=true;
		for(k=0;k<n;k++){
			w=G.getWeight(u,k);
			if(S[k]==false&&w<maxValue&&dist[u]+w<dist[k]){
				dist[k]=dist[u]+w;
				path[k]=u;
			}
		}
	}
}

template<class T,class E>
void City_printShortestPath(Graph<T,E>& G,int v1,int v2,E dist[],int path[],int key){
	cout<<"�ӳ���";cout<<((string)G.getValue(v1));cout<<"������" ;cout<<((string)G.getValue(v2));
	if(key==0)cout<<"��������·����"<<endl;
	else  cout<<"ʱ������·����"<<endl;
	int n=G.NumberOfVertices();
	int *d=new int[n];
	int j=v2,k=0;
	while(j!=v1){d[k++]=j;j=path[j];}
	cout<<((string)G.getValue(v1));
	while(k>0){cout<<"--->"<<(string)G.getValue(d[--k]);}
	cout<<endl;
	if(key==0) cout<<"����Ϊ��"<<dist[v2]<<"Ԫ"<<endl;
	else cout<<"��ʱΪ��"<< dist[v2]<<"����"<<endl;
	
	delete []d;
}


template<class T,class E>
void City_user(Graph<T,E>& gt,Graph<T,E>& gp){
	int  key1,key2,key3,select1,select2;
	string cityname1,cityname2,cityname;
	while(true){
	
	cout<<"1.�༭����"<<endl<<"2.�༭�г�ʱ�̱�"<<endl<<"3.��ѯ"<<endl<<"4.�����"<<endl 
	 <<"������Ž���ѡ��"<<endl; 
    cin>>select1;
    
	if(select1==1){
    loop1:	cout<<"1.��ӳ��У�2.ɾ������:";
		cin>>select2;
		if(select2==1){
			cout<<"��������";cin>>cityname;
			City city_add(cityname);city_add.key=gt.NumberOfVertices();
			insertCity(gt,city_add);
			insertCity(gp,city_add);
		} 
		else if(select2==2){
			cout<<"��������";cin>>cityname;
			removeCity(gt,cityname);
			removeCity(gp,cityname);
		}  
		else {cout<<"�������!"<<endl;goto loop1; }
	}
	
	else if(select1==2){
	loop2:	cout<<"1.���ʱ�̱�2.ɾ��ʱ�̱�:";cin>>select2;
		if(select2==1){
			E pt; 
			cout<<"������������";cin>>cityname1>>cityname2;
			cout<<"Ʊ�ۣ�";cin>>pt;
			insertCityPT(gp,cityname1,cityname2,pt);
			cout<<"ʱ����";cin>>pt;
			insertCityPT(gt,cityname1,cityname2,pt);
		}
		else if(select2==2)
		{
				cout<<"������������";cin>>cityname1>>cityname2;
				removeCityPT(gp,cityname1,cityname2);
				removeCityPT(gt,cityname1,cityname2);
		}
	    else {cout<<"�������!"<<endl;goto loop2; }
	}
	
	else if(select1==3){
		E dist1[10],dist2[10];int path1[10],path2[10];
		cout<<"����������У�";cin>>cityname1;
		cout<<"������ֹ����: ";cin>>cityname2;
        ShortestPath(gp,gp.search(cityname1),dist1,path1);
        City_printShortestPath(gp,gp.search(cityname1),gp.search(cityname2),dist1,path1,0);
        ShortestPath(gt,gt.search(cityname1),dist2,path2);
        City_printShortestPath(gt,gt.search(cityname1),gt.search(cityname2),dist2,path2,1);
	}
    else if (select1==4)cout<<"�۸��"<<endl<<gp
	<<"========================================================="<<endl
	<<"ʱ���"<<endl<<gt;
	else cout<<"��������������룺"<<endl; 
    
    
	}
}




#endif
