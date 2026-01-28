#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
/* ================= TO SHUFFLE ARRAY ================= */
void shuffleArray(int arr[], int n){
    srand(time(0));
    for(int i = n - 1; i > 0; i--){
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
/* ================= LINKED LIST FOR DECK ================= */
class ListNode{
public:
    int id;
    ListNode* next;
    ListNode(int value){
        id = value;
        next = NULL;
    }
};
class LinkedList{
private:
    ListNode* head;
public:
    LinkedList(){
        head = NULL;
    }
    void insert(int value){
        ListNode* newNode = new ListNode(value);
        newNode->next = head;
        head = newNode;
    }
    ListNode* getHead(){
        return head;
    }
};
/* ================= CARD STRUCT ================= */
struct Card {
    int id;
    bool matched;
};
/* ================= VISUAL BOARD ================= */
void printBoard(Card** board, bool** reveal, int N){
    cout << "\n";
    for (int i = 0; i < N; i++){
        for (int k = 0; k < N; k++){
        	cout << "+----";
		}
        cout << "+\n";
        for (int j = 0; j < N; j++){
            cout << "| ";
            if(reveal[i][j] || board[i][j].matched)
                cout << board[i][j].id << "  ";
            else
                cout << "*  ";
        }
        cout << "|\n";
    }
    for(int k = 0; k < N; k++){
    	cout << "+----";
	}
    cout << "+\n";
}
/* ================= STACK TO FLIP CARDS ================= */
class StackNode{
public:
    int r, c;
    StackNode* next;
    StackNode(int row, int col){
        r = row;
        c = col;
        next = NULL;
    }
};
class Stack{
private:
    StackNode* top;
public:
    Stack(){
        top = NULL;
    }
    void push(int r, int c){
        StackNode* newNode = new StackNode(r, c);
        newNode->next = top;
        top = newNode;
    }
    void pop(){
        if(top == NULL) 
			return;
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
    StackNode* peek(){
        return top;
    }
    bool isEmpty(){
        return top == NULL;
    }
    void clear(){
        while(!isEmpty())
            pop();
    }
};
/* ================= MAIN FUNCTION ================= */
int main(){
    int choice, N;
    cout << "===== CARD MATCHING MEMORY GAME =====\n";
    cout << "Select Difficulty Level:\n";
    cout << "1. Easy (4 x 4)\n";
    cout << "2. Medium (6 x 6)\n";
    cout << "3. Hard (8 x 8)\n";
    cout << "Enter choice: ";
    cin >> choice;
    if(choice == 1)
        N = 4;
    else if(choice == 2)
        N = 6;
    else
        N = 8;
    int totalCards = N * N;
    int totalPairs = totalCards / 2;
    /* ===== CREATE LINKED LIST DECK ===== */
    LinkedList deck;
    for(int i = 1; i <= totalPairs; i++){
        deck.insert(i);
        deck.insert(i);
    }
    /* ===== DYNAMIC BOARD CREATION ===== */
    Card** board = new Card*[N];
    bool** reveal = new bool*[N];
    for (int i = 0; i < N; i++) {
        board[i] = new Card[N];
        reveal[i] = new bool[N];
    }
    /* ===== FILL BOARD FROM LINKED LIST ===== */
    // Step 1: Copy linked list into array
	int total = N * N;
	int* values = new int[total];
	ListNode* temp = deck.getHead();
	for(int i = 0; i < total; i++){
	    values[i] = temp->id;
    	temp = temp->next;
	}
	// Step 2: Shuffle array
	shuffleArray(values, total);
	// Step 3: Fill board using shuffled values
	int idx = 0;
	for(int i = 0; i < N; i++){
	    for(int j = 0; j < N; j++){
	        board[i][j].id = values[idx++];
    	    board[i][j].matched = false;
        	reveal[i][j] = false;
    	}
	}
	delete[] values;
    /* ===== GAME LOGIC USING STACK ===== */
    Stack flipped;
    int moves = 0;
    int matchedPairs = 0;
    while(matchedPairs < totalPairs){
        printBoard(board, reveal, N);
        int r, c;
        cout << "\nEnter row and column (0-" << N-1 << "): ";
        cin >> r >> c;
        if(r < 0 || r >= N || c < 0 || c >= N || reveal[r][c]){
            cout << "Invalid move! Try again.\n";
            continue;
        }
        reveal[r][c] = true;
        flipped.push(r, c);
        moves++;
        printBoard(board, reveal, N);
        // Check when two cards are flipped
        if(flipped.peek() && flipped.peek()->next){
            StackNode* first = flipped.peek();
            StackNode* second = flipped.peek()->next;
            int r1 = first->r, c1 = first->c;
            int r2 = second->r, c2 = second->c;
            if(board[r1][c1].id == board[r2][c2].id){
                cout << "--- MATCH FOUND! ---\n";
                board[r1][c1].matched = true;
                board[r2][c2].matched = true;
                matchedPairs++;
            }else{
                cout << "--- Not a match! ---\n";
                reveal[r1][c1] = false;
                reveal[r2][c2] = false;
            }
            flipped.clear();
        }
    }
    /* ===== GAME OVER ===== */
    printBoard(board, reveal, N);
    cout << "\n--- CONGRATULATIONS! YOU WON ---\n";
    cout << "Total Moves: " << moves << endl;
    return 0;
}
