#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    float x;  // 期初資金
    int n;  //期數


    printf("期數 = ");
    scanf("%d", &n);
    printf("期初投入 = ");
    scanf("%f", &x);

    float c[n-1];  // 每期報酬
    int i, j;
    for(i=0; i<n; i++){
        printf("第 %d 期報酬 = ", i+1);
        scanf("%f", &c[i]);
    }

/*
    // 檢查輸入資料
    printf("----------------\n");
    printf("期初投入 = %f\n", x);
    printf("期數 = %d\n", n);
    for(i=0; i<n; i++){
        printf("第 %d 期報酬 = %f\n", i+1, c[i]);
    }
*/

    // 計算開始
    float Low, High, Middle = 0;
    float Value = 0, Discount = 0;  //f(x)值, (1+r)^-i 值
    int direc;

    printf("\n-------Bisection Method-------\n");
    printf("Low = ");
    scanf("%f", &Low);
    printf("High = ");
    scanf("%f", &High);
    printf("線性方向 1=右上, -1=右下 = ");
    scanf("%d", &direc);

    while(High - Low >= 0.0001){
        Middle = (Low+High)/2;
        Value = 0; // f(x)值
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
            printf("\n計算過程High %f, Low %f, Mid %f, Value %f", High, Low, Middle, Value);
        } else if(direc == 1) {
            if(Value<0){
                Low = Middle;
            } else {
                High = Middle;
            }
            printf("\n計算過程High %f, Low %f, Mid %f, Value %f", High, Low, Middle, Value);
        }
    }
    printf("\n\n# Yield rate IRR = %f", High);

    // Newton-Raphson method
    printf("\n\n----Newton-Raphson method----");
    printf("\n輸入初始猜定IRR值 : ");

    float Xo = 0; // 輸入者猜定IRR初始值
    scanf("%f", &Xo);

    // 開始計算
    Value = 1; // 初始 f(Xo) 值，要算到 Value <= 0.0001
    float dif_fx = 0;   // f'(x) 值計算
    while(abs(Value) >= 0.0001) {
        Value = 0; // f(Xo)值
        for (i=0; i<n; i++){
            Discount = 1;
            for(j=0; j<=i; j++){
                Discount /= 1+Xo;
            }
            Value += Discount*c[i];
        }
        Value -= x;

        // fit Xo 位置 -> X(k+1)
        dif_fx = 0;   // f'(x) 值計算
        for(int t=1; t<=n ;t++){
            dif_fx += t*c[t-1]/pow(1+Xo, t+1);
        }
        dif_fx = -dif_fx;

        Xo -= Value/(dif_fx);
        printf("\n計算過程 Value = %f  X = %f" , Value, Xo);
    }
    printf("\n\n# Yield rate IRR = %f\n", Xo);


}
