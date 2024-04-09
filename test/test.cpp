// clang -S -emit-llvm test.cpp -o test.ll

int a;
int b = 1;
int c = 1 + a * 2 - 3 / b;

int f() {
    int a;
    int b = 1;
    int c = 1 + a * 2 - 3 / b;
}

int main() {
    return 0;
}
