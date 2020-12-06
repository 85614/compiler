
// struct Test
// {
//     int a;
//     int b;
// };

// struct zzq;

// struct Test zzq;


// int a[1][2][3];


// int main() {
//     int** b, d;
//     int c[1][2];
//     b = &c;
//     a[0][0][1] = 1;
//     //print_int(a[0][0][1]);
//     return 0;
// }


// // int main() 
// // {
// //     (a + 8)[1];
// //     int a = 1, b = 2;
// //     a = b ^ 2 ^ 3;

// //     for (i = 0; i < 10; i = i + 1) 
// // {
// //             if  (a < 5) a = a + 1;
// //             else  if  (a >= 5) 
// //     {
// //                     a = a + 2;
// //                 
// //     }
// //         
// // }
// //      // 或者是其他自定义的输出函数
// //     print_int(i);
// //     while (a < 40) 
// // {
// //             a = a + 1;
// //         
// // }
// // for (;;)
// // {
// // }
// // for (int a = 1; a < 20; a = a  + 1)
// // {
// //     a = a + 1;
// // }
// //     print_int(a);
// //     return 0;
// // }


void swap(int* a1, int* b) {
    int t = *a1;
    *a1 = *b;
    *b = t;
}

int main()
{
    int a = 2;
    int b = 3;
    print_int(a);
    print_int(b);
    int* pa = &a;
    int* pb = &b;
    swap(pa, pb);
    print_int(a);
    print_int(b);
}




