#include <iostream>
#include <queue>
using namespace std;

typedef struct{
    int** keys;
    int numOfRows;
}Triangle;

typedef struct avlNode{
   
    avlNode* left;
    avlNode* right;
    int key; 
    int height;
};

int calculateBinomialCoef(int n, int k) {
    int value = 1;

    if (k < 0 || k > n)
        return 0;

    if (k == 0 || k == n)
        return 1;

    if (k > (n/2))
        k = n - k;

    for (int i = 0; i < k; i++) {
        value = value * (n - i);
        value = value / (i + 1);
    }
    return value;
}

Triangle generateLozanicTriangle(Triangle triangle) {
    
    cout << "Unesi broj redova Lozanicevog trougla:\n";
    cin >> triangle.numOfRows;

    triangle.keys = new int* [triangle.numOfRows];
    for (int i = 0; i < triangle.numOfRows ; i++) {
        triangle.keys[i] = new int[i + 1];
        for (int j = 0; j <= i ; j++) {
            if (j == 0 || i == 0 || j == i) {
                triangle.keys[i][j] = 1;
            }
            else {
                triangle.keys[i][j] = triangle.keys[i - 1][j - 1] + triangle.keys[i - 1][j] - 0.25 * (1 + pow(-1, i)) * (1 - pow(-1, j)) * calculateBinomialCoef((0.5 * i) - 1, 0.5 * (j - 1));
            }
        }
    }

    return triangle;
}

void printTriangle(Triangle triangle) {

    for (int i = 0; i < triangle.numOfRows; i++) {
        for (int j = 0; j <= i; j++) {
            cout << triangle.keys[i][j] << " ";
        }
        cout << endl;
    }
}

int binarySearch(Triangle triangle) {
    
    int row;
    cout << "Unesi broj reda:\n";
    cin >> row;

    if (row < 0 || row >= triangle.numOfRows) {
        return -1;
    }
    else
    {
        int key;
        cout << "Unesi kljuc za pretragu:\n";
        cin >> key;
        int rowItems;

        if ((row + 1) % 2 == 1) {
            rowItems = (row + 1) / 2 + 1;
        }
        else
        {
            rowItems = (row + 1) / 2 + 1;
        }

        int numOfSteps = 0;
        int low = 0;
        int high = rowItems - 1;

        while (low <= high) {
   
            int mid = low + (high - low) / 2;
            numOfSteps++;

            if (triangle.keys[row][mid] == key) {
                cout << "Broj koraka:" << numOfSteps << endl;
                cout << "Index:";
                return mid;
            }
            if (triangle.keys[row][mid] < key) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        return 0;
    }
}

int interpolationSearch(Triangle triangle) {
    int row;
    cout << "Unesi broj reda:\n";
    cin >> row;

    if (row < 0 || row >= triangle.numOfRows) {
        return -1;
    }
    else
    {
        int key;
        cout << "Unesi kljuc za pretragu:\n";
        cin >> key;
        int rowItems;

        if ((row + 1) % 2 == 1) {
            rowItems = (row + 1) / 2 + 1;
        }
        else
        {
            rowItems = (row + 1) / 2 + 1;
        }

        int numOfSteps = 0;
        int low = 0;
        int high = rowItems - 1;

        while (low <= high && key <= triangle.keys[row][high] && key >= triangle.keys[row][low]) {
            
            numOfSteps++;

            if (low == high) {
                if (key == triangle.keys[row][high]) {
                    cout << "Broj koraka:" << numOfSteps << endl;
                    cout << "Index:";
                    return high;
                }
                    
                return 0;
            }

            int mid = low + (high - low)*(key - triangle.keys[row][low])/(triangle.keys[row][high] - key);
            

            if (key == triangle.keys[row][mid]) {
                cout << "Broj koraka:" << numOfSteps << endl;
                cout << "Index:";
                return mid;
            }
                
            else if (triangle.keys[row][mid] < key) {
                low = mid + 1;
            }
                
            else {
                high = mid - 1;
            }
                
        }
        return 0;
    }
}



int getHeight(avlNode* node) {
    int lenght;
    cout << "Unesi velicinu skupa:\n";
    cin >> lenght;
    cout << "Unesi elemente:\n";
    int* array = new int[lenght];

    for (int i = 0; i < lenght; i++) {
        int key;
        cin >> key;
        array[i] = key;
    }

    int* commonKeys = new int[lenght];
    int index = 0;

    for (int i = 0; i < lenght; i++) {
        int check = findKeyInAvl(node, array[i]);
        if (check == 1) {
            commonKeys[index++] = array[i];
        }
    }
    avlNode* newRoot = nullptr;
    for (int i = 0; i < index; i++) {
        newRoot = insert(newRoot, commonKeys[index]);
    }

    return newRoot;
    //
    if (node != nullptr) {
        return node->height;
    }
    else
    {
        return 0;
    }
}

int getBalance(avlNode* node) {
    int lenght;
    cout << "Unesi velicinu skupa:\n";
    cin >> lenght;
    cout << "Unesi elemente:\n";
    int* array = new int[lenght];

    for (int i = 0; i < lenght; i++) {
        int key;
        cin >> key;
        array[i] = key;
    }

    int* commonKeys = new int[lenght];
    int index = 0;

    for (int i = 0; i < lenght; i++) {
        int check = findKeyInAvl(node, array[i]);
        if (check == 1) {
            commonKeys[index++] = array[i];
        }
    }
    avlNode* newRoot = nullptr;
    for (int i = 0; i < index; i++) {
        newRoot = insert(newRoot, commonKeys[index]);
    }

    return newRoot;
    //
    if (node != nullptr) {
        return getHeight(node->left) - getHeight(node->right);
    }
    else
    {
        return 0;
    }
    
}

avlNode* rotate(avlNode* node, char direction) {
    int lenght;
    cout << "Unesi velicinu skupa:\n";
    cin >> lenght;
    cout << "Unesi elemente:\n";
    int* array = new int[lenght];

    for (int i = 0; i < lenght; i++) {
        int key;
        cin >> key;
        array[i] = key;
    }

    int* commonKeys = new int[lenght];
    int index = 0;

    for (int i = 0; i < lenght; i++) {
        int check = findKeyInAvl(node, array[i]);
        if (check == 1) {
            commonKeys[index++] = array[i];
        }
    }
    avlNode* newRoot = nullptr;
    for (int i = 0; i < index; i++) {
        newRoot = insert(newRoot, commonKeys[index]);
    }

    return newRoot;
    //
    avlNode* child = nullptr, * temp = nullptr;

    switch (direction) {
    case 'l':
        child = node->right;
        temp = child->left;
    
        child->left = node;
        node->right = temp;

        break;
    case 'r':
        child = node->left;
        temp = child->right;

        child->right = node;
        node->left = temp;

        break;
    }
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    child->height = max(getHeight(child->left), getHeight(child->right)) + 1;

    return child;
}

avlNode* balance(avlNode* node,int key) {
    int lenght;
    cout << "Unesi velicinu skupa:\n";
    cin >> lenght;
    cout << "Unesi elemente:\n";
    int* array = new int[lenght];

    for (int i = 0; i < lenght; i++) {
        int key;
        cin >> key;
        array[i] = key;
    }

    int* commonKeys = new int[lenght];
    int index = 0;

    for (int i = 0; i < lenght; i++) {
        int check = findKeyInAvl(node, array[i]);
        if (check == 1) {
            commonKeys[index++] = array[i];
        }
    }
    avlNode* newRoot = nullptr;
    for (int i = 0; i < index; i++) {
        newRoot = insert(newRoot, commonKeys[index]);
    }

    return newRoot;
    //
    
    int balance = getBalance(node);

    if (balance > 1) {
        if (key < node->left->key) {
            return rotate(node, 'r');
        }
        else {
            node->left = rotate(node->left, 'l');
            return rotate(node, 'r');
        }
    }

    if (balance < -1) {
        if (key > node->right->key) {
            return rotate(node, 'l');
        }
        else {
            node->right = rotate(node->right, 'r');
            return rotate(node, 'l');
        }
    }

    return node;
}

avlNode* insert(avlNode* node, int key) {
    int lenght;
    cout << "Unesi velicinu skupa:\n";
    cin >> lenght;
    cout << "Unesi elemente:\n";
    int* array = new int[lenght];

    for (int i = 0; i < lenght; i++) {
        int key;
        cin >> key;
        array[i] = key;
    }

    int* commonKeys = new int[lenght];
    int index = 0;

    for (int i = 0; i < lenght; i++) {
        int check = findKeyInAvl(node, array[i]);
        if (check == 1) {
            commonKeys[index++] = array[i];
        }
    }
    avlNode* newRoot = nullptr;
    for (int i = 0; i < index; i++) {
        newRoot = insert(newRoot, commonKeys[index]);
    }

    return newRoot;
    //
    if (node == nullptr) {
        return new avlNode{ nullptr, nullptr,key, 1 };
    }

    else if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    else {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    node = balance(node, key);

    return node;
}

avlNode* createAVLTreeFromArray() {
    int lenght;
    cout << "Unesi velicinu skupa:\n";
    cin >> lenght;
    cout << "Unesi elemente:\n";
    avlNode* node = nullptr;
    for (int i = 0; i < lenght; i++) {
        int key;
        cin >> key;
        node = insert(node, key);
    }
    return node;
}


void printAVLTree(avlNode* root) {
    int lenght;
    cout << "Unesi velicinu skupa:\n";
    cin >> lenght;
    cout << "Unesi elemente:\n";
    int* array = new int[lenght];

    for (int i = 0; i < lenght; i++) {
        int key;
        cin >> key;
        array[i] = key;
    }

    int* commonKeys = new int[lenght];
    int index = 0;

    for (int i = 0; i < lenght; i++) {
        int check = findKeyInAvl(node, array[i]);
        if (check == 1) {
            commonKeys[index++] = array[i];
        }
    }
    avlNode* newRoot = nullptr;
    for (int i = 0; i < index; i++) {
        newRoot = insert(newRoot, commonKeys[index]);
    }

    return newRoot;
    //
    if (root == nullptr) return;

    printAVLTree(root->left);
    cout << root->key << " ";
    printAVLTree(root->right);
}

int findKeyInAvl(avlNode* node,int key) {
    int lenght;
    cout << "Unesi velicinu skupa:\n";
    cin >> lenght;
    cout << "Unesi elemente:\n";
    int* array = new int[lenght];

    for (int i = 0; i < lenght; i++) {
        int key;
        cin >> key;
        array[i] = key;
    }

    int* commonKeys = new int[lenght];
    int index = 0;

    for (int i = 0; i < lenght; i++) {
        int check = findKeyInAvl(node, array[i]);
        if (check == 1) {
            commonKeys[index++] = array[i];
        }
    }
    avlNode* newRoot = nullptr;
    for (int i = 0; i < index; i++) {
        newRoot = insert(newRoot, commonKeys[index]);
    }

    return newRoot;
    //
    if (node == nullptr) {
        cout << "Nema trazenog kljuca!";
        return 0;
    }
    else if (key < node->key) {
        findKeyInAvl(node->left, key);
    }
    else if (key > node->key) {
        findKeyInAvl(node->right, key);
    }
    else {
        cout << "Kljuc je pronadjen u stablu!";
        return 1;
    }
}

void deleteTree(avlNode* node) {
    int lenght;
    cout << "Unesi velicinu skupa:\n";
    cin >> lenght;
    cout << "Unesi elemente:\n";
    int* array = new int[lenght];

    for (int i = 0; i < lenght; i++) {
        int key;
        cin >> key;
        array[i] = key;
    }

    int* commonKeys = new int[lenght];
    int index = 0;

    for (int i = 0; i < lenght; i++) {
        int check = findKeyInAvl(node, array[i]);
        if (check == 1) {
            commonKeys[index++] = array[i];
        }
    }
    avlNode* newRoot = nullptr;
    for (int i = 0; i < index; i++) {
        newRoot = insert(newRoot, commonKeys[index]);
    }

    return newRoot;
    //
    if (node == nullptr) return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

avlNode* findCommonKeys(avlNode* node) {

    int lenght;
    cout << "Unesi velicinu skupa:\n";
    cin >> lenght;
    cout << "Unesi elemente:\n";
    int* array = new int[lenght];

    for (int i = 0; i < lenght; i++) {
        int key;
        cin >> key;
        array[i] = key;
    }

    int* commonKeys = new int[lenght];
    int index = 0;

    for (int i = 0; i < lenght; i++) {
        int check = findKeyInAvl(node, array[i]);
        if (check == 1) {
            commonKeys[index++] = array[i];
        }
    }
    avlNode* newRoot = nullptr;
    for (int i = 0; i < index; i++) {
        newRoot = insert(newRoot, commonKeys[index]);
    }

    return newRoot;
    
}

int main() {
   
    Triangle triangle{};
    avlNode* root = nullptr;
    avlNode* root2 = nullptr;
    int choice;
    
    while (true) {
        cout << "[1]Generisi Lozanicev trougao\n[2]Ispisi\n[3]Binarna pretraga kljuca\n[4]Interpolaciona pretraga kljuca\n\n[5]Generisi AVL stablo iz niza\n[6]Ispisi stablo\n[7]Pronadji kljuc u stablu\n[8]Obrisi stablo\n[9]Odradi presek dva stabla\n[0]Izlaz\n";
        cin >> choice;
        switch (choice) {
        case 1: triangle = generateLozanicTriangle(triangle);
            break;
        case 2: printTriangle(triangle);
            break;
        case 3: cout << binarySearch(triangle) << endl;
            break;
        case 4: cout << interpolationSearch(triangle) << endl;
            break;
        case 5: root = createAVLTreeFromArray();
            break;
        case 6: printAVLTree(root);
            cout << '\n';
            break;
        case 7:
            int key;
            cout << "Unesite kljuc za pretragu:\n";
            cin >> key;
            cout << findKeyInAvl(root,key) << endl;;
            break;
        case 8: deleteTree(root);
            break;
        case 9: root2 = findCommonKeys(root);
                printAVLTree(root2);
            break;
        case 0: exit(1);
            break;
        }
    }
    

    return 0;
}