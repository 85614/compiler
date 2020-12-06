int f(int n) {
    if (n == 1) {
        return 1;
    } else if (n == 2) {
        return 2;
    }
    // int a = f(n - 1);
    // int b = f(n - 2);
    int a = 0, b = -2 * 3;
    return a + b;
}

int main() {
    int d = f(5);
    print_int(d);
}