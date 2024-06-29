#include <iostream>
#include <random>
#include <cstdlib>

using namespace std;

int getRandom() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 1);
    return dis(gen);
}


bool isSafe(int** arr, int x, int y, int n) {
    return (x < n && y < n && arr[x][y] == 1);
}

bool RatInMaze(int** arr, int x, int y, int n, int** solArr) {
    if (x == n - 1 && y == n - 1 && arr[x][y] == 1) {
        solArr[x][y] = 1;
        return true;
    }

    if (isSafe(arr, x, y, n)) {
        solArr[x][y] = 1;

        if (RatInMaze(arr, x + 1, y, n, solArr)) {
            return true;
        }
        if (RatInMaze(arr, x, y + 1, n, solArr)) {
            return true;
        }

        solArr[x][y] = 0; 
        return false;
    }

    return false;
}

int main() {
    while (true) {
        system("clear");
        int n;
        cout << "Enter the size of the array: ";
        cin >> n;

        int** arr = new int*[n];
        for (int i = 0; i < n; i++) {
            arr[i] = new int[n];
        }

        cout << "The maze matrix is: " << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr[i][j] = getRandom();
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }

        int** solArr = new int*[n];
        for (int i = 0; i < n; i++) {
            solArr[i] = new int[n];
            fill(solArr[i], solArr[i] + n, 0);
        }

        cout << "The path is: " << endl;
        if (RatInMaze(arr, 0, 0, n, solArr)) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << solArr[i][j] << " ";
                }
                cout << endl;
            }
        } else {
            cout << "No path found" << endl;
        }

        // Deallocate memory
        for (int i = 0; i < n; i++) {
            delete[] arr[i];
            delete[] solArr[i];
        }
        delete[] arr;
        delete[] solArr;

        cout << "Press 1 to try again, 0 to exit: ";
        int choice;
        cin >> choice;
        if (choice == 0) break;
    }

    return 0;
}
