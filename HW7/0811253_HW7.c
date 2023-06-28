#include <stdio.h>
#include <math.h>

// �w�q�̤j����
#define MAX_TERM 7

// �w�q�Q�v�洫�]IRS�^������Ƶ��c
typedef struct {
    int term;
    double bid;
    double offer;
    double swapRate;
} IRSQuote;

// �w�q�Q�v���u���c
typedef struct {
    int term;
    double zeroRate;
} ZeroCouponCurve;

// �޹u�k�p��s���Q�v
void bootstrap(IRSQuote quotes[], ZeroCouponCurve curve[]) {
    // �N�̵u�������Q�v�����[�J�Q�v���u
    curve[0].term = quotes[0].term;
    curve[0].zeroRate = quotes[0].swapRate;

    // ���j�p���L�������s���Q�v
    for (int i = 1; i < MAX_TERM; i++) {
        curve[i].term = quotes[i].term;

        // �p��s���s���Q�v
        double prevZeroRate = curve[i - 1].zeroRate;
        double swapRate = quotes[i].swapRate;
        curve[i].zeroRate = pow((1 + swapRate) * (1 + prevZeroRate), 1.0 / quotes[i].term) - 1;
    }
}

// �L�X�Q�v���u
void printCurve(ZeroCouponCurve curve[]) {
    printf("Term\tZero Rate\n");
    for (int i = 0; i < MAX_TERM; i++) {
        printf("%d\t%.6f%%\n", curve[i].term, curve[i].zeroRate * 100);
    }
}

int main() {
    // �Q�v�洫�]IRS�^�������
    IRSQuote quotes[] = {
        {1, 2.25, 2.27, 2.26},
        {2, 2.26, 2.29, 2.275},
        {3, 2.27, 2.30, 2.285},
        {4, 2.3, 2.315, 2.32},
        {5, 2.33, 2.38, 2.355},
        {6, 2.37, 2.405, 2.398},
        {7, 2.41, 2.47, 2.44}
    };

    // �ЫاQ�v���u
    ZeroCouponCurve curve[MAX_TERM];

    // �ϥΩ޹u�k�p��s���Q�v
    bootstrap(quotes, curve);

    // �L�X�Q�v���u
    printCurve(curve);

    return 0;
}
