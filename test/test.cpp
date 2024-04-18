// clang -S -emit-llvm test/test.cpp -o test/test.ll

int x = 1;
int y = 2 * x + 3;

int f(int a, int b) {
    while (x == 1) {
        if (x > 1) {
            break;
        } else {
            x = x - 1;
        }
        x = x + 1;
        if (x <= 1 || y >= 1) {
            continue;
        }
        x = x - 1;
    }
    return y;
}

int main() {
    return 0;
}
