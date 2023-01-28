#include <iostream>
#include <pthread.h>

using namespace std;

int invalidRow, inavalidCol;
int flag=1;

struct parameters{
    int row,col;
    int (* arr)[9];
};

void * checkRow(void * params) {
    //if another thread has identified and error
    if(flag==0){
        pthread_exit(NULL);
    }
    
    parameters * data = (parameters *) params;
    int startRow= data->row;
    int startCol= data->col;
    
    for(int i= startRow; i<9; ++i) {
        //1d array of zeros
        int row[10] = {0};
        
        for (int j= startCol; j<9; ++j) {
            int val= data->arr[i][j];
            //cout<<val<<endl;
            if(val<1 || val>10){
                cout<<"Number is out of bound"<<endl;
                invalidRow= i;
                inavalidCol= j;
                flag=0;
                pthread_exit(NULL);
            }
            //cout<<row[val]<<endl;
            if (row[val]!= 0) {
                cout<<"Number is of repeated value"<<endl;
                invalidRow= i;
                inavalidCol= j;
                flag=0;
                pthread_exit(NULL);
            }
            else
                row[val] = 1;
        }
    }
    return (void *) 1;
}

void * checkCol(void * params) {
    //if another thread has identified and error
    if(flag==0){
        pthread_exit(NULL);
    }
    
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startCol = data->col;
    
    for (int i= startCol; i < 9; ++i) {
        int col[10]= {0};
        for (int j= startRow; j < 9; ++j) {
            int val= data->arr[j][i];
            if(val<1 || val>10){
                cout<<"Number is out of bound"<<endl;
                invalidRow= i;
                inavalidCol= j;
                flag=0;
                pthread_exit(NULL);
            }
            if (col[val]!= 0) {
                cout<<"Number is of repeated value"<<endl;
                invalidRow= i;
                inavalidCol= j;
                flag=0;
                
                pthread_exit(NULL);
            }
            else
                col[val] = 1;
        }
    }
    return (void *) 1;
}

void * checkSubGrid(void * params) {
    //if another thread has identified and error
    if(flag==0){
        pthread_exit(NULL);
    }
    
    parameters * data = (parameters *) params;
    int startRow= data->row;
    int startCol= data->col;
    int saved[10]= {0};
    
    for (int i= startRow; i<startRow + 3; ++i) {
        for (int j= startCol; j<startCol + 3; ++j) {
            int val= data->arr[i][j];
            if(val<1 || val>10){
                cout<<"Number is out of bound"<<endl;
                invalidRow= i;
                inavalidCol= j;
                flag=0;
                pthread_exit(NULL);
            }
            if (saved[val] != 0) {
                invalidRow= i;
                inavalidCol= j;
                flag=0;
                
                pthread_exit(NULL);
            }
            else
                saved[val] = 1;
        }
    }
    return (void *) 1;
}



 void printGrid(int arr[9][9]){
    
    for(int row= 0; row<9; row++){
		for(int col= 0; col<9; col++){
		    cout<<arr[row][col]<<(col + 1 < 9 ? ", " : "\n"); //tenary operator
		}
	}
}
//print function for 3x3 sub grids
void printSubGrids(int arr[9][9]){
    int r=9;
    int c=9;
    
    //not used
    int startRow= r - (r % 3);
    int startCol= c - (c % 3);
   
   //sub grid1
   cout<<"Sub grid 1"<<endl;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout<<arr[i][j]<<(j + 1 < 3 ? ", " : "\n");
            //cout<<"i: "<<i<< " j: "<< j<<endl; 
        }
    }
    cout<<"\nSub grid 2"<<endl;
    for (int i = 0; i < 3; i++){
        for (int j = 3; j < 6; j++){
            cout<<arr[i][j]<<(j + 1 < 6 ? ", " : "\n");
        }
    }
    cout<<"\nSub grid 3"<<endl;
    for (int i = 0; i < 3; i++){
        for (int j = 6; j < 9; j++){
            cout<<arr[i][j]<<(j + 1 < 9 ? ", " : "\n");
        }
    }
    cout<<"\nSub grid 4"<<endl;
    for (int i = 3; i < 6; i++){
        for (int j = 0; j < 3; j++){
            cout<<arr[i][j]<<(j + 1 < 3 ? ", " : "\n");
        }
    }
    cout<<"\nSub grid 5"<<endl;
    for (int i = 3; i < 6; i++){
        for (int j = 3; j < 6; j++){
            cout<<arr[i][j]<<(j + 1 < 6 ? ", " : "\n");
        }
    }
    cout<<"\nSub grid 6"<<endl;
    for (int i = 3; i < 6; i++){
        for (int j = 6; j < 9; j++){
            cout<<arr[i][j]<<(j + 1 < 9 ? ", " : "\n");
        }
    }
    cout<<"\nSub grid 7"<<endl;
    for (int i = 6; i < 9; i++){
        for (int j = 0; j < 3; j++){
            cout<<arr[i][j]<<(j + 1 < 3 ? ", " : "\n");
        }
    }
    cout<<"\nSub grid 8"<<endl;
    for (int i = 6; i < 9; i++){
        for (int j = 3; j < 6; j++){
            cout<<arr[i][j]<<(j + 1 < 6 ? ", " : "\n");
        }
    }
    cout<<"\nSub grid 9"<<endl;
    for (int i = 6; i < 9; i++){
        for (int j = 6; j < 9; j++){
            cout<<arr[i][j]<<(j + 1 < 9 ? ", " : "\n");
        }
    }
}

void* parentThread(void* arg)
{
    
  
    return (void *) 0;
}

int main(){
    
    int mainMaxSize=9;
    pthread_t ptid;     //could not create parent thread because of type casting errors
    void * parentFlag;
    
    
    int arr[9][9] = {  
            {6, 2, 4, 5, 3, 9, 1, 8, 7},
            {5, 1, 9, 7, 2, 8, 6, 3, 4},
            {8, 3, 7, 6, 1, 4, 2, 9, 5},
            {1, 4, 3, 8, 6, 5, 7, 2, 9},
            {9, 5, 8, 2, 4, 7, 3, 6, 1},
            {7, 6, 2, 3, 9, 1, 4, 5, 8},
            {3, 7, 1, 9, 5, 6, 8, 4, 2},
            {4, 9, 6, 1, 8, 2, 5, 7, 3},
            {2, 8, 5, 4, 7, 3, 9, 1, 6}
        };
        
    //___________________________________________________________    
    pthread_create(&ptid, NULL, &parentThread, (void *) arr);
        
    pthread_join(ptid, &parentFlag);
    //___________________________________________________________  
    
    //creating objects
    parameters *RowObj = new parameters;
    RowObj->row = 0;
    RowObj->col = 0;
    RowObj->arr = arr;
    
    parameters *ColObj = new parameters;
    ColObj->row = 0;
    ColObj->col = 0;
    ColObj->arr = arr;
    
    
    //sub grid1
    parameters *obj1 = new parameters;
    obj1->row = 0;
    obj1->col = 0;
    obj1->arr = arr;
    //sub grid2
    parameters *obj2 = new parameters;
    obj2->row = 0;
    obj2->col = 3;
    obj2->arr = arr;
    //sub grid3
    parameters *obj3 = new parameters;
    obj3->row = 0;
    obj3->col = 6;
    obj3->arr = arr;
    //sub grid4
    parameters *obj4 = new parameters;
    obj4->row = 3;
    obj4->col = 0;
    obj4->arr = arr;
    //sub grid5
    parameters *obj5 = new parameters;
    obj5->row = 3;
    obj5->col = 3;
    obj5->arr = arr;
    //sub grid6
    parameters *obj6 = new parameters;
    obj6->row = 3;
    obj6->col = 6;
    obj6->arr = arr;
    //sub grid7
    parameters *obj7 = new parameters;
    obj7->row = 6;
    obj7->col = 0;
    obj7->arr = arr;
    //sub grid8
    parameters *obj8 = new parameters;
    obj8->row = 6;
    obj8->col = 3;
    obj8->arr = arr;
    //sub grid9
    parameters *obj9 = new parameters;
    obj9->row = 6;
    obj9->col = 6;
    obj9->arr = arr;
    
    
    pthread_t Rowthread, Colthread;
    pthread_t thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;
    
    //Condition: Thread will return the value to Main thread.
    //can be used to tell if numbers in puzzel are valid if value is 1 and O for invalid
    void * all_rows;
    void * all_cols;
    void * square1;
    void * square2;
    void * square3;
    void * square4;
    void * square5;
    void * square6;
    void * square7;
    void * square8;
    void * square9;
    
    pthread_create(&Rowthread, NULL, checkRow, (void *) RowObj);
    pthread_create(&Colthread, NULL, checkCol, (void *) ColObj);
    
    pthread_create(&thread1, NULL, checkSubGrid, (void *) obj1);
    pthread_create(&thread2, NULL, checkSubGrid, (void *) obj2);
    pthread_create(&thread3, NULL, checkSubGrid, (void *) obj3);
    pthread_create(&thread4, NULL, checkSubGrid, (void *) obj4);
    pthread_create(&thread5, NULL, checkSubGrid, (void *) obj5);
    pthread_create(&thread6, NULL, checkSubGrid, (void *) obj6);
    pthread_create(&thread7, NULL, checkSubGrid, (void *) obj7);
    pthread_create(&thread8, NULL, checkSubGrid, (void *) obj8);
    pthread_create(&thread9, NULL, checkSubGrid, (void *) obj9);

    
    //will return flag values, 1 for success and 0 for failuire
    pthread_join(Rowthread, &all_rows);
    pthread_join(Colthread, &all_cols);
    pthread_join(thread1, &square1);
    pthread_join(thread2, &square2);
    pthread_join(thread3, &square3);
    pthread_join(thread4, &square4);
    pthread_join(thread5, &square5);
    pthread_join(thread6, &square6);
    pthread_join(thread7, &square7);
    pthread_join(thread8, &square8);
    pthread_join(thread9, &square9);
    
    
    if (flag==1) {
        cout<<"Puzzle HAS been solved"<<endl;
    }
    else{
        cout<<"Puzzle has (NOT) been solved\n"<<endl;
        cout<<"Invalid entry at: ("<<invalidRow<<","<<inavalidCol<<") = "<<arr[invalidRow][inavalidCol]<<endl;
        cout<<"Inavalid Coloumn: "<<inavalidCol<<endl;
        cout<<"Inavalid Row: "<<invalidRow<<endl;
    }
    
    
    cout<<endl;
    printGrid(arr);
    
    return 0;
}
// create a 9x9 matrix grid
//initilize no enteries as the number 0, because 0 is not used in sudoku
//find if there is a null value in the Board

//IF there exists a null value, then fill it
//before filling, check if the number to be filled can be assigned following the rules
//make 3 functions to check those rules:
// function 1, to check in row (1 thread assigned here)
// function 2, to check in col (1 thread assigned here)
// function 3, to check in the sub 3x3grids. total of 9 3x3sub grids (9 thread assigned here)

