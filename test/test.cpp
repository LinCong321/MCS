// clang -S -emit-llvm test/test.cpp -o test/test.ll

const float x = 1 * 2 + 3;
const int y = 3.1;
const int a = x * -y / 2;

int f() {
    return a * 10 - y;
}

int main() {

    return 0;
}
