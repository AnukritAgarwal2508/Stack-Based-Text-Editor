#include <iostream>
#include <stack>
#include <string>
#include <fstream>

using namespace std;

class TextEditor {
public:
    TextEditor() {
        text = "";
        textHistory.push(text);
    }

    void insertText(const string& newText) {
        text += newText;
        textHistory.push(text);
        redoHistory = stack<string>();
        cout << "Inserted: " << newText << endl;
    }

    void undo() {
        if (textHistory.size() > 1) {
            redoHistory.push(textHistory.top());
            textHistory.pop();
            text = textHistory.top();
            cout << "Undo: " <<  "  " << endl;
            cout << "undo operation performed" << endl;
        } else {
            cout << "Nothing to undo." << endl;
        }
    }

    void redo() {
    if (!redoHistory.empty()) {
        string previousText = text;
        textHistory.push(redoHistory.top());
        text = redoHistory.top();
        redoHistory.pop();
        cout << "Redo operation performed" << endl;
        cout << "Current Text: " << text << endl; // Display current text
    } else {
        cout << "Nothing to redo." << endl;
    }

    }

    void displayText() const {
        cout << "Current Text:\n" << text << endl;
    }

    void clearText(int numChars) {
        if (numChars <= text.length()) {
            string clearedText = text.substr(0, numChars);
            text = text.substr(numChars);
            textHistory.push(text);
            cout << "Cleared Text (" << numChars << " characters): " << clearedText << endl;
        } else {
            cout << "Cannot clear more characters than available in the text." << endl;
        }
    }

    void saveToFile(const string& filename) {
        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            outputFile << text;
            outputFile.close();
            cout << "Text saved to file: " << filename << endl;
        } else {
            cout << "Unable to save text to file." << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            text = "";
            textHistory = stack<string>();
            redoHistory = stack<string>();
            textHistory.push(text);
            string line;
            while (getline(inputFile, line)) {
                insertText(line + "\n");
            }
            inputFile.close();
            cout << "Text loaded from file: " << filename << endl;
        } else {
            cout << "Unable to load text from file." << endl;
        }
    }

    void search(const string& query) {
        size_t pos = text.find(query);
        if (pos != string::npos) {
            cout << "Text found at position " << pos << endl;
        } else {
            cout << "Text not found." << endl;
        }
    }

private:
    string text;
    stack<string> textHistory;
    stack<string> redoHistory;
};

int main() {
    TextEditor editor;

    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Insert Text" << endl;
        cout << "2. Undo" << endl;
        cout << "3. Redo" << endl;
        cout << "4. Display Text" << endl;
        cout << "5. Clear Text" << endl;
        cout << "6. Save to File" << endl;
        cout << "7. Load from File" << endl;
        cout << "8. Search" << endl;
        cout << "9. Exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter text to insert: ";
                string newText;
                cin.ignore();
                getline(cin, newText);
                editor.insertText(newText);
                break;
            }
            case 2:
                editor.undo();
                break;
            case 3:
                editor.redo();
                break;
            case 4:
                editor.displayText();
                break;
            case 5: {
                int numChars;
                cout << "Enter the number of characters to clear: ";
                cin >> numChars;
                editor.clearText(numChars);
                break;
            }
            case 6: {
                cout << "Enter filename to save: ";
                string filename;
                cin >> filename;
                editor.saveToFile(filename);
                break;
            }
            case 7: {
                cout << "Enter filename to load: ";
                string filename;
                cin >> filename;
                editor.loadFromFile(filename);
                break;
            }
            case 8: {
                cout << "Enter text to search: ";
                string query;
                cin.ignore();
                getline(cin, query);
                editor.search(query);
                break;
            }
            case 9:
                cout << "Exiting the text editor. Final text:\n";
                editor.displayText();
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}