# Autopet 🐕
Um sistema de automação para criação de pets
## Especificações do projeto
- Duas entradas analógicas:
    - Uma célula de carga, que determina se a quantidade de comida está adequada
    - Sensor de temperatura que indica se o ambiente está adequado ao pet.
- Duas saídas com PWM:
    - A primeira saída será uma “resposta” ao sensor que determina a quantidade de comida. Caso a quantidade de comida seja insuficiênte, um servo motor irá liberar mais comida.
    - A segunda resposta emite um alerta sonoro através de um buzzer, quando a temperatura do ambiente está inadequada.
## Materiais utilizados
- ESP32
- Célula de carga
- HX711 (conversor análogico/digital)
- sensor de temperatura - bmp180
- servo motor
- Local para armazenar o alimento
- Suportes para o sistema
- botão para acionar manualmente
- buzzer - posteriormente substituído por um led.
## Lógica do projeto
![fluxograma do projeto](https://i.imgur.com/UBsQCLM.png)
## Circuito no Tinkercad
Link para circuito no Tinkercad com arduíno: https://www.tinkercad.com/things/krvaTeJLrZt-terrific-jaiks-crift/editel?sharecode=B6k1aOKvax8Yi2JtdWxgYM5Vq6nWotabHLyWoVr_Q6I
![Circuito no tinkercad](https://i.imgur.com/JolEgCj.png)
## Evolução da montagem do projeto
![Montagem do sensor de temperatura](https://i.imgur.com/nlsBvq4.png)
![Substituição do buzzer por leds](https://i.imgur.com/u7xKt0i.png)
![Adicionando célula de carga](https://i.imgur.com/ibqWsRS.png)
## Referências
- https://www.mundodaeletrica.com.br/sensor-de-temperatura-tipos-funcionamento/
- https://www.flintec.com/br/sensores-de-peso/celulas-de-carga/como-funciona-uma-célula-de-carga
- https://blog.kalatec.com.br/o-que-e-servo-motor/
- https://esp32io.com/tutorials/esp32-piezo-buzzer
- https://esp32io.com/tutorials/esp32-servo-motor
