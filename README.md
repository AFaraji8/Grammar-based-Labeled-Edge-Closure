# Grammar-based-Labeled-Edge-Closure-C-
## Project summary
A small C++ program (`r.cpp`) that reads a labelled directed graph and a set of grammar rules of the form `X -> A B`, then computes new labelled edges that can be inferred by applying these grammar rules over existing edges. The program repeatedly applies the rules until no additional edges can be derived, and prints the total number of new edges discovered.

## Files
- `r.cpp` — main C++ source. Implements loading of the grammar and graph, rule-based inference of new edges, and counting of discovered edges.
- `grammar.txt` — grammar rules input (see format below).
- `graph.txt` — graph input (see format below).
- `grammar1.txt`, `grammar2.txt`, `graph1.txt`, `graph2.txt` — other sample inputs included in the repository.

## Input formats

1) `grammar.txt`
- Each non-empty line describes a rule with three tokens: `TABDIL S1 S2` (separated by whitespace).
- Interpretation: `TABDIL -> S1 S2` (e.g. `C A B` means `C -> A B`).
- Example:
```
C A B
D B C
B A D
A C D
```

2) `graph.txt`
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

## What the program does (brief)
- Loads grammar rules and builds a list of rules `X -> A B`.
- Loads the graph into an adjacency matrix of labels (single label per ordered pair is stored if present).
- Finds edge pairs that match the right-hand side `A` then `B` (i.e. `u -[A]-> m -[B]-> v`), and infers a new edge `u -[X]-> v` according to `X -> A B`.
- Repeats combining newly inferred edges with existing edges and with other rules until no further edges are produced (a closure/fixpoint is reached).
- Outputs a single integer: the number of new edges discovered during the inference process.

## Build & run (Windows / PowerShell)
- You can compile using your MinGW/G++ toolchain. Example (adjust compiler path if needed):

```powershell
# Compile
C:\msys64\mingw64\bin\g++.EXE -Wall -Wextra -g3 r.cpp -o r.exe

# Run (reads grammar.txt and graph.txt from current directory)
.\\r.exe
```

Or use the provided VS Code task `C/C++: g++.exe build active file` to build.

## Output
- The program prints a single integer (to stdout) which is the count of inferred edges produced by the algorithm.
