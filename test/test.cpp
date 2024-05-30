// clang -S -emit-llvm test/test.cpp -o test/test.ll
// find . -type f -exec wc -l {} +

void sort(int a[], int l, int r) {
    if (l >= r) {
        return;
    }

    int i = l, j = r, mid = a[(l + r) / 2];
    while (i < j) {
        i = i + 1;
        while (a[i] < mid) {
            i = i + 1;
        }
        while (a[j] > mid) {
            j = j - 1;
        }

        if (i <= j) {
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            i = i + 1;
            j = j - 1;
        }
    }

    sort(a, l, j);
    sort(a, i, r);
}

void f(int a[][30]) {
    sort(a[10], a[0][0], 10);
}

int main() {
    int a[20][30];
    f(a);
    return 0;
}