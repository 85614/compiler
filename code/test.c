



struct AA{
  int a;
};

struct AA a;

struct AA b;

void fun(int a) {
    a = 1;
}

int main(){
  a = b;
  return 0;
}

