int main()
{
    int a[3];
    int *p1 = a, *p2 = a + 1, *p3 = a + 2;
    *p1 = 1;
    *p2 = 2;
    *p3 = 3;
    for (int i = 0; i < 3; i = i + 1)
        print_int(a[i]);
    print_int(p3 - p1);
}