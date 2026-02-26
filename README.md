# Grammar-based Labeled-Edge Closure (C++)

A specialized C++ tool designed to compute the transitive closure of labeled directed graphs based on **Context-Free Grammar (CFG)** production rules. This problem, often referred to as **CFL-Reachability**, is a cornerstone of static program analysis and formal language theory.

## 📌 Project Summary
The program (`r.cpp`) reads a directed graph with labeled edges and a set of grammar rules (e.g., $X \to AB$). It then infers new labeled edges by identifying paths that match the grammar. For example, if the graph contains $u \xrightarrow{A} m$ and $m \xrightarrow{B} v$, the program derives a new edge $u \xrightarrow{X} v$. This process repeats until a **fixed point** is reached, meaning no more edges can be inferred.

## 📂 Project Structure
- **`r.cpp`**: Core source code implementing the inference engine and worklist logic.
- **`grammar.txt`**: The active production rules for the current execution.
- **`graph.txt`**: The primary input graph.
- **`Samples/`**: Includes additional test cases (`grammar1.txt`, `graph1.txt`, etc.) for validation.

## 🔑 Internal Logic & Mapping
To understand the source code, here are the primary components:

* **`class rule`**: Encapsulates a CFG production rule ($S1 + S2 \implies Tabdil$).
* **`class newedges`**: Represents an inferred edge defined by its source (`v1`), destination (`v2`), and label (`size`).
* **`nedge` / `nnedge`**: These vectors act as a **Worklist**. `nedge` stores discovered edges, while `nnedge` buffers newly found edges during the current iteration to prevent iterator invalidation.
* **`matrix[ras][ras]`**: An adjacency matrix used for $O(1)$ lookup of initial edge labels between vertices.
* **`total`**: A long-integer counter that tracks the cumulative number of newly discovered edges.

## 📥 Input Formats

### 1. Grammar Rules (`grammar.txt`)
Each line defines a rule where three tokens represent a binary production:
- **Format:** `TABDIL S1 S2` (interpreted as $TABDIL \to S1 S2$).
- **Example:** `C A B` means "An A-labeled edge followed by a B-labeled edge creates a C-labeled edge."
- Each non-empty line describes a rule with three tokens: `TABDIL S1 S2` (separated by whitespace).
- Interpretation: `TABDIL -> S1 S2` (e.g. `C A B` means `C -> A B`).
- Example:
```
C A B
D B C
B A D
A C D
```

### 2. Graph Definition (`graph.txt`)
- **Line 1:** An integer $N$ (Total vertices, indexed $0 \dots N-1$).
- **Successive Lines:** `u v LABEL` (A directed edge from $u$ to $v$ with a single-character label).

- The first line contains a single integer: number of vertices `N` (vertices are assumed to be 0..N-1).
- Each following line describes a directed labelled edge as three tokens: `u v LABEL` (separated by whitespace), meaning an edge from `u` to `v` with label `LABEL` (single character label expected).
- Example:
```
7
0 4 A
0 1 A
0 6 B
1 2 B
1 3 D
... (more edges)
```



## 🛠️ What the program does (brief)
- Loads grammar rules and builds a list of rules `X -> A B`.
- Loads the graph into an adjacency matrix of labels (single label per ordered pair is stored if present).
- Finds edge pairs that match the right-hand side `A` then `B` (i.e. `u -[A]-> m -[B]-> v`), and infers a new edge `u -[X]-> v` according to `X -> A B`.
- Repeats combining newly inferred edges with existing edges and with other rules until no further edges are produced (a closure/fixpoint is reached).
- Outputs a single integer: the number of new edges discovered during the inference process.

## 📊 Output
- The program prints a single integer (to stdout), which is the count of inferred edges produced by the algorithm.


---
Developed as the Data Structures Project.

