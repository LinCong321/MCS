// clang -S -emit-llvm test.cpp -o test.ll

const int x = 1;

void f() {
    int b = 2;
    return;
}

int main() {
    return 0;
}
