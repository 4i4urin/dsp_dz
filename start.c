#include <stdio.h>
#include <stdlib.h>
#include "goertzel.h"


#define VECT_LEN 1000
#define FREQ_NUM 8
#define SEMPLING_FREQ 24000

void read_in_vect(FILE* file, s8* pin_vect, u16 vect_len);
u8 read_user_freq(u16* p_freq_arr, u8 freq_lim);

int main(void)
{
    s8 in_vect[VECT_LEN] = { 0 };
    u8 freq_num = 0;
    u16 freq_arr[FREQ_NUM] = { 0 };
    u8 goert_res[FREQ_NUM] = { 0 };

    read_in_vect(fopen("input.txt", "r"), in_vect, VECT_LEN);
    freq_num = read_user_freq(freq_arr, FREQ_NUM);

    for (u8 i = 0; i < freq_num; i++)
        if (freq_arr[i] >= SEMPLING_FREQ / 2)
            freq_arr[i] = 0;
        else     
            freq_arr[i] = freq_arr[i] * VECT_LEN / SEMPLING_FREQ;

    // do goertsel things
    goertzel_arr(in_vect, VECT_LEN, freq_arr, freq_num, goert_res);
    for (u8 i = 0; i < freq_num; i++)
        printf("\nFind freq = %d\nres = %d\n", 
            freq_arr[i] * SEMPLING_FREQ / VECT_LEN, goert_res[i]);    
    
    return 0;
}


u8 read_user_freq(u16* p_freq_arr, u8 freq_lim)
{
    u8 freq_num;
    printf("How much freq you want to find? (8 is max)> ");
    scanf("%hhd", &freq_num);
    if (freq_num > freq_lim)
    {
        printf("ERROR: freq over the limit\n");
        exit(100);
    }

    for (u8 i = 0; i < freq_num; i++)
    {
        printf("Decimal freq > ");
        scanf("%hd", p_freq_arr + i);
    }

    return freq_num;
}


void read_in_vect(FILE* file, s8* pin_vect, u16 vect_len)
{
    if (file == NULL)
    {
        printf("ERROR: Can't read file\n");
        exit(100);
    }

    for (u16 i = 0; i < vect_len; i++)
        fscanf(file, "%hhd\n", pin_vect + i);
}

