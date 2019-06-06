# Thoughts on Solving

Brute force: try all possible assignments of 1-9 in every box. 9^(9^2) = 1.9 * 10** 77 permutations.

Adding constraints: for each empty cell, inspect its row, column and "box". The cell can't take on anything occuring in each row, column and box.