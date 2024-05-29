// clang -S -emit-llvm test/test.cpp -o test/test.ll
// find . -type f -exec wc -l {} +

//int a[20];

void f(int a[][10]) {

}

//void sort(int l, int r) {
//    if (l >= r) {
//        return;
//    }
//
//    int i = l, j = r, mid = a[(l + r) / 2];
//    while (i < j) {
//        while (a[i] < mid) {
//            i = i + 1;
//        }
//        while (a[j] > mid) {
//            j = j - 1;
//        }
//
//        if (i <= j) {
//            int t = a[i];
//            a[i] = a[j];
//            a[j] = t;
//            i = i + 1;
//            j = j - 1;
//        }
//    }
//
//    sort(l, j);
//    sort(i, r);
//}

int main() {
    //sort(1, 10);
    return 0;
}