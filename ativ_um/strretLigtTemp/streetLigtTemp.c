#include <stdio.h>
#include "pico/stdlib.h"
#include "hardwire/timer.h"

#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define NUMLEDS 3
volatile _Atomic uint estado;//0 - vermelho, 1- amarelho 2 - verde
static __uint8_t leds[3] = {13,11,12};

void liga_amarelo()//usar função separada pra ligar amarelo para n bagunçar
{
    for(__uint8_t i=0; i<2; i++)
    {
    gpio_put(leds[i], true);//liga vermelho e verde
    }
    estado =1;
    return;
}
void liga_vermelho()
{
gpio_put(leds[0]);
estado=0;
return;
}
void liga_verde()
{
gpio_put(leds[1], true);
estado=2;//indicação que agora ta verde
return;
}
void processa_repeticao()
{
    for(int i=0; i<NUMLEDS; i++)//desligar leds
    {
        gpio_put(leds[i], false);
    }
    switch ((estado))
    {
    case 0://0 é o primeiro e relacionado a vermelho
        //gpio_put(LED_RED, false)//para amarelo manter vermelho maximo e ligar verde
        (void)liga_amarelo();
        break;
    case 1://se for 1 é amarelo
        (void)liga_verde();//liga verde
        break;
    case 2://se for 2 é verde
        (void)liga_vermelho();
        break;
    }
    return;
}
void startaLeds()
{
    for (int i =0; i<NUMLEDS; i++)
    {
        gpio_init(leds[i]);
        gpio_set_dir(leds[i], GPIO_OUT);
    }
    return;
}

int main()
{
    stdio_init_all();
    startaLeds();

    add_repeating_timer
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
