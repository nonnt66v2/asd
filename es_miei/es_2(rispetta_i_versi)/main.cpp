#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <functional>

using namespace std;

// Structure to represent a node in the binary tree
struct Node {
    char c;       // character represented by this node
    int freq;     // frequency of this character
    Node* left;
    Node* right;
};

// Function to calculate the frequency of each character in the input
//string
        map<char, int> calculateFrequency(const string& str) {
    map<char, int> freq;
    for (char c : str) {
        freq[c]++;
    }
    return freq;
}

// Function to build a Huffman tree from the frequencies
Node* buildTree(map<char, int>& freq) {
    priority_queue<Node*, vector<Node*> pq,
    function<bool(const Node&, const Node&)>> pq(
            [](const Node& a, const Node& b) {
                return a.freq < b.freq;
            }
    );

    for (auto it = freq.begin(); it != freq.end(); ++it) {
        Node* node = new Node();
        node->c = it->first;
        node->freq = it->second;
        pq.push(node);
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node();
        newNode->c = '\0';
        newNode->freq = left->freq + right->freq;
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

// Function to generate Huffman codes from the tree
string generateCodes(Node* root, const string& str) {
    string codeStr;
    for (char c : str) {
        Node* node = root;
        while (node->c != '\0') {
            if (node->left && node->left->c == c) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        codeStr += node->c == '0' ? "0" : "1";
    }
    return codeStr;
}

int main() {
    string str = "this is a test";
    map<char, int> freq = calculateFrequency(str);

    Node* root = buildTree(freq);
    string codeStr = generateCodes(root, str);

    cout << "Huffman codes: " << codeStr << endl;

    return 0;
}

