// clang -S -emit-llvm test/test.cpp -o test/test.ll

int x = 1;
int y = 2 * x + 3;

int f() {
    int a = 3;
    if (!x != !y) {
        y = y + 1;
    } else {
        y = y - 1;
    }
    return y;
}

int main() {
    return 0;
}
