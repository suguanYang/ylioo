## 2.3-7
Describe a $\theta(n lgn)$-time algorithm that, given a set S of n integers and another integer x, determines whether or not there exist two elements in S whose sum is exactly x.
```
def set_sum(S, x):
    sort(S)
    for i to S:
        subtract = x - i
        if binary_search(S, subtract):
            return True
```
