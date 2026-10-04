#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    int cost;
    string owner;
    Node* next;

    Node(string n, int c) {
        name = n;
        cost = c;
        owner = "None";
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;
    int count;
    bool circular;

public:
    LinkedList() {
        head = nullptr;
        count = 0;
        circular = false;
    }

    ~LinkedList() {
        Node* current = head;

        for (int i = 0; i < count; i++) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void add(string name, int cost) {
        if (circular) {
            return;
        }

        Node* newNode = new Node(name, cost);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* current = head;

            while (current->next != nullptr) {
                current = current->next;
            }

            current->next = newNode;
        }

        count++;
    }

    Node* search(string name) {
        Node* current = head;

        for (int i = 0; i < count; i++) {
            if (current->name == name) {
                return current;
            }

            current = current->next;
        }

        return nullptr;
    }

    bool remove(string name) {
        if (circular || head == nullptr) {
            return false;
        }

        if (head->name == name) {
            Node* temp = head;
            head = head->next;
            delete temp;
            count--;
            return true;
        }

        Node* current = head;

        while (current->next != nullptr) {
            if (current->next->name == name) {
                Node* temp = current->next;
                current->next = temp->next;
                delete temp;
                count--;
                return true;
            }

            current = current->next;
        }

        return false;
    }

    void print() {
        Node* current = head;

        for (int i = 0; i < count; i++) {
            cout << current->name
                 << " - $" << current->cost
                 << " - Owner: " << current->owner << endl;

            current = current->next;
        }
    }

    Node* getHead() {
        return head;
    }

    void makeCircular() {
        if (head == nullptr || circular) {
            return;
        }

        Node* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = head;
        circular = true;
    }
};

struct Player {
    string name;
    int money;
    Node* position;

    Player(string n, Node* start) {
        name = n;
        money = 500;
        position = start;
    }
};

void movePlayer(Player& player, int spaces, Node* start) {
    for (int i = 0; i < spaces; i++) {
        player.position = player.position->next;

        if (player.position == start) {
            cout << player.name << " passed start." << endl;
        }
    }
}

void handleProperty(Player& player) {
    Node* property = player.position;

    cout << player.name << " landed on "
         << property->name
         << " ($" << property->cost << ")" << endl;

    if (property->owner == "None") {
        if (player.money >= property->cost) {
            player.money -= property->cost;
            property->owner = player.name;

            cout << player.name << " bought "
                 << property->name << endl;
        }
        else {
            cout << "Not enough money." << endl;
        }
    }
    else {
        cout << "Owned by " << property->owner << endl;
    }

    cout << player.name << ": $" << player.money << endl;
}

int main() {
    cout << "LINKED LIST" << endl;
    cout << "-----------" << endl;

    LinkedList list;

    list.add("Boardwalk", 400);
    list.add("Park Place", 350);
    list.add("Baltic Avenue", 60);
    list.add("Oriental Avenue", 100);

    cout << "\nAdded:" << endl;
    list.print();

    cout << "\nSearch: Park Place" << endl;
    Node* found = list.search("Park Place");

    if (found != nullptr) {
        cout << "Found: " << found->name << endl;
    }
    else {
        cout << "Not found." << endl;
    }

    cout << "\nSearch: Missing Property" << endl;
    found = list.search("Missing Property");

    if (found == nullptr) {
        cout << "Not found." << endl;
    }

    cout << "\nRemove: Boardwalk" << endl;
    cout << (list.remove("Boardwalk") ? "Removed" : "Not found") << endl;

    cout << "\nRemove: Baltic Avenue" << endl;
    cout << (list.remove("Baltic Avenue") ? "Removed" : "Not found") << endl;

    cout << "\nRemove: Oriental Avenue" << endl;
    cout << (list.remove("Oriental Avenue") ? "Removed" : "Not found") << endl;

    cout << "\nRemaining:" << endl;
    list.print();

    cout << "\nRemove: Missing Property" << endl;
    cout << (list.remove("Missing Property") ? "Removed" : "Not found") << endl;

    LinkedList emptyList;

    cout << "\nRemove from empty list:" << endl;
    cout << (emptyList.remove("Nothing") ? "Removed" : "Not found") << endl;

    cout << "\nMONOPOLY" << endl;
    cout << "--------" << endl;

    LinkedList board;

    board.add("Mediterranean Avenue", 60);
    board.add("Baltic Avenue", 60);
    board.add("Oriental Avenue", 100);
    board.add("Vermont Avenue", 100);
    board.add("Connecticut Avenue", 120);
    board.add("St. Charles Place", 140);
    board.add("States Avenue", 140);
    board.add("Virginia Avenue", 160);
    board.add("St. James Place", 180);
    board.add("Tennessee Avenue", 180);

    board.makeCircular();

    cout << "\nBoard:" << endl;
    board.print();

    Player player1("P1", board.getHead());
    Player player2("P2", board.getHead());

    int rolls[] = {1, 2, 3, 2, 5, 5, 2, 2, 4, 4, 6, 6};

    for (int turn = 1; turn <= 12; turn++) {
        cout << "\nTurn " << turn << endl;

        Player* currentPlayer;

        if (turn % 2 == 1) {
            currentPlayer = &player1;
        }
        else {
            currentPlayer = &player2;
        }

        int roll = rolls[turn - 1];

        cout << currentPlayer->name
             << " rolled " << roll << endl;

        movePlayer(*currentPlayer, roll, board.getHead());
        handleProperty(*currentPlayer);
    }

    cout << "\nRESULTS" << endl;
    cout << "P1: $" << player1.money << endl;
    cout << "P2: $" << player2.money << endl;

    cout << "\nPROPERTY OWNERS" << endl;
    board.print();

    return 0;
}
