#include <iostream>
using namespace std;

template<typename T>
class AVLNode {
public:
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;

    AVLNode(T value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

template<typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int getHeight(AVLNode<T>* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalance(AVLNode<T>* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(AVLNode<T>* node) {
        if (node != nullptr) {
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);
            if (leftHeight > rightHeight) {
                node->height = 1 + leftHeight;
            }
            else {
                node->height = 1 + rightHeight;
            }
        }
    }

    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* temp = x->right;

        x->right = y;
        y->left = temp;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* temp = y->left;

        y->left = x;
        x->right = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode<T>* leftRightRotate(AVLNode<T>* node) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    AVLNode<T>* rightLeftRotate(AVLNode<T>* node) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    AVLNode<T>* insert(AVLNode<T>* node, T value) {
        if (node == nullptr) {
            return new AVLNode<T>(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        else {
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }

        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }

        if (balance > 1 && value > node->left->data) {
            return leftRightRotate(node);
        }

        if (balance < -1 && value < node->right->data) {
            return rightLeftRotate(node);
        }

        return node;
    }

    AVLNode<T>* deleteNode(AVLNode<T>* node, T value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        }
        else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                AVLNode<T>* temp;
                if (node->left) {
                    temp = node->left;
                }
                else {
                    temp = node->right;
                }

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else {
                AVLNode<T>* temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (node == nullptr) {
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }

        if (balance > 1 && getBalance(node->left) < 0) {
            return leftRightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }

        if (balance < -1 && getBalance(node->right) > 0) {
            return rightLeftRotate(node);
        }

        return node;
    }

    AVLNode<T>* findMin(AVLNode<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void inorderDisplay(AVLNode<T>* node) {
        if (node != nullptr) {
            inorderDisplay(node->left);
            cout << node->data << " ";
            inorderDisplay(node->right);
        }
    }

    void collectNodes(AVLNode<T>* node, T* arr, int& index) {
        if (node != nullptr) {
            collectNodes(node->left, arr, index);
            arr[index++] = node->data;
            collectNodes(node->right, arr, index);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insertValue(T value) {
        root = insert(root, value);
    }

    void deleteValue(T value) {
        root = deleteNode(root, value);
    }

    void displayNodes() {
        inorderDisplay(root);
        cout << endl;
    }

    int recursiveHeight(AVLNode<T>* node) {
        if (node == nullptr) return 0;
        int leftHeight = recursiveHeight(node->left);
        int rightHeight = recursiveHeight(node->right);
        if (leftHeight > rightHeight) {
            return 1 + leftHeight;
        }
        else {
            return 1 + rightHeight;
        }
    }

    int findBalancingFactor(AVLNode<T>* node) {
        return getBalance(node);
    }

    AVLNode<T>* getRoot() {
        return root;
    }

    AVLTree<T> mergeAVLTrees(AVLTree<T>& other) {
        AVLTree<T> merged;

        T* arr1 = new T[10000];
        T* arr2 = new T[10000];
        int index1 = 0, index2 = 0;

        collectNodes(this->root, arr1, index1);
        collectNodes(other.root, arr2, index2);

        T* mergedArr = new T[20000];
        int i = 0, j = 0, k = 0;

        while (i < index1 && j < index2) {
            if (arr1[i] <= arr2[j]) {
                mergedArr[k++] = arr1[i++];
            }
            else {
                mergedArr[k++] = arr2[j++];
            }
        }

        while (i < index1) {
            mergedArr[k++] = arr1[i++];
        }

        while (j < index2) {
            mergedArr[k++] = arr2[j++];
        }

        for (int m = 0; m < k; m++) {
            merged.insertValue(mergedArr[m]);
        }

        delete[] arr1;
        delete[] arr2;
        delete[] mergedArr;

        return merged;
    }
};

class SongNode {
public:
    char name[20];
    int frequency;
    SongNode* next;
    SongNode* left;
    SongNode* right;
    int height;

    SongNode(char* songName, int freq) : frequency(freq), next(nullptr), left(nullptr), right(nullptr), height(1) {
        int i = 0;
        while (songName[i] != '\0' && i < 19) {
            name[i] = songName[i];
            i++;
        }
        name[i] = '\0';
    }
};

class SongAVLTree {
private:
    SongNode* root;

    int getHeight(SongNode* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalance(SongNode* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(SongNode* node) {
        if (node != nullptr) {
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);
            if (leftHeight > rightHeight) {
                node->height = 1 + leftHeight;
            }
            else {
                node->height = 1 + rightHeight;
            }
        }
    }

    SongNode* rightRotate(SongNode* y) {
        SongNode* x = y->left;
        SongNode* temp = x->right;

        x->right = y;
        y->left = temp;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    SongNode* leftRotate(SongNode* x) {
        SongNode* y = x->right;
        SongNode* temp = y->left;

        y->left = x;
        x->right = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    SongNode* insert(SongNode* node, char* songName, int freq) {
        if (node == nullptr) {
            return new SongNode(songName, freq);
        }

        if (freq < node->frequency) {
            node->left = insert(node->left, songName, freq);
        }
        else if (freq > node->frequency) {
            node->right = insert(node->right, songName, freq);
        }
        else {
            SongNode* newSong = new SongNode(songName, freq);
            newSong->next = node->next;
            node->next = newSong;
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && freq < node->left->frequency) {
            return rightRotate(node);
        }

        if (balance < -1 && freq > node->right->frequency) {
            return leftRotate(node);
        }

        if (balance > 1 && freq > node->left->frequency) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && freq < node->right->frequency) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void displayInorder(SongNode* node) {
        if (node != nullptr) {
            displayInorder(node->left);

            cout << node->name << " (freq: " << node->frequency << ")";
            SongNode* temp = node->next;
            while (temp != nullptr) {
                cout << " -> " << temp->name << " (freq: " << temp->frequency << ")";
                temp = temp->next;
            }
            cout << endl;

            displayInorder(node->right);
        }
    }

    SongNode* findSong(SongNode* node, char* songName) {
        if (node == nullptr) return nullptr;

        int cmp = 0;
        for (int i = 0; node->name[i] != '\0' && songName[i] != '\0'; i++) {
            if (node->name[i] != songName[i]) {
                if (node->name[i] < songName[i]) {
                    cmp = -1;
                }
                else {
                    cmp = 1;
                }
                break;
            }
        }

        if (cmp == 0) {
            int len1 = 0, len2 = 0;
            while (node->name[len1] != '\0') len1++;
            while (songName[len2] != '\0') len2++;
            if (len1 != len2) {
                if (len1 < len2) {
                    cmp = -1;
                }
                else {
                    cmp = 1;
                }
            }
        }

        if (cmp == 0) {
            return node;
        }
        else if (cmp < 0) {
            return findSong(node->right, songName);
        }
        else {
            return findSong(node->left, songName);
        }
    }

    SongNode* findSongInChain(SongNode* node, char* songName) {
        SongNode* current = node;
        while (current != nullptr) {
            int match = 1;
            for (int i = 0; current->name[i] != '\0' || songName[i] != '\0'; i++) {
                if (current->name[i] != songName[i]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

public:
    SongAVLTree() : root(nullptr) {}

    void insertSong(char* songName, int freq) {
        root = insert(root, songName, freq);
    }

    void playSong(char* songName) {
        SongNode* freqNode = findSongByName(root, songName);
        if (freqNode != nullptr) {
            cout << "Playing " << songName << " (frequency increased from " << freqNode->frequency << " to " << (freqNode->frequency + 1) << ")" << endl;
            freqNode->frequency++;
        }
        else {
            cout << "Song not found!" << endl;
        }
    }

    SongNode* findSongByName(SongNode* node, char* songName) {
        if (node == nullptr) return nullptr;

        SongNode* found = findSongInChain(node, songName);
        if (found != nullptr) return found;

        SongNode* leftResult = findSongByName(node->left, songName);
        if (leftResult != nullptr) return leftResult;

        return findSongByName(node->right, songName);
    }

    void displaySongs() {
        displayInorder(root);
    }

    void showMenu() {
        cout << "\n=== SPOTIFY SONG MANAGER ===" << endl;
        cout << "1. Display all songs" << endl;
        cout << "2. Play a song" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
    }

    void runMenu() {
        int choice;
        char songName[20];

        while (true) {
            showMenu();
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "\nCurrent Song Tree:" << endl;
                displaySongs();
                break;
            case 2:
                cout << "Enter song name to play: ";
                cin >> songName;
                playSong(songName);
                break;
            case 3:
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid choice!" << endl;
            }
        }
    }
};

class MinHeap {
private:
    int* heap;
    int capacity;
    int size;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)] > heap[index]) {
            int temp = heap[index];
            heap[index] = heap[parent(index)];
            heap[parent(index)] = temp;
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < size && heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < size && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            int temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;
            heapifyDown(smallest);
        }
    }

public:
    MinHeap(int cap) : capacity(cap), size(0) {
        heap = new int[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    void insert(int value) {
        if (size >= capacity) {
            cout << "Heap is full!" << endl;
            return;
        }

        heap[size] = value;
        heapifyUp(size);
        size++;
    }

    int extractMin() {
        if (size <= 0) {
            cout << "Heap is empty!" << endl;
            return -1;
        }

        int min = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);

        return min;
    }

    void buildHeap(int arr[], int n) {
        size = n;
        for (int i = 0; i < n; i++) {
            heap[i] = arr[i];
        }

        for (int i = (n / 2) - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    void printHeap() {
        cout << "Heap: ";
        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }

    void extractTopK(int k) {
        cout << "Top " << k << " priority tasks: ";
        for (int i = 0; i < k && size > 0; i++) {
            cout << extractMin() << " ";
        }
        cout << endl;
    }
};

class HashNode {
public:
    int key;
    HashNode* next;

    HashNode(int k) : key(k), next(nullptr) {}
};

class HashTable {
private:
    HashNode** table;
    int tableSize;
    int currentSize;

    int hashFunction(int key) {
        return key % tableSize;
    }

    double loadFactor() {
        return (double)currentSize / tableSize;
    }

    void rehash() {
        HashNode** oldTable = table;
        int oldSize = tableSize;

        tableSize = tableSize * 2;
        currentSize = 0;
        table = new HashNode * [tableSize];

        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }

        for (int i = 0; i < oldSize; i++) {
            HashNode* current = oldTable[i];
            while (current != nullptr) {
                insertChaining(current->key);
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }

        delete[] oldTable;
    }

public:
    HashTable(int size) : tableSize(size), currentSize(0) {
        table = new HashNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < tableSize; i++) {
            HashNode* current = table[i];
            while (current != nullptr) {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insertChaining(int key) {
        if (loadFactor() > 0.7) {
            rehash();
        }

        int index = hashFunction(key);
        HashNode* newNode = new HashNode(key);

        if (table[index] == nullptr) {
            table[index] = newNode;
        }
        else {
            newNode->next = table[index];
            table[index] = newNode;
        }

        currentSize++;
    }

    bool search(int key) {
        int index = hashFunction(key);
        HashNode* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    void displayChaining() {
        cout << "Hash Table (Chaining):" << endl;
        for (int i = 0; i < tableSize; i++) {
            cout << "Index " << i << ": ";
            HashNode* current = table[i];
            while (current != nullptr) {
                cout << current->key << " -> ";
                current = current->next;
            }
            cout << "NULL" << endl;
        }
    }
};

class BucketHashTable {
private:
    int** buckets;
    int* bucketSizes;
    int numBuckets;
    int bucketCapacity;
    int totalElements;

    int hashFunction(int key) {
        return key % numBuckets;
    }

public:
    BucketHashTable(int buckets, int capacity) : numBuckets(buckets), bucketCapacity(capacity), totalElements(0) {
        this->buckets = new int* [numBuckets];
        bucketSizes = new int[numBuckets];

        for (int i = 0; i < numBuckets; i++) {
            this->buckets[i] = new int[bucketCapacity];
            bucketSizes[i] = 0;
        }
    }

    ~BucketHashTable() {
        for (int i = 0; i < numBuckets; i++) {
            delete[] buckets[i];
        }
        delete[] buckets;
        delete[] bucketSizes;
    }

    void insert(int key) {
        int index = hashFunction(key);

        if (bucketSizes[index] < bucketCapacity) {
            buckets[index][bucketSizes[index]] = key;
            bucketSizes[index]++;
            totalElements++;
        }
        else {
            cout << "Bucket " << index << " is full! Cannot insert " << key << endl;
        }
    }

    bool search(int key) {
        int index = hashFunction(key);

        for (int i = 0; i < bucketSizes[index]; i++) {
            if (buckets[index][i] == key) {
                return true;
            }
        }

        return false;
    }

    void display() {
        cout << "Hash Table (Bucketing):" << endl;
        for (int i = 0; i < numBuckets; i++) {
            cout << "Bucket " << i << ": ";
            for (int j = 0; j < bucketSizes[i]; j++) {
                cout << buckets[i][j] << " ";
            }
            cout << endl;
        }
    }
};

void displayMenu() {
    cout << "1. Test AVL Tree Template" << endl;
    cout << "2. Build specific AVL Tree and deletions" << endl;
    cout << "3. Merge two AVL Trees" << endl;
    cout << "4. Spotify Song Manager" << endl;
    cout << "5. Task Scheduler (MinHeap)" << endl;
    cout << "6. Hash Table Implementation" << endl;
    cout << "7. Display Time Complexities" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\n=== QUESTION 1: AVL Tree Template Test ===" << endl;
            AVLTree<int> avl;
            int values[] = { 10, 20, 30, 40, 50, 25 };

            cout << "Time Complexity - Insert: O(log n)" << endl;
            cout << "Time Complexity - Delete: O(log n)" << endl;
            cout << "Time Complexity - Search: O(log n)" << endl;
            cout << "Time Complexity - Height: O(n)" << endl;
            cout << "Time Complexity - Balance Factor: O(1)" << endl;
            cout << "Time Complexity - Rotations: O(1)" << endl;

            for (int i = 0; i < 6; i++) {
                avl.insertValue(values[i]);
            }

            cout << "AVL Tree (Inorder): ";
            avl.displayNodes();
            cout << "Height: " << avl.recursiveHeight(avl.getRoot()) << endl;
            cout << "Balance Factor of Root: " << avl.findBalancingFactor(avl.getRoot()) << endl;
            break;
        }
        case 2: {
            cout << "\n=== QUESTION 2: Specific AVL Tree Construction and Deletions ===" << endl;
            AVLTree<int> avl2;
            int nodes[] = { 40, 50, 60, 30, 35, 45, 20, 35, 46, 70, 41, 42 };

            cout << "Inserting nodes: ";
            for (int i = 0; i < 12; i++) {
                avl2.insertValue(nodes[i]);
                cout << nodes[i] << " ";
            }
            cout << endl;

            cout << "AVL Tree after insertions: ";
            avl2.displayNodes();

            int deleteNodes[] = { 35, 60, 45, 40 };
            for (int i = 0; i < 4; i++) {
                cout << "Deleting " << deleteNodes[i] << ": ";
                avl2.deleteValue(deleteNodes[i]);
                avl2.displayNodes();
            }
            break;
        }
        case 3: {
            cout << "\n=== QUESTION 3: Merge Two AVL Trees ===" << endl;
            cout << "Time Complexity - Merge: O(n + m)" << endl;

            AVLTree<int> avl3, avl4;

            int tree1[] = { 10, 20, 30 };
            int tree2[] = { 15, 25, 35 };

            for (int i = 0; i < 3; i++) {
                avl3.insertValue(tree1[i]);
                avl4.insertValue(tree2[i]);
            }

            cout << "Tree 1: ";
            avl3.displayNodes();
            cout << "Tree 2: ";
            avl4.displayNodes();

            AVLTree<int> merged = avl3.mergeAVLTrees(avl4);
            cout << "Merged Tree: ";
            merged.displayNodes();
            break;
        }
        case 4: {
            cout << "\n=== QUESTION 4: Spotify Song Manager ===" << endl;
            SongAVLTree songTree;

            char song1[] = "Song_A";
            char song2[] = "Song_B";
            char song3[] = "Song_C";
            char song4[] = "Song_D";
            char song5[] = "Song_E";
            char song6[] = "Song_F";
            char song7[] = "Song_G";
            char song8[] = "Song_H";
            char song9[] = "Song_I";
            char song10[] = "Song_J";
            char song11[] = "Song_K";

            songTree.insertSong(song1, 1);
            songTree.insertSong(song2, 5);
            songTree.insertSong(song3, 9);
            songTree.insertSong(song4, 2);
            songTree.insertSong(song5, 4);
            songTree.insertSong(song6, 6);
            songTree.insertSong(song7, 8);
            songTree.insertSong(song8, 3);
            songTree.insertSong(song9, 7);
            songTree.insertSong(song10, 9);
            songTree.insertSong(song11, 5);

            cout << "Initial Song Tree:" << endl;
            songTree.displaySongs();

            songTree.runMenu();
            break;
        }
        case 5: {
            cout << "\n=== QUESTION 5: Task Scheduler (MinHeap) ===" << endl;
            cout << "Time Complexity - Insert: O(log n)" << endl;
            cout << "Time Complexity - Extract Min: O(log n)" << endl;
            cout << "Time Complexity - Build Heap: O(n)" << endl;

            MinHeap minHeap(20);
            int tasks[] = { 15, 10, 20, 8, 12, 25, 18 };

            minHeap.buildHeap(tasks, 7);
            cout << "After building heap: ";
            minHeap.printHeap();

            minHeap.insert(5);
            cout << "After inserting task with priority 5: ";
            minHeap.printHeap();

            cout << "Extracting highest priority task: " << minHeap.extractMin() << endl;
            cout << "After extraction: ";
            minHeap.printHeap();

            cout << "Extracting top 3 priority tasks: ";
            minHeap.extractTopK(3);
            break;
        }
        case 6: {
            cout << "\n=== QUESTION 6: Hash Table Implementation ===" << endl;
            cout << "Time Complexity - Insert: O(1) average, O(n) worst case" << endl;
            cout << "Time Complexity - Search: O(1) average, O(n) worst case" << endl;

            HashTable hashTable(7);
            BucketHashTable bucketTable(3, 5);

            int products[] = { 17, 26, 15, 9, 11, 43, 75, 19, 35, 45, 55, 9, 10, 21, 61, 23 };

            cout << "Inserting products using Chaining:" << endl;

            for (int i = 0; i < 16; i++) {
                hashTable.insertChaining(products[i]);
            }
            hashTable.displayChaining();

            cout << "\nInserting products using Bucketing:" << endl;
            for (int i = 0; i < 16; i++) {
                bucketTable.insert(products[i]);
            }
            bucketTable.display();

            cout << "\nTime Complexities:" << endl;
            cout << "AVL Insert/Delete/Search: O(log n)" << endl;
            cout << "AVL Merge: O(n + m)" << endl;
            cout << "Heap Insert/Extract: O(log n)" << endl;
            cout << "Hash Table Insert/Search: O(1) average, O(n) worst case" << endl;
            break;
        }
        case 7: {
            cout << "\n=== QUESTION 7: Time Complexities Summary ===" << endl;
            cout << "\nAVL Tree Operations:" << endl;
            cout << "- Insert: O(log n)" << endl;
            cout << "- Delete: O(log n)" << endl;
            cout << "- Search: O(log n)" << endl;
            cout << "- Height: O(1) if stored, O(n) if calculated" << endl;
            cout << "- Balance Factor: O(1)" << endl;
            cout << "- Rotations: O(1)" << endl;
            cout << "- Merge: O(n + m)" << endl;

            cout << "\nMinHeap Operations:" << endl;
            cout << "- Insert: O(log n)" << endl;
            cout << "- Extract Min: O(log n)" << endl;
            cout << "- Build Heap: O(n)" << endl;
            cout << "- Heapify Up: O(log n)" << endl;
            cout << "- Heapify Down: O(log n)" << endl;

            cout << "\nHash Table Operations:" << endl;
            cout << "- Insert (Chaining): O(1) average, O(n) worst case" << endl;
            cout << "- Search (Chaining): O(1) average, O(n) worst case" << endl;
            cout << "- Insert (Bucketing): O(1) if bucket not full" << endl;
            cout << "- Search (Bucketing): O(bucket size)" << endl;
            cout << "- Rehashing: O(n)" << endl;
            break;
        }
        case 8: {
            cout << "\nExiting program. Goodbye!" << endl;
            return 0;
        }
        default: {
            cout << "\nInvalid choice! Please enter a number between 1 and 8." << endl;
            break;
        }
        }
    }
    return 0;
}