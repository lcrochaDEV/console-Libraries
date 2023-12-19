#include "HardwareSerial.h"
/*LUCAS ROCHA*/
/*
 * Portas Analogicas A = 1,2,3,4,5,6,7.
 * Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.
 * Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.
 *
 * Data 12/07/2023
*/
/************/
#include "Console.h"
int contagem = 0; //CONTADOR

//CONTA O TAMANHO DO ARRAY
template< typename T, size_t N > size_t ArraySize (T (&) [N]) {
  return N; 
}
//***BUFFER MEMORY***//
String bufferArray[5]; // =>  [PIN = type String, NUMBER PIN = type Nunber, MODE OPERATION = type Number, ON|OFF = type String]
//***BUFFER MEMORY***//

String promptCLI; //NOME DO MODULO
int digitalPinArr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; //ARRAY DE PINOS
int analogPinArr[] = {14, 15, 16, 17, 18, 19, 20, 21}; //ARRAY DE PINOS
String modeOperation[3] = {"INPUT", "OUTPUT", "INPUT_PULLUP"}; //ARRAY DE MODOS

//GENÉRIO
int arrayIndexOff(String nomeDoModo){
  while(contagem < ArraySize(modeOperation)) {
    if(nomeDoModo == modeOperation[contagem]){
      return contagem;
    break;
    }
    contagem++;
  }
contagem = 0;
}
Console::Console(String consoleText = ""){
    this->consoleTextView = consoleText;
}
void Console::elementName(String consoleText = "ARDUINO"){
    promptCLI = consoleText;
}
void Console::helloWord(String consoleText = "Hello Word"){
  messageViewMsg1(consoleText);
  messageViewMsg1(promptCLI + "> ");
}
void Console::consoleView(){
  if (Serial.available() > 0) {
    String consoleText = Serial.readString();
    consoleText.trim();
    if (consoleText.length() > 1) {
      consoleText.toUpperCase();
      arduinoPins(consoleText);
    }else{
      returnConsoleText("("+ consoleText +")Pino não Encontrado!");
    }
  }
}
//MENU PINOS DIGITAIS
void Console::arduinoPins(String consoleText){
  if(consoleText.startsWith("D") && consoleText.length() <= 3) {
    //ZERANDO ARRAY BUFFER
    for (int i = 0; i <= arrayIndexOff(bufferArray[0]); i++) {
      bufferArray[i] = ""; 
    }
    if(consoleText.substring(1).equals(String(digitalPinArr[consoleText.substring(1).toInt()]))){ //VERIFICA SE EXISTE NO ARRAY
      bufferArray[0] = consoleText; //OBRIGATÓRIO
      bufferArray[1] = digitalPinArr[consoleText.substring(1).toInt()]; //OBRIGATÓRIO
      pin_mode();
    }else {
      returnConsoleText("Pino não encontrado!");
    }
  } else if(consoleText.startsWith("A") && consoleText.length() <= 3) {
      //ZERANDO ARRAY BUFFER
      for (int i = 0; i <= arrayIndexOff(bufferArray[0]); i++) {
        bufferArray[i] = ""; 
      }
      while(sizeof(analogPinArr)/sizeof(analogPinArr[0])) {
        if(analogPinArr[consoleText.substring(1).toInt()]){ //VERIFICA SE EXISTE NO ARRAY
          bufferArray[0] = consoleText; //OBRIGATÓRIO
          bufferArray[1] = analogPinArr[consoleText.substring(1).toInt()];
          pin_mode();
        }else {
          returnConsoleText("Pino não encontrado!");
        }
      break;
      }
  }else {
    subMenuFunction(consoleText);
  }
}
//SUB-MENU
void Console::subMenuFunction(String consoleText){
  if(consoleText == "LISTPIN"){
      mostraPinos();
  }else if(consoleText == "INPUT" || consoleText == "OUTPUT" || consoleText == "INPUT_PULLUP"){
      pin_mode(consoleText);
  }else if(consoleText == "ON" || consoleText == "OFF"){
      pinOnOff(consoleText);
  }else if(consoleText == "END"){
    retornMenuPrincipal();
  }else if(consoleText == "HELP"){
    help();
  }else  {
    returnConsoleText("error, comando null!"); //ERRO
  }
}
void Console::analogPins(String consoleText){
  messageViewMsg1(promptCLI + "-" + consoleText + ">");
}
//MOSTRA PINOS NA LISTA
void Console::mostraPinos(){
  if(bufferArray[1] != 0) {
    messageViewMsg1("Pino: " + String(bufferArray[0]));
    messageViewMsg1("Número do Pino: " + String(bufferArray[1]));
    String operacaoMode = bufferArray[2] == "0"  ? "INPUT" : NULL || bufferArray[2] == "1" ? "OUTPUT" : NULL || bufferArray[2] == "2" ? "INPUT_PULLUP" : NULL;
    messageViewMsg1("Modo de Operação: " + operacaoMode);
    messageViewMsg1("Estado: " + String(bufferArray[3]));
 }else{
  returnConsoleText("Pino não Cadastrado.");
 }
}//SEM FUNCIONALIDADE NO MOMENTO
//MENSAGEM DE TODO O PROGRAMA
void Console::pin_mode(String consoleText = ""){
 if(consoleText != NULL) {
    if(bufferArray[0] != NULL){
      bufferArray[2] = arrayIndexOff(consoleText);
      messageViewMsg1("Modo de Operação " + consoleText + " Acionado!");
      messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">");
    }else{
      returnConsoleText("Selecione um Pino!"); //ERRO
    }
  }else{
      messageViewMsg1("Escolha um Modo de Operação");
      messageViewMsg1("INPUT, OUTPUT ou INPUT_PULLUP");
      messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">");
  }
}
void Console::pinOnOff(String consoleText){
  if(bufferArray[2] != NULL){
    bufferArray[3] = consoleText;
    activePin();
  }else if(!bufferArray[0]){
    returnConsoleText("error, comando null!"); //ERRO
  }else{
    returnConsoleText("Selecione um Pino!");
  }
}
void Console::activePin(){
  if(bufferArray[3] == "ON"){
    digitalWrite (bufferArray[1].toInt(), HIGH); 
    ativo("ativo");
  }else if(bufferArray[3] == "OFF"){
    digitalWrite (bufferArray[1].toInt(), LOW);
    ativo("desativado");
  }else{
    returnConsoleText("error, comando null!"); //ERRO
  }
}
void Console::ativo(String consoleText){
  messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">" + bufferArray[4]);
  messageViewMsg1("Pino " + bufferArray[0] + " " + consoleText +" com sucesso!");
  messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">");
}
void Console::retornMenuPrincipal(){
  for (int i = 0; i <= 2; i++) {
    bufferArray[i] = "\0"; 
  }
    messageViewMsg1(promptCLI + "> ");
}
void Console::help(){
  messageViewMsg1("/**PINOS ARDUINO NANO**/");
  messageViewMsg1("Portas Analogicas A = 0, 1 ,2 ,3 , 4, 5, 6, 7.");
  messageViewMsg1("Portas Analogicas/Digitais 14, 15, 16, 17, 18, 19, 20.");
  messageViewMsg1("Portas Digitais D = 2,3,4,5PWM,6PWM,7,8,9PWM,10PWM,11PWM,12,13.");
  messageViewMsg1("Data 12/07/2023");
  messageViewMsg1("/***/");
  messageViewMsg1(promptCLI + "> ");
}
void Console::returnConsoleText(String consoleText){
  if(bufferArray[0] == NULL){
    messageViewMsg1(consoleText);
    messageViewMsg1(promptCLI + "> ");
  }else if(bufferArray[3] == NULL){
    messageViewMsg1("Comando não encontrado!");
    messageViewMsg1("Escolha um Modo de Operação");
    messageViewMsg1("INPUT, OUTPUT ou INPUT_PULLUP");
    messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">");
  }else {
    messageViewMsg1(consoleText);
    messageViewMsg1(promptCLI + "-" + bufferArray[0] + ">");
  }
}
//MENSAGEM DE TODO O PROGRAMA
void Console::messageViewMsg1(String consoleText){
  Serial.println(consoleText);
}
void Console::messageViewMsg2(){
  Serial.println(consoleTextView);
}