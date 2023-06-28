
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
 
int matran[100][100], matrix[100][100];
bool visitedByRobot1[100][100]; 
bool visited[100][100]; 
int rows, cols;

int board[][5]={{2, 1, 14, 12, 17},
				{3, 16, 22, 91, 23},
				{4, 56, 87, 31, 65},
				{27, 43, 90, 100, 101},
				{76, 54, 32, 99, 66},
				{178, 154, 150, 200, 543}}; 

int board2[16][16];

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
 
struct Point {
    int x, y, value;
    Point(int x, int y, int value) : x(x), y(y), value(value) {}
};

string intToString(int value) {
    ostringstream oss;
    oss << value;
    return oss.str();
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

// Hàm di chuy?n ??n ô có giá tr? l?n nh?t xung quanh
bool findMaxNeighbor(int& x, int& y) { //allVisited dung cho mang trung 
    int maxVal = 0;
    int newStart_x = 0, newStart_y = 0;
    bool allVisited = true;

    // Kiem tra các ô xung quanh và t?m ô có giá tr? l?n nh?t
    int dx[] = {-1, 1, 0, 0}; // hàng
    int dy[] = {0, 0, -1, 1}; // c?t

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (hopLe(nx, ny)) {
            allVisited = false; // Ô ch?a ???c ?i qua
            if (matran[nx][ny] > maxVal) {
                maxVal = matran[nx][ny];
                newStart_x = nx;
                newStart_y = ny;
            }
        }
    }

     //N?u t?t c? các ô xung quanh ?? ???c ?i qua, d?ng l?i
    if (allVisited) {
        return false;
    }
	
    // Di chuy?n t?i ô có giá tr? l?n nh?t
    x = newStart_x;
    y = newStart_y;
    return true;
}

vector<Point> path;
// Ham de quy tim duong di toi uu 
void toiuu(int x, int y, int b[], int b_length, int total) {
    // Kiem tra dieu kien dung  
    if (!hopLe(x, y)) {
        // Kiem tra xem duong di hien tai co toi uu không
        if (totalArray(b, b_length) == total) {
            size = b_length;
            for (int i = 0; i < b_length; i++) {
                arr[i] = b[i];
            }
        }
        return;
    }

    b[b_length] = matran[x][y];
    path.push_back(Point(x, y, matran[x][y]));
    b_length++;
    total += matran[x][y];

    // Danh dau o da di qua
    visited[x][y] = true;

    // Di chuyen den o co gia tri lon nhat xung quanh
    findMaxNeighbor(x, y);

    toiuu(x, y, b, b_length, total);

    // Tro lai vi tri ban dau cua duong di và visited
    b_length--;  
    visited[x][y] = false;
}
vector<Point> point1, point2; 
void toiuu2(int x2, int y2, int b2[], int b_length2, int total2) {
    // Kiem tra dieu kien dung  
    if (!hopLe(x2, y2)) {
        // Kiem tra xem duong di hien tai co toi uu không
        if (totalArray(b2, b_length2) == total2) {
            size2 = b_length2;
            for (int i = 0; i < b_length2; i++) {
                arr2[i] = b2[i];
            }
        }
        return;
    }

    b2[b_length2] = matran[x2][y2];
    point2.push_back(Point(x2, y2, matran[x2][y2]));
    b_length2++;
    total2 += matran[x2][y2];

    // Danh dau o da di qua
    visited[x2][y2] = true;

    // Di chuyen den o co gia tri lon nhat xung quanh
    findMaxNeighbor(x2, y2);

    toiuu2(x2, y2, b2, b_length2, total2);

    // Tro lai vi tri ban dau cua duong di và visited
    b_length2--;  
    visited[x2][y2] = false;
}

 /*
vector<Point> point1, point2;  
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
	point1.push_back(Point(x1, y1, matran[x1][y1]));
	b2[b_length2]=matran[x2][y2];
	point2.push_back(Point(x2, y2, matran[x2][y2]));
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
*/

void findDistinctNeighbor(int& x, int& y, int currentValue, bool visited[100][100]) {
    int newstartx = 0, newstarty = 0;
    int dx[] = {-1, 1, 0, 0}; // Offsets for neighboring cells (up, right, down, left)
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (hopLe(nx, ny) && matran[nx][ny] != currentValue && !visited[nx][ny]) {
            newstartx = nx;
            newstarty = ny;
            break;
        } 
    }
    x = newstartx;
    y = newstarty;
}

 vector<int> uniqueArr1, uniqueArr2;
void test2(int x, int y, int x2, int y2, int b[], int b2[], int b_length, int b_length2, int total, int total2) {
    toiuu(x, y, b, b_length, total);
    toiuu2(x2, y2, b2, b_length2, total2);

    // T?m các s? không gi?ng trong m?ng arr và thêm vào uniqueArr1
    for (int i = 0; i < size; i++) {
        bool found = false;
        for (int j = 0; j < size2; j++) {
            if (arr[i] == arr2[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            uniqueArr1.push_back(arr[i]);
        }
    }

    // T?m các s? không gi?ng trong m?ng arr2 và thêm vào uniqueArr2
    for (int i = 0; i < size2; i++) {
        bool found = false;
        for (int j = 0; j < size; j++) {
            if (arr2[i] == arr[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            uniqueArr2.push_back(arr2[i]);
        }
    }

    // C?p nh?t m?ng arr và arr2
    size = uniqueArr1.size();
    size2 = uniqueArr2.size();

    for (int i = 0; i < size; i++) {
        arr[i] = uniqueArr1[i];
    }

    for (int i = 0; i < size2; i++) {
        arr2[i] = uniqueArr2[i];
    }
}



void KoTrung(int x1, int y1, int x2, int y2, int b1[], int b2[], int b_length1, int b_length2, int total1, int total2) {
    int new_arr2[100], s2 = 0;
    toiuu(x1, y1, b1, b_length1, total1);
	
    if (matran[x2][y2] == matran[x1][y1]) {
        // T?m m?t ?i?m láng gi?ng khác ch?a ???c th?m
        findDistinctNeighbor(x2, y2, matran[x1][y1], visited);
    }
	toiuu2(x2, y2, b2, b_length2, total2); 
    for (int i = 0; i < size2; i++) {
        bool found = false;

        for (int j = 0; j < size; j++) {
            if (arr2[i] == arr[j]) {
                // T?m m?t ?i?m láng gi?ng khác ch?a ???c th?m
                //findDistinctNeighbor(x2, y2, matran[x1][y1], visited);
                found = true;
                break;
            }
        }

        if (!found) {
            new_arr2[s2] = arr2[i];
            s2++;
        }
    }

    // C?p nh?t l?i m?ng arr2 và size2
    size2 = s2;
    for (int i = 0; i < size2; i++) {
        arr2[i] = new_arr2[i];
        uniqueArr2.push_back(int(arr2[i]));
    }
}


void xoaMangVisited(){
	for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            visited[i][j] = false;
        }
	}
} 

void displayMatrix(const vector<vector<int> >& matrix, const vector<Point>& path) {
    int rows = matrix.size();
    int columns = matrix[0].size();

    vector<vector<string> > displayMatrix(rows, vector<string>(columns));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            displayMatrix[i][j] = intToString(matrix[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << setw(3) << displayMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (vector<Point>::const_iterator it = path.begin(); it != path.end(); ++it) {
        displayMatrix[it->x][it->y] = "  \033[1;31mX\033[0m"; //doi o di qua thanh X mau do 

        // Xóa màn hinh
        system("cls");

        //hien thi robot di chuyen 
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << setw(3) << displayMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        Sleep(500);
    }
}

void displayMatrix2(const vector<vector<int> >& matrix, const vector<Point>& point1, const vector<Point>& point2) {
    int rows = matrix.size();
    int columns = matrix[0].size();

    vector<vector<string> > displayMatrix(rows, vector<string>(columns));

    // Initialize the display matrix with values from the integer matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            displayMatrix[i][j] = intToString(matrix[i][j]);
        }
    }

    // Display the initial matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << setw(3) << displayMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Display the robot 1 movement on the matrix
    for (int k = 0; k < point1.size(); k++) {
        int x1 = point1[k].x;
        int y1 = point1[k].y;

        displayMatrix[x1][y1] = "  \033[1;31mX\033[0m"; // Change the cell value to "X" in red for robot 1

        // Clear the screen
        system("cls");

        // Display the matrix with robot 1 movement
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << setw(3) << displayMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        Sleep(500);
    }

    // Reset the display matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            displayMatrix[i][j] = intToString(matrix[i][j]);
        }
    }

    // Display the robot 2 movement on the matrix
    for (int k = 0; k < point2.size(); k++) {
        int x2 = point2[k].x;
        int y2 = point2[k].y;

        displayMatrix[x2][y2] = "  \033[1;34mO\033[0m"; // Change the cell value to "O" in blue for robot 2

        // Clear the screen
        system("cls");

        // Display the matrix with robot 2 movement
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << setw(3) << displayMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        Sleep(500);
    }

    // Change the cells visited by the robots to "X" and "O" respectively
    for (int k = 0; k < point1.size(); k++) {
        int x1 = point1[k].x;
        int y1 = point1[k].y;

        displayMatrix[x1][y1] = "  \033[1;31mX\033[0m";
    }

    for (int k = 0; k < point2.size(); k++) {
        int x2 = point2[k].x;
        int y2 = point2[k].y;

        displayMatrix[x2][y2] = "  \033[1;34mO\033[0m";
    }
}
/*
const vector<int> path2; 
void displayMatrix3(const vector<vector<int> >& matrix, const vector<Point>& path, const vector<int>& path2) {
    int rows = matrix.size();
    int columns = matrix[0].size();

    vector<vector<string> > displayMatrix(rows, vector<string>(columns));

    // Initialize the display matrix with values from the integer matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            displayMatrix[i][j] = intToString(matrix[i][j]);
        }
    }

    // Display the initial matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << setw(3) << displayMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Display the robot 1 movement on the matrix
    for (int k = 0; k < path.size(); k++) {
        int x1 = path[k].x;
        int y1 = path[k].y;

        displayMatrix[x1][y1] = "  \033[1;31mX\033[0m"; // Change the cell value to "X" in red for robot 1

        // Clear the screen
        system("cls");

        // Display the matrix with robot 1 movement
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << setw(3) << displayMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        usleep(10000);
    }

    // Reset the display matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            displayMatrix[i][j] = intToString(matrix[i][j]);
        }
    }

    // Display the robot 2 movement on the matrix
    for (int k = 0; k < path2.size(); k++) {
        int x2 = path2[k].x;
        int y2 = path2[k].y;

        displayMatrix[x2][y2] = "  \033[1;34mO\033[0m"; // Change the cell value to "O" in blue for robot 2

        // Clear the screen
        system("cls");

        // Display the matrix with robot 2 movement
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << setw(3) << displayMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        usleep(10000);
    }

    // Change the cells visited by the robots to "X" and "O" respectively
    for (int k = 0; k < path.size(); k++) {
        int x1 = path[k].x;
        int y1 = path[k].y;

        displayMatrix[x1][y1] = "  \033[1;31mX\033[0m";
    }

    for (int k = 0; k < path2.size(); k++) {
        int x2 = path2[k].x;
        int y2 = path2[k].y;

        displayMatrix[x2][y2] = "  \033[1;34mO\033[0m";
    }
}*/
int main() {
	int choice; 
	int start_x1, start_y1;
	int start_x2, start_y2;
	int start_x, start_y;
	int score1=0, score2=0;
	do{
	for(int i = 0; i <= 59; i++){
    	usleep(10000);  
    	cout << "^~";  
  	} 
  	cout<<endl<<endl; 
  	// Ma màu ANSI de chuyen doi màu
    string blue = "\033[1;34m";
    string red = "\033[1;31m";
    string green = "\033[1;32m"; 
    string reset = "\033[0m";
  	cout << blue <<"\t\t  _ _ _  _ _ _ _  _ _ _ _  _ _ _    _  _           _ _ _ _   _ _    _ _ _ _    _ _   _ _ _\n";
	cout << "\t\t /  _ _)(    _  \\(    _ _)(      \\ ( \\/ )         (    _  \\ /   \\  (   _   \\  /   \\ (_   _)\n";
	cout << "\t\t(  (_  \\ )      / )   _)   )  D  (  )  /           )      /(   O )  )  _   ( (   O )  ) (\n";
	cout << "\t\t \\_ _ _/(_ _\\ _ )(_ _ _ _)(_ _ _ / (__/           (_ _\\ _ ) \\_ _/  (_ _ _ _/  \\_ _/  (_ _)\n"; 
	cout<<reset; 
	cout<<endl; 
	cout<< red <<"\t\t\t\t         Cre: Vu Nguyen Phuong - 2251120437 - CN22H\n\n";  
	cout<< green;
    cout<<"\t\t\t\t0"; 
	for(int i=1; i<=56; i++){
		usleep(10000);
		cout<<"="; 
	}
	cout<<"0\n"; 
    cout<<"\t\t\t\t|                                                        |\n"; 
    cout<<"\t\t\t\t|    	          ~~$GREEDY ROBOTS$~~	                 |\n"; 
    cout<<"\t\t\t\t|                                                        |\n";  
    cout<<"\t\t\t\t| ------------------------------------------------------ |\n"; 
    cout<<"\t\t\t\t|                      << MENU >>                        |\n"; 
    cout<<"\t\t\t\t|                                                        |\n"; 
	cout<<"\t\t\t\t| Choose Mode (1-4):                                     |\n"; 
	cout<<"\t\t\t\t|                                                        |\n"; 
    cout<<"\t\t\t\t| (1.) Tim duong di toi uu cho robot (Default Mode).     |\n";
	cout<<"\t\t\t\t| (2.) Tim duong di toi uu cho 2 robot va cac diem trung |\n"; 
	cout<<"\t\t\t\t| (3.) Dat vi tri bat ky cho 2 robot nhung vi tri di roi |\n";
	cout<<"\t\t\t\t| se khong duoc di lai.                                  |\n"; 
	cout<<"\t\t\t\t| (4.) Thoat (ESC).                                      |\n";
	cout<<"\t\t\t\t|                                                        |\n"; 
	cout<<"\t\t\t\t|   ---------------------------------------------------- |\n"; 
	cout<<"\t\t\t\t|    	     ~~~~~~~Other Information~~~~~~              |\n";
	cout<<"\t\t\t\t|                                                        |\n"; 
	cout<<"\t\t\t\t| (5.) About Me.		                         |\n"; 
	cout<<"\t\t\t\t| (6.) Game Rules                                        |\n"; 
	cout<<"\t\t\t\t|                                                        |\n"; 
	cout<<"\t\t\t\t0"; 
	for(int i=1; i<=56; i++){
		usleep(10000);
		cout<<"="; 
	}
	cout<<"0\n";
	cout<<reset; 
	cout<<"- - - - - - - -\n"; 
	cout<<"Choose Mode: \n"; 
	cout<<"- - - - - - - -\n";
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
    if (!input_file) {
        cout << "Khong tim thay file input.txt" << endl;
        break;
    }
        		
    input_file >> rows >> cols;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            input_file >> matran[i][j];
        }
	}
    input_file.close();	
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 13; j++) {
            board2[i][j] = rand() % 100; 
        }
    }
	switch(choice){
		case 1:
			{
				cout<<"so do di goc!"<<endl;
				drawBoard(); 
				    /* In ma tr?n
    				for (int i = 0; i < 16; ++i) {
        				for (int j = 0; j < 16; ++j) {
            				cout << board2[i][j] << " ";
       	 				}
        				cout << endl;
    				}*/
        		do{ 
        			cout<<"Hay nhap vi tri bat dau cho robot: "<<endl;
					cin>>start_x>>start_y; 
				}while(start_x > rows || start_y > cols); 
				toiuu(start_x, start_y, arr, 0, 0);
				cout<<"Robot: "<<"+) dong: "<< start_x <<" "<<"+) cot: "<< start_y <<endl<<endl;  
				xoaMangVisited();
				
				vector<vector<int> > matran(rows, vector<int>(cols));
		
				for (int i = 0; i < rows; i++) {
    				for (int j = 0; j < cols; j++) {
        				matran[i][j] = board[i][j];
    				}
				}
				cout<<"Dang tien hanh tim duong di cho robot: ";
        		
        		for(int i=0; i<=2; i++){
        			sleep(1);
					cout<<". "; 
				} 
				
				displayMatrix(matran, path);
				path.clear(); //xoa gia tri cu luu trong path  

        		cout<<"=>> Duong di cua Robot 1!"<<endl; 
        		cout<<endl; 
        		
        		// Ghi ket qua vào file output.txt
        		ofstream output_file("output.txt");
        		if (!output_file) {
            		cout << "file output.txt khong tim thay!" << endl;
            		break;
        		} 
        		
        		output_file <<"Robot Steps: " << size <<endl;
        		output_file <<"Robot Path: "; 
        		for (int i = 0; i < size; i++) {
            		output_file << arr[i] << " ";
        		} 
				cout<<endl; 
        		output_file.close();
        		cout << "Duong di toi uu cua robot duoc ghi vào File output.txt" << endl; 
        		cout<<endl;
				cout<<"(==>> Keo xuong duoi dung cac chuc nang khac cua GAME! ! ! <<== )"<<endl;	
    		}
			break;
			
		case 2:
			{
				vector<Point> path1;
				int mangTrung[1000];
				int trung=0;  
        		int score1=0, score2=0;
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
    			
    			toiuu(start_x1, start_y1, arr1, 0, 0); 
    			path1=path; 
    			path.clear();
    			//xoaMangVisited();
    			toiuu2(start_x2, start_y2, arr2, 0, 0); 
    			path= path1;
				vector<vector<int> > matran(rows, vector<int>(cols));
				// Populating the matran array with values from the board array
				for (int i = 0; i < rows; i++) {
    				for (int j = 0; j < cols; j++) {
        				matran[i][j] = board[i][j];
    				}
				}
				
				displayMatrix2(matran, path, point2);
				point2.clear();
				 
    			// Ghi ket qua vào file output.txt
    			ofstream output_file("output.txt");
    			if (!output_file) {
        			cout << "file output.txt khong tim thay!" << endl;
        			break;
    			}
				
				cout<<"'X' la duong di cua robot 1 va 'O' la duong di robot 2";
        		
				cout<<endl<<endl;
				
    			output_file << "Robot 1 " << endl; 
    			output_file <<"Robot Steps: "<< size << endl;
    			output_file <<"Robot Path: " ;
    			
    			for(int i=1; i<=29; i++){
					usleep(10000);
					cout<<"="; 
				}
				cout<<">> The Winner is: \n"; 
				
    			for (int i = 0; i < size; i++) {
        			output_file << arr[i] << " ";
        			score1+=arr[i]; 
    			}
    			
				//output_file <<endl; 
				cout<<endl; 
				cout <<"  Robot 1 Score: "<<score1; 
				
    			// In ra duong di va so buoc cho robot 2
    			output_file << endl;
    			output_file << endl; 
    			
    			output_file << "Robot 2 "<< endl;
    			output_file <<"Robot Steps: "<< size2 << endl; 
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
    			for (int i = 0; i < size; i++) {
        			for (int j = 0; j < size2; j++) {
            			if (arr[i] == arr2[j]) {
                			mangTrung[trung]=arr1[i];
							trung++;
							break; 
            			}
        			}
    			}
    			for(int i=0; i<trung; i++){
    				output_file<<mangTrung[i]<<" "; 
				}  
				cout<<"  So diem trung: "<<trung<<endl; 
				
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
				
        		int score1=0, score2=0;
        		int step1=0, step2=0; 
        		int new_arr1[100], new_arr2[100]; 
        		int s1=0, s2=0; 
        		bool robot1Moved=false; 
        		cout<<"So do goc: \n";
				drawBoard(); 
				do{ 
        			cout<<"nhap vi tri bat dau cua robot 1: \n";
					cin>>start_x1>>start_y1;
				
					cout<<"nhap vi tri bat dau cua robot 2: \n";
					cin>>start_x2>>start_y2; 
				}while(start_x1 > rows || start_y1 > cols || start_x2 > rows || start_y2 > cols); 
				//xoa nhung o danh dau da visited trc do 
				xoaMangVisited();
    			
				
				vector<vector<int> > matran(rows, vector<int>(cols));
				//lay du lieu tu ma tran board 
				for (int i = 0; i < rows; i++) {
    				for (int j = 0; j < cols; j++) {
        				matran[i][j] = board[i][j];
    				}
				}
	/*			
toiuu(start_x1, start_y1, arr, 0, 0);
toiuu2(start_x2, start_y2, arr2, 0, 0);

// Check and filter values in arr2
for (int i = 0; i < size2; i++) {
    bool found = false;
    if(i==0){ 
    	found=false; 
	} 
    for (int j = 0; j < size; j++) {
        if (arr2[i] == arr[j]) {
            found = true;
            break;
        }
    }
    if (!found) {
        int currentVal = arr2[i];
        int current_x = point2[i].x;
        int current_y = point2[i].y;
        //bool isValid = true;

        // Ki?m tra các ô xung quanh
        int dx[] = {-1, 1, 0, 0}; // hàng
        int dy[] = {0, 0, -1, 1}; // c?t
		bool isValid=true;
        for (int k = 0; k < 4; k++) {
            int nx = current_x + dx[k];
            int ny = current_y + dy[k];
			 
            // Ki?m tra ?i?u ki?n
            if (!(nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny] && matran[nx][ny] != currentVal)) {
                isValid = false;
                break;
            }
        }

        if (isValid) {
            new_arr2[s2] = currentVal;
             
            s2++;
        }
    }
    
} */
KoTrung(start_x1, start_y1, start_x2, start_y2, arr, arr2, 0, 0, 0, 0);
    			/*
    			displayMatrix2(matran, path, uniqueArr2); 
				path.clear();
				uniqueArr2.clear();*/
				cout<<endl; 
				cout<<"'X' la duong di cua robot 1 va 'O' la duong di robot 2\n\n"; 
    			ofstream output_file("output.txt");
    			if (!output_file) {
        			cout << "file output.txt khong tim thay" << endl;
        			break;
    			}

    			// In ra duong di va so buoc cho robot 1
    			output_file << "Robot 1 "<< endl;
    			output_file << "Robot Path: "; 
    			
    			for(int i=0; i < size; i++){
    				step1++; 
    				output_file << arr[i] <<" ";
					score1+=arr[i];  
				} 
				output_file<<endl; 
				output_file <<"Steps Robot: "<< step1 << endl; 
				output_file << endl; 
    			cout <<"Robot 1 Score: "<<score1<<endl; 
    			// In ra duong di va so buoc cho robot 2
    			output_file << endl;
    			output_file << endl; 
    			
    			output_file << "Robot 2 "<< endl; 
    			output_file << "Robot Path: ";
    			for (int i = 0; i < size2; i++) {
        			step2++;
        			output_file << arr2[i] <<" ";
					score2+=arr2[i];
    			}
    			output_file << endl; 
    			output_file <<"Steps Robot: "<< step2 << endl; 
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
			{
				cout<<blue; 
			 	cout<<"0"; 
				for(int i=1; i<=71; i++){
					usleep(10000);
					cout<<"="; 
				}
				cout<<"0\n"; 
				cout<<"|                                                                       |\n"; 
				cout<<"|                                                                       |\n";
				cout<<"|           _ _ _ _  _    _  _        _ _ _ _  _ _ _ _                  |" << endl;
     			cout<<"|          |    _  \\|  | |  |  |     |  _ _ _ /  _ _ _|                 |" << endl;
    			cout<<"|          |   |_)  |  | |  |  |     |    _|  \\_ _   \\                  |" << endl;
    			cout<<"|          |    _  <|  |_|  |  |_ _ _|  |_ _ _ _ _ )  |                 |" << endl;
    			cout<<"|          | _ | \\_  \\_ _ _/| _ _ _ _|_ _ _ _|_ _ _ _ /                 |" << endl;
    			cout<<"|                                                                       |\n";
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
				cout<<reset; 
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

