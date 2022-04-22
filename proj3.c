#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t task_send_Handle = NULL;
TaskHandle_t task_receive_Handle = NULL;
QueueHandle_t queue;

void task_send(void *arg)
{
   char string_send[9];
   sprintf(string_send, "data 1");
   xQueueSend(queue, (void *)string_send, pdMS_TO_TICKS(100));
   printf("Send:  %s \n", string_send);

   sprintf(string_send, "data 2");
   xQueueSend(queue, (void *)string_send, pdMS_TO_TICKS(100));
   printf("Send:  %s \n", string_send);

   sprintf(string_send, "data 3");
   xQueueSend(queue, (void *)string_send, pdMS_TO_TICKS(100));
   printf("Send:  %s \n\n", string_send);

   while (1)
   {
      vTaskDelay(pdMS_TO_TICKS(1000));
   }
}

void task_receive(void *arg)
{
   char string_receive[9];
   while (1)
   {
      if ( xQueueReceive(queue, &(string_receive), pdMS_TO_TICKS(100)) ){
         printf("Received:  %s \n", string_receive);
      }
   }
}

void app_main()
{
   // Queue creation
   queue = xQueueCreate(5, 10);

   // Available
   printf("\nAvailable at the begining: %d \n\n", uxQueueSpacesAvailable(queue));

   // Write data to queue
   xTaskCreate(task_send, "task_send", 4096, NULL, 10, &task_send_Handle);
   vTaskDelay(pdMS_TO_TICKS(1000));
   
   // Available
   printf("Available after writing: %d \n\n", uxQueueSpacesAvailable(queue));

   // Read data from queue
   xTaskCreate(task_receive, "task_receive", 4096, NULL, 10, &task_receive_Handle);
   vTaskDelay(pdMS_TO_TICKS(1000));
   
   // Available
   printf("\nAvailable at the end: %d \n\n", uxQueueSpacesAvailable(queue));
}