#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

int arr[1000]; 
int arr1[1000]; 
int arr2[1000];  

int size = 0;  
int size1 = 0;  
int size2 = 0; 
 
int matran[100][100];
bool visitedByRobot1[100][100]; 
bool visited[100][100];
bool visited2[100][100];
bool visited3[100][100]; 
int rows, cols;

int board[][5]={{2, 1, 14, 12, 17},
				{3, 16, 22, 91, 23},
				{4, 56, 87, 31, 65},
				{27, 43, 90, 100, 101},
				{76, 54, 32, 99, 66},
				{178, 154, 150, 200, 543}}; 

int board2[6][5]; 
void Random(){
	int rows=6, cols=5;
    srand(time(0));
    int board2[rows][cols];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <=cols; j++) {
            board2[i][j] = rand() % 100 + 1; 
        }
    }

    cout<<"_____"<<"______"<<"_____"<<"_____"<<"_______"<<endl; 
	cout<<"| "<< board2[0][0]<< " | "<< board2[0][1]<< " | "<< board2[0][2]<< " | "<< board2[0][3]<< " | "<< board2[0][4]<< "  |"<<endl;
	cout<<"|----|"<<"----|"<<"----|"<<"----|"<<"-----|"<<endl; 
	cout<<"| "<< board2[1][0]<< " | "<< board2[1][1]<< " | "<< board2[1][2]<< " | "<< board2[1][3]<< " | "<< board2[1][4]<< "  |"<<endl;
	cout<<"|----|"<<"----|"<<"----|"<<"----|"<<"-----|"<<endl;
	cout<<"| "<< board2[2][0]<< " | "<< board2[2][1]<< " | "<< board2[2][2]<< " | "<< board2[2][3]<< " | "<< board2[2][4]<< "  |"<<endl; 
	cout<<"|----|"<<"----|"<<"----|"<<"----|"<<"-----|"<<endl;
	cout<<"| "<< board2[3][0]<< " | "<< board2[3][1]<< " | "<< board2[3][2]<< " | "<< board2[3][3]<< " | "<< board2[3][4]<< "  |"<<endl;
	cout<<"|----|"<<"----|"<<"----|"<<"----|"<<"-----|"<<endl;
	cout<<"| "<< board2[4][0]<< " | "<< board2[4][1]<< " | "<< board2[4][2]<< " | "<< board2[4][3]<< " | "<< board2[4][4]<< "  | "<<endl;
	cout<<"|----|"<<"----|"<<"----|"<<"----|"<<"-----|"<<endl;
	cout<<"| "<< board2[5][0]<< " | "<< board2[5][1]<< " | "<< board2[5][2]<< " | "<< board2[5][3]<< " | "<< board2[5][4]<< "  |"<<endl;
	cout<<"|----"<<"----"<<"----"<<"----"<<"----------|"<<endl;
}
	
void drawBoard(){
	cout<<"_____"<<"______"<<"_____"<<"_____"<<"______"<<endl; 
	cout<<"| "<< board[0][0]<< "  | "<< board[0][1]<< "  | "<< board[0][2]<< " | "<< board[0][3]<< " | "<< board[0][4]<< "  |"<<endl;
	cout<<"|----|"<<"----|"<<"----|"<<"----|"<<"-----|"<<endl; 
	cout<<"| "<< board[1][0]<< "  | "<< board[1][1]<< " | "<< board[1][2]<< " | "<< board[1][3]<< " | "<< board[1][4]<< "  |"<<endl;
	cout<<"|----|"<<"----|"<<"----|"<<"----|"<<"-----|"<<endl;
	cout<<"| "<< board[2][0]<< "  | "<< board[2][1]<< " | "<< board[2][2]<< " | "<< board[2][3]<< " | "<< board[2][4]<< "  |"<<endl; 
	cout<<"|----|"<<"----|"<<"----|"<<"----|"<<"-----|"<<endl;
	cout<<"| "<< board[3][0]<< " | "<< board[3][1]<< " | "<< board[3][2]<< " |"<< board[3][3]<< " | "<< board[3][4]<< " |"<<endl;
	cout<<"|----|"<<"----|"<<"----|"<<"----|"<<"-----|"<<endl;
	cout<<"| "<< board[4][0]<< " | "<< board[4][1]<< " | "<< board[4][2]<< " | "<< board[4][3]<< " | "<< board[4][4]<< "  | "<<endl;
	cout<<"|----|"<<"----|"<<"----|"<<"----|"<<"-----|"<<endl;
	cout<<"|"<< board[5][0]<< " |"<< board[5][1]<< " |"<< board[5][2]<< " |"<< board[5][3]<< " | "<<board[5][4]<< " |"<<endl;
	cout<<"|----"<<"----"<<"----"<<"----"<<"---------|"<<endl;
} 
 
// Hàm tính tinh tung gia tri cua 1 mang 
int totalArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Hàm kiem tra 1 0 co hop le de di chuyen không
bool hopLe(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y]);
}

bool hopLeRobot1(int x, int y){
	return (hopLe(x, y) && !visitedByRobot1[x][y]); 
} 

// Hàm di chuyen den o co gia tri lon nhat xung quanh
void findMaxNeighbor(int& x, int& y) {
    int maxVal = 0;
    int newStart_x = 0, newStart_y=0;

    // Kiem tra các ô xung quanh và tim ô có giá tri lon nhat
    int dx[] = {-1, 1, 0, 0}; // hang
    int dy[] = {0, 0, -1, 1}; // cot

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (hopLe(nx, ny) && matran[nx][ny] > maxVal) {
            maxVal = matran[nx][ny];
            newStart_x = nx;
            newStart_y = ny;
        }
    }

    // Di chuyen toi o có giá tri lon nhat
    x = newStart_x;
    y = newStart_y;
}

// Ham de quy tim duong di toi uu 
void toiuu(int x, int y, int b[], int b_length, int total, int board[][5]) {
    // Kiem tra dieu kien dung  
    if (!hopLe(x, y)) {
        // Kiem tra xem duong di hien tai co toi uu không
        if (totalArray(b, b_length) == total) {
            size = b_length;
            for (int i = 0; i < b_length; i++) {
                arr[i] = b[i];
				/* 
                int row=arr[i]/5;
				int col=arr[i]%5;
				board[row][col]=matran[x][y]; */
            }
        }
        return;
    }

    // Cap nhat duong di và tung gia tri 
    b[b_length] = matran[x][y];
    b_length++;
    total += matran[x][y];

    // Dánh dau o da di qua
    visited[x][y] = true;
    //board[x][y]=0; 

    // Di chuyen den o co gia tri lon nhat xung quanh
    findMaxNeighbor(x, y);

    // Ðe quy tim duong di toi o tiep theo 
    toiuu(x, y, b, b_length, total, board);

    // Tro lai vi tri ban dau cua duong di và visited
    b_length--;  
	//board[x][y]=0; 
    visited[x][y] = false;
}

void toiuu2robot(int x1, int y1, int x2, int y2, int b1[], int b2[], int b_length1, int b_length2, int total1, int total2){
	if(!hopLe(x1, y1) || !hopLe(x2, y2)){
		if(totalArray(b1, b_length1) == total1 || totalArray(b2, b_length2) == total2){
			size1=b_length1;
			size2=b_length2;
			for(int i=0; i<b_length1; i++){
			 	arr1[i]=b1[i];
			} 
			for(int i=0; i<b_length2; i++){
				arr2[i]=b2[i]; 
			} 
		}
		return; 
	} 
	
	//cap nhat duong di va tung gia tri
	b1[b_length1]=matran[x1][y1];
	b2[b_length2]=matran[x2][y2];
	b_length1++;
	b_length2++;
	total1+=matran[x1][y1];
	total2+=matran[x2][y2]; 
	
	//danh dau o da di qua
	visited[x1][y1]=true;
	visited[x2][y2]=true;
	
	//di chuyen toi o co gia tri lon nhat xuung quanh robot1
	findMaxNeighbor(x1, y1);
	//di chuyen toi o co gia tri lon nhat xung quanh robot2
	findMaxNeighbor(x2, y2);
	
	//de quy tim duong di toi uu cho 2 robot
	toiuu2robot(x1, y1, x2, y2, b1, b2, b_length1, b_length2, total1, total2);
	
	//tro lai vi tri ban dau và visited
	b_length1--;
	b_length2--;
	visited[x1][y1]=false;
	visited[x2][y2]=false; 
} 
void xoaMangVisited(){
	for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            visited[i][j] = false;
        }
	}
} 
/*
void get_robotMove(int board[][5], int* arr, int size) {
    // Ðánh dau nhung ðuong di toi uu cua robot 1  
    for (int i = 0; i < size; i++) {
        int row = arr[i] / 5;
		int col = arr[i] % 5;  
		board[row][col]=0;  
    }
}

void printUpdatedBoard(int board[][5], int row, int col ) {
    cout << "_____" << "______" << "_____" << "_____" << "______" << endl;
    for (int i = 0; i < row; i++) {
        cout << "|  ";
        for (int j = 0; j < col; j++) {
            if (board[i][j] == 0) {
                cout << "0 | ";
            } else {
                cout << board[i][j] << "   | ";
            }
        }
        cout << endl;
        cout << "|----|" << "----|" << "----|" << "----|" << "-----|" << endl;
    }
}
*/

void findMaxNeighborr(int x, int y, int robot, int otherX, int otherY) {
    int maxVal = INT_MIN;
    int maxNeighborX = x;
    int maxNeighborY = y;

    // Check all neighboring positions
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int newX = x + dx;
            int newY = y + dy;

            // Exclude the current position and out-of-bounds positions
            if ((dx != 0 || dy != 0) && hopLe(newX, newY) && (newX != otherX || newY != otherY)) {
                // Update the maximum neighbor value and position
                if (matran[newX][newY] > maxVal && !visited[newX][newY]) {
                    maxVal = matran[newX][newY];
                    maxNeighborX = newX;
                    maxNeighborY = newY;
                }
            }
        }
    }

    // Update the current position based on the maximum neighbor
    if (robot == 1) {
        int x1 = maxNeighborX;
        int y1 = maxNeighborY;
    } else if (robot == 2) {
        int x2 = maxNeighborX;
        int y2 = maxNeighborY;
    }
}

void KoTrung(int x1, int y1, int x2, int y2, int b1[], int b2[], int b_length1, int b_length2, int total1, int total2) {
    int mangtrung[100], trung = 0;

    if (!hopLe(x1, y1) || !hopLe(x2, y2)) {
        if (totalArray(b1, b_length1) == total1 || totalArray(b2, b_length2) == total2) {
            size1 = b_length1;
            size2 = b_length2;
            for (int i = 0; i < b_length1; i++) {
                arr1[i] = b1[i];
            }
            for (int i = 0; i < b_length2; i++) {
                arr2[i] = b2[i];
            }
        }
        return;
    }

    // Ki?m tra v? trí hi?n t?i c?a c? hai con robot
    bool visited1 = visited[x1][y1];
    bool visited2 = visited[x2][y2];

    // N?u c? hai con robot ð? ði qua v? trí hi?n t?i
    if (visited1 && visited2) {
        return;
    }

    // N?u con robot 1 ð? ði qua v? trí hi?n t?i, ch? x? l? con robot 2
    if (visited1) {
        // Update path và total cho Robot 2
        b2[b_length2] = matran[x2][y2];
        b_length2++;
        total2 += matran[x2][y2];

        // Ðánh d?u v? trí hi?n t?i c?a Robot 2 là ð? ði qua
        visited[x2][y2] = true;

        // T?m các v? trí lân c?n t?i ða cho Robot 2
        findMaxNeighborr(x2, y2, 2, x1, y1);

        // G?i ð? quy cho Robot 2
        KoTrung(x1, y1, x2, y2, b1, b2, b_length1, b_length2, total1, total2);

        // Revert các thay ð?i sau khi th? các ðý?ng ði c?a Robot 2
        b_length2--;
        visited[x2][y2] = false;
    }

    // N?u con robot 2 ð? ði qua v? trí hi?n t?i, ch? x? l? con robot 1
    else if (visited2) {
        // Update path và total cho Robot 1
        b1[b_length1] = matran[x1][y1];
        b_length1++;
        total1 += matran[x1][y1];

        // Ðánh d?u v? trí hi?n t?i c?a Robot 1 là ð? ði qua
        visited[x1][y1] = true;

        // T?m các v? trí lân c?n t?i ða cho Robot 1
        findMaxNeighborr(x1, y1, 1, x2, y2);

        // G?i ð? quy cho Robot 1
        KoTrung(x1, y1, x2, y2, b1, b2, b_length1, b_length2, total1, total2);

        // Revert các thay ð?i sau khi th? các ðý?ng ði c?a Robot 1
        b_length1--;
        visited[x1][y1] = false;
    }

    // N?u c? hai con robot chýa ði qua v? trí hi?n t?i
    else {
        // Update path và total cho Robot 1
        b1[b_length1] = matran[x1][y1];
        b_length1++;
        total1 += matran[x1][y1];

        // Update path và total cho Robot 2
        b2[b_length2] = matran[x2][y2];
        b_length2++;
        total2 += matran[x2][y2];

        // Ðánh d?u v? trí hi?n t?i c?a c? hai con robot là ð? ði qua
        visited[x1][y1] = true;
        visited[x2][y2] = true;

        // T?m các v? trí lân c?n t?i ða cho c? hai con robot
        findMaxNeighborr(x1, y1, 1, x2, y2);
        findMaxNeighborr(x2, y2, 2, x1, y1);

        // G?i ð? quy cho c? hai con robot
        KoTrung(x1, y1, x2, y2, b1, b2, b_length1, b_length2, total1, total2);

        // Revert các thay ð?i sau khi th? các ðý?ng ði c?a c? hai con robot
        b_length1--;
        b_length2--;
        visited[x1][y1] = false;
        visited[x2][y2] = false;
    }
}

void displayMatrix(const vector<vector<int> >& matrix, const vector<Point>& path) {
    int rows = matrix.size();
    int columns = matrix[0].size();

    vector<vector<string> > displayMatrix(rows, vector<string>(columns));

    // khoi tao ma tran hien thi voi gia tri ban dau tu ma tran so 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            displayMatrix[i][j] = intToString(matrix[i][j]);
        }
    }

    // Hien thi ma tran ban dau 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << setw(3) << displayMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Hien thi robot di chuyen trên ma tran
    for (vector<Point>::const_iterator it = path.begin(); it != path.end(); ++it) {
        displayMatrix[it->x][it->y] = "X"; // doi ô di qua thanh "X"

        // Xoa man hinh 
        system("cls"); // Windows

        // Hien thi ma tran voi robot di chuyen
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << setw(3) << displayMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        // Delay de chuong trinh chay cham 
        Sleep(500); // 500ms (Windows)
    }

    // doi các ô da di qua thành "X"
    for (vector<Point>::const_iterator it = path.begin(); it != path.end(); ++it) {
        displayMatrix[it->x][it->y] = "X";
    }
}
int main() {
	int choice; 
	int start_x1, start_y1;
	int start_x2, start_y2;
	int start_x, start_y;
	int score1=0, score2=0;
	do{
		//Random();
		//cout<<endl<<endl;
		 
	for(int i = 0; i <= 28; i++){
    	usleep(100000);  
    	cout << "^~";  
  	} 
  	cout<<endl<<endl; 
	  
    cout<<"0"; 
	for(int i=1; i<=55; i++){
		usleep(10000);
		cout<<"="; 
	}
	cout<<"0\n"; 
    cout<<"|                                                       |\n"; 
    cout<<"|    	          ~~$GREEDY ROBOTS$~~	                |\n"; 
    cout<<"|                                                       |\n";  
    cout<<"| ----------------------------------------------------  |\n"; 
    cout<<"|                      << MENU >>                       |\n"; 
    cout<<"|                                                       |\n"; 
	cout<<"| Choose Mode (1-4):                                    |\n"; 
	cout<<"|                                                       |\n"; 
    cout<<"| 1. Tim duong di toi uu cho robot (Default Mode).      |\n";
	cout<<"| 2. Tim duong di toi uu cho 2 robot va cac diem trung. |\n"; 
	cout<<"| 3. Dat vi tri bat ky cho 2 robot nhung vi tri di roi  |\n";
	cout<<"| se khong duoc di lai.                                 |\n"; 
	cout<<"| 4. Thoat (ESC).                                       |\n";
	cout<<"|                                                       |\n"; 
	cout<<"| ----------------------------------------------------  |\n"; 
	cout<<"|    	    ~~~~~~~Other Information~~~~~~              |\n";
	cout<<"|                                                       |\n"; 
	cout<<"| 5. About Me.		                                |\n"; 
	cout<<"| 6. Game Rules                                         |\n"; 
	cout<<"| 7. See My Other Project!                              |\n"; 
	cout<<"|                                                       |\n"; 
	cout<<"0"; 
	for(int i=1; i<=55; i++){
		usleep(10000);
		cout<<"="; 
	}
	cout<<"0\n";  
	
	cin>>choice;
	
	if (choice == 4) {
		cout<<"Thanks For Playing\n\n"; 
        cout << "Hen gap lai";
        for (int i = 1; i <= 3; i++) {
            sleep(1);
            cout << "! ";
        }
        cout << endl;
        break;
    }
        
	ifstream input_file("input.txt");
    // Kiem tra xem file input.txt có ton tai hay không
    if (!input_file) {
        cout << "Không thay file input.txt" << endl;
        break;
    }
        		
    input_file >> rows >> cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            input_file >> matran[i][j];
        }
	}
    input_file.close();
        		
	switch(choice){
		case 1:
			{
				cout<<"so do di goc!"<<endl;
				drawBoard(); 
        		//int start_x, start_y;
        		do{ 
        			cout<<"Hay nhap vi tri bat dau cho robot: "<<endl;
					cin>>start_x>>start_y; 
				}while(start_x > rows || start_y > cols); 
				cout<<"Robot: "<<"+) dong: "<< start_x <<" "<<"+) cot: "<< start_y <<endl<<endl;  
				xoaMangVisited();
        		toiuu(start_x, start_y, arr, 0, 0, board);
        		//get_robotMove(board, arr, size);
        		//cout<<"Duong di cua Robot 1!"<<endl; 
        		//printUpdatedBoard(board, 6, 5); 
        		cout<<endl; 
        		displayMatrix()
        		// Ghi ket qua vào file output.txt
        		ofstream output_file("output.txt");
        		if (!output_file) {
            		cout << "file output.txt khong tim thay!" << endl;
            		break;
        		} 
        		output_file << size <<endl;
        		for (int i = 0; i < size; i++) {
            		output_file << arr[i] << " ";
        		}
        		cout<<"Dang tien hanh tim duong di cho robot: ";
        		
        		for(int i=0; i<=2; i++){
        			sleep(1);
					cout<<". "; 
				} 
				cout<<endl<<endl; 
        		output_file.close();
        		cout << "Duong di toi uu cua robot duoc ghi vào File output.txt" << endl; 
        		cout<<endl;
				cout<<"(==>> Keo xuong duoi dung cac chuc nang khac cua GAME! ! ! <<== )"<<endl;	
    		}
			break;
			
		case 2:
			{
				int mangTrung[1000];
				int trung=0;  
        		int score1=0, score2=0;
        		//int start_x1, start_y1;
        		//int start_x2, start_y2;
        		cout<<"So do goc!\n";
				drawBoard(); 
				cout<<endl; 
				
				do{ 
        			cout<<"nhap vi tri bat dau cua robot 1: \n";
					cin>>start_x1>>start_y1;
				
					cout<<"nhap vi tri bat dau cua robot 2: \n";
					cin>>start_x2>>start_y2; 
				}while(start_x1 > rows || start_y1 > cols || start_x2 > rows || start_y2 > cols);
				 
				cout<<">> >>Ban dat Robot 1 o vi tri: "<<endl;
				cout<<"- Robot 1: "<<"+) dong: "<< start_x1 <<" "<<"+) cot: "<< start_y1 <<endl;  
				cout<<"- Robot 2: "<<"+) dong: "<< start_x2 <<" "<<"+) cot: "<< start_y2 <<endl<<endl;  
				
        		// Goi hàm tim duong di toi uu cho 2 robot 
				xoaMangVisited();
    			
    			toiuu2robot(start_x1, start_y1, start_x2, start_y2, arr1, arr2, 0, 0, 0, 0); 

    			// Ghi ket qua vào file output.txt
    			ofstream output_file("output.txt");
    			if (!output_file) {
        			cout << "file output.txt khong tim thay!" << endl;
        			break;
    			}
				
				cout<<"Dang tien hanh tim duong di cho robot: ";
        		
        		for(int i=0; i<=2; i++){
        			sleep(1);
					cout<<". "; 
				} 
				cout<<endl<<endl;
				
    			// In ra duong di va so buoc cho robot 1
    			output_file << "Robot 1 " << endl; 
    			output_file <<"Steps Robot: "<< size1 << endl;
    			output_file <<"Robot Path: " ;
    			
    			for(int i=1; i<=29; i++){
					usleep(10000);
					cout<<"="; 
					}
				cout<<">> The Winner is: \n"; 
				
    			for (int i = 0; i < size1; i++) {
        			output_file << arr1[i] << " ";
        			score1+=arr1[i]; 
    			}
    			
				//output_file <<endl; 
				cout<<endl; 
				cout <<"  Robot 1 Score: "<<score1; 
				
    			// In ra duong di va so buoc cho robot 2
    			output_file << endl;
    			output_file << endl; 
    			
    			output_file << "Robot 2 "<< endl;
    			output_file <<"Steps Robot: "<< size2 << endl; 
    			output_file << "Robot Path: "; 
    			
    			for (int i = 0; i < size2; i++) {
        			output_file << arr2[i] << " ";
        			score2+=arr2[i]; 
    			}
    			
    			//output_file << endl; 
    			cout<<endl; 
    			cout <<"  Robot 2 Score: "<<score2<<endl; 
    			
				// In ra vi tri ma hai robot di trung nhau
				output_file << endl; 
				output_file << endl; 
				
    			output_file << "Vi tri ma hai robot di trung nhau:" << endl;
    			for (int i = 0; i < size1; i++) {
        			for (int j = 0; j < size2; j++) {
            			if (arr1[i] == arr2[j]) {
                			mangTrung[trung]=arr1[i];
							trung++;
							break; 
            			}
        			}
    			}
    			
    			for(int i=0; i<trung; i++){
    				output_file<<mangTrung[i]<<" "; 
				}  
				
    			// So sanh so buoc cua hai robot
    			if (score1 < score2) {
        			cout << endl;
        			for(int i=1; i<=29; i++){
						usleep(10000);
						cout<<"="; 
					} 
        			cout << ">> Robot 2 Win! ! !" << endl<<endl;
    			} 
				else if (score1 > score2) {
        			cout << endl;
        			for(int i=1; i<=29; i++){
						usleep(10000);
						cout<<"="; 
					} 
        			cout << ">> Robot 1 Win!" << endl<<endl;
    			} 
				else {
        			cout << endl;
        			for(int i=1; i<=29; i++){
						usleep(10000);
						cout<<"="; 
					} 
        			cout << ">> Draw!" << endl<<endl;
    			}
    			
    			output_file.close();
    			cout << "Duong di toi uu cua 2 robot duoc ghi vào file output.txt" << endl;
    			cout<<endl;
				cout<<"( ==>> Keo xuong duoi dung cac chuc nang khac cua GAME! ! ! <<== )"<<endl;  
			}
			break;
				 
		case 3:
			{
        		int trung[100], t=0; 
        		int score1=0, score2=0;
        		int step=0; 
				do{ 
        			cout<<"nhap vi tri bat dau cua robot 1: \n";
					cin>>start_x1>>start_y1;
				
					cout<<"nhap vi tri bat dau cua robot 2: \n";
					cin>>start_x2>>start_y2; 
				}while(start_x1 > rows || start_y1 > cols || start_x2 > rows || start_y2 > cols); 
				
				xoaMangVisited();
        		// Goi hàm tim duong di toi uu cho 2 robot
    			KoTrung(start_x1, start_y1, start_x2, start_y2, arr1, arr2, 0, 0, 0, 0);

    			// Ghi ket qua vào file output.txt
    			ofstream output_file("output.txt");
    			if (!output_file) {
        			cout << "file output.txt khong tim thay" << endl;
        			break;
    			}

    			// In ra duong di va so buoc cho robot 1
    			output_file << "Robot 1 "<< endl;
    			output_file <<"Steps Robot: "<< size2 << endl; 
    			output_file << "Robot Path: "; 
    			
    			for(int i=0; i<size1; i++){
    				output_file << arr1[i] <<" ";
					score1+=arr1[i];  
				} 
				
				output_file << endl; 
    			cout <<"Robot 1 Score: "<<score1<<endl; 
    			// In ra duong di va so buoc cho robot 2
    			output_file << endl;
    			output_file << endl; 
    			
    			output_file << "Robot 2 "<< endl; 
    			output_file << "Robot Path: ";
    			for (int i = 0; i < size2; i++) {
        				step++;
        				output_file << arr2[i] <<" ";
						score2+=arr2[i];
						break;  
    			}
    			output_file << endl; 
    			output_file <<"Steps Robot: "<< step << endl; 
    			output_file << endl; 
    			cout <<"Robot 2 Score: "<<score2<<endl; 
    			
    			// So sanh so buoc cua hai robot
    			cout <<"The winners is: "<< endl;
    			if (score1 < score2) {
        			cout << endl;
        			for(int i=1; i<=29; i++){
						usleep(10000);
						cout<<"="; 
					}
        			cout << ">> Robot 2 Win!" << endl;
    			} 
				else if (score1 > score2) {
        			cout << endl;
        			for(int i=1; i<=29; i++){
						usleep(10000);
						cout<<"="; 
					}
        			cout << ">> Robot 1 Win!" << endl;
    			} 
				else {
        			cout << endl;
        			for(int i=1; i<=29; i++){
						usleep(10000);
						cout<<"="; 
					}
        			cout << ">> Draw!" << endl;
    			}
    			
    			output_file.close();
    			cout << "Duong di va so buoc cua 2 robot duoc ghi vào file output.txt" << endl;
    			cout<<endl;
				cout<<"( ==>> Keo xuong duoi dung cac chuc nang khac cua GAME! ! ! <<== )"<<endl; 
			}
			break;
		
		case 5:
			{
				cout<<"          <<|>> GIOI THIEU BAN THAN! <<|>>\n"; 
				for(int i=1; i<=49; i++){
					usleep(10000);
					cout<<"_"; 
				} 
				cout<<endl; 
				cout<<"     Student: Vu Nguyen Phuong\n";
				cout<<endl; 
				cout<<"     MSSV: 2251120437\n";
				cout<<endl; 
				cout<<"     Class: CN22H\n";
				cout<<endl; 
				cout<<"     Major: Information Technology\n ";
				cout<<endl; 
				cout<<"     School: University Of Transport HCM City\n"; 
				for(int i=1; i<=49; i++){
					usleep(10000);
					cout<<"_"; 
				} 
				cout<<endl;
			}
			break;
			
		case 6:
			{ 	cout<<"0"; 
				for(int i=1; i<=71; i++){
					usleep(10000);
					cout<<"="; 
				}
				cout<<"0\n"; 
				cout<<"|                                                                       |\n"; 
				cout<<"|                             ~~~RULES~~~                               |\n";
				cout<<"|                                                                       |\n";
				cout<<"| (+) Robots di theo 4 huong (tren, duoi, trai, phai)                   |\n";
				cout<<"|                                                                       |\n";
				cout<<"| (+) Robots se di theo huong so co gia tri lon hon gia tri hien tai    |\n";
				cout<<"|                                                                       |\n";
				cout<<"| (+) O che do 1 Robot se tu dong di chuyen tu vi tri ban dau           |\n";
				cout<<"| ma nguoi choi dat                                                     |\n";
				cout<<"|                                                                       |\n"; 
				cout<<"| (+) O che do 2 nguoi choi se dat vi tri bat dau cho 2 robot           |\n";
				cout<<"| sau do se in ra nhung vi tri ma chung trung nhau va so sanh           |\n";
				cout<<"| con robot nao co so diem cao hon se thang                             |\n";
				cout<<"|                                                                       |\n"; 
				cout<<"| (+) O che do 3 nguoi choi se nhap vi tri bat dau cho 2 con robot      |\n";
				cout<<"| nhung vi tri ma robot di qua roi se khong duoc di nua sau khi 2 robot |\n";
				cout<<"| hoan thanh duong di, robot nao co so diem cao hon se thang            |\n"; 
				cout<<"|                                                                       |\n";
				cout<<"0"; 
				for(int i=1; i<=71; i++){
					usleep(10000);
					cout<<"="; 
				}
				cout<<"0\n"; 
				cout<<endl; 
			}
			break;
			
		case 7:
			{
				for(int i=1; i<=39; i++){
					usleep(10000);
					cout<<"~"; 
				} 
					cout<<endl; 
				cout<<"  Check out my other projects on GitHub\n";
				cout<<endl; 
				cout<<"  GitHub account: vuphuong1794\n";
				cout<<endl; 
				cout<<"  Gmail: Pvunguyen84@gmail.com\n"; 
				cout<<endl; 
				cout<<"  Zalo/Phone: 0783203982\n"; 
 
				for(int i=1; i<=39; i++){
					usleep(10000);
					cout<<"~"; 
				}
				cout<<endl; 
			}
			break;
			 
		default:
			cout<<"Lua chon cua ban ko hop le"; 
		}
		cout<<endl; 
		
	}while(choice != 4);
	
    return 0;
}

