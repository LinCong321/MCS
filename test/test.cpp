// clang -S -emit-llvm test/test.cpp -o test/test.ll

void f() {
    int x = 1;
    float y = 3.14;
}

int main() {
    return 0;
}
