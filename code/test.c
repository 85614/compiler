

// int fibo(int n) {
//     if (n == 1) {
//         return 1;
//     } else if (n == 2) {
//         return 2;
//     }
//     int a = fibo(n - 1);
//     int b = fibo(n - 2);
//     return a + b;
// }

// int main() {
//     int d = fibo(5);
//     print_int(d);
// }

int main()
{
    int a[3];
    int *p1, *p2, *p3;
    p1 = a;
    p2 = a + 1;
    p3 = p1 + 2;
    *p1 = 1;
    *p2 = 2;
    *p3 = 3;
    for (int i = 0; i < 3; i = i + 1)
        print_int(a[i]);
    print_int(p3 - p1);
}