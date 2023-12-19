#ifndef CONSOLE_H
#define CONSOLE_H
 
#include <Arduino.h>

class Console {
    public:
    Console(String consoleText = "");
    void elementName(String consoleText = "ARDUINO");
    void helloWord(String consoleText  = "Hello Word");
    void consoleView();
    void messageViewMsg2();
    private:
    String consoleTextView;

    void arduinoPins(String consoleText);
    void subMenuFunction(String consoleText);
    void analogPins(String consoleText);
    void mostraPinos();
    //MODO DE OPERAÇÃO DO PINO SELECIONADO
    void pin_mode(String consoleText = "");
    void pinOnOff(String consoleText);
    void activePin();
    void ativo(String consoleText);
    void retornMenuPrincipal();
    void help();
    void returnConsoleText(String consoleText);
    //MENSAGEM DE TODO O PROGRAMA
    void messageViewMsg1(String consoleText);
};
 
#endif