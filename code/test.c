// 多维指针
// 指针加减
int main()
{
    int a[3];
    for (int i = 0; i < 3; i = i + 1)
        a[i] = i + 1;
    for (int i = 0; i < 3; i = i + 1)
        print_int(a[i]);
    int *ptr = a;
    int **pptr = &ptr;
    *(*pptr + 2) = 4;
    for (int i = 0; i < 3; i = i + 1)
        print_int(a[i]);
    print_int(**pptr);
    ptr = a + 2;
    print_int(**pptr);
    print_int(ptr - a);
}