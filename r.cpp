#include<iostream>
#include<fstream>
using namespace std;
#include<vector>
#include<set>
#include <bits/stdc++.h> 
#include<utility>


class rule
{
public:
    char tabdil;
    char s1 ;
    char s2 ;
    rule(char t,char a,char b){
    tabdil=t;
    s1=a ;
    s2=b ;
    }
    
};



class newedges
{
public:
    long v1;
    long v2 ;
    char size ;
    newedges(int a,int b,char t){
    size=t;
    v1=a ;
    v2=b ;
    }
     
    
};

bool operator==( const newedges & rhs ,const newedges & a) 
{
    return (a.size==rhs.size && a.v1==rhs.v1 && a.v2==rhs.v2);
}

int main(){
set <char> need;
// map<char,int>findindex;
vector<rule> law;
// read rules
ifstream in("grammar.txt");
if(!in){cout<<"eror";}
while(!in.eof()){
    char tabdil;
    char s1 ;
    char s2 ;
    in>>tabdil;
    in>>s1;
    in>>s2;
    rule s(tabdil,s1,s2);
    need.insert(s1);
    need.insert(s2);
    law.push_back(s);

}
law.pop_back();
in.close();

vector<pair<newedges,int>> nedge;
vector<pair<newedges,int>> nnedge;


ifstream iin("graph.txt");
int ras; iin>>ras;
if(!iin){cout<<"eror";}
char matrix[ras][ras];
memset(matrix,'0', sizeof(matrix[0][0]) * ras * ras);
char siz;
while(!iin.eof()){
    int firstv ;
    int secendv ;
    iin>>firstv;
    iin>>secendv;
    iin>>siz;

    if(matrix[firstv][secendv]=='0')
        matrix[firstv][secendv]=siz;
    else if (need.find(firstv)==need.end() || need.find(secendv)==need.end())
    {
        newedges s(firstv,secendv,siz);
        pair <newedges,int> x (s,-1);
        nedge.push_back(x);
        
    }
    


}
nedge.pop_back();



long total=0;
for(auto ii=law.begin();ii!=law.end();ii++)
{
    for(int f1=0;f1<ras;f1++)
    {
        for(int ss1=0;ss1<ras;ss1++)
        {
            if(matrix[f1][ss1]==(*ii).s1)
            {
                for(int z=0;z<ras;z++)
                {
                    if(matrix[ss1][z]==(*ii).s2)
                    {
                        newedges s (f1,z,(*ii).tabdil);
                        pair<newedges,int> x (s,ss1);

                        if(find(nedge.begin(),nedge.end(),x)==nedge.end())
                        {

                            total++;
                            // if (need.find((*ii).tabdil)!=need.end())
                            // {
                            
                                nedge.push_back(x);    
                            // }

                        }
                        
                                            
                    }
                }
            }

        }
    }
// cout<<" finish\n";
}


for(auto it=nedge.begin();it!=nedge.end();it++)
{
    newedges i=(*it).first;
    char x=(i).size;
    int a=(i).v1;
    int b=(i).v2;
    for(auto q=law.begin();q!=law.end();q++)
    {
        if((*q).s1==x)
        {
            for(int z=0;z<ras;z++)
            {
                if(matrix[b][z]==(*q).s2)
                {
                    newedges s (a,z,(*q).tabdil);
                    pair<newedges,int> x (s,b);
                    if(find(nedge.begin(),nedge.end(),x)==nedge.end() && find(nnedge.begin(),nnedge.end(),x)==nnedge.end())
                    {
                        total++;
                        // if (need.find((*q).tabdil)!=need.end())
                            // {   
                                nnedge.push_back(x);    
                            // }
                    }
                }

            }
            for(auto ee=nedge.begin();ee!=nedge.end();ee++)
            {   newedges e=(*ee).first;
                if((e).size==(*q).s2 && b==(e).v1)
                {    
                newedges s(a,(e).v2,(*q).tabdil);
                pair<newedges,int> x (s,b);
                if(find(nedge.begin(),nedge.end(),x)==nedge.end() && find(nnedge.begin(),nnedge.end(),x)==nnedge.end())
                    {
                        total++;
                        // if (need.find((*q).tabdil)!=need.end())
                            // {                                        
                                nnedge.push_back(x);    
                            // }
                            
                    }
                    
                                        
                }
            }    
        }
        if((*q).s2==x)
        {
            for(int z=0;z<ras;z++)
            {
                if(matrix[z][a]==(*q).s1)
                {                    
                    newedges s(z,b,(*q).tabdil);                    
                    pair<newedges,int> x (s,a);
                    if(find(nedge.begin(),nedge.end(),x)==nedge.end() && find(nnedge.begin(),nnedge.end(),x)==nnedge.end())
                    {
                        total++;
                        // if (need.find((*q).tabdil)!=need.end())
                            // {                                   
                                nnedge.push_back(x);    
                            // }
                    }
                }
            }
            /*
            for(auto e=nedge.begin();e!=nedge.end();e++)
            {
                if((*e).size==(*q).s1)
                {
                    total++;
                    newedges s((*e).v1,b,(*q).tabdil);
                    if (need.find((*q).tabdil)!=need.end())
                    nedge.push_back(s);
                }
            }
            */    
        }        
    }

}




while(!nnedge.empty())
{
    auto it = nnedge.back();
    nnedge.pop_back();
    newedges i =(it).first;
    char x=(i).size;
    long a=(i).v1;
    long b=(i).v2;
   
    for(auto q=law.begin();q!=law.end();q++)
    {
        if((*q).s1==x)
        {
            for(int z=0;z<ras;z++)
            {
                if(matrix[b][z]==(*q).s2)
                {
                    newedges s(a,z,(*q).tabdil);
                    pair<newedges,int> xx (s,b);
                    if(find(nedge.begin(),nedge.end(),xx)==nedge.end() && find(nnedge.begin(),nnedge.end(),xx)==nnedge.end())
                    {
                        total++;
                        // if (need.find((*q).tabdil)!=need.end())
                            // {                                   
                                nnedge.push_back(xx);                          
                            // }
                    }
                }
            }
            for(auto ee=nedge.begin();ee!=nedge.end();ee++)
            {
                newedges e=(*ee).first;
                if((e).size==(*q).s2 && b==(e).v1)
                {
                    
                    newedges s(a,(e).v2,(*q).tabdil);                    
                    pair<newedges,int> xx (s,(e).v1);
                    if(find(nedge.begin(),nedge.end(),xx)==nedge.end() && find(nnedge.begin(),nnedge.end(),xx)==nnedge.end())
                    {
                        total++;
                        // if (need.find((*q).tabdil)!=need.end())
                            // {   
                                
                                nnedge.push_back(xx);    
                            // }
                    }


                }
            }    
        }
        if((*q).s2==x)
        {
            for(int z=0;z<ras;z++)
            {
                if(matrix[z][a]==(*q).s1)
                {
                    
                    newedges s(z,b,(*q).tabdil);
                    pair<newedges,int> xx (s,a);
                    if(find(nedge.begin(),nedge.end(),xx)==nedge.end() && find(nnedge.begin(),nnedge.end(),xx)==nnedge.end())
                    {
                        total++;
                        // if (need.find((*q).tabdil)!=need.end())
                            // {                                   
                                nnedge.push_back(xx);    
                            // }
                    }                    
                }
            }
            
            for(auto ee=nedge.begin();ee!=nedge.end();ee++)
            {
                newedges e=(*ee).first;
                if((e).size==(*q).s1 && a==(e).v2)
                {
                    newedges s((e).v1,b,(*q).tabdil);
                    pair<newedges,int> xx (s,(e).v2);
                    if(find(nedge.begin(),nedge.end(),xx)==nedge.end() && find(nnedge.begin(),nnedge.end(),xx)==nnedge.end())
                    {
                        total++;
                        // if (need.find((*q).tabdil)!=need.end())
                            // {   
                                
                                nnedge.push_back(xx);    
                            // }
                    }                    
                    
                }
            }
                
        }        
    }

nedge.push_back(it);


}














cout<< total;

return 0;
}