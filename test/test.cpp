// clang -S -emit-llvm test/test.cpp -o test/test.ll

int fib(int n) {
    if (n <= 0) {
        return -1;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

int main() {
    int n = 10;
    int m = fib(n) + 1;
    return 0;
}