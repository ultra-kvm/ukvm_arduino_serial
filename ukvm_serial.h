#ifndef UKVM_Serial_H
#define UKVM_Serial_H

void ukvm_serial_log(String str){
    Serial.println(str);
}

class UKVM_Serial {
  public:
  void (*log)(String);
  void (*onCommand)(String, String);


  String data = "";
  bool newData = false;

  

  
  void init(int baud = 9600){
    Serial.begin(baud);
    this->log = ukvm_serial_log;
  }




  void checkSerial(){
    if (newData == true){
      handleSerialCmd(String(data));
      data = "";
      newData = false;
    }

    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                data += rc;
            }
            else {
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
  }

  void _checkSerial(){
    int len = Serial.available();
    while (len > 0){
      delay(10);
      //log("Data available: " + String(len));
      char _char = Serial.read();
      if (_char == '\n'){
        //log("Incoming data: " + data);
        handleSerialCmd(data);
        data = "";
        return;
      }
      data += _char;
    }
  }

  void handleSerialCmd(String input){
    onCommand(utils.parseStr(input, 0, "="), utils.parseStr(input, 1, "="));
  }
};


#endif // UKVM_Serial_H