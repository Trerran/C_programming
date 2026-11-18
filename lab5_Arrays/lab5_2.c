#include <stdio.h>

int zones(int num){
    if (num<100){
        return 0;
    }
    else if(99<num && num<140){
        return 1;
    }
    else if(139<num && num<170){
        return 2;
    }
    else{
        return 3;
    }
}

void zones_by_value(int hr[],int size){
    int peace=0, warm_up=0, cardio=0, peak=0;
    for(int i=0;i<size;i++){
        if (zones(hr[i])==0){
            peace+=1;
        }
        else if(zones(hr[i])==1){
            warm_up+=1;
        }
        else if(zones(hr[i])==2){
            cardio+=1;
        }
        else{
            peak+=1;
        }
    }
    printf("Покой: %d\nРазминка: %d\nКардио: %d\nПик: %d\n",peace,warm_up,cardio,peak);

}

void timekeeping(int hr[],int size){
    int res=0;
    for(int i=0,tmp=0,pr_res=0;i<size;i++){
        if ((i==0 && zones(hr[i])>=2) ||  (i==(size-1) && zones(hr[i])>=2)){
            pr_res+=1;
        }
        else if (i!=0 && i!=(size-1)){
            tmp=zones(hr[i-1]); 
            if (tmp>=2 && zones(hr[i])>=2){
                pr_res+=1;
            }
            else if (tmp<2 && zones(hr[i])>=2 ){
                pr_res=1;  
            }
            else {
                pr_res = 0;
            }       
        }
        else{
                pr_res=0;
            }
        if (pr_res>res){
                res=pr_res;
            }
    }

    printf("Самая длинная серия: %d\n", res);
}

void Average_heart_rate(int hr[],int size){
    float average=0;
    for(int i=0;i<size;i++){
        average+=hr[i];
    }
    average/=size;
    printf("Средний пульс: %.2f\n",average);
}

int main(void){
    int hr[24] = {85, 92, 98, 105, 118, 130, 142, 148, 151, 147, 150, 160, 165, 158, 143, 138, 120, 110, 104, 96, 90, 88, 150, 152};
    zones_by_value(hr,24);
    timekeeping(hr,24);
    Average_heart_rate(hr,24);
    return 0;
}
