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

bool hopLeRobot1(int x, int y){
	return (hopLe(x, y) && visitedByRobot1[x][y]); 
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

void findDistinctNeighbor(int& x, int& y, int currentValue) {
    int dx[] = {-1, 0, 1, 0}; // Offsets for neighboring cells (up, right, down, left)
    int dy[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (hopLe(nx, ny) && matran[nx][ny] != currentValue) {
            // Found a neighboring cell with a different value, update Robot 2's position
            x = nx;
            y = ny;
            return;
        }
    }
}
vector<Point>Point1, Point2;
void KoTrung(int x1, int y1, int x2, int y2, int b1[], int b2[], int b_length1, int b_length2, int total1, int total2) {
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

    // ktra vtri hien tai robot 1 va 2 co trung gtri khong 
    if (matran[x1][y1] == matran[x2][y2]) {
        // di chuyen robot 2 toi nhung o co gia tri khac robot 1 
        findDistinctNeighbor(x2, y2, matran[x1][y1]);
    }

    // Update the path and total values
    b1[b_length1] = matran[x1][y1];
    Point1.push_back(Point(x1, y1, matran[x1][y1]));
    b2[b_length2] = matran[x2][y2];
    Point2.push_back(Point(x2, y2, matran[x2][y2]));
    b_length1++;
    b_length2++;
    total1 += matran[x1][y1];
    total2 += matran[x2][y2];

    visited[x1][y1] = true;
    visited[x2][y2] = true;
    
    findMaxNeighbor(x1, y1);
    findMaxNeighbor(x2, y2);

    KoTrung(x1, y1, x2, y2, b1, b2, b_length1, b_length2, total1, total2);

    b_length1--;
    b_length2--;
    visited[x1][y1] = false;
    visited[x2][y2] = false;
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
        Sleep(1000);
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

    // Display the robot movement on the matrix
    for (int k = 0; k < point1.size(); k++) {
        int x1 = point1[k].x;
        int y1 = point1[k].y;
        int x2 = point2[k].x;
        int y2 = point2[k].y;

        displayMatrix[x1][y1] = "  \033[1;31mX\033[0m"; // Change the cell value to "X" in red for robot 1
        displayMatrix[x2][y2] = "  \033[1;34mO\033[0m"; // Change the cell value to "O" in blue for robot 2

        // Clear the screen
        system("cls");

        // Display the matrix with robot movement
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << setw(3) << displayMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        Sleep(1000);
    }

    // Change the cells visited by the robots to "X" and "O" respectively
    for (int k = 0; k < point1.size(); k++) {
        int x1 = point1[k].x;
        int y1 = point1[k].y;
        int x2 = point2[k].x;
        int y2 = point2[k].y;

        displayMatrix[x1][y1] = "  \033[1;31mX\033[0m";
        displayMatrix[x2][y2] = "  \033[1;34mO\033[0m";
    }
}

int main() {
	int choice; 
	int start_x1, start_y1;
	int start_x2, start_y2;
	int start_x, start_y;
	int score1=0, score2=0;
	do{
	for(int i = 0; i <= 28; i++){
    	usleep(100000);  
    	cout << "^~";  
  	} 
  	cout<<endl<<endl; 
	cout<<"         Cre: Vu Nguyen Phuong - 2251120437 - CN22H\n\n";  
    cout<<"0"; 
	for(int i=1; i<=56; i++){
		usleep(10000);
		cout<<"="; 
	}
	cout<<"0\n"; 
    cout<<"|                                                        |\n"; 
    cout<<"|    	          ~~$GREEDY ROBOTS$~~	                 |\n"; 
    cout<<"|                                                        |\n";  
    cout<<"| ------------------------------------------------------ |\n"; 
    cout<<"|                      << MENU >>                        |\n"; 
    cout<<"|                                                        |\n"; 
	cout<<"| Choose Mode (1-4):                                     |\n"; 
	cout<<"|                                                        |\n"; 
    cout<<"| (1.) Tim duong di toi uu cho robot (Default Mode).     |\n";
	cout<<"| (2.) Tim duong di toi uu cho 2 robot va cac diem trung |\n"; 
	cout<<"| (3.) Dat vi tri bat ky cho 2 robot nhung vi tri di roi |\n";
	cout<<"| se khong duoc di lai.                                  |\n"; 
	cout<<"| (4.) Thoat (ESC).                                      |\n";
	cout<<"|                                                        |\n"; 
	cout<<"|   ---------------------------------------------------- |\n"; 
	cout<<"|    	     ~~~~~~~Other Information~~~~~~              |\n";
	cout<<"|                                                        |\n"; 
	cout<<"| (5.) About Me.		                         |\n"; 
	cout<<"| (6.) Game Rules                                        |\n"; 
	cout<<"|                                                        |\n"; 
	cout<<"0"; 
	for(int i=1; i<=56; i++){
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
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
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
				/*
				// file output 
				ofstream outputFile("output.txt");
    			if (outputFile.is_open()) {
        			int totalValue = 0;
        			int count = 0;
        			outputFile << endl << "Cac gia tri cua robot: ";
        			for (vector<Point>::const_iterator it = path.begin(); it != path.end(); ++it) {
            			outputFile << it->value << " ";
            			totalValue += it->value;
            			count++;
        			}
        			outputFile << endl;
        			outputFile << "Tong gia tri cua robot: ";
        			outputFile << totalValue << endl;
        			outputFile << "So o ma robot da di: ";
        			outputFile << count << endl;
        			outputFile.close();
    			}
				*/
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
    			
    			toiuu2robot(start_x1, start_y1, start_x2, start_y2, arr1, arr2, 0, 0, 0, 0); 
    			
				vector<vector<int> > matran(rows, vector<int>(cols));
				// Populating the matran array with values from the board array
				for (int i = 0; i < rows; i++) {
    				for (int j = 0; j < cols; j++) {
        				matran[i][j] = board[i][j];
    				}
				}
				
				displayMatrix2(matran, point1, point2);
				point1.clear();
				point2.clear(); 
    			// Ghi ket qua vào file output.txt
    			ofstream output_file("output.txt");
    			if (!output_file) {
        			cout << "file output.txt khong tim thay!" << endl;
        			break;
    			}
				
				cout<<"X la duong di cua robot 1 va Y la duong di robot 2";
        		
				cout<<endl<<endl;
				
    			output_file << "Robot 1 " << endl; 
    			output_file <<"Robot Steps: "<< size1 << endl;
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
        		int step1=0, step2=0; 
        		cout<<"So do goc: \n";
				drawBoard(); 
				do{ 
        			cout<<"nhap vi tri bat dau cua robot 1: \n";
					cin>>start_x1>>start_y1;
				
					cout<<"nhap vi tri bat dau cua robot 2: \n";
					cin>>start_x2>>start_y2; 
				}while(start_x1 > rows || start_y1 > cols || start_x2 > rows || start_y2 > cols); 
				
				xoaMangVisited();
        		// Goi hàm tim duong di toi uu cho 2 robot
    			KoTrung(start_x1, start_y1, start_x2, start_y2, arr1, arr2, 0, 0, 0, 0);
				vector<vector<int> > matrix(rows, vector<int>(cols));
				// Populating the matran array with values from the board array
				for (int i = 0; i < rows; i++) {
    				for (int j = 0; j < cols; j++) {
        				matran[i][j] = board[i][j];
    				}
				}
				
				displayMatrix2(matrix, Point1, Point2);
    			// Ghi ket qua vào file output.txt
    			ofstream output_file("output.txt");
    			if (!output_file) {
        			cout << "file output.txt khong tim thay" << endl;
        			break;
    			}

    			// In ra duong di va so buoc cho robot 1
    			output_file << "Robot 1 "<< endl;
    			output_file << "Robot Path: "; 
    			
    			for(int i=0; i<size1; i++){
    				step1++; 
    				output_file << arr1[i] <<" ";
					score1+=arr1[i];  
				} 
				output_file<<endl; 
				output_file <<"Steps Robot: "<< size2 << endl; 
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
			 
		default:
			cout<<"Lua chon cua ban ko hop le"; 
		}
		cout<<endl; 
	}while(choice != 4);
    return 0;
}

