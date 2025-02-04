#include <stdio.h>
#include "pico/stdlib.h"
#include "hardwire/timer.h"

#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
volatile _Atomic uint estado;//0 - vermelho, 1- amarelho 2 - verde
void liga_amarelo()//usar função separada pra ligar amarelo para n bagunçar
{

}
void processa_repeticao()
{
    switch ((estado))
    {
    case 0://0 é o primeiro e relacionado a vermelho
        //gpio_put(LED_RED, false)//para amarelo manter vermelho maximo e ligar verde
        gpio_put(LED_GREEN,true);
        estado=1;
        break;
    case 1:
        
        break;
    }
}

int main()
{
    stdio_init_all();
    gpio_init(LED_BLUE);
    gpio_init(LED_GREEN);
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    add_repeating_timer
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
