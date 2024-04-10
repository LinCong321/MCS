// clang -S -emit-llvm test.cpp -o test.ll

int x = 1;
const int y = x - 1;

int main() {
    int a;
    return y;
}
