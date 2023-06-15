#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

int arr[1000]; 
int arr1[1000]; //luu tru duong di robot 1 
int arr2[1000]; //luu tru duong di robot 2 

int size = 0;  
int size1 = 0; //so buoc robot 1 
int size2 = 0; //so buoc robot 2
 
int matran[100][100];
bool visitedByRobot1[100][100]; 
bool visited[100][100];
int rows, cols;

int board[][5]={{2, 1, 14, 12, 17},
				{3, 16, 22, 91, 23},
				{4, 56, 87, 31, 65},
				{27, 43, 90, 100, 101},
				{76, 54, 32, 99, 66},
				{178, 154, 150, 200, 543}};
void get_robotMove() {
    // ��nh d?u nh?ng ��?ng �i t?i �u c?a robot 1 l� 'x'
    for (int i = 0; i < size1; i++) {
        int position = arr1[i];
        int row = position / 5;
        int col = position % 5;
        board[row][col] = 'x';
    }

    // ��nh d?u nh?ng ��?ng �i t?i �u c?a robot 2 l� 'x'
    for (int i = 0; i < size2; i++) {
        int position = arr2[i];
        int row = position / 5;
        int col = position % 5;
        board[row][col] = 'x';
    }
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
	cout<<"|"<< board[5][0]<< " |"<< board[5][1]<< " |"<< board[5][2]<< " |"<< board[5][3]<< " |"<< board[5][4]<< "  |"<<endl;
	cout<<"|----"<<"----"<<"----"<<"----"<<"---------|"<<endl;
	
} 
 
 void printUpdatedBoard() {
    cout << "_____" << "______" << "_____" << "_____" << "______" << endl;
    for (int i = 0; i < rows; i++) {
        cout << "| ";
        for (int j = 0; j < cols; j++) {
            cout << board[i][j] << "  | ";
        }
        cout << endl;
        cout << "|----|" << "----|" << "----|" << "----|" << "-----|" << endl;
    }
}


// H�m t�nh tinh tung gia tri cua 1 mang 
int totalArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// H�m kiem tra 1 0 co hop le de di chuyen kh�ng
bool isValidMove(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y]);
}

bool isValidMoveRobot1(int x, int y){
	return (isValidMove(x, y) && !visitedByRobot1[x][y]); 
} 

// H�m di chuyen den o co gia tri lon nhat xung quanh
void moveToMaxNeighbor(int& x, int& y) {
    int maxVal = -1;
    int newX = x;
    int newY = y;

    // Kiem tra c�c � xung quanh v� tim � c� gi� tri lon nhat
    int dx[] = {-1, 1, 0, 0}; // hang
    int dy[] = {0, 0, -1, 1}; // cot

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValidMove(nx, ny) && matran[nx][ny] > maxVal) {
            maxVal = matran[nx][ny];
            newX = nx;
            newY = ny;
        }
    }

    // Di chuyen toi � c� gi� tri lon nhat
    x = newX;
    y = newY;
}

// H�m de quy tim duong di toi uu 
void toiuu(int x, int y, int b[], int b_length, int total) {
    // Kiem tra dieu kien dung  
    if (!isValidMove(x, y)) {
        // Kiem tra xem duong di hien tai co toi uu kh�ng
        if (totalArray(b, b_length) == total) {
            size = b_length;
            for (int i = 0; i < b_length; i++) {
                arr[i] = b[i]; 
            }
        }
        return;
    }

    // Cap nhat duong di v� tung gia tri 
    b[b_length] = matran[x][y];
    b_length++;
    total += matran[x][y];

    // ��nh dau o da di qua
    visited[x][y] = true;

    // Di chuyen den o co gia tri lon nhat xung quanh
    moveToMaxNeighbor(x, y);

    // �e quy tim duong di toi o tiep theo 
    toiuu(x, y, b, b_length, total);

    // Tro lai vi tri ban dau cua duong di v� visited
    b_length--;
    visited[x][y] = false;
}

void toiuu2robot(int x1, int y1, int x2, int y2, int b1[], int b2[], int b_length1, int b_length2, int total1, int total2){
	if(!isValidMove(x1, y1) || !isValidMove(x2, y2)){
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
	moveToMaxNeighbor(x1, y1);
	//di chuyen toi o co gia tri lon nhat xung quanh robot2
	moveToMaxNeighbor(x2, y2);
	
	//de quy tim duong di toi uu cho 2 robot
	toiuu2robot(x1, y1, x2, y2, b1, b2, b_length1, b_length2, total1, total2);
	
	//tro lai vi tri ban dau v� visited
	b_length1--;
	b_length2--;
	visited[x1][y1]=false;
	visited[x2][y2]=false; 
} 

void KoTrung(int x1, int y1, int x2, int y2, int b1[], int b2[], int b_length1, int b_length2, int total1, int total2){
	if(!isValidMove(x1, y1) || !isValidMoveRobot1(x2, y2)){
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
	visitedByRobot1[x2][y2]=true;
	
	//di chuyen toi o co gia tri lon nhat xuung quanh robot1
	moveToMaxNeighbor(x1, y1);
	//di chuyen toi o co gia tri lon nhat xung quanh robot2
	moveToMaxNeighbor(x2, y2);
	
	//de quy tim duong di toi uu cho 2 robot
	KoTrung(x1, y1, x2, y2, b1, b2, b_length1, b_length2, total1, total2);
	
	//tro lai vi tri ban dau v� visited
	b_length1--;
	b_length2--;
	visited[x1][y1]=false;
	visitedByRobot1[x2][y2]=false;
} 

int main() {
	int choice, total, total1; 
	drawBoard();
	do{
		for(int i = 0; i <= 28; i++){
    	usleep(100000);  
    	cout << "^~";  
  		} 
  	cout<<endl<<endl; 
	  
    cout<<"0======================~~~@MENU@~~~====================0\n";
    cout<<"|                                                      |\n"; 
    cout<<"|    	          ~~$GREEDY ROBOTS$~~	               |\n"; 
    cout<<"|                                                      |\n";  
    cout<<"| ---------------------------------------------------- |\n"; 
	cout<<"| Choose Mode (1-4):                                   |\n"; 
    cout<<"| 1.Tim duong di toi uu cho robot(Normal Mode).        |\n";
	cout<<"| 2.Tim duong di toi uu cho 2 robot va cac diem trung. |\n"; 
	cout<<"| 3.Dat vi tri bat ky cho 2 robot ko di lai vtri cu.   |\n";
	cout<<"| 4.Thoat (ESC).                                       |\n";
	cout<<"| ---------------------------------------------------- |\n"; 
	cout<<"|    	    ~~~~~~~Other Information~~~~~~             |\n";
	cout<<"| 5. About Me.		                               |\n"; 
	cout<<"| 6. Game Rules                                        |\n"; 
	cout<<"| 7. See My Other Project!                             |\n"; 
	cout<<"0======================================================0\n"; 
	cin>>choice;
	
	if (choice == 4) {
        cout << "Hen gap lai";
        for (int i = 1; i <= 3; i++) {
            sleep(1);
            cout << "! ";
        }
        cout << endl;
        break;
    }
        
	ifstream input_file("input.txt");
    // Kiem tra xem file input.txt c� ton tai hay kh�ng
    if (!input_file) {
        cout << "Kh�ng thay file input.txt" << endl;
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
        		int start_x, start_y;
        		cout<<"Hay nhap vi tri bat dau cho robot: "<<endl;
				cin>>start_x>>start_y; 
				cout<<">> >>Ban dat Robot o vi tri: "<<"dong: "<<start_x<<" "<<"cot: "<<start_y<<endl; 
        		// Goi h�m tim duong di toi uu cho 1 robot
        		toiuu(start_x, start_y, arr, 0, 0);
        
        		// Ghi ket qua v�o file output.txt
        		ofstream output_file("output.txt");
        		if (!output_file) {
            		cout << "Kh�ng thay file output.txt" << endl;
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
				cout<<endl; 
        		output_file.close();
        		cout << "Duong di toi uu cua robot duoc ghi v�o File output.txt" << endl; 
    		}
			break;
			
		case 2:
			{
				int mangTrung[1000];
				int trung=0; 
				int score1=0, score2=0; 
        
        		int start_x1, start_y1;
        		int start_x2, start_y2;
        		
				cout<<"nhap vi tri bat dau cua robot 1: \n";
				cin>>start_x1>>start_y1;
				cout<<"nhap vi tri bat dau cua robot 2: \n";
				cin>>start_x2>>start_y2; 
				
        		// Goi h�m tim duong di toi uu cho 2 robot
    			toiuu2robot(start_x1, start_y1, start_x2, start_y2, arr1, arr2, 0, 0, 0, 0); 
    			printUpdatedBoard();
    			get_robotMove();

    			// Ghi ket qua v�o file output.txt
    			ofstream output_file("output.txt");
    			if (!output_file) {
        			cout << "Kh�ng thay file output.txt" << endl;
        			break;
    			}

    			// In ra duong di va so buoc cho robot 1
    			output_file << "Robot 1 " << endl; 
    			output_file <<"Steps Robot: "<< size1 << endl;
    			output_file <<"Robot Path: " ;
    			for (int i = 0; i < size1; i++) {
        			output_file << arr1[i] << " ";
        			score1+=arr1[i]; 
    			}
				output_file <<endl; 
				output_file <<"Score: "<<score1; 
				
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
    			
    			output_file << endl; 
    			output_file <<"Score: "<<score2; 
    			
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
    			if (total1 < total) {
        			output_file << endl;
        			output_file << "Robot 1 Win!" << endl;
    			} 
				else if (total1 > total) {
        			output_file << endl;
        			output_file << "Robot 2 Win!" << endl;
    			} 
				else {
        			output_file << endl;
        			output_file << "Draw!" << endl;
    			}
    			output_file.close();
    			cout << "duong di va so buoc cua 2 robot duoc ghi v�o file output.txt" << endl;
    			break;
				}
				
		case 3:
			{
				int score1=0, score2=0; 
        		int start_x1, start_y1;
        		int start_x2, start_y2;
        		int trung[100], t=0; 
				cout<<"nhap vi tri bat dau cua robot 1: \n";
				cin>>start_x1>>start_y1;
				cout<<"nhap vi tri bat dau cua robot 2: \n";
				cin>>start_x2>>start_y2; 
				
        		// Goi h�m tim duong di toi uu cho 2 robot
    			KoTrung(start_x1, start_y1, start_x2, start_y2, arr1, arr2, 0, 0, 0, 0);

    			// Ghi ket qua v�o file output.txt
    			ofstream output_file("output.txt");
    			if (!output_file) {
        			cout << "Kh�ng thay file output.txt" << endl;
        			break;
    			}

    			// In ra duong di va so buoc cho robot 1
    			output_file << "Robot 1 "<< endl;
    			output_file <<"Steps Robot: "<< size2 << endl; 
    			output_file << "Robot Path: "; 
    			for(int i=0; i<size1; i++){
    				output_file << arr1[i] <<" ";
					score1+=arr1[i]; 
					trung[t]=arr1[i];
					t++; 
				} 
				
				output_file << endl; 
    			output_file <<"Score: "<<score1
				; 
    			// In ra duong di va so buoc cho robot 2
    			output_file << endl;
    			output_file << endl; 
    			
    			output_file << "Robot 2 "<< endl;
    			output_file <<"Steps Robot: "<< size2 << endl; 
    			output_file << "Robot Path: "; 
    			for (int i = 0; i < size2; i++) {
        			if(arr2[i]!=trung[i]){
        				output_file << arr2[i] <<" ";
						score2+=arr2[i];
						break; 
					} 
    			}
    			
    			output_file << endl; 
    			output_file <<"Score: "<<score2<<endl; 
    			
    			// So sanh so buoc cua hai robot
    			output_file <<"The winners is: "<< endl;
    			if (total1 < total) {
        			output_file << endl;
        			output_file << "Robot 1 Win!" << endl;
    			} 
				else if (total1 > total) {
        			output_file << endl;
        			output_file << "Robot 2 Win!" << endl;
    			} 
				else {
        			output_file << endl;
        			output_file << "Draw!" << endl;
    			}
    			output_file.close();
    			cout << "duong di va so buoc cua 2 robot duoc ghi v�o file output.txt" << endl;
			}
			break;
		
		case 5:
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
			cout<<"     School: University Of Transport HCM City\n"; 
			for(int i=1; i<=49; i++){
				usleep(10000);
				cout<<"_"; 
			} 
			cout<<endl; 
			break;
			
		case 6:
			{ 
				cout<<"0=======================================================================0\n";
				cout<<"|                                                                       |\n"; 
				cout<<"|                          ~~~RULES~~~                                  |\n";
				cout<<"|                                                                       |\n";
				cout<<"| + Robots di theo 4 huong (tren, duoi, trai, phai)                     |\n";
				cout<<"|                                                                       |\n";
				cout<<"| +Robots se di theo huong so co gia tri lon hon gia tri hien tai       |\n";
				cout<<"|                                                                       |\n";
				cout<<"| +O che do 1 Robot se tu dong di chuyen tu vi tri ban dau              |\n";
				cout<<"| ma nguoi choi dat                                                     |\n";
				cout<<"|                                                                       |\n"; 
				cout<<"| +O che do 2 nguoi choi se dat vi tri bat dau cho 2 robot              |\n";
				cout<<"| sau do se in ra nhung vi tri ma chung trung nhau va so sanh           |\n";
				cout<<"| con robot nao co so diem cao hon se thang                             |\n";
				cout<<"|                                                                       |\n"; 
				cout<<"| +O che do 3 nguoi choi se nhap vi tri bat dau cho 2 con robot         |\n";
				cout<<"| nhung vi tri ma robot di qua roi se khong duoc di nua sau khi 2 robot |\n";
				cout<<"| hoan thanh duong di, robot nao co so diem cao hon se thang            |\n"; 
				cout<<"|                                                                       |\n";
				cout<<"0=======================================================================0\n"; 
				cout<<endl; 
			}
			break;
			
		case 7:
			{
				cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; 
				cout<<"  Check out my other projects on GitHub\n";
				cout<<"  GitHub account: vuphuong1794\n";
				cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"; 
			}
			break;
			 
		default:
			cout<<"Lua chon cua ban ko hop le"; 
		}
		cout<<endl; 
		
	}while(choice != 4);
	
    return 0;
}

