// struct B;
struct AA{
    int a;
};

// struct AA *a;

struct test {
    // int **a;
    // int b[4], **f;
    int c;
    int d, e;
    struct AA *ptr;
    struct test *ptr;
};

int main() {
    struct test t;
    // struct test* ptr;
    // ptr = &t;
    // t.a = 1;
    // t.b = 2;
    t.c = 3;
    // t.d = t.b * t.c;
    print_int(t.d);
}
