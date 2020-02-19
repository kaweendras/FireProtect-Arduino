void senddata() {
  //  String path = "/Test/temp test json";
  String path = "/Test/" + num;
  String jsonStr = "";

  FirebaseJson json1;
  FirebaseJsonData jsonObj;

  json1.set("temp/thresh hold/", String(thresh_val));
  json1.set("temp/value/", String(ii));

  Serial.println("------------------------------------");
  Serial.println("JSON Data");
  json1.toString(jsonStr, true);
  Serial.println(jsonStr);
  Serial.println("------------------------------------");

  Serial.println("------------------------------------");
  Serial.println("Set JSON test...");

  if (Firebase.set(firebaseData, path, json1))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.print("VALUE: ");
    printResult(firebaseData);
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

}
