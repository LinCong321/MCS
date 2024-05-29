// clang -S -emit-llvm test/test.cpp -o test/test.ll

int a[10];
const int b[10][20] = {{1, 2, 3}, {}, {2, 3}};
int c;
const int d[10] = {1, 2, 3};
const int e = 1 + 2;

int main() {
    int a1[10];
    int b1[10][20] = {{1, 2, 3}};
    int c1;
    const int d1[10] = {1, 2, 3};
    const int e1 = 1 + 2;
    return 0;
}