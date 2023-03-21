## Examples

### Basics

```
io main() {
    bool is_prime; // false by default
 
    int n; n = 61;
    
    int i; i = 2;
    while (i * i < n && !is_prime) {
        if (n % i == 0) {
            is_prime = true;
        }
        i = i + 1;
    }
    
    println(is_prime); // output: true
}
```

### Functions (TODO)

```
// pure means that function don't have side-effects
pure pow(int base, int exponent) int {
    int p; p = 1;
    int e; e = exponent;
    while (e > 0) {
        p = base * p;
        e = e - 1;
    }
    return p;
}

// io means that function can modify the world and may have side-effects
io main() {
    int x; x = 3;
    int y; y = pow(x, x);
    println(y); // output: 27
}
```

### User types (TODO)

- All members are private
- Only methods can modify members
- Methods can't modify arguments

```
pure abs(int x) int {
    if x > 0 {
        return x;
    }
    return -x;
}

type Point {
members:
    int x;
    int y;
    
methods:
    io PrintAndZero() {
        println(x, y);
        x = 0;
        y = 0;
    }
    
    pure Distance(Point other) int {
        return abs(x - other.x) + abs(y - other.x);
    }
}

```