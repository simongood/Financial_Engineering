#include <stdio.h>
#include <math.h>

// 定義最大期限
#define MAX_TERM 7

// 定義利率交換（IRS）報價資料結構
typedef struct {
    int term;
    double bid;
    double offer;
    double swapRate;
} IRSQuote;

// 定義利率曲線結構
typedef struct {
    int term;
    double zeroRate;
} ZeroCouponCurve;

// 拔靴法計算零息利率
void bootstrap(IRSQuote quotes[], ZeroCouponCurve curve[]) {
    // 將最短期限的利率報價加入利率曲線
    curve[0].term = quotes[0].term;
    curve[0].zeroRate = quotes[0].swapRate;

    // 遞迴計算其他期限的零息利率
    for (int i = 1; i < MAX_TERM; i++) {
        curve[i].term = quotes[i].term;

        // 計算新的零息利率
        double prevZeroRate = curve[i - 1].zeroRate;
        double swapRate = quotes[i].swapRate;
        curve[i].zeroRate = pow((1 + swapRate) * (1 + prevZeroRate), 1.0 / quotes[i].term) - 1;
    }
}

// 印出利率曲線
void printCurve(ZeroCouponCurve curve[]) {
    printf("Term\tZero Rate\n");
    for (int i = 0; i < MAX_TERM; i++) {
        printf("%d\t%.6f%%\n", curve[i].term, curve[i].zeroRate * 100);
    }
}

int main() {
    // 利率交換（IRS）報價資料
    IRSQuote quotes[] = {
        {1, 2.25, 2.27, 2.26},
        {2, 2.26, 2.29, 2.275},
        {3, 2.27, 2.30, 2.285},
        {4, 2.3, 2.315, 2.32},
        {5, 2.33, 2.38, 2.355},
        {6, 2.37, 2.405, 2.398},
        {7, 2.41, 2.47, 2.44}
    };

    // 創建利率曲線
    ZeroCouponCurve curve[MAX_TERM];

    // 使用拔靴法計算零息利率
    bootstrap(quotes, curve);

    // 印出利率曲線
    printCurve(curve);

    return 0;
}
