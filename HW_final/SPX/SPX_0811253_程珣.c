#include <stdio.h>
#include <math.h>

# define lenMax 500

int length;// 數據長度

void Theorem2(float call[lenMax], float put[lenMax], float X[lenMax], float Vcall[lenMax], float Vput[lenMax]){
    // 履約價單調性原理
    // 1. 一標的call option履約價高的的價錢需 < 履約價低的的價錢
    // 2.        put option履約價高的的價錢需 > 履約價低的的價錢
    printf("==== Theorem2 : ==========\n");
    float space, per;

    printf("# call option price does not match strike price\n");
    printf("strike_price       call  strike_price       call  / Arbitrage space       / volume\n");
    for(int i=0; i<length; i++){
        for(int j=i+1; j<length-i-1; j++){
            if(call[i] < call[j]){
                space = call[j] - call[i];
                per = space / (call[j] + call[i]);
                printf("%12.0f %10.2f  %12.0f %10.2f  / %15.2f %5.2f / %6.0f\n", X[i], call[i], X[j], call[j], space, per, Vcall[i]);
            }
        }
    }

    printf("\n# put option price does not match strike price \n");
    printf("strike_price       put  strike_price       put  / Arbitrage space       / volume\n");
    for(int i=0; i<length; i++){
        for(int j=i+1; j<length-i-1; j++){
            if(put[i] > put[j]){
                space = put[i] - put[j];
                per = space / (call[j] + call[i]);
                printf("%12.0f %9.2f  %12.0f %9.2f  / %15.2f %5.2f / %6.0f\n", X[i], put[i], X[j], put[j], space, per, Vput[i]);
            }
        }
    }

}

void Theorem3_AmericaOption(float call[lenMax], float put[lenMax], float X[lenMax], float s, float Vcall[lenMax], float Vput[lenMax]){
    // 1. call price永遠 < s 股票價格
    // 2. put price永遠 < 其 X 履約價
    printf("\n==== Theorem3_AmericaOption : ==========\n");
    float space, per;

    //1.
    printf("# call option price > market price : %8.2f\n", s);
    printf("strike_price       call  / Arbitrage space       / volume\n");
    for(int i=0; i<length; i++){
        if (call[i] > s){
            space = call[i] - s;
            per = space / (call[i] + s);
            printf("%12.0f %10.2f  / %15.2f %5.2 / %6.0f\n", X[i], call[i], space, per, Vcall[i]);
        }
    }

    //2.
    printf("\n# put option price > strike price\n");
    printf("strike_price       put  / Arbitrage space       / volume\n");
    for(int i=0; i<length; i++){
        if (put[i] > X[i]){
            space = X[i] - put[i];
            per = space / (X[i] + put[i]);
            printf("%12.0f %9.2f  / %15.2f %5.2f / %6.0f\n", X[i], put[i], space, per, Vput[i]);
        }
    }
}


void Theorem3_EuropeOption(float call[lenMax], float put[lenMax], float X[lenMax], float pv[lenMax], float s, float Vcall[lenMax], float Vput[lenMax]){
    // 1. call price永遠 < s 股票價格
    // 2. put price永遠 < 其 PVx 履約價現值

    printf("\n==== Theorem3_EuropeOptionOption : ==========\n");
    float space, per;

    //1.
    printf("# call option price > market price : %8.2f\n", s);
    printf("strike_price       call  / Arbitrage space       / volume\n");
    for(int i=0; i<length; i++){
        if (call[i] > s){
            space = call[i] - s;
            per = space / (call[i] + s);
            printf("%12.0f %10.2f  / %15.2f %5.2f / %6.0f\n", X[i], call[i], space, per, Vcall[i]);
        }
    }
    //2.
    printf("\n# put option price > PV_strike price\n");
    printf("strike_price       put  PV_strike price  / Arbitrage space       / volume\n");
    for(int i=0; i<length; i++){
        if (put[i] > pv[i]){
            space = pv[i] - put[i];
            per = space / (pv[i] + put[i]);
            printf("%12.0f %9.2f  %15.2f  / %15.2f %5.2f / %6.0f\n", X[i], put[i], pv[i], space, per, Vput[i]);
        }
    }
}

void Theorem4(float call[lenMax], float X[lenMax], float pv[lenMax], float s, float Vcall[lenMax]){
    //C,call price >= Max( s-PVx, 0)
    printf("\n==== Theorem4 : ==========\n# call price < Max( s-PVx, 0 ), s = %8.2f\n", s);
    printf("strike_price       call  Max( s-PVx, 0 )        pv  / Arbitrage space       / volume\n");
    float term;
    float space, per;
    for( int i=0; i<length; i++){
        term = s - pv[i];
        if (term < 0.) term = 0.;
        if (call[i] < term){
            space = term - call[i];
            per = space / (term + call[i]);
            printf("%12.0f %10.2f  %15.2f   %7.2f  / %15.2f %5.2f / %6.0f\n", X[i], call[i], term, pv[i], space, per, Vcall[i]);
        }
    }

}

void Theorem6_EuroPutLower(float put[lenMax], float X[lenMax], float pv[lenMax], float s, float Vput[lenMax]){
    // put >= Max( PVx-S, 0)
    printf("\n==== Theorem6 : ==========\n# put price < Max( PVx-s, 0 ), s = %8.2f\n", s);
    printf("strike_price        put  Max( PVx-s, 0 )        pv  / Arbitrage space       / volume\n");
    float term;
    float space, per;
    for( int i=0; i<length; i++){
        term = pv[i] - s;
        if (term < 0.) term = 0.;
        if (put[i] < term){
            space = term - put[i];
            per = space / (term + put[i]);
            printf("%12.0f %10.2f  %15.2f   %7.2f  / %15.2f %5.2f / %6.0f\n", X[i], put[i], term, pv[i], space, per, Vput[i]);
        }
    }
}

void Theorem7_UsPutLower(float put[lenMax], float X[lenMax], float s, float Vput[lenMax]){
    // put >= Max( X-S, 0)
    printf("\n==== Theorem7 : ==========\n# put price < Max( X-s, 0 ), s = %8.2f\n", s);
    printf("strike_price        put  Max( X-s, 0 )  / Arbitrage space       / volume\n");
    float term;
    float space, per;
    for( int i=0; i<length; i++){
        term = X[i] - s;
        if (term < 0.) term = 0.;
        if (put[i] < term){
            space = term - put[i];
            per = space / (term + put[i]);
            printf("%12.0f %10.2f  %13.2f  / %15.2f %5.2f / %6.0f\n", X[i], put[i], term, space, per, Vput[i]);
        }
    }
}




int main(){
    float r, s;  //利率, 股價(取期貨價格)
    //float call[length], put[length], X[length], pv[length], VolumeCall[length], VolumePut[length];  // call price, put price, 履約價, 現值, 交易量
    float call[lenMax], put[lenMax], X[lenMax], pv[lenMax], VolumeCall[lenMax], VolumePut[lenMax];
    printf("input data length : ");
    scanf("%d", &length);



    printf("input rate : ");
    scanf("%f", &r);
    r /= 100;

    printf("input Futures price : ");
    scanf("%f", &s);


    printf("input strike_price call_price call_volume put_price put_volume\n");
    for(int i=0; i<length; i++){
        scanf("%f %f %f %f %f", &X[i], &call[i], &VolumeCall[i], &put[i], &VolumePut[i]);
        pv[i] = X[i]/(1.0 + r);
    }

/*
    // check data correct
    printf("\n\n-----------------------------------\n");
    printf("len = %d\n", length);
    printf("r = %f\n", r);
    printf("s = %f\n", s);
    for(int i=0; i<length; i++){
        printf("%f %f %f %f %f %f\n", X[i], call[i], VolumeCall[i], put[i], VolumePut[i], pv[i]);
    }
*/

    printf("\n\n-----------------------------------\n");
    printf("len = %d\n", length);
    printf("r = %f\n", r);
    printf("s = %f\n\n", s);

    // Theorem check
    Theorem2(call, put ,X, VolumeCall, VolumePut);
    Theorem3_AmericaOption(call, put, X, s, VolumeCall, VolumePut);
    Theorem3_EuropeOption(call, put, X, pv, s, VolumeCall, VolumePut);
    Theorem4(call, X, pv, s, VolumeCall);
    Theorem6_EuroPutLower(put, X, pv, s, VolumePut);
    Theorem7_UsPutLower(put, X, s, VolumePut);



    return 0;
}
