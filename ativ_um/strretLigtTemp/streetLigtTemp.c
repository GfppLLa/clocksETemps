#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "pico/bootrom.h"  //
#include "hardware/pwm.h"
#include "pico/time.h"

#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define BOTAO_A 5
#define BOTAO_B 6
#define BOTAO_C 22
#define OUT_PIN 7
#define BUZZER_A_PIN 10
#define BUZZER_B_PIN 21
#define NUM_PIXELS 25
#define DEBOUNCING_TIME_US 220
#define NUMLEDS 3
//variaveis
volatile _Atomic uint8_t estado;//0 - vermelho; 1- amarelho; 2 - verde
static uint8_t leds[3] = {13,11,12};
volatile _Atomic uint8_t outroContador =0;
volatile uint32_t hora_presente;
static volatile uint32_t ultimo_pressionamento = 0;
struct repeating_timer timer;
volatile _Atomic uint_8t saida_teste=0;
//

//prototipos
void entrarModoBootloader();
void liga_amarelo();
void liga_vermelho();
void liga_verde();
bool processa_repeticao();
void startaLeds();
void tocar_tom_buzzer(uint16_t frequency, uint32_t duration_ms);
void entrarModoBootloader();
void tratar_botoes(uint gpio, uint32_t events);
void entrarModoBootloaderDois();
//
void tratar_botoes(uint gpio, uint32_t events)
{
    //debounce();
    
      hora_presente = to_us_since_boot(get_absolute_time());
    if(gpio==BOTAO_C)
    {
        if(hora_presente-ultimo_pressionamento>DEBOUNCING_TIME_US*1000)
        {
            bool botao_pressionado=!gpio_get(BOTAO_C);
            if(botao_pressionado)
            {saida_teste=1;}
        }

    }
            ultimo_pressionamento=hora_presente;

}

void liga_amarelo()//usar função separada pra ligar amarelo para n bagunçar
{
    for(uint8_t i=0; i<2; i++)
    {
    gpio_put(leds[i], true);//liga vermelho e verde
    }

    return;
}
void liga_vermelho()
{
gpio_put(leds[0], true);

return;
}
void liga_verde()
{
gpio_put(leds[1], true);

return;
}
bool processa_repeticao()
{
    printf("\n\n----teste processa_repeticao()----\n\n");
    for(int i=0; i<NUMLEDS; i++)//desligar leds
    {
        gpio_put(leds[i], false);
    }
    switch (estado)
    {
    case 0://0 é o primeiro e relacionado a vermelho
        //gpio_put(LED_RED, false)//para amarelo manter vermelho maximo e ligar verde
        liga_amarelo();
        estado=1;
        break;
    case 1://se for 1 é amarelo
       liga_verde();//liga verde
        estado=2;
        break;
    case 2://se for 2 é verde
        liga_vermelho();
        estado=0;
        break;
    }
    outroContador++;
    return true;
}
void startaLeds()
{
    for (int i =0; i<NUMLEDS; i++)
    {
        gpio_init(leds[i]);
        gpio_set_dir(leds[i], GPIO_OUT);
    }

    gpio_init(BOTAO_C);
    gpio_set_dir(BOTAO_C, GPIO_IN);
    gpio_pull_up(BOTAO_C);
    gpio_set_irq_enabled_with_callback(BOTAO_C, GPIO_IRQ_EDGE_FALL, true, &tratar_botoes);
    
    return;
}
void tocar_tom_buzzer(uint16_t frequency, uint32_t duration_ms) {
   if (frequency == 0) {
        sleep_ms(duration_ms); // Silêncio (pausa)
        return;
    }

    gpio_set_function(BUZZER_B_PIN, GPIO_FUNC_PWM); // Configura pino do buzzer para PWM
    uint sliceNum = pwm_gpio_to_slice_num(BUZZER_B_PIN);

    uint clockDiv = 4; // Ajuste fino para manter precisão
    pwm_set_clkdiv(sliceNum, clockDiv);

    uint wrapValue = (125000000 / clockDiv) / frequency; // Cálculo mais preciso do período
    pwm_set_wrap(sliceNum, wrapValue);
    pwm_set_gpio_level(BUZZER_B_PIN, wrapValue / 2); // Duty cycle 50% (onda quadrada estável)
    
    pwm_set_enabled(sliceNum, true); // Ativa o PWM
    sleep_ms(duration_ms); // Mantém o som pelo tempo especificado

    // Suaviza a transição desligando PWM gradualmente
    for (int i = wrapValue / 2; i > 0; i -= wrapValue / 20) {
        pwm_set_gpio_level(BUZZER_B_PIN, i);
        sleep_ms(2);
    }

    pwm_set_enabled(sliceNum, false); // Desliga o PWM
    gpio_set_function(BUZZER_B_PIN, GPIO_FUNC_SIO);
    gpio_put(BUZZER_B_PIN, 0);

    sleep_ms(20); // Pequena pausa para evitar sobreposição de notas
}
void entrarModoBootloader() {
    for(uint8_t i=0; i<NUMLEDS; i++)
    {
    gpio_put(leds[i], true);//
    }
    tocar_tom_buzzer(1000, 200); 
    sleep_ms(100);            
    for(uint8_t i=0; i<NUMLEDS; i++)
    {
    gpio_put(leds[i], false);//
    }  
    tocar_tom_buzzer(1500, 200); 
    sleep_ms(100);    
    for(uint8_t i=0; i<NUMLEDS; i++)
    {
    gpio_put(leds[i], true);//
    }           
    tocar_tom_buzzer(2000, 300);
    sleep_ms(100);    
    for(uint8_t i=0; i<NUMLEDS; i++)
    {
    gpio_put(leds[i], false);//
    }           
    tocar_tom_buzzer(1000, 200);
    sleep_ms(50);       
    for(uint8_t i=0; i<NUMLEDS; i++)
    {
    gpio_put(leds[i], true);//
    }         
    tocar_tom_buzzer(1500, 200); 
    sleep_ms(50);  
    for(uint8_t i=0; i<NUMLEDS; i++)
    {
    gpio_put(leds[i], false);//
    }              
    tocar_tom_buzzer(2000, 400);
    reset_usb_boot(0, 0); // Reinicia no modo bootloader
}
void entrarModoBootloaderDois() {
tocar_tom_buzzer(2000, 300);  
for(uint8_t i=0; i<NUMLEDS; i++)
    {
    gpio_put(leds[i], true);//
    }
sleep_ms(150);                
tocar_tom_buzzer(1500, 250);  
for(uint8_t i=0; i<NUMLEDS; i++)
    {
    gpio_put(leds[i], false);//
    }
sleep_ms(150);                
tocar_tom_buzzer(1000, 250);  
for(uint8_t i=0; i<NUMLEDS; i++)
    {
    gpio_put(leds[i], true);//
    }
sleep_ms(200);                
tocar_tom_buzzer(800, 300);   
sleep_ms(250);                
tocar_tom_buzzer(600, 400);   
for(uint8_t i=0; i<NUMLEDS; i++)
    {
    gpio_put(leds[i], false);//
    }
sleep_ms(300);                
tocar_tom_buzzer(400, 500);  

}
int main()
{
    stdio_init_all();
    (void)startaLeds();
    entrarModoBootloaderDois();
    (void)liga_vermelho();
    bool timer_status=add_repeating_timer_ms(-3000, processa_repeticao, NULL, &timer);
    while (true) {
        printf("\nstatus timer: %d \nestado atual: %d\nnumero de ciclos: %d",timer_status, estado, outroContador);
        sleep_ms(1000);
        if(saida_teste==1)
        {
            sleep_ms(50);
            entrarModoBootloader();
        }
    }
}
