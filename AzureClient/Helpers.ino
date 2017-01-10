//http://hardwarefun.com/tutorials/url-encoding-in-arduino


// http://arduino.stackexchange.com/questions/1013/how-do-i-split-an-incoming-string
String splitStringByIndex(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1  };  
  int maxIndex = data.length()-1;
  
  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
      found++;
      strIndex[0] = strIndex[1]+1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


const char *GetValue(const char* value){
  char *temp = new char[strlen(value) + 1];
  strcpy(temp, value);
  return temp;
}

const char *GetStringValue(String value){
  int len = value.length() + 1;
  char *temp = new char[len];
  value.toCharArray(temp, len);
  return temp;
}
