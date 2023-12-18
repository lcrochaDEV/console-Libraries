#include "Console.h"

Console consoleView;

void setup() {
  delay(100);
  Serial.begin(9600);
  consoleView.elementName("ESP-NOW");
  consoleView.helloWord("O Modulo Iniciou com Sucesso...");
}

void loop() {
  consoleView.consoleView();
}
