#include <TensorFlowLite.h>
#include "tensorflow/lite/experimental/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "data.h"

// Globales, utilizados para compatibilidad con Sketch de  Arduino.
namespace { 
  const tflite::Model* model = nullptr;
  
  tflite::MicroInterpreter* interpreter = nullptr;
  constexpr int kTensorArenaSize = 4 * 1024;
  uint8_t tensor_arena[kTensorArenaSize];
  tflite::ErrorReporter* error_reporter = nullptr;

  TfLiteTensor* input = nullptr;
  TfLiteTensor* output = nullptr;
}  

void setup() {
  Serial.begin(115200);

  model = tflite::GetModel(mi_data);

  /*
  Serial.print("Model provided is schema version: ");
  Serial.print(model->version());
  Serial.print("\nTensorFlow Lite Library version: ");
  Serial.println(TFLITE_SCHEMA_VERSION);
  */

  static tflite::ops::micro::AllOpsResolver resolver;
  static tflite::MicroInterpreter static_interpreter( model, 
                                                      resolver, 
                                                      tensor_arena, 
                                                      kTensorArenaSize, 
                                                      error_reporter);
                                                      
   interpreter = &static_interpreter;
   TfLiteStatus allocate_status = interpreter->AllocateTensors();


   input = interpreter->input(0);
   output = interpreter->output(0);

   int indice = 0;

   for (int u = 0; u < 15; u++) {
      input->data.f[u] = test[indice][u];
    }

   TfLiteStatus invoke_status = interpreter->Invoke();

   Serial.print(output->data.f[0]);
   Serial.print("     ");
   Serial.print(output->data.f[1]);
   Serial.print("     ");
   Serial.print(output->data.f[2]);

}



void loop() {

}


