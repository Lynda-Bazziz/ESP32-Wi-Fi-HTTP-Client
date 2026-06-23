#include <stdio.h>



#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_timer.h"
#include "freertos/timers.h"

#include "esp_wifi.h"
#include "nvs_flash.h"
#include "lwip/sys.h" //tct_stack
#include "lwip/err.h" //tcp_stack
#include "freertos/event_groups.h"
#include "esp_http_client.h"



//tcpip_adapter_init() pour initialiser le reseau
//espevent_loop_init() pour initialiser le event loop


//nvs_flash_init() //initialisation des adresse mac


EventGroupHandle_t survaillance;
                                 
    esp_err_t event_handler( void* ctx, system_event_t *event ){
                 switch (event->event_id)
                 {
                 case (SYSTEM_EVENT_STA_START):
                    printf("\n entrain de se connecter");
                    break;
                 
                case (SYSTEM_EVENT_STA_CONNECTED):
                    printf("\n connected");
                    break;

                case (SYSTEM_EVENT_STA_DISCONNECTED):
                    printf("\n connextion echouer");
                    esp_wifi_connect();
                    break;

                 case (SYSTEM_EVENT_STA_GOT_IP):
                    printf("\n entrain de se connecter");
                     xEventGroupSetBits(survaillance,1);
                    break;
                 
                 default:
                 printf("\n switch case a echouer");
                    break;
                 }

    }


void init_config (){

                            //////////1)INITIALISSATTIOONNNNNNNNN//////////

tcpip_adapter_init();
espevent_loop_init(event_handler,NULL);
    
 //initialiser l event loop

wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
esp_wifi_init(&cfg);


                           /////////////2)configuration)//////////////////////


esp_wifi_set_mode(WIFI_MODE_STA);
wifi_config_t configuration = {
   .sta={
     .ssid= "Test",
     .password = "Essai2020",
   },

};
esp_wifi_start();
SYSTEM_EVENT_STA_START;
esp_wifi_set_config(ESP_IF_WIFI_STA , &configuration);
}

void tache_utili(void* parameters){
xEventGroupWaitBits(survaillance,1,pdTRUE,pdTRUE,portMAX_DELAY);
char* ip4addr_ntoa(const ip4_addr_t * addr);

while (1)
{
       printf("Configuration réseau :\n");
        tcpip_adapter_ip_info_t ipInfo;
        tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ipInfo);
        printf("- Adresse IP : %s\n", ip4addr_ntoa(&ipInfo.ip));
        printf("- Masque de sous-réseau : %s\n", ip4addr_ntoa(&ipInfo.netmask));
        printf("- Passerelle : %s\n", ip4addr_ntoa(&ipInfo.gw));

        vTaskDelay(pdMS_TO_TICKS(2000));
}

}



esp_err_t http_handler_event (esp_http_client_event_handler_t* event){
    switch (event->eventid)
    {
    case HTTP_EVENT_ON_DATA:
        printf("je suis ici",event-eventid);
        break;
    
    default:
        break;
    }
}



void config_http_client(
esp_http_client_config_t client_config ={
    .url = "http//ipadress_serveur/get",
    .method = http_METHOD_POST,
    .event_handler = http_handler_event,
};

esp_http_client_handle_t client = esp_http_client_init(&client_config);
const char* message= "bonjour je suis connecter";
err_t var =  esp_http_client_set_post_field(client,strlen message);
if (var == ESP_OK)
{
    printf("données envoyées");
}else{
    printf("echec d envoie");
}

err_t var1 = esp_http_client_perform(client);
if (var1 == ESP_OK)
{
    printf("données envoyées");
}else{
    printf("echec d envoie");
}

esp_http_client_cleanup();

);






void app_main(void)
{
survaillance = xEventGroupCreate();
nvs_flash_init();
init_config();
xTaskCreate(survaillance,"utili",1024,NULL,4,NULL);
}
