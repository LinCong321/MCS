// clang -S -emit-llvm test/test.cpp -o test/test.ll

const int x = 1;
const float y = 2;

void f() {
    int a = -x + y;
    int b = +(x * !y);
    float c = -x / (-y);
    float d = !x - +y;
}

int main() {
    return 0;
}
