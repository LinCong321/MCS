// clang -S -emit-llvm test/test.cpp -o test/test.ll

int a[10] = {1, 2, 3};
//const int b[5] = {4, 5};

void f() {
    //int c[10] = {1, 2, 3};
}

int main() {
    return 0;
}
