#include <stdio.h>

enum Status { Alarm, Off, Wait };

enum Status alarmClockStatus(enum Status status, int key, int time) 
{
    switch(status) 
        {
            case Off:
                if (key) {
                    status = Wait;
                }

            case Wait:
                if (time == 5) {
                    status = Alarm;
                }
                else if (!key) {
                    status = Off;
                }

            case Alarm:
                if (!key || time == 10) {
                    status = Off;
                    key = 0;
                }
        }

    if (status == Off) {
        printf("Status: Off - Key: %d - Time: %d\n", key, time);
    }
    else if (status == Wait) {
        printf("Status: Wait - Key: %d - Time: %d\n", key, time);
    }
    else {
        printf("Status: Alarm - Key: %d - Time: %d\n", key, time);
    }

    return status;
}

void alarmClock(int a[], int size) 
{
    enum Status status = Off;
    int time = 0;
    int key = 0;
    
    int i = 0;
    while (1) {
        if (i >= size && status == Off) {
            break;
        }

        key = (i < size) ? a[i] : key;
        status = alarmClockStatus(status, key, time);
        time = (status == Off) ? 0 : (time + 1);
        i++;
    }
}

int main() 
{
    int n;
    printf("Nhap so lan bat tat: ");
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    alarmClock(a, n);

    return 0;
}
