#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
using namespace std;
float distance(float x1, float x2, float y1, float y2);
int computeCode(float x, float y, int p, float obs[][4]);

int main()
{
    int i, j, o, n, b, c, h, g;
    float slope, a, goal_radius, x_temp, y_temp, x_goal_min, x_goal_max, y_goal_min, y_goal_max, rect[10][4], x_points[50], y_points[50], x_nearest_point, y_nearest_point, x_starting_point, y_starting_point, x_goal_point, y_goal_point, x_random_point, y_random_point, incremental_distance, K, dist[40];;
    cout<<"starting point- first x, then y\n";
    cin>>x_starting_point;
    cin>>y_starting_point;
    cout<<"goal point- first x then y\n";
    cin>>x_goal_point;
    cin>>y_goal_point;
    cout<<"Enter incremental distance\n";
    cin>>incremental_distance;
    cout<<"Enter number of rectangular obstacles\n";
    cin>>n;
    for(i=1; i<=n; i++)
    {
        cout<<"Enter x and y coordinates of top right and bottom left corners of obstacle "<<i<<" in that order\n";
        for(j=0; j<=3; j++)
        {
            cin>>rect[i][j];
        }
    }
    cout<<"Enter number of iterations\n";
    cin>>K;
    cout<<"Enter goal radius (tolerance)\n";
    cin>>goal_radius;

    x_points[0]=x_starting_point;
    y_points[0]=y_starting_point;
    x_goal_min= x_goal_point-goal_radius;
    x_goal_max= x_goal_point+goal_radius;
    y_goal_min= y_goal_point-goal_radius;
    y_goal_max= y_goal_point+goal_radius;

    for(i=1; i<=K; i++)
    {
     x_nearest_point=x_starting_point;
     y_nearest_point=y_starting_point;
     srand(time(0));
     x_random_point=rand() % 11;
     y_random_point=rand() % 11;

     dist[0]=distance(x_starting_point, x_random_point, y_starting_point, y_random_point);
     for(j=1;j<i;j++)
     {
         dist[j]=distance(x_points[j],x_random_point,y_points[j],y_random_point);
         if (dist[j]<dist[j-1])
         {
             x_nearest_point=x_points[j];
             y_nearest_point=y_points[j];
         }

     }

     if(x_nearest_point==x_random_point)
     {
        slope=57;
     }
     else
     {
        slope=(y_random_point-y_nearest_point)/(x_random_point-x_nearest_point);
     }
     
     h=0;
     for(o=1; o<=n; o++)
     {
        b=1;
        while(a<=incremental_distance)
        {
           a=b*0.01;
           x_temp= (a/sqrt(1+slope*slope))+x_nearest_point;
           y_temp= slope*(x_temp-x_nearest_point)+y_nearest_point;
           c=computeCode(x_temp, y_temp, o, rect);
           if(c==0)
           {
               h=1;
               break;
           }
           b++;
        }
        if(h==1)
        {
            break;
        }

     }
     if(h==0)
     {
         x_points[i]=x_temp;
         y_points[i]=y_temp;
     }
        
    }
     
 g=0;   
 for(i=0; i<=K; i++)
 {
    if((x_points[i]>x_goal_min & x_points[i]<x_goal_max)&(y_points[i]>y_goal_min & y_points[i]<x_goal_max))
    {
        g=1;
        break;
    }
 }
 
 if(g==0)
 {
     cout<<"Goal not met\n";
 }
 else
 {
     cout<<"Goal met!\n";
 }
 

 for(i=0; i<=K; i++)
 {
     cout<<x_points[i]<<" "<<y_points[i]<<" ";
 }

    return 0;
}

float distance(float x1, float x2, float y1, float y2)
{
    float d;
    d=sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
    return d;
}

int computeCode(float x, float y, int p, float obs[][4]) 
{ 
    float x_max = obs[p][0]; 
    float y_max = obs[p][1]; 
    float x_min = obs[p][2]; 
    float y_min = obs[p][3];
    const int INSIDE = 0; // 0000 
    const int LEFT = 1; // 0001 
    const int RIGHT = 2; // 0010 
    const int BOTTOM = 4; // 0100 
    const int TOP = 8; // 1000 
  
    // initialized as being inside 
    int code = INSIDE; 
  
    if (x < x_min) // to the left of rectangle 
    {
        code |= LEFT; 
    }
    else if (x > x_max) // to the right of rectangle 
    {
        code |= RIGHT;
    } 
    if (y < y_min) // below the rectangle 
    {
        code |= BOTTOM;
    }    
 
    else if (y > y_max) // above the rectangle 
    {
      code |= TOP; 
    } 
  
    return code; 
} 