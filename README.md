# AVL Tree String Indexer & Search Engine

An optimized, memory-efficient string indexing and prefix search engine implemented in C++ using an AVL Tree. This project was developed as part of the **Data Structures** course.

---

## 👥 Team Members & Responsibilities

*   **Elena Paleocosta (Member A - Core AVL Infrastructure):** Responsible for the design of the AVL node, recursive balanced tree injection, height-independent balance factor propagation logic, tree visualization, automatic multi-directional rotations (LL, RR, LR, RL), and proper garbage collection to prevent memory leaks.
*   **Stratos Vasilellis (Member B - Search Engine & String Analytics):** Responsible for the custom string comparator, string skip-matching search optimization, advanced prefix querying with wildcards (`*`), performance evaluation (Big-O analysis), and technical report documentation.

---

## 🚀 Project Architecture

The search engine is built on top of a self-balancing binary search tree (AVL Tree) that maintains an optimal height of $O(\log n)$ at all times, ensuring predictable and blazing-fast search operations even with millions of words.

### 📐 Structural Innovation: Height-Independent Balancing
Strictly following the project constraints, this implementation **does not store node heights** in memory. Instead, tree balance is managed dynamically during the recursive backtracking phase using a single boolean flag (`heightIncreased` / `heightDecreased`). Balance Factors ($bf = \text{height}(L) - \text{height}(R)$) are updated mathematically using algebraic transitions:

*   **Left Rotation Balance Update:**
    $$parent.bf = parent.bf + 1 - \min(0, rightChild.bf)$$
    $$rightChild.bf = rightChild.bf + 1 + \max(0, parent.bf)$$
*   **Right Rotation Balance Update:**
    $$parent.bf = parent.bf - 1 - \max(0, leftChild.bf)$$
    $$leftChild.bf = leftChild.bf - 1 + \min(0, parent.bf)$$

---

## 🛠️ Features

*   **Dynamic AVL Ingestion:** Memory-leak-free insertion of string keys with automated structural rebalancing.
*   **Four-Way Rotations:** Fully implemented Single (Left/Right) and Double (Left-Right/Right-Left) rotations triggered when $|bf| > 1$.
*   **Optimized Prefix Search:** Wildcard support (e.g., searching for `datastruct*` returns all matching keys in $O(\log n + s)$ time, where $s$ is the number of matching results).
*   **Skip-Match Comparison:** Advanced search optimization that remembers parent character matches to skip redundant comparisons down the tree path.
*   **Deterministic Deletion:** Complete removal of nodes with dynamic sub-tree height collapsing and parent rebalancing.

---

## 📂 Repository Structure

```text
├── AVLNode.h            # Definition of the AVL Tree Node structure
├── AVLTree.h            # Public API and internal helper signatures
├── AVLTree.cpp          # Full implementation of Insertion, Deletion, and Rotations
├── StringEngine.h/.cpp  # String comparison, prefix matching, and skip-search logic
├── main.cpp             # Interactive console interface and testing suite
└── README.md            # Project documentation (this file)
