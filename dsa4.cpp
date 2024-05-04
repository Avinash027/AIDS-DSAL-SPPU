#include <iostream>
using namespace std;

class Node {
    string word;
    string meaning;
    Node *left;
    Node *right;
public:
    Node() {
        word = "";
        meaning = "";
        left = NULL;
        right = NULL;
    }
    Node(string word, string meaning) {
        this->word = word;
        this->meaning = meaning;
        left = NULL;
        right = NULL;
    }
    friend class Dictionary;
};

class Dictionary {
    Node *root;
public:
    Dictionary() {
        root = NULL;
    }

    // add Node
    void insert() {
        Node *new_node = new Node();
        // input new node
        cout << "Enter new Word: ";
        cin >> new_node->word;
        cout << "Enter meaning:";
        cin.ignore();
        getline(cin, new_node->meaning);
        // If root is null i.e dictionary is empty
        if (root == NULL) {
            root = new_node;
            cout << "Word Added to Dictionary !" << endl;
            return;
        }
        Node *current = root;
        while (current != NULL) {
            if (current->word > new_node->word) {
                if (current->left == NULL) {
                    current->left = new_node;
                    cout << "left" << current->word << endl;
                    return;
                }
                current = current->left;
            }
            else {
                if (current->right == NULL) {
                    current->right = new_node;
                    cout << "right" << current->word << endl;
                    return;
                }
                current = current->right;
            }
        }
    }

    //Traversal:
    void inorder(Node *temp) {
        if (temp == NULL) {
            return;
        }
        inorder(temp->left);
        cout << temp->word << " = " << temp->meaning << endl;
        inorder(temp->right);
    }

    void inorder() {
        inorder(root);
    }

    //Preorder:
    void postorder(Node *temp) {
        if (temp == NULL) {
            return;
        }
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->word << " = " << temp->meaning << endl;
    }

    void postorder() {
        postorder(root);
    }

    //Searching a node
    int search(string key) {
        int count = 0;
        Node *current = root;
        while (current != NULL) {
            if (current->word == key) {
                count = count + 1;
                cout << current->word << " = " << current->meaning << endl;
            }
            if (current->word > key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return count;
    }

    //Update Function
    void update(string key) {
        Node *current = root;
        string meaning;
        while (current != NULL) {
            if (current->word == key) {
                cout << current->word << " = " << current->meaning << endl;
                cout << "Enter new meaning: " << endl;
                cin.ignore();
                getline(cin, meaning);
                current->meaning = meaning;
                return;
            }
            if (current->word > key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
    }

    //Delete a Node
    void deleteNode(string key) {
        Node *current = root;
        Node *parent = NULL;

        // 3 Conditions for deletion
        // 1. Node to be deleted is a leaf node
        // 2. Node to be deleted have one child
        // 3. Node to be deleted has two children
        while (current != NULL && current->word != key) {
            parent = current;
            if (current->word > key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        // If current is null then value is not present
        if (current == NULL) {
            cout << "Word is not present in the dictionary!!" << endl;
            return;
        }

        // Check the node to be deleted has 0 or 1 child
        if (current->left == NULL || current->right == NULL) {
            // check if current have left or right child
            Node *new_node = current->left ? current->left : current->right;

            // check if current is parents left or right
            if (parent == NULL) {
                root = new_node;
            }
            else if (parent->left == current) {
                parent->left = new_node;
            }
            else {
                parent->right = new_node;
            }
            delete current;
        }
        else {
            Node *prev = NULL;
            Node *temp = current->right;
            while (temp->left != NULL) {
                prev = temp;
                temp = temp->left;
            }
            prev != NULL ? prev->left = temp->right : current->right = temp->right;
            current->word = temp->word;
            current->meaning = temp->meaning;
            delete temp;
        }
    }
};

int main() {
    Dictionary *dict = new Dictionary();
    cout << "1. View New Words (Ascending Order)" << endl;
    cout << "2. View New Words (Descending Order)" << endl;
    cout << "3. Add Words" << endl;
    cout << "4. Search Word" << endl;
    cout << "5. Update Word" << endl;
    cout << "6. Exit" << endl;

    int ch = 0;
    string key;
    bool flag = true;
    while (flag) {
        cout << "Enter Your choice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            cout << "----------------------------\n";
            cout << "Ascending Order:" << endl;
            dict->inorder();
            cout << "----------------------------\n";
            break;
        case 2:
            cout << "----------------------------\n";
            cout << "Descending Order:" << endl;
            dict->postorder();
            cout << "----------------------------\n";
            break;
        case 3:
            cout << "----------------------------\n";
            dict->insert();
            cout << "----------------------------\n";
            break;
        case 4:
            cout << "----------------------------\n";
            cout << "Enter key to search: ";
            cin >> key;
            cout << dict->search(key) << " entries found!" << endl;
            cout << "----------------------------\n";
            break;
        case 5:
            cout << "----------------------------\n";
            cout << "Enter key to update: ";
            cin >> key;
            dict->update(key);
            cout << "----------------------------\n";
            break;
        case 6:
            cout << "----------------------------\n";
            cout << "EXIT" << endl;
            flag = false;
            cout << "----------------------------\n";
            break;
        default:
            cout << "----------------------------\n";
            cout << "Invalid Input" << endl;
        }
    }
    delete dict;
    return 0;
}
