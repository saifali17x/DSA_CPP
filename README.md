# DSA_CPP

This repository contains implementations of various data structures and algorithms in C++. The main focus is on AVL Trees, Min Heaps, Hash Tables, and a simple Spotify Song Manager. Each data structure is implemented with its respective operations and time complexities.

## Table of Contents

- [AVL Tree](#avl-tree)
- [Spotify Song Manager](#spotify-song-manager)
- [Min Heap](#min-heap)
- [Hash Table](#hash-table)
- [Bucket Hash Table](#bucket-hash-table)
- [Time Complexities](#time-complexities)
- [Usage](#usage)

## AVL Tree

The AVL Tree implementation includes:

- Insertion
- Deletion
- Balancing
- Inorder traversal
- Merging two AVL Trees

### Time Complexities

- Insert: O(log n)
- Delete: O(log n)
- Search: O(log n)
- Height: O(n)
- Balance Factor: O(1)
- Rotations: O(1)

## Spotify Song Manager

A simple application to manage songs using an AVL Tree. It allows users to:

- Display all songs
- Play a song (increases its frequency)
- Exit the application

## Min Heap

The Min Heap implementation includes:

- Insertion of tasks
- Extracting the highest priority task
- Building a heap from an array
- Extracting top K priority tasks

### Time Complexities

- Insert: O(log n)
- Extract Min: O(log n)
- Build Heap: O(n)

## Hash Table

The Hash Table implementation uses chaining for collision resolution. It includes:

- Insertion of keys
- Searching for keys
- Displaying the hash table

### Time Complexities

- Insert: O(1) average, O(n) worst case
- Search: O(1) average, O(n) worst case

## Bucket Hash Table

A bucket-based hash table implementation that allows for fixed-size buckets. It includes:

- Insertion of keys
- Searching for keys
- Displaying the hash table

## Time Complexities

- Insert (Chaining): O(1) average, O(n) worst case
- Search (Chaining): O(1) average, O(n) worst case
- Insert (Bucketing): O(1) if bucket not full
- Search (Bucketing): O(bucket size)

## Usage

To run the program, simply compile the `main.cpp` file and execute the resulting binary. Follow the on-screen menu to interact with the various data structures and algorithms.

```bash
g++ main.cpp -o data_structures
./data_structures
```
