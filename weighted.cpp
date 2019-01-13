#include<iostream>
#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include<vector>
#include<iterator>
#include<utility>
#include<time.h>        //for getCoords2()
#define PI 3.14159265
using namespace std;

void addEdge(vector< pair<int,int> > [],int,int,int);
void diplayGraph(vector< pair<int,int> > [],int);
vector< pair<int,int> > getCoords(int);
vector< pair<int,int> > getCoords2(int);

int main()
{
    int n,e;
    cout<<"Enter the no. of Vertices: ";cin>>n;
    cout<<"Enter the no. of Edges: ";cin>>e;
    vector< pair<int,int> > arr[n];
    int c1,c2,weight;
    cout<<"Enter connection as in ' a,b,weight ' and remember node starts from 0:-"<<endl;//or 'from A:-'
    for (int i=0;i<e;i++)
    {
        scanf("%d,%d,%d",&c1,&c2,&weight);
        addEdge(arr,c1,c2,weight);
    }

    //////////////////

    int gd=DETECT,gm;
    initgraph(&gd, &gm, ""); //or  "C:\\TC\\BGI"
    diplayGraph(arr,n);
    getch();
    closegraph();
    return 0;
}

void addEdge(vector< pair<int,int> > arr[],int u, int v,int weight)
{
    arr[u].push_back(make_pair(v,weight));  //arr[u-'A'].push_back(v-'A') if you decide to enter letters, also change below line
    arr[v].push_back(make_pair(u,weight));  //comment this line for directed graph from u to v
}

void diplayGraph(vector< pair<int,int> > arr[],int n)
{
    vector< pair<int,int> > coords = getCoords(n); //this returns coords in circular form
   // vector< pair<int,int> > coords = getCoords2(n);   //this returns coords in random manner,
   //uncomment line above and comment line above the above line to use this

    //  Time to draw Edges
    vector< pair<int,int> >::iterator i;
    char str[5];
    for(int f=0;f<n;f++)//this is just printing all edges from each node no., therefore it can be further optimized
    {
        for(i = arr[f].begin();i <  arr[f].end();i++) //f can be acknowledged as from
        {
            line(coords[f].first,coords[f].second,coords[(*i).first].first,coords[(*i).first].second);
           sprintf(str,"%d",(*i).second);
            outtextxy((coords[(*i).first].first + coords[f].first)/2 - 5,(coords[(*i).first].second + coords[f].second)/2 -7,str); //5 and 7 are random no. to relocate acc. to perfect viewing
            //outtextxy((5*coords[(*i).first].first + coords[f].first)/6,(5*coords[(*i).first].second + coords[f].second)/6,"*");
            //uncomment above line for directed graph, this is section formula (co-ordinate geometry)
        }
    }

    //  Time to draw Points
    char symbol[1];
    strcpy(symbol,"A");// or "A"
    setbkcolor(WHITE);// since we are going to fill circle with white color, so text-bg-color is also changed to white
    setfillstyle(SOLID_FILL,WHITE);
    for(int i=0;i<coords.size();i++)
    {
        setcolor(LIGHTGRAY);
        circle(coords[i].first,coords[i].second,15);//you can take any radius; a hollow circle of light-gray color is formed
        floodfill(coords[i].first+1,coords[i].second+1,LIGHTGRAY); //fill every thing except light-gray,thus forming boundary
        setcolor(BLACK);
        outtextxy(coords[i].first-5,coords[i].second-7,symbol);//5 and 7 are random no. to relocate acc. to perfect viewing
        *symbol+=1;     //increments the ASCII first char of symbol array i.e. symbol itself
    }
}

vector< pair<int,int> > getCoords(int n)
{
    int cenX=getmaxx()/2,cenY=getmaxy()/2; //finding center
    vector< pair<int,int> > coords; //Co-ordinates
    int x,y;
    x=0;
    y=(25*n); //25 is just a no. it could be anything.
    coords.push_back(make_pair(x+cenX,cenY+y));      //A.K.A. Translation of Origin (geometry)
   for(int i=1;i<n;i++)
   {
    int newX=(x*cos(2*PI/n) - y*sin(2*PI/n));       //counter-clock-wise rotation
    y=(y*cos(2*PI/n) + x*sin(2*PI/n));
    x=newX;
    coords.push_back(make_pair(x+cenX,cenY+y));
   }
   return coords;
}


vector< pair<int,int> > getCoords2(int n)
{
    int maxX=getmaxx()-30,maxY=getmaxy()-30; //-30 to create bottom and right boundary, +15 later
    vector< pair<int,int> > coords; //Co-ordinates
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
    coords.push_back(make_pair((rand()%maxX)+15,(rand()%maxY)+15));//+15 to create top and left boundary
    //since radius is 15 so boundary are made to keep them inside screen
    }
    return coords;
}

