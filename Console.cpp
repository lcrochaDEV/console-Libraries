#include"Console.h"

/**************************LUCAS ROCHA****************************/
/*
 * Portas Analogicas A = 1,2,3,4,5,6,7.
 * Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.
 * Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.
 *
 * Data 12/07/2023
*/
/*****************************************************************/
template< typename T, size_t N > size_t ArraySize (T (&) [N]){
  return N; 
}
String promptCLI; //NOME DO MODULO
String pinType[30] = {"D13"};
String bufferArray[3]; // =>  activePin, estado}

int pin_On = HIGH; //PIN STATE ALTO = 1
int pin_Off = LOW; //PIN STATE BAIXO = 0

int contagem = 0; //CONTADOR

Console::Console(String _consoleTextView){
     consoleTextView = _consoleTextView;
}
void Console::elementName(String _consoleTextView = "ARDUINO"){
    consoleTextView = _consoleTextView;
    promptCLI = _consoleTextView;
}
void Console::helloWord(String _consoleTextView = "Hello Word"){
  consoleTextView = _consoleTextView;
  messageView(_consoleTextView);
  messageView(promptCLI + "> ");
}
void Console::consoleView(){
  if (Serial.available() > 0) {
    String _consoleTextView = Serial.readString();
    _consoleTextView.trim();
    if (_consoleTextView.length() > 1) {
      _consoleTextView.toUpperCase();
      pinTypeExiste(_consoleTextView);
    }else{
      returnConsoleText("("+ _consoleTextView +")Pino não Encontrado!");
    }
  }
}
void Console::pinTypeExiste(String _consoleTextView){
  while(contagem < ArraySize(pinType)) {
    if(_consoleTextView != pinType[contagem]){ //VERIFICA SE EXISTE NO ARRAY
      if (_consoleTextView.indexOf("A") == 0 && _consoleTextView.length() == 2 || _consoleTextView.indexOf("D") == 0 && _consoleTextView.length() <= 3) {
        bufferArray[0] = _consoleTextView; //OBRIGATÓRIO
        messageView(promptCLI + "-" + _consoleTextView + ">");
      break;
      }else if(_consoleTextView == "LISTPIN"){
        mostraPinos();
      break;
      }else if(_consoleTextView == "INPUT" || _consoleTextView == "OUTPUT" || _consoleTextView == "INPUT_PULLUP"){
        pin_mode(_consoleTextView);
      break;
      }else if(_consoleTextView == "ON" || _consoleTextView == "OFF"){;
        pinOnOff(_consoleTextView);
      break;
      }else if(_consoleTextView == "END"){
        retornMenuPrincipal();
      break;
      }else if(_consoleTextView == "HELP"){
        help();
      break;
      }else  {
        returnConsoleText("error, comando null!"); //ERRO
      break;
      }
    }
    contagem++;
  }
contagem = 0;
}
//MOSTRA PINOS NA LISTA
void Console::mostraPinos(){
  if(pinType[1] != 0) {
    for (int i = 0; i < ArraySize(pinType); i++) {
      if(pinType[i] != 0) {
        messageView(pinType[i]);
      }
    }
 }else{
  returnConsoleText("Apenas o pino " + pinType[0] + "(default) Cadastrado.");
 }
}  
//MENSAGEM DE TODO O PROGRAMA
void Console::pin_mode(String _consoleTextView){
  if(bufferArray[0] != NULL){
    bufferArray[1] = _consoleTextView;
    messageView("Modo de Operação " + _consoleTextView + " Acionado!");
    messageView(promptCLI + "-" + bufferArray[0] + ">");
  }else{
    returnConsoleText("Selecione um Pino!");
  }
}
void Console::pinOnOff(String _consoleTextView){
  bufferArray[2] = _consoleTextView;
   if(bufferArray[0] == NULL){
    returnConsoleText("Selecione um Pino!");
  }else if(bufferArray[1] != NULL){
    onOff(bufferArray[2]);
    activePin();
  }else{
    returnConsoleText("error, comando null!"); //ERRO
  }
}
void Console::activePin(){
  int activePin = bufferArray[0].substring(1).toInt(); //BUSCA O NUMERO EM ESTRING E TRANSFORMA EM INT
  if(bufferArray[2] == "ON"){
    digitalWrite (activePin, pin_On);  
  }else if(bufferArray[2] == "OFF"){
    digitalWrite (activePin, pin_Off);
  } 
}
void Console::onOff(String onOff){
  if(onOff == "ON"){
    ativo(onOff, "ativo");
  }else if(onOff == "OFF"){
    ativo(onOff, "desativado");
  }else{
    returnConsoleText("error, comando null!"); //ERRO
  }
}
void Console::ativo(String onOff, String _consoleTextView){
  messageView(promptCLI + "-" + bufferArray[0] + ">" + onOff);
  messageView("Pino " + bufferArray[0] + " " + _consoleTextView +" com sucesso!");
  messageView(promptCLI + "-" + bufferArray[0] + ">");
}
void Console::retornMenuPrincipal(){
  for (int i = 0; i <= 2; i++) {
    bufferArray[i] = "\0"; 
  }
    messageView(promptCLI + "> ");
}
void Console::help(){
  messageView("/***********************PINOS ARDUINO NANO************************/");
  messageView("Portas Analogicas A = 1,2,3,4,5,6,7.");
  messageView("Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.");
  messageView("Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.");
  messageView("Data 12/07/2023");
  messageView("/*****************************************************************/");
  messageView(promptCLI + "> ");
}
void Console::returnConsoleText(String _consoleTextView){
  if(bufferArray[0] == NULL){
    messageView(_consoleTextView);
    messageView(promptCLI + "> ");
  }else {
    messageView(_consoleTextView);
    messageView(promptCLI + "-" + bufferArray[0] + ">");
  }
}
//MENSAGEM DE TODO O PROGRAMA
void Console::messageView(String _consoleTextView){
  Serial.print(_consoleTextView);
  Serial.println();
}