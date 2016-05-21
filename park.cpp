#include<iostream>
#include "omp.h"
using namespace std;

int parkinfo[4][10]={0};
int vehcount=0;
int arr[2]={0};

class Vehicle
{
    string licensenumber;
    int row;
    int column;
    bool status;
    int num;
    public:
    
    void setNum(int j)
    {
        num=j;
    }
    
    bool getstatus()
    {
        return status;
    }
    
    void getfreeplace() ;
    
}v[10];


void Vehicle::getfreeplace()
{
    	int r, c, fromrow = 0, torow = 4 ;
    
//    #pragma omp parallel for
	for ( r = fromrow ; r < torow ; r++ )
 		{
  			for ( c = 0 ; c < 10 ; c++ )
  			{
   				if ( parkinfo[r][c] == 0 )
                {
				    row = r ;
				    column = c ;
                    parkinfo[r][c]=num;
                    vehcount++;
                    status=true;
				     return;
   				}
              
  			}
        
     
 		}
    
 	if(r == 4)
    {
 		cout<<"Unable to find parking spot for "<<num<<endl;
 	}
}






int main()
{
    cout<<"Welcome to 9th Street Parking Lot"<<endl;
    int number;
    int choice;
  int count=0;  
    int i=0;
do
		{
		  printf ( "\nCar Parking\n" ) ;
		  printf ( "1. Issue token\n" ) ;
		  printf ( "2. Number Entered\n");
          printf ( "3. Park\n");
          printf("4.Print Matrix\n");
          printf ( "5. Number parked\n"); 
		  printf ( "Enter your choice \n");
		  scanf ( "%d", &choice ) ;
    
		  switch (choice)
  			{
   				case 1 :
                  
      				cout<< "Enter vehicle number: "<<endl;
      				scanf ( "%d", &number ) ;
      				if(number!=0)
                    {
      				    v[count].setNum(number);
                        count++;
      				}
        
      				printf ( "\nPress any key to continue...\n" ) ;
          		
      				break ;
   				case 2 :
   				
      				printf ( "Total vehicles entered lot: %d\n", count ) ;
          			printf ( "\nPress any key to continue...\n") ;
          		
      				break ;
                  
              case 3:
                  {
                      #pragma omp parallel for
                      for(i=0;i<count;i++)
                      {
                           #pragma omp parallel
                          if(v[i].getstatus()==false)
                          v[i].getfreeplace();
                      }
                  }break;
                  
              case 4:
                  {
                      int r,c;
                    for ( r = 0 ; r < 4 ; r++ )
 		{
  			for ( c = 0 ; c < 10 ; c++ )
  			{
                
            if(parkinfo[r][c]!=0)    
   			cout<<"Car number "<<parkinfo[r][c]<<" parked at ["<<r<<"]["<<c<<"]"<<endl;
  			}
 		}  
                  }break;
                  
              case 5:
                  {
             
      				printf ( "Total vehicles parked in the lot: %d\n", vehcount ) ;
          			printf ( "\nPress any key to continue...\n") ;
          		
      				break ;
                  }break;
                  
                  
			}
}while(choice<=5);

    
    
    return 0;
}