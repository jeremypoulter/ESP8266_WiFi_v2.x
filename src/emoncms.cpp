#include "emonesp.h"
#include "emoncms.h"
#include "config.h"
#include "http.h"
#include "input.h"

#include <Arduino.h>

//EMONCMS SERVER strings

boolean emoncms_connected = false;

unsigned long packets_sent = 0;
unsigned long packets_success = 0;

#include "cert.dst_root_ca_x3.cer.h"

void
emoncms_publish(String url) {
  Profile_Start(emoncms_publish);

  if (emoncms_apikey != 0) {
    DEBUG.println(emoncms_server.c_str() + String(url));
    packets_sent++;
    // Send data to Emoncms server
    String result = "";
    if (emoncms_fingerprint != 0) {
      // HTTPS on port 443 if HTTPS fingerprint is present
      DEBUG.println("HTTPS");
      delay(10);
      result =
        get_https(emoncms_server.c_str(), url, 443, CONTENT_DST_ROOT_CA_X3_CER, sizeof(CONTENT_DST_ROOT_CA_X3_CER) - 1);
    } else {
      // Plain HTTP if other emoncms server e.g EmonPi
      DEBUG.println("HTTP");
      delay(10);
      result = get_http(emoncms_server.c_str(), url);
    }
    if (result == "ok") {
      packets_success++;
      emoncms_connected = true;
    } else {
      emoncms_connected = false;
      DEBUG.print("Emoncms error: ");
      DEBUG.println(result);
    }
  }

  Profile_End(emoncms_publish, 10);
}
