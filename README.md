
Repositório criado para projeto do programa de residência **EmbarcaTech**, uma realização **CEPEDI** e apresentada ao professor  **RICARDO MENEZES PRATES** com conteúdo de Temporizadores da ***UNIDADE 4 CAPITULO 5***.  

## Atividade 1: Semáforo Automático  

A primeira atividade implementa um semáforo automático que segue a seguinte sequência:  

1. **Inicialização**:  
   - Assim que a placa BitDogLab é ligada, ocorre um sinal **luminoso e sonoro** indicando que o sistema iniciou.  
2. **Sequência de Semáforo**:  
   - O **LED vermelho** acende primeiro.  
   - Após **3 segundos**, acende o **LED amarelo** (simulado pela ativação simultânea dos LEDs **vermelho e verde**).  
   - Após mais **3 segundos**, acende apenas o **LED verde**.  
3. **Saída no Terminal**:  
   - A cada **1 segundo**, o estado atual da operação é impresso no terminal.  
4. **(Opcional)** Modo Bootloader via GPIO 22:  
   - Um botão conectado ao **GPIO 22** pode ser usado para forçar a placa a entrar no modo bootloader.  

### Simulação  
A simulação deste projeto está disponível no **Wokwi**, permitindo testar e visualizar o funcionamento do semáforo antes da execução real na placa.  

---

## Atividade 2: Temporizador Acionado por Interrupção  

A segunda atividade implementa um **temporizador baseado em interrupção**, acionado pelo **botão no GPIO 5**.  

### Funcionamento  

1. **Inicialização**:  
   - Ao ligar a placa BitDogLab, ocorre **apenas um sinal sonoro** para indicar que o sistema foi iniciado.  
2. **Disparo do Temporizador**:  
   - Pressionar o **botão no GPIO 5** inicia a cronometragem.  
   - Todos os **LEDs RGB** (nos **GPIOs 13, 11 e 12**) são **acesos simultaneamente**.  
   - O **botão não tem efeito enquanto a contagem está ativa**.  
3. **Sequência de Apagamento**:  
   - Após **3 segundos**, o **LED azul (GPIO 12)** apaga.  
   - Após mais **3 segundos**, o **LED vermelho (GPIO 13)** apaga.  
   - Por fim, após mais **3 segundos**, o **LED verde (GPIO 11)** apaga.  

4. **(Opcional)** Modo Bootloader e Efeitos Extras:  
   - Pressionar o **GPIO 22** força o modo bootloader.  
   - Ao entrar no bootloader, **todos os LEDs piscam várias vezes** e uma **música de encerramento** é tocada como efeito extra.  

---

## Dependências  

Para compilar e executar este projeto, você precisará:  

- **Placa Raspberry Pi Pico ou BitDogLab**  
- **Ambiente de desenvolvimento do RP2040** (CMake, GCC)  
- **Bibliotecas necessárias** para manipulação de **GPIOs e LEDs RGB**  
- **Simulador Wokwi** (opcional, mas recomendado para testes)  

### Como Compilar  

1. Instale o SDK do **RP2040** e configure o ambiente de desenvolvimento com **CMake**.  
2. Clone este repositório:  

    ```bash
    git clone https://github.com/seu_usuario/clocksETemps.git
    cd clocksETemps
    ```

3. Compile cada atividade separadamente:  

    - **Para a Atividade 1 (Semáforo Automático)**:  

      ```bash
      cd ativ_um/streetLightTemp
      mkdir build
      cd build
      cmake ..
      make
      ```

    - **Para a Atividade 2 (Temporizador por Interrupção)**:  

      ```bash
      cd ../../../ativ_dois/buttonEClock
      mkdir build
      cd build
      cmake ..
      make
      ```

4. Após a compilação, transfira o arquivo gerado (`.uf2`) para a placa via USB.  
   - Se necessário, pressione o botão do **GPIO 22** para entrar no modo bootloader.  


---

## Simulação  

Os arquivos **diagram.json** dentro das pastas **streetLightTemp** e **buttonEClock** podem ser carregados no **Wokwi** para simulação do funcionamento antes da execução real na placa.  

---
### Demonstração

Veja uma demonstração em vídeo do funcionamento do sistema no YouTube:

[**Assista à Demonstração no YouTube**](https://youtube.com/live/7SHDxxW0SWs)

- **Aluno:** Gleison Fonseca de Paula

---
---
## Licença  

Este projeto está licenciado sob a **Licença GNU**.  

---

<div align="center">
    GNUs not Unix
</div>
