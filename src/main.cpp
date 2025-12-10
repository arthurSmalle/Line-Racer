#include <Arduino.h>

#include "state machine/FSM.h"
#include "state machine/StatesEnum.h"
// states that will be used
#include "robot states/RSInit.h"
#ifdef USE_IMU
#include "robot states/TSMagnetometer.h"
#endif
#ifdef USE_BLE
#include <ArduinoBLE.h>
#endif

#ifdef USE_BLE
RSInit * initial_state = new RSInit(Init);
FSM fsm = FSM(initial_state);
#else
RSCurve * initial_state = new RSCurve();
FSM fsm = FSM(initial_state);
#endif

  // BLE consts and objects 
#ifdef USE_BLE
  const char * deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
  const char * deviceServiceRequestCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1215";
//  const char * deviceServiceResponseCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1216";

    BLEService followingLineService(deviceServiceUuid);
    BLEIntCharacteristic followingLineRequestCharacteristic(deviceServiceRequestCharacteristicUuid, BLEWrite);
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
StatesEnum ble_state = Init;
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
      ble_state = StatesEnum(followingLineRequestCharacteristic.value());
      fsm.set_current_state(ble_state);
    }
    fsm.update();
}
#else
fsm.update();
#endif
}
