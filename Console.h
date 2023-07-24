
#ifndef CONSOLE_H
#define CONSOLE_H
 
#include <Arduino.h>

class Console {
    public:
    Console(String _consoleTextView = "");
        void elementName(String _consoleTextView  = "ARDUINO");
        void helloWord(String _consoleTextView  = "Hello Word");
        void consoleView();
        void pinTypeExiste(String _consoleTextView);
        void mostraPinos();
        //MODO DE OPERAÇÃO DO PINO SELECIONADO
        void pin_mode(String _consoleTextView);
        void pinOnOff(String _consoleTextView);
        void activePin();
        void onOff(String _consoleTextView);
        void ativo(String onOff, String _consoleTextView);
        void retornMenuPrincipal();
        void help();
        void returnConsoleText(String _consoleTextView);
        //MENSAGEM DE TODO O PROGRAMA
        void messageView(String _consoleTextView);
        //String push();
    private:
    String consoleTextView;   
};
 
#endif