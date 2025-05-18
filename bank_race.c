#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int balance = 100;
volatile bool flag[2] = {false, false};
volatile int turn;

void *withdraw0(void *arg) {
    flag[0] = true;
    turn = 1;
    while (flag[1] && turn == 1);

    if (balance >= 50) {
        printf("Personi 0: duke tërhequr 50 euro\n");
        sleep(1);
        balance -= 50;
        printf("Personi 0: bilanci i mbetur: %d\n", balance);
    } else {
        printf("Personi 0: nuk ka mjaftueshëm para\n");
    }

    flag[0] = false;
    return NULL;
}

void *withdraw1(void *arg) {
    flag[1] = true;
    turn = 0;
    while (flag[0] && turn == 0);

    if (balance >= 50) {
        printf("Personi 1: duke tërhequr 50 euro\n");
        sleep(1);
        balance -= 50;
        printf("Personi 1: bilanci i mbetur: %d\n", balance);
    } else {
        printf("Personi 1: nuk ka mjaftueshëm para\n");
    }

    flag[1] = false;
    return NULL;
}

int main() {
    pthread_t t0, t1;

    pthread_create(&t0, NULL, withdraw0, NULL);
    pthread_create(&t1, NULL, withdraw1, NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    return 0;
}
