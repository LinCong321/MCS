// clang -S -emit-llvm test.cpp -o test.ll

int x = 1 * 2 + 3 / 4;
int y = x * 2 / (3.0 + 4);

int f() {
    int a;
    int b = 1.0;
    int c = 1 + a * 2 - 3 / b;
    return c;
}

int main() {
    return 0;
}
