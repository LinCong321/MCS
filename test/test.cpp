// clang -S -emit-llvm test/test.cpp -o test/test.ll

int x = 1.0;
int y = 2;

int f() {
    if (x || y) {
        x = x + 1;
    }
    return x;
}

int main() {
    return 0;
}
