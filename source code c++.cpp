#include <iostream>
#include <fstream>

using namespace std;

int matran[100][100];
bool visited[100][100];
int arr[1000]; 
int arr1[1000]; //luu tru duong di robot 1 
int arr2[1000]; //luu tru duong di robot 2 
int size = 0;  
int size1 = 0; //so buoc robot 1 
int size2 = 0; //so buoc robot 2 
int rows, cols;

// Hàm tính tinh tung gia tri cua 1 mang 
int totalArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

// Hàm kiem tra 1 0 co hop le de di chuyen không
bool isValidMove(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && !visited[x][y]);
}

// Hàm di chuyen den o co gia tri lon nhat xung quanh
void moveToMaxNeighbor(int& x, int& y) {
    int maxVal = -1;
    int newX = x;
    int newY = y;

    // Kiem tra các ô xung quanh và tim ô có giá tri lon nhat
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

    // Di chuyen toi ô có giá tri lon nhat
    x = newX;
    y = newY;
}

// Hàm de quy tim duong di toi uu 
void toiuu(int x, int y, int b[], int b_length, int total) {
    // Kiem tra dieu kien dung  
    if (!isValidMove(x, y)) {
        // Kiem tra xem duong di hien tai co toi uu không
        if (totalArray(b, b_length) == total) {
            size = b_length;
            for (int i = 0; i < b_length; i++) {
                arr[i] = b[i]; 
            }
        }
        return;
    }

    // Cap nhat duong di và tung gia tri 
    b[b_length] = matran[x][y];
    b_length++;
    total += matran[x][y];

    // Ðánh dau o da di qua
    visited[x][y] = true;

    // Di chuyen den o co gia tri lon nhat xung quanh
    moveToMaxNeighbor(x, y);

    // Ðe quy tim duong di toi o tiep theo 
    toiuu(x, y, b, b_length, total);

    // Tro lai vi tri ban dau cua duong di và visited
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
	
	//tro lai vi tri ban dau và visited
	b_length1--;
	b_length2--;
	visited[x1][y1]=false;
	visited[x2][y2]=false; 
	 
} 

int main() {
	int choice, total, total1; 
	do{
    cout<<"0=================~~~@MENU@~~~=================0\n";
    cout<<"|                                              |\n"; 
    cout<<"|    	      ~~$GREEDY ROBOTS$~~	       |\n"; 
    cout<<"|                                              |\n"; 
    cout<<"| -------------------------------------------- |\n"; 
	cout<<"| Choose Mode (1-4):                           |\n"; 
    cout<<"| 1.Tim duong di toi uu cho robot              |\n";
	cout<<"| 2.Tim duong di toi uu cho 2 robot và so sanh |\n";
	cout<<"| 3.Dat vi tri bat ky cho 2 robot              |\n";
	cout<<"| 4.Thoat (ESC)                                |\n";
	cout<<"| -------------------------------------------- |\n"; 
	cout<<"|    	~~~~~~~Other Information~~~~~~         |\n";
	cout<<"| 5. About Me		                       |\n"; 
	cout<<"| 6. Game Rules                                |\n"; 
	cout<<"| 7. See My Other Project!                     |\n"; 
	cout<<"0==============================================0\n"; 
	cin>>choice;
	
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
        		int start_x = 0, start_y = 0;
        		// Goi hàm tim duong di toi uu cho 1 robot
        		toiuu(start_x, start_y, arr, 0, 0);
        
        		// Ghi ket qua vào file output.txt
        		ofstream output_file("output.txt");
        		if (!output_file) {
            		cout << "Không thay file output.txt" << endl;
            		break;
        		}
        		
        		output_file << size <<endl;
        		for (int i = 0; i < size; i++) {
            		output_file << arr[i] << " ";
        		}
        		output_file.close();
        		cout << "duong di toi uu cua 1 robot duoc ghi vào file output.txt" << endl; 
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
				
        		// Goi hàm tim duong di toi uu cho 2 robot
    			toiuu2robot(start_x1, start_y1, start_x2, start_y2, arr1, arr2, 0, 0, 0, 0);

    			// Ghi ket qua vào file output.txt
    			ofstream output_file("output.txt");
    			if (!output_file) {
        			cout << "Không thay file output.txt" << endl;
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
    			cout << "duong di va so buoc cua 2 robot duoc ghi vào file output.txt" << endl;
    			break;
				}
		case 3:
			
			break;
		
		case 4: 
		
			break; 
		
		case 5:
			break;
			
		case 6:
			break;
			
		case 7:
			break;
			 
		default:
			cout<<"lua chon cua ban ko hop le"; 
		}
		cout<<endl; 
	}while(choice != 4);
	
    return 0;
}

