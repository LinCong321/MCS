// clang -S -emit-llvm test/test.cpp -o test/test.ll

const int x = 10;
int y[x / 2 + 3];

int main() {
    return 0;
}
