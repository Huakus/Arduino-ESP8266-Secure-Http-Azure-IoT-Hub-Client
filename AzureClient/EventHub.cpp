#include "EventHub.h"


String Eventhub::createSas(char *key, String url){  
  // START: Create SAS  
  // https://azure.microsoft.com/en-us/documentation/articles/service-bus-sas-overview/
  // Where to get seconds since the epoch: local service, SNTP, RTC

  String stringToSign = url + "\n" + _cloud->sasExpiryDate;

  // START: Create signature
  Sha256.initHmac((const uint8_t*)key, 44);
  Sha256.print(stringToSign);
  
  char* sign = (char*) Sha256.resultHmac();
  int signLen = 32;
  // END: Create signature

  // START: Get base64 of signature
  int encodedSignLen = base64_enc_len(signLen);
  char encodedSign[encodedSignLen];
  base64_encode(encodedSign, sign, signLen);   
  // END: Get base64 of signature

  // SharedAccessSignature
  return "sr=" + url + "&sig="+ urlEncode(encodedSign) + "&se=" + _cloud->sasExpiryDate +"&skn=" + _cloud->id;
  // END: create SAS
}

void Eventhub::initialiseHub() {
  String url = urlEncode("https://")  + urlEncode(_cloud->host) + urlEncode(EVENT_HUB_END_POINT);
  _cloud->endPoint = EVENT_HUB_END_POINT;
  _cloud->fullSas = createSas(_cloud->key, url);
}
