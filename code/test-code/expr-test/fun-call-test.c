

struct A{
    int a;
};

void fun(int a, int *b);

int fun2(struct A *a);



int main() {
  struct A a;
  int b;
  fun(1, &b);
  b = fun2(&a);
  // b = fun(b, &b);

}
