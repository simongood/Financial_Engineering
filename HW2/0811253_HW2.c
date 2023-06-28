#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    float x;  // ������
    int n;  //����


    printf("���� = ");
    scanf("%d", &n);
    printf("�����J = ");
    scanf("%f", &x);

    float c[n-1];  // �C�����S
    int i, j;
    for(i=0; i<n; i++){
        printf("�� %d �����S = ", i+1);
        scanf("%f", &c[i]);
    }

/*
    // �ˬd��J���
    printf("----------------\n");
    printf("�����J = %f\n", x);
    printf("���� = %d\n", n);
    for(i=0; i<n; i++){
        printf("�� %d �����S = %f\n", i+1, c[i]);
    }
*/

    // �p��}�l
    float Low, High, Middle = 0;
    float Value = 0, Discount = 0;  //f(x)��, (1+r)^-i ��
    int direc;

    printf("\n-------Bisection Method-------\n");
    printf("Low = ");
    scanf("%f", &Low);
    printf("High = ");
    scanf("%f", &High);
    printf("�u�ʤ�V 1=�k�W, -1=�k�U = ");
    scanf("%d", &direc);

    while(High - Low >= 0.0001){
        Middle = (Low+High)/2;
        Value = 0; // f(x)��
        for (i=0; i<n; i++){
            Discount = 1;
            for(j=0; j<=i; j++){
                Discount /= 1+Middle;
            }
            Value += Discount*c[i];
        }
        Value -= x;
        if(direc == -1) {
            if(Value>0){
                Low = Middle;
            } else {
                High = Middle;
            }
            printf("\n�p��L�{High %f, Low %f, Mid %f, Value %f", High, Low, Middle, Value);
        } else if(direc == 1) {
            if(Value<0){
                Low = Middle;
            } else {
                High = Middle;
            }
            printf("\n�p��L�{High %f, Low %f, Mid %f, Value %f", High, Low, Middle, Value);
        }
    }
    printf("\n\n# Yield rate IRR = %f", High);

    // Newton-Raphson method
    printf("\n\n----Newton-Raphson method----");
    printf("\n��J��l�q�wIRR�� : ");

    float Xo = 0; // ��J�̲q�wIRR��l��
    scanf("%f", &Xo);

    // �}�l�p��
    Value = 1; // ��l f(Xo) �ȡA�n��� Value <= 0.0001
    float dif_fx = 0;   // f'(x) �ȭp��
    while(abs(Value) >= 0.0001) {
        Value = 0; // f(Xo)��
        for (i=0; i<n; i++){
            Discount = 1;
            for(j=0; j<=i; j++){
                Discount /= 1+Xo;
            }
            Value += Discount*c[i];
        }
        Value -= x;

        // fit Xo ��m -> X(k+1)
        dif_fx = 0;   // f'(x) �ȭp��
        for(int t=1; t<=n ;t++){
            dif_fx += t*c[t-1]/pow(1+Xo, t+1);
        }
        dif_fx = -dif_fx;

        Xo -= Value/(dif_fx);
        printf("\n�p��L�{ Value = %f  X = %f" , Value, Xo);
    }
    printf("\n\n# Yield rate IRR = %f\n", Xo);


}
