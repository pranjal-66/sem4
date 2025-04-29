
#include <iostream>
#include <cstring>
#include <limits>
using namespace std;
struct DictionaryEntry {
    char key[20];
    char meaning[100];
};
struct TreeNode {
    TreeNode *left;
    DictionaryEntry data;
    TreeNode *right;
};
class Stack {
    int top;
    TreeNode *data[30];
public:
    Stack() { top = -1; }
    bool isEmpty() { return top == -1; }
    void push(TreeNode *p) { data[++top] = p; }
    TreeNode *pop() { return data[top--]; }
};
class DictionaryBST {
    TreeNode *root;
    int comparisons;
public:
    DictionaryBST() { root = NULL; comparisons = 0; }
    TreeNode *getRoot() { return root; }
    void insertEntry(DictionaryEntry entry) {
        TreeNode *newNode = new TreeNode{NULL, entry, NULL};
        if (!root) { root = newNode; return; }
        TreeNode *current = root, *parent = NULL;
        while (current) {
            parent = current;
            if (!strcmp(current->data.key, entry.key)) {
                cout << "\nDuplicate entry!"; return;
            }
            current = strcmp(entry.key, current->data.key) < 0 ? current->left : current->right;
        }
        if (strcmp(entry.key, parent->data.key) < 0)
            parent->left = newNode;
        else
            parent->right = newNode;
    }
    void displayAscending(TreeNode *node) {
        if (node) {
            displayAscending(node->left);
            cout << node->data.key << ": " << node->data.meaning << endl;
            displayAscending(node->right);
        }
    }
    void displayDescending(TreeNode *node) {
        DictionaryEntry entries[100];
        Stack s;
        TreeNode *p = node;
        int count = 0;
        while (p) { s.push(p); p = p->left; }
        while (!s.isEmpty()) {
            p = s.pop();
            strcpy(entries[count].key, p->data.key);
            strcpy(entries[count].meaning, p->data.meaning);
            count++;
            p = p->right;
            while (p) { s.push(p); p = p->left; }
        }
        for (int i = count - 1; i >= 0; i--)
            cout << entries[i].key << ": " << entries[i].meaning << endl;
    }
    void deleteEntry(char key[]) {
        TreeNode *current = root, *parent = NULL;
        bool found = false;
        while (current) {
            if (!strcmp(current->data.key, key)) { found = true; break; }
            parent = current;
            current = strcmp(key, current->data.key) < 0 ? current->left : current->right;
        }
        if (!found) { cout << "\nKey not found!"; return; }
        if (!current->left && !current->right) {
            if (current == root) root = NULL;
            else if (parent->left == current) parent->left = NULL;
            else parent->right = NULL;
            delete current;
        } else if (!current->right) {
            if (current == root) root = current->left;
            else if (parent->left == current) parent->left = current->left;
            else parent->right = current->left;
            delete current;
        } else {
            TreeNode *p = current->right, *q = current;
            while (p->left) { q = p; p = p->left; }
            current->data = p->data;
            if (q == current) q->right = p->right;
            else q->left = p->right;
            delete p;
        }
        cout << "\nEntry deleted!";
    }
    void updateEntry(char key[]) {
        TreeNode *current = root;
        char newMeaning[100];
        while (current) {
            if (!strcmp(current->data.key, key)) {
                cout << "\nCurrent meaning of '" << key << "': " << current->data.meaning;
                cout << "\nEnter new meaning: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.getline(newMeaning, 100);
                strcpy(current->data.meaning, newMeaning);
                cout << "Updated successfully!"; return;
            }
            current = strcmp(key, current->data.key) < 0 ? current->left : current->right;
        }
        cout << "\nKey not found!";
    }
    void searchEntry(char key[]) {
        TreeNode *current = root;
        comparisons = 0;
   while (current) {
            comparisons++;
            if (!strcmp(current->data.key, key)) {
                cout << current->data.key << ": " << current->data.meaning;
                cout << "\nFound after " << comparisons << " comparisons."; return;
            }
            current = strcmp(key, current->data.key) < 0 ? current->left : current->right;
        }
        cout << "\nKey not found after " << comparisons << " comparisons.";
    }
};
int main() {
    DictionaryBST dict;
    int choice, subChoice;
    DictionaryEntry entry;
    char keyword[30];
    while (true) {
        cout << "\n******** DICTIONARY MENU *********";
        cout << "\n1. Add Word\n2. Display Words (Ascending)\n3. Delete Word";
        cout << "\n4. Update Meaning\n5. Display Words (Asc/Desc)";
        cout << "\n6. Search Word\n7. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 1:
                cout << "\nEnter keyword: ";
                cin.getline(entry.key, 20);
                cout << "Enter meaning: ";
                cin.getline(entry.meaning, 100);
                dict.insertEntry(entry);
                break;
            case 2:
                dict.displayAscending(dict.getRoot());
                break;
            case 3:
                cout << "\nEnter keyword to delete: ";
                cin.getline(keyword, 30);
                dict.deleteEntry(keyword);
                break;
            case 4:
                cout << "\nEnter keyword to update: ";
                cin.getline(keyword, 30);
                dict.updateEntry(keyword);
                break;
            case 5:
                cout << "\n1. Ascending\n2. Descending\nEnter choice: ";
                cin >> subChoice;
                cin.ignore();
                if (subChoice == 1)
                    dict.displayAscending(dict.getRoot());
                else
                    dict.displayDescending(dict.getRoot());
                break;
            case 6:
                cout << "\nEnter keyword to search: ";
                cin.getline(keyword, 30);
                dict.searchEntry(keyword);
                break;
            case 7:
                cout << "Exiting..."; return 0;
            default:
                cout << "Invalid choice!";
        }
    }
}


