#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fe first 
#define se second 
#define rep(n) for(int i=0;i<n;i++)
struct node 
{
	int val;
	node *l,*r;
	node()
	{
		l=NULL;
		r=NULL;
		val=0;
	}
};

node* v[100004];

void buildtree(int s,int e,node *pos)
{
	if(s==e)
	   pos->val=1;
	else
	{
		int mid=(s+e)>>1;
		pos->l=new node(); 
		pos->r=new node();
		buildtree(s,mid,pos->l);
		buildtree(mid+1,e,pos->r);
		pos->val=pos->l->val+pos->r->val;
	}   
}

void update(int s,int e,node* pos,node* prev,int id)
{
	if(s==e)
	 pos->val=0;
	else
	{
		int mid=s+e>>1;
		if(id<=mid)
		{
			pos->r=prev->r;
			pos->l=new node();
			update(s,mid,pos->l,prev->l,id);
		}
		else
		{
			pos->l=prev->l;
			pos->r=new node();
			update(mid+1,e,pos->r,prev->r,id); 
		}
		
		pos->val=pos->l->val+pos->r->val;
	} 
}

void show(int s,int e,node *pos)
{
	if(s==e)
	 { 
	 	 cout<<s<<" "<<e<<" "<<pos->val<<endl;
	 }
	else
	{
		int mid=(s+e)>>1;
		//pos->l=new node(); 
		//pos->r=new node();
		show(s,mid,pos->l);
		show(mid+1,e,pos->r);
		//pos->val=pos->l->val+pos->r->val;
		cout<<s<<" "<<e<<" "<<pos->val<<endl;
	}   
}

int query(int s,int e ,node* pos,int loc)
{
	if(s==e)
	 {
	 	//cout<<s<<" "<<e<<" "<<pos->val<<endl;
	 	return s;
	 }
	else
	{
		int mid=(s+e)>>1;
		int k=pos->l->val;
		//cout<<s<<" "<<e<<" "<<pos->val<<endl;
		if(loc<=k)
		return query(s,mid,pos->l,loc);
		else
		return query(mid+1,e,pos->r,loc-k);
	} 

}

int main()
{
	vector<int> v1[100003],v2;
	int a[100003],n,max=0;
	cin>>n;
	int q;
	cin>>q;
	rep(n)
	{
		int s;
		cin>>s;
		v2.pb(s);
		v1[s].pb(i);
		if(max<s)
		max=s;
	}	
	int prev=0;
	for(int i=1;i<=max;i++)
	{
		a[i]=prev;
		prev+=v1[i].size();
	}
	cout<<endl;
	v[0]=new node();
	buildtree(0,n-1,v[0]);	
	//show(0,n-1,v[0]);
	int k=1;
	for(int i=1;i<=max;i++)
	{
		for(int j=0;j<v1[i].size();j++)
		{
			v[k]=new node();
			update(0,n-1,v[k],v[k-1],v1[i][j]);
			//if(k==3)
			//show(0,n-1,v[3]);
			++k;
		}
	}
	
	rep(q)
	{
		int f,p;
		cin>>f>>p;
		int ans=query(0,n-1,v[a[f]],p);
		cout<<v2[ans]<<endl;
	}	
return 0;
}
