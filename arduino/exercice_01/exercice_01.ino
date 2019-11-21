#include <TensorFlowLite.h>
#include "tensorflow/lite/experimental/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "data.h"

namespace { 
  const tflite::Model* model = nullptr;
}  

void setup() {
  Serial.begin(115200);

  model = tflite::GetModel(mi_data);

  Serial.print("Model provided is schema version: ");
  Serial.print(model->version());
  Serial.print("\nTensorFlow Lite Library version: ");
  Serial.println(TFLITE_SCHEMA_VERSION);

}

void loop() {

}


