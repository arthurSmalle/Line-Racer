#include <Arduino.h>

#include "api/Compat.h"
#include "state machine/FSM.h"
//#include "robot states/RSInit.h"
#include "state machine/StatesEnum.h"
// states that will be used
#include "robot states/RSAdjustOnStraight.h"

#include "robot states/TSSpeakers.h"
#include "robot states/TSAngleController.h"
#ifdef USE_IMU
#include "robot states/TSMagnetometer.h"
#endif
#ifdef USE_BLE
#include <ArduinoBLE.h>
#endif

  // global objects
  // RSInit * rsinit = new RSInit(StatesEnum::AdjustOnStraight);
  // TSSpeakers * speaker = new TSSpeakers();
  // TSAngleController * anglecontroller = new TSAngleController();
 RSAdjustOnStraight * straight = new RSAdjustOnStraight();
  FSM fsm = FSM(straight);

  // BLE consts and objects 
#ifdef USE_BLE
  const char * deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
  const char * deviceServiceRequestCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1215";
//  const char * deviceServiceResponseCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1216";

    BLEService followingLineService(deviceServiceUuid);
    BLEBoolCharacteristic followingLineRequestCharacteristic(deviceServiceRequestCharacteristicUuid, BLEWrite);
#endif
  
  void setup(){
    Serial.begin(115200);
#ifdef USE_IMU
    IMU.begin();
#endif
#ifdef USE_BLE
    // init ble
    BLE.begin();
    BLE.setDeviceName("Supra");
    BLE.setLocalName("Supra");
    if (!BLE.begin()) {
     Serial.println("- Starting Bluetooth® Low Energy module failed!");
     digitalWrite(13, HIGH);
    }
    // prepare ble service and charasteristics
    BLE.setAdvertisedService(followingLineService);
    followingLineService.addCharacteristic(followingLineRequestCharacteristic);
    BLE.addService(followingLineService);
    BLE.advertise();
  

#endif
  }
#ifdef USE_BLE
bool enable_line_following = false;
#endif
void loop(){
#ifdef USE_BLE
  BLEDevice central = BLE.central();
  // while(!central){
  // Serial.println("- Discovering central device...");
  // delay(400);
  // }
  
  if (central) {
    Serial.println("* Connected to central device!");
    Serial.print("* Device MAC address: ");
    Serial.println(central.address());
    Serial.println(" ");
  }
  while(central.connected()){
    if (followingLineRequestCharacteristic.written()) {
      enable_line_following = followingLineRequestCharacteristic.value();
    }
    if (enable_line_following){
      fsm.update();
    }
}
#else
fsm.update();
#endif
}
