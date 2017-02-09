
//Command to execute
//g++-5 -fopenmp -I  /usr/local/Cellar/boost/1.60.0_2/include -L /usr/local/Cellar/boost/1.60.0_2/lib -lboost_chrono -lboost_system -lcurses -std=c++14 parking.cpp -o parking

#include <iostream>
#include <curses.h>
#include <time.h>
#include <string.h>
#include "omp.h"
#include <boost/chrono.hpp>


using namespace std;
using namespace boost::chrono;

struct Vehicle{
    string licenceNo;
    int row;
    int col;
    int num;
    bool parkStatus;
};

int parkinfo[4][10] ; //parkinginfo
int vehiclecount ; //vehicle count
struct Vehicle * add (int, int, int, bool ) ;
void getfreeplace( int *);
void displayParking();
void getRowColumnOfVehicle(int, int*);
void deleteVehicle(struct Vehicle * );


void getfreeplace(int *returnarr)
{
    int r, c, fromrow = 0, torow = 4 ;
    int x = 0;
    
    for ( r = fromrow ; r < torow ; r++ )
    {
        for ( c = 0 ; c < 10 ; c++ )
        {   returnarr[0] = -1;
            returnarr[1] = -1;
            
            //#pragma omp critical
            //          {
            
            if ( parkinfo[r][c] == 0  ){
                printf("in loop");
                if ( parkinfo[r][c] != -1) {
                    printf("in loop");
                    
                    
                    returnarr[0] = r ;
                    returnarr[1] = c ;
                    
                    parkinfo[r][c] = -1;
                    x = 1;
                    // break;
                    return;
                    
                    
                }
            }
            //      }//omp end
            
            
            //   }//omp critical
            if (x==1) break;
            
        }
    }
    
    
    if(r == 4){
        returnarr[0]=-1;
        returnarr[1]=-1;
    }
    return ;
}

void displayParkingParallel(){
    omp_set_num_threads(10);
#pragma omp parallel for
    for (int r = 0 ; r < 4 ; r++ )
    {
        for ( int c = 0 ; c < 10 ; c++ )
        {
            printf("%d\t ",parkinfo[r][c]);
        }
        printf("\n");
  		}
}

void displayParking(){

    for (int r = 0 ; r < 4 ; r++ )
    {
        for ( int c = 0 ; c < 10 ; c++ )
        {
            printf("%d\t ",parkinfo[r][c]);
        }
        printf("\n");
  		}
}

struct Vehicle * add ( int row, int col, int num, bool parkStatus)
{
    struct Vehicle *v ;
    v = ( struct Vehicle * ) malloc ( sizeof ( struct Vehicle ) ) ;
    //v -> licenceNo = t ;
    v -> row = row ;
    v -> col = col ;
    vehiclecount++ ;
   	parkinfo[row][col] = num ;
    return v ;
}

void getRowColumnOfVehicle(int num, int* returnarray)
{
    int r = 0;
    for (r = 0 ; r < 4 ; r++ )
    {
        for ( int c = 0 ; c < 10 ; c++ )
        {
            if ( parkinfo[r][c] == num){
                returnarray[0] = r;
                returnarray[1] = c;
                return;
            }
        }
  		}
    if(r == 4){
        returnarray[0]=-1;
        returnarray[1]=-1;
    }
}

void deleteVehicle(struct Vehicle *v){
    printf("\n Row i delete....  ");
    fprintf(stderr, "\n Row i delete.... %d  col... %d" ,v->row, v->col);
    parkinfo[v -> row][v -> col] = 0 ;
    vehiclecount--;

    parkinfo[v -> row][v -> col] = 0 ;
    vehiclecount--;
}

int randomGenerator(){
    int random=rand() % 40+1;
    for (int r = 0 ; r < 4 ; r++ )
    {
        for ( int c = 0 ; c < 10 ; c++ )
        {
            
        }
  		}
}

int main( )
{
    int finish=1, choice, number=0, row = 0, col = 0 ;
    std::string parkYesNo;
    int returnedArr[2];
    int returnedRowColArr[2];
    
    struct Vehicle *veh[4][10] ;
    double startTime = omp_get_wtime();
    
    system ( "clear" ) ;
    while(finish)
    {
        printf ( "\nCar Parking\n" ) ;
        printf ( "1. Enter Parking\n" ) ;
        printf ( "2. Total no. of vehicles parked\n");
        printf ( "3. Display\n");
        printf ( "4. Exit\n");
        
        printf ( "Enter your choice \n");
        scanf ( "%d", &choice ) ;
        auto dt_s = high_resolution_clock::now();
        
        
        switch (choice)
        {
            case 1 :
                printf ( "\nEntry in parking: \n" ) ;
                printf ( "Do you want to park : (yes/no) " );
                scanf ( "%s", &parkYesNo ) ;
                
                
                if (parkYesNo.compare("yes"))
                {
                    omp_set_num_threads(2);
#pragma omp parallel for
                    for(int i=0;i<2;i++)
                    { int row1 = 0;
                        int col1 = 0;
                        
                        printf("Thread Number %d.. time-- %f",omp_get_thread_num(), startTime);
                        
                        time_t rawtime;
                        struct tm * timeinfo;
                        time ( &rawtime );
                        timeinfo = localtime ( &rawtime );
                        
#pragma omp critical
                        {
                            
                            getfreeplace(returnedArr);
                            
                            if(returnedArr[0] != -1 && returnedArr[1] != -1 ){
                                row1 = returnedArr[0];
                                col1 = returnedArr[1];
                                printf("\n row--- %d   col...%d... value.. %d..", row1, col1, parkinfo[row][col]);
                                number = rand() % 40 + 1;
                                printf ( "\nNumber: ***%d\n",number) ;
                                veh[row][col] = add (row1, col1, number, true);
                                
                                
                                printf ("\nSJSU North Parking Lot\nReceipt No:%d\n=====================\n",vehiclecount) ;
                                printf ( "%s", asctime (timeinfo));
                                printf("*******Thread Number*** %d\n",omp_get_thread_num());
                                printf ("Parking ticket no: %d",number) ;
                                printf ( "\n-------------------\n");
                            }
                            else{
                                printf ( "\nNo parking slot free to park\n" ) ;
                            }
                        }//omp critical end
                        startTime = omp_get_wtime();
                        if(row1 != -1 && col1 != -1){
#pragma omp critical
                            {
                                
                                printf("/n row --- %d, col --- %d\n", row1, col1);
                            }
                            while( (omp_get_wtime() - startTime) < 2.0){
                                // printf("sleeping.... %d",omp_get_thread_num());
                            }//end while
                            
                            // displayParking();
#pragma omp critical
                            {
                                printf("\n after delete\n");
                            }
                            printf("\n row --XXXX- %d, col -XXXX-- %d\n", row1, col1);
                            deleteVehicle(veh[row1][col1]);
                            //free(veh[row1][col1]);
                            // veh[row1][col1] = NULL;
                            // displayParking();
                            
                        }
                    }//end for
                }
                
                else
                {
                    printf ( "Exit Direction\n" ) ;
                }
                printf ( "\nPress any key to continue...\n" ) ;
                getchar();
            {
                printf("time start.... %lu",dt_s);
                auto dt1 = high_resolution_clock::now();
                auto dt = duration_cast<nanoseconds> (high_resolution_clock::now() - dt_s);
                printf("\n new dt = %lu  ",dt1);
                printf( "\n dt = %lu ns \n",dt.count()); }
                // printf("agreement : %.3f ",(ref - val));
                // std::cout << "agreement: " << std::setprecision(3) << (ref - val) << "\n";
                break ;
            case 2 :
                printf ( "Total vehicles parked: %d\n", vehiclecount ) ;
                printf ( "\nPress any key to continue...\n") ;
                getchar();
                break ;
            case 3 :
                printf ( "Parking Lot Display\n") ;
                displayParking();
                printf ( "Parking Lot Parallel Display\n") ;
                displayParkingParallel();
                printf ( "\nPress any key to continue...\n") ;
                getchar();
                break ;
            case 4 :
                printf ( "Enter the Ticket num\n") ;
                scanf ( "%d", &number ) ;
                getRowColumnOfVehicle(number,returnedRowColArr);
                if(returnedRowColArr[0]!=-1 && returnedRowColArr[1]!=-1)
                {
                    deleteVehicle(veh[returnedRowColArr[0]][returnedRowColArr[1]]);
                    free(veh[returnedRowColArr[0]][returnedRowColArr[1]]);
                    veh[returnedRowColArr[0]][returnedRowColArr[1]] = NULL;
                }
                printf ( "\nPress any key to continue...\n") ;
                getchar();
                break ;
            default:
                finish = 0 ;
                return 0;
        }
    }
    
    
}
