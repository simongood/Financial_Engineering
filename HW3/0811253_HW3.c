#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void countPrice(float date, float dateLack, int n, float c, float r){
    float w = dateLack/date;
    printf("w = %f", w);

    // 計算 Dirty price
    float dirtyP=0, Discount;
    int i, j;
    for(i=1; i<=n; i++){
        Discount = pow(1+r, -w);
        for(j=1; j<=i-1; j++){
            Discount /= 1+r;
        }
        dirtyP += Discount*c;
        if(i==n) dirtyP += Discount*100;
    }
    printf("\n\ndirty price = %f", dirtyP);

    // 計算 accrued interest
    float Accrued = c*(1 - w);
    printf("\nAccrued interest = %f", Accrued);

    // 計算 clean price
    printf("\nClean price = %f\n", dirtyP - Accrued);
    printf("                        #Answer\n");
}


int main(void) {
    int n;      // 總共期數
    float c, r; // 每期支付coupon, 單期利率
    printf("單期利率 r = ");
    scanf("%f", &r);
    printf("總共期數 n = ");
    scanf("%d", &n);
    printf("每期支付coupon, c = ");
    scanf("%f", &c);


    // dirty price, clean price, accrued interest

    /* actual/actual 計算開始 */
    printf("\n--------actual/actual---------\n\n");
    float date, dateLack; // 一期天數, 距離最近到期日天數

    printf("一期天數 (Number of days in the coupon period) = ");
    scanf("%d", &date);
    printf("距離最近到期日天數 (Number of days to the next payment date) = ");
    scanf("%d", &dateLack);

    countPrice(date, dateLack, n, c, r);


    /* Day Count Conventions:30/360 計算開始 */
    printf("\n--------Day Count Conventions:30/360---------\n\n");
    int ys, y2, y1,ms, m2, m1, ds, d2, d1;  // settlement date, 最近到期日日期, 當期期初日期
    printf("settlement date (year month day) = ");
    scanf("%d %d %d", &ys, &ms, &ds);
    printf("當期到期日日期 (year month day) = ");
    scanf("%d %d %d", &y2, &m2, &d2);
    printf("當期期初日期 (year month day) = ");
    scanf("%d %d %d", &y1, &m1, &d1);

    date = 360.*(y2-y1) + 30.*(m2-m1) + (d2-d1);
    dateLack = 360.*(y2-ys) + 30.*(m2-ms) + (d2-ds);
    printf("\nNumber of days in the coupon period = %f\n", date);
    printf("Number of days to the next payment date = %f\n", dateLack);

    countPrice(date, dateLack, n, c, r);

    return 0;
}
