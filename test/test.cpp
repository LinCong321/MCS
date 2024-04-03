int a = 0;

int f() {
    int x = 1;
    {
        int x = 2;
        int x = 3;
    }
    return a;
}

int main() {
    return 0;
}
