#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Forward declarations
class Match;
class Listing;
class Team;
class FootballField;
class City;

// Match class
class Match {
protected:
    int ID;
    int Time;
    string Name;

public:
    void setID(int id) { ID = id; }
    int getID() const { return ID; }
    void setName(string n) { Name = n; }
    string getName() const { return Name; }
    void setTime(int t) { Time = t; }
    int getTime() const { return Time; }
    
    // Add comparison operators
    bool operator==(const Match& other) const {
        return ID == other.ID;
    }
    
    bool operator!=(const Match& other) const {
        return !(*this == other);
    }
};

// Listing class
class Listing {
protected:
    int ID;
    Match* match;
    int noAvailable;

public:
    void setID(int id) { ID = id; }
    int getID() const { return ID; }
    void setMatch(Match* m) { match = m; }
    Match* getMatch() const { return match; }
    void setNoAvailable(int no) { noAvailable = no; }
    int getNoAvailable() const { return noAvailable; }
    
    bool operator==(const Listing& other) const {
        return ID == other.ID;
    }
    
    bool operator!=(const Listing& other) const {
        return !(*this == other);
    }
};

// Team class
class Team {
protected:
    int ID;
    vector<Match*> MatchList;
    string Name;
    string Country;
    string Coach;

public:
    void setID(int id) { ID = id; }
    int getID() const { return ID; }
    void setName(string n) { Name = n; }
    string getName() const { return Name; }
    void setCountry(string C) { Country = C; }
    string getCountry() const { return Country; }
    void setCoach(string c) { Coach = c; }
    string getCoach() const { return Coach; }
    void addMatch(Match* m) { MatchList.push_back(m); }
    vector<Match*> getMatchList() const { return MatchList; }
    
    bool operator==(const Team& other) const {
        return ID == other.ID;
    }
    
    bool operator!=(const Team& other) const {
        return !(*this == other);
    }

    void displayMatches() {
        cout << "Matches for team " << Name << ":" << endl;
        for (auto match : MatchList) {
            cout << "Match ID: " << match->getID() << ", Name: " << match->getName() << ", Time: " << match->getTime() << endl;
        }
    }
};

// FootballField class
class FootballField {
protected:
    int ID;
    string Name;
    vector<Listing*> listings;

public:
    void setID(int id) { ID = id; }
    int getID() const { return ID; }
    void setName(string n) { Name = n; }
    string getName() const { return Name; }
    void addListing(Listing* l) { listings.push_back(l); }
    vector<Listing*> getListings() const { return listings; }
    
    bool operator==(const FootballField& other) const {
        return ID == other.ID;
    }
    
    bool operator!=(const FootballField& other) const {
        return !(*this == other);
    }

    void displayListings() {
        cout << "Listings for football field " << Name << ":" << endl;
        for (auto listing : listings) {
            cout << "Listing ID: " << listing->getID() << ", Match: " << listing->getMatch()->getName() 
                 << ", Available: " << listing->getNoAvailable() << endl;
        }
    }
};

// City class
class City {
protected:
    int ID;
    string Name;
    vector<FootballField*> footballFields;
    vector<Team*> teams;

public:
    void setID(int id) { ID = id; }
    int getID() const { return ID; }
    void setName(string n) { Name = n; }
    string getName() const { return Name; }
    void addFootballField(FootballField* f) { footballFields.push_back(f); }
    vector<FootballField*> getFootballFields() const { return footballFields; }
    void addTeam(Team* t) { teams.push_back(t); }
    vector<Team*> getTeams() const { return teams; }
    
    bool operator==(const City& other) const {
        return ID == other.ID;
    }
    
    bool operator!=(const City& other) const {
        return !(*this == other);
    }

    void displayInfo() {
        cout << "City: " << Name << endl;
        cout << "Football Fields:" << endl;
        for (auto field : footballFields) {
            cout << "- " << field->getName() << " (ID: " << field->getID() << ")" << endl;
        }
        cout << "Teams:" << endl;
        for (auto team : teams) {
            cout << "- " << team->getName() << " (ID: " << team->getID() << ")" << endl;
        }
    }
};

// Node implementation
template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

// LinkedList implementation
template <typename T>
class LinkedList {
protected:
    Node<T>* head;
    int count;

public:
    LinkedList() : head(nullptr), count(0) {}
    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    Node<T>* getHead() const { return head; }

    void insert(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        count++;
    }

    bool remove(T val) {
        if (head == nullptr) return false;

        if (head->data == val) {
            Node<T>* toDelete = head;
            head = head->next;
            delete toDelete;
            count--;
            return true;
        }

        Node<T>* current = head;
        while (current->next != nullptr && current->next->data != val) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Node<T>* toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
            count--;
            return true;
        }

        return false;
    }

    T* find(int id) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data.getID() == id) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    void display() {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << "ID: " << current->data.getID() << ", Name: " << current->data.getName() << endl;
            current = current->next;
        }
    }

    int size() const { return count; }
};

// Stack implementation
template <typename T>
class Stack {
private:
    Node<T>* top;
    int count;

public:
    Stack() : top(nullptr), count(0) {}
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = top;
        top = newNode;
        count++;
    }

    T pop() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        Node<T>* temp = top;
        T poppedValue = top->data;
        top = top->next;
        delete temp;
        count--;
        return poppedValue;
    }

    T peek() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return top->data;
    }

    bool isEmpty() const { return top == nullptr; }
    int size() const { return count; }

    void display() {
        Node<T>* current = top;
        while (current != nullptr) {
            cout << "ID: " << current->data.getID() << ", Name: " << current->data.getName() << endl;
            current = current->next;
        }
    }
};

// Queue implementation
template <typename T>
class Queue {
private:
    Node<T>* front;
    Node<T>* rear;
    int count;

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw out_of_range("Queue is empty");
        }
        Node<T>* temp = front;
        T dequeuedValue = front->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        count--;
        return dequeuedValue;
    }

    T peek() {
        if (isEmpty()) {
            throw out_of_range("Queue is empty");
        }
        return front->data;
    }

    bool isEmpty() const { return front == nullptr; }
    int size() const { return count; }

    void display() {
        Node<T>* current = front;
        while (current != nullptr) {
            cout << "ID: " << current->data.getID() << ", Name: " << current->data.getName() << endl;
            current = current->next;
        }
    }
};

// Application class to manage everything
class SaudiFIFAWorldCup2034 {
private:
    LinkedList<Match> matchList;
    LinkedList<Listing> listingList;
    LinkedList<Team> teamList;
    LinkedList<FootballField> footballFieldList;
    LinkedList<City> cityList;

    Stack<Match> matchStack;
    Stack<Listing> listingStack;
    Stack<Team> teamStack;
    Stack<FootballField> footballFieldStack;
    Stack<City> cityStack;

    Queue<Match> matchQueue;
    Queue<Listing> listingQueue;
    Queue<Team> teamQueue;
    Queue<FootballField> footballFieldQueue;
    Queue<City> cityQueue;

public:
    void displayMainMenu() {
        int choice;
        do {
            cout << "\nSaudi FIFA World Cup 2034 - Main Menu\n";
            cout << "1. Matches\n";
            cout << "2. Football Fields\n";
            cout << "3. Teams\n";
            cout << "4. Cities\n";
            cout << "5. Convert to Stacks (Part 2)\n";
            cout << "6. Convert to Queues (Part 3)\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: displaySubMenu("Matches"); break;
                case 2: displaySubMenu("Football Fields"); break;
                case 3: displaySubMenu("Teams"); break;
                case 4: displaySubMenu("Cities"); break;
                case 5: convertToStacks(); break;
                case 6: convertToQueues(); break;
                case 0: cout << "Exiting...\n"; break;
                default: cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }

    void displaySubMenu(string category) {
        int choice;
        do {
            cout << "\n" << category << " Menu\n";
            cout << "1. Display\n";
            cout << "2. Insert\n";
            cout << "3. Delete\n";
            cout << "4. Modify\n";
            cout << "5. Find\n";
            cout << "0. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: displayItems(category); break;
                case 2: insertItem(category); break;
                case 3: deleteItem(category); break;
                case 4: modifyItem(category); break;
                case 5: findItem(category); break;
                case 0: cout << "Returning to Main Menu...\n"; break;
                default: cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }

    void displayItems(string category) {
        if (category == "Matches") {
            cout << "\nMatches List:\n";
            matchList.display();
        } else if (category == "Football Fields") {
            cout << "\nFootball Fields List:\n";
            footballFieldList.display();
        } else if (category == "Teams") {
            cout << "\nTeams List:\n";
            teamList.display();
        } else if (category == "Cities") {
            cout << "\nCities List:\n";
            cityList.display();
        }
    }

    void insertItem(string category) {
        if (category == "Matches") {
            Match m;
            int id, time;
            string name;
            cout << "Enter Match ID: ";
            cin >> id;
            cout << "Enter Match Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Match Time: ";
            cin >> time;
            m.setID(id);
            m.setName(name);
            m.setTime(time);
            matchList.insert(m);
            cout << "Match added successfully.\n";
        }
        // Similar implementations for other categories...
        else if (category == "Football Fields") {
            FootballField f;
            int id;
            string name;
            cout << "Enter Football Field ID: ";
            cin >> id;
            cout << "Enter Football Field Name: ";
            cin.ignore();
            getline(cin, name);
            f.setID(id);
            f.setName(name);
            footballFieldList.insert(f);
            cout << "Football Field added successfully.\n";
        }
        else if (category == "Teams") {
            Team t;
            int id;
            string name, country, coach;
            cout << "Enter Team ID: ";
            cin >> id;
            cout << "Enter Team Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Team Country: ";
            getline(cin, country);
            cout << "Enter Team Coach: ";
            getline(cin, coach);
            t.setID(id);
            t.setName(name);
            t.setCountry(country);
            t.setCoach(coach);
            teamList.insert(t);
            cout << "Team added successfully.\n";
        }
        else if (category == "Cities") {
            City c;
            int id;
            string name;
            cout << "Enter City ID: ";
            cin >> id;
            cout << "Enter City Name: ";
            cin.ignore();
            getline(cin, name);
            c.setID(id);
            c.setName(name);
            cityList.insert(c);
            cout << "City added successfully.\n";
        }
    }

    void deleteItem(string category) {
        int id;
        cout << "Enter ID to delete: ";
        cin >> id;

        if (category == "Matches") {
            Match* m = matchList.find(id);
            if (m) {
                matchList.remove(*m);
                cout << "Match deleted successfully.\n";
            } else {
                cout << "Match not found.\n";
            }
        }
        // Similar implementations for other categories...
        else if (category == "Football Fields") {
            FootballField* f = footballFieldList.find(id);
            if (f) {
                footballFieldList.remove(*f);
                cout << "Football Field deleted successfully.\n";
            } else {
                cout << "Football Field not found.\n";
            }
        }
        else if (category == "Teams") {
            Team* t = teamList.find(id);
            if (t) {
                teamList.remove(*t);
                cout << "Team deleted successfully.\n";
            } else {
                cout << "Team not found.\n";
            }
        }
        else if (category == "Cities") {
            City* c = cityList.find(id);
            if (c) {
                cityList.remove(*c);
                cout << "City deleted successfully.\n";
            } else {
                cout << "City not found.\n";
            }
        }
    }

    void modifyItem(string category) {
        int id;
        cout << "Enter ID to modify: ";
        cin >> id;

        if (category == "Matches") {
            Match* m = matchList.find(id);
            if (m) {
                int time;
                string name;
                cout << "Enter new Match Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter new Match Time: ";
                cin >> time;
                m->setName(name);
                m->setTime(time);
                cout << "Match updated successfully.\n";
            } else {
                cout << "Match not found.\n";
            }
        }
        // Similar implementations for other categories...
        else if (category == "Football Fields") {
            FootballField* f = footballFieldList.find(id);
            if (f) {
                string name;
                cout << "Enter new Football Field Name: ";
                cin.ignore();
                getline(cin, name);
                f->setName(name);
                cout << "Football Field updated successfully.\n";
            } else {
                cout << "Football Field not found.\n";
            }
        }
        else if (category == "Teams") {
            Team* t = teamList.find(id);
            if (t) {
                string name, country, coach;
                cout << "Enter new Team Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter new Team Country: ";
                getline(cin, country);
                cout << "Enter new Team Coach: ";
                getline(cin, coach);
                t->setName(name);
                t->setCountry(country);
                t->setCoach(coach);
                cout << "Team updated successfully.\n";
            } else {
                cout << "Team not found.\n";
            }
        }
        else if (category == "Cities") {
            City* c = cityList.find(id);
            if (c) {
                string name;
                cout << "Enter new City Name: ";
                cin.ignore();
                getline(cin, name);
                c->setName(name);
                cout << "City updated successfully.\n";
            } else {
                cout << "City not found.\n";
            }
        }
    }

    void findItem(string category) {
        int id;
        cout << "Enter ID to find: ";
        cin >> id;

        if (category == "Matches") {
            Match* m = matchList.find(id);
            if (m) {
                cout << "Match found:\n";
                cout << "ID: " << m->getID() << ", Name: " << m->getName() << ", Time: " << m->getTime() << endl;
            } else {
                cout << "Match not found.\n";
            }
        }
        // Similar implementations for other categories...
        else if (category == "Football Fields") {
            FootballField* f = footballFieldList.find(id);
            if (f) {
                cout << "Football Field found:\n";
                cout << "ID: " << f->getID() << ", Name: " << f->getName() << endl;
            } else {
                cout << "Football Field not found.\n";
            }
        }
        else if (category == "Teams") {
            Team* t = teamList.find(id);
            if (t) {
                cout << "Team found:\n";
                cout << "ID: " << t->getID() << ", Name: " << t->getName() 
                     << ", Country: " << t->getCountry() << ", Coach: " << t->getCoach() << endl;
            } else {
                cout << "Team not found.\n";
            }
        }
        else if (category == "Cities") {
            City* c = cityList.find(id);
            if (c) {
                cout << "City found:\n";
                cout << "ID: " << c->getID() << ", Name: " << c->getName() << endl;
            } else {
                cout << "City not found.\n";
            }
        }
    }

    void convertToStacks() {
        // Convert all linked lists to stacks
        Node<Match>* matchNode = matchList.getHead();
        while (matchNode != nullptr) {
            matchStack.push(matchNode->data);
            matchNode = matchNode->next;
        }

        Node<Listing>* listingNode = listingList.getHead();
        while (listingNode != nullptr) {
            listingStack.push(listingNode->data);
            listingNode = listingNode->next;
        }

        Node<Team>* teamNode = teamList.getHead();
        while (teamNode != nullptr) {
            teamStack.push(teamNode->data);
            teamNode = teamNode->next;
        }

        Node<FootballField>* fieldNode = footballFieldList.getHead();
        while (fieldNode != nullptr) {
            footballFieldStack.push(fieldNode->data);
            fieldNode = fieldNode->next;
        }

        Node<City>* cityNode = cityList.getHead();
        while (cityNode != nullptr) {
            cityStack.push(cityNode->data);
            cityNode = cityNode->next;
        }

        cout << "All lists converted to stacks.\n";
    }

    void convertToQueues() {
        // Convert all linked lists to queues
        Node<Match>* matchNode = matchList.getHead();
        while (matchNode != nullptr) {
            matchQueue.enqueue(matchNode->data);
            matchNode = matchNode->next;
        }

        Node<Listing>* listingNode = listingList.getHead();
        while (listingNode != nullptr) {
            listingQueue.enqueue(listingNode->data);
            listingNode = listingNode->next;
        }

        Node<Team>* teamNode = teamList.getHead();
        while (teamNode != nullptr) {
            teamQueue.enqueue(teamNode->data);
            teamNode = teamNode->next;
        }

        Node<FootballField>* fieldNode = footballFieldList.getHead();
        while (fieldNode != nullptr) {
            footballFieldQueue.enqueue(fieldNode->data);
            fieldNode = fieldNode->next;
        }

        Node<City>* cityNode = cityList.getHead();
        while (cityNode != nullptr) {
            cityQueue.enqueue(cityNode->data);
            cityNode = cityNode->next;
        }

        cout << "All lists converted to queues.\n";
    }
};

int main() {
    SaudiFIFAWorldCup2034 app;
    app.displayMainMenu();
    return 0;
}