// clang -S -emit-llvm test/test.cpp -o test/test.ll

int x = 1;
int y = 2 * x + 3;


int main() {
    return 0;
}
