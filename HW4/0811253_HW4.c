#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main() {

    // ======Macaulay Duration============
    printf("====== Macaulay Duration ============ \n\n");
    int n;
    float c, r,value=0, Discount, Duration=0;
    printf("�п�J���� n: ");
    scanf("%d", &n);
    printf("�п�J�Ů� C(percent): ");
    scanf("%f", &c);
    printf("�п�J�Q�v r: ");
    scanf("%f", &r);
    for(int i=1; i<=n; i++){
        Discount = 1;
        for(int j=1; j<=i; j++){
            Discount /= 1+r;
        }
        Duration += i*Discount*c;
        value += Discount*c;
        if(i == n){
            value += Discount*100;
            Duration += n*Discount*100;
        }
        // printf("i = %d, Duration = %f, value = %f\n", i, Duration, value);
    }

    Duration /= value;
    printf("\nMacaulay Duration = %f\n\n", Duration);



    // ======= Modified Duration =======

    printf("======= Modified Duration =======\n\n");
    float ModD=0, Rchange;
    ModD = Duration/(1+r);
    printf("Modified Duration = %f\n", ModD);

    printf("�п�J�ܰʧQ�v : ");
    scanf("%f", &Rchange);

    printf("\nthe approximate percentage price change = %f (percent)\n\n", (-ModD)*Rchange*100);


    return 0;
}
