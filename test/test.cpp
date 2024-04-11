// clang -S -emit-llvm test/test.cpp -o test/test.ll

int x = 1.0;

int f() {
    float y = 2;
    y = x - y;
    return y;
}

int main() {
    return 0;
}
