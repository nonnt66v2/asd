#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << setw(3) << elem;
        }
        cout << endl;
    }
}
void printMatrix(const vector<vector<string>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << setw(3) << elem;
        }
        cout << endl;
    }
}
void printMatrix(const vector<vector<string>>& matrix, const string& a, const string& b) {
    cout << "      ";
    for (char ch : b) {
        cout << setw(3) << ch;
    }
    cout<<endl;
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (i > 0) {
            cout << setw(3) << a[i - 1];
        } else {
            cout << "   ";
        }
        for (const auto& elem : matrix[i]) {
            cout << setw(3) << elem;
        }
        cout << endl;
    }
}

int LCS_length(string a, string b, int dimA, int dimB, vector<vector<int>>& c) {
    for (int i = 0; i < dimA; i++) {
        for (int j = 0; j < dimB; j++) {
            if (i == 0 || j == 0) {
                c[i][j] = 0;
            } else if (a[i] == b[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
            } else {
                c[i][j] = max(c[i][j - 1], c[i - 1][j]);
            }
        }
    }
    printMatrix(c);
    return c[dimA - 1][dimB - 1];
}

void LCS_lenght_withPath( string a, string b,int dimA, int dimB, vector<vector<int>>& c) {
    vector<vector<string>> P(dimA, vector<string>(dimB, "0"));

    for (int i = 1; i < dimA; i++) {
        for (int j = 1; j < dimB; j++) {
            if (a[i] == b[j]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                P[i][j] = "\\";
            }else {
                if (c[i - 1][j] >= c[i][j - 1]) {
                    c[i][j] = c[i - 1][j];
                    P[i][j] = "|";
                } else {
                    c[i][j] = c[i][j - 1];
                    P[i][j] = "-";
                }
            }
        }
    }

    cout << endl;
    printMatrix(P,a,b);
}

string backtrackLCS(const vector<vector<int>>& c, const string& a, const string& b, int dimA, int dimB) {
    string lcs;
    int i = dimA - 1, j = dimB - 1;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            lcs = a[i - 1] + lcs;
            i--;
            j--;
        } else if (c[i - 1][j] >= c[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    return lcs;
}


int main() {
    string a = "denise";
    string b = "lorenzo";

    int dimA = a.length() ;
    int dimB = b.length() ;
    vector<vector<int>> c(dimA, vector<int>(dimB, 0));
    int length = LCS_length(a, b, dimA, dimB, c);
    cout << "\nLCS length: " << length << endl;
    string lcs = backtrackLCS(c, a, b, dimA, dimB);
    cout << "LCS: " << lcs << endl;
    /*vector<vector<int>> d(dimA, vector<int>(dimB, 0));
    LCS_lenght_withPath(a,b,dimA,dimB,d);*/
    return 0;
}