struct test {
    int **a;
    int b[4], **f;
    int c;
    int d, e;
};

int main() {
    struct test t;
    // t.a = 1;
    // t.b = 2;
    t.c = 3;
    // t.d = t.b * t.c;
    print_int(t.d);
}
