// clang -S -emit-llvm test/test.cpp -o test/test.ll

int a[10][20];

int main() {
    float b = a[1][2];
    return 0;
}