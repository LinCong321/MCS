// clang -S -emit-llvm test/test.cpp -o test/test.ll

int x = 1;
int y = 2;

int f() {
    int a = 1;
    if (x) {
        return x;
    } else {
       a = a + 1;
    }
}

int main() {
    return 0;
}
