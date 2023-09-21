
## Modo de Utilização da Biblioteca Arduino IDE

Essa Biblioteca usa Três Parâmetros.

```C++
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
### Principais Comandos
```C++
consoleView.elementName(); // Define um nome Para o Elemento
```
```C++
consoleView.helloWord(); // Pode ser definida qualquer frase de Inicialização, mais não é obrigatória.
```
```C++
consoleView.consoleView(); // Chama à Serial do Arduino
```


<div id="ling">  
  <img  width="100" src="https://camo.githubusercontent.com/b44f0ac2814194d49b6d5c0808217956abde3fe6eea7622f1f6b4ae80065f059/68747470733a2f2f6370703461726475696e6f2e636f6d2f6173736574732f696d616765732f666f6f7465725f6c6f676f2e737667" style="max-width: 100%;">
  <img width="100" src="https://icon-library.com/images/arduino-icon/arduino-icon-21.jpg" style="max-width: 100%;"> 
</div><!-- LINGUAGENS-->