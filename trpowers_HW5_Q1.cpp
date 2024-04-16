#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Node class template
template<typename T>
class Node {
    // Make MyList a friend class to access private members directly
    friend class MyList<T>;
private:
    T data;
    Node<T>* next;
public:
    Node(T newData) : data(newData), next(nullptr) {}
};

// MyList class template
template<typename T>
class MyList {
private:
    Node<T>* head;
public:
    MyList() : head(nullptr) {}

    void insertHead(T theData) {
        Node<T>* newNode = new Node<T>(theData);
        newNode->next = head;
        head = newNode;
    }

    T deleteHead() {
        if (head == nullptr) {
            throw logic_error("List is empty");
        }
        Node<T>* temp = head;
        T data = temp->data;
        head = head->next;
        delete temp;
        return data;
    }

    bool search(T& target) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == target) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void display() {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// Profile struct
struct Profile {
    string fullname;
    string state;

    bool operator==(const Profile& rhs) const {
        return (fullname == rhs.fullname);
    }

    bool operator!=(const Profile& rhs) const {
        return (fullname != rhs.fullname);
    }

    friend ostream& operator<<(ostream& out, const Profile& user) {
        out << user.fullname << "--" << user.state;
        return out;
    }
};

int main() {
    ifstream file("presidentsWstates.txt");
    string line;
    Profile temp;
    MyList<Profile> pMyList;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, temp.fullname, '\t');
            getline(ss, temp.state, '\t');
            pMyList.insertHead(temp);
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }

    // Test display function
    pMyList.display();

    // Test search function
    Profile searchProfile = {"George Washington", "VA"};
    cout << "Search result: " << (pMyList.search(searchProfile) ? "Found" : "Not found") << endl;

    // Test deleteHead function
    try {
        cout << "Deleted data: " << pMyList.deleteHead() << endl;
    } catch (const logic_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
