# Graphs

## Basic Info : 

### Key Points to Remember : 
1. If there are n nodes then the maximum number of edges in an undirected graph is nC2 = n(n-1)/2.
2. If there are n nodes then the maximum number of edges in a directed graph is n(n-1) (Because for each node we can have an edge to all other nodes).



## Representation of Graphs : 
Example Graph :

```mermaid
graph TD
    A -- B;
    A -- C;
    A -- D;
    A -- E;
```
### 1. Adjacency Matrix : 

|   | A | B | C | D | E |
|---|---|---|---|---|---|
| A | 0 | 1 | 1 | 1 | 1 |
| B | 1 | 0 | 0 | 0 | 0 |
| C | 1 | 0 | 0 | 0 | 0 |
| D | 1 | 0 | 0 | 0 | 0 |
| E | 1 | 0 | 0 | 0 | 0 |


### 2. Adjacency List : 

- `A`: `[B, C, D, E]`
- `B`: `[A]`
- `C`: `[A]`
- `D`: `[A]`
- `E`: `[A]`


