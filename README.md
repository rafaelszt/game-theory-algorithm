# Game Theory

AI that plays tic-tac-toe, doesn't always wins, but it should, so a few bugs are there.


## Minimax Algorithm

#### Pseudocode

```
01 function minimax(node, depth, maximizingPlayer)
02     if depth = 0 or node is a terminal node
03         return the heuristic value of node

04     if maximizingPlayer
05         bestValue := −∞
06         for each child of node
07             v := minimax(child, depth − 1, FALSE)
08             bestValue := max(bestValue, v)
09         return bestValue

10     else    (* minimizing player *)
11         bestValue := +∞
12         for each child of node
13             v := minimax(child, depth − 1, TRUE)
14             bestValue := min(bestValue, v)
15         return bestValue
```

```
(* Initial call for maximizing player *)
minimax(origin, depth, TRUE)
```

[Source](https://en.wikipedia.org/wiki/Minimax#Pseudocode)

## Alpha-beta Algorithm

#### Pseudocode

```
01 function alphabeta(node, depth, α, β, maximizingPlayer)
02      if depth = 0 or node is a terminal node
03          return the heuristic value of node
04      if maximizingPlayer
05          v := -∞
06          for each child of node
07              v := max(v, alphabeta(child, depth – 1, α, β, FALSE))
08              α := max(α, v)
09              if β ≤ α
10                  break (* β cut-off *)
11          return v
12      else
13          v := +∞
14          for each child of node
15              v := min(v, alphabeta(child, depth – 1, α, β, TRUE))
16              β := min(β, v)
17              if β ≤ α
18                  break (* α cut-off *)
19          return v
```

```
(* Initial call for maximizing player *)
alphabeta(origin, depth, -∞, +∞, TRUE)
```

[Source](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning#Pseudocode)
