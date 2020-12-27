

int main()
{
    int a = 1;
    {
        print_int(a);
    }
    {
        int a = 2;
        print_int(a);
    }
    {
        int a = 3;
        print_int(a);
    }
}
