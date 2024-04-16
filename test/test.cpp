// clang -S -emit-llvm test/test.cpp -o test/test.ll

int x = 1;
int y = 2 * x + 3;

int f() {
    while (x == 1) {
        if (x > 1) {
            break;
        }
        x = x + 1;
        if (x <= 1) {
            continue;
        } else {
            x = x + 1;
        }
        x = x - 1;
    }
    return x;
}

int main() {
    return 0;
}
