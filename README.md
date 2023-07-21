
# Modo de Utiliazção da Biblioteca Arduino IDE

Essa Biblioteca usa Três Parâmetros.

```
consoleView.elementName(); // Define um nome Para o Elemento
```
```
consoleView.helloWord(); //Pode ser definida qualquer frase de Inicialização.
```
```
consoleView.consoleView(); //Chama o Serial do Arduino
```
```
#include "Console.h" //Inclui a Biblioteca

Console consoleView;

void setup() {
  delay(100);
  Serial.begin(9600);
  consoleView.elementName("ESP-NOW"); //Defineo o nome do modulo
  consoleView.helloWord("O Modulo Iniciou com Sucesso..."); //Define boas Vinda do Terminal
}

void loop() {
  consoleView.consoleView();
}

```