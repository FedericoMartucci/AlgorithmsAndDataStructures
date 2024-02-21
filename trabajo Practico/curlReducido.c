#include "curlReducido.h"

// Función que maneja la respuesta de la solicitud HTTP

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t realsize = size * nmemb;
    //printf("imprime dato: %.*s", (int)realsize, (char *)contents);        //aca se imprime el contenido
    return realsize;
}

int cargarCurl(CURL** curl, char* x_secret)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    *curl = curl_easy_init();
    if(curl == NULL)
        return NO_PUDO_CARGAR;

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, x_secret); //cambiar por su codigo
    curl_easy_setopt(*curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(*curl, CURLOPT_SSL_VERIFYPEER, 0L);        // Establecer la función de retorno de llamada para manejar la respuesta
    curl_easy_setopt(*curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    return TODO_OK;
}

int verificarConectividad(CURL** curl){
    CURLcode res;
    char url[100] = "https://www.google.com.ar";
    curl_easy_setopt(*curl, CURLOPT_URL, url);
    res = curl_easy_perform(*curl); //primero esto
    if(res != CURLE_OK)
        return ERROR_SOLICITUD;
    return TODO_OK;
}

int enviarPalabra(CURL** curl, char* palabra)
{
    CURLcode res;
    char url[100] = "https://api.pons.com/v1/dictionary?l=dees&q=";
    strcat(url, palabra);
    //printf("URL:%s\n",url);
    curl_easy_setopt(*curl, CURLOPT_URL, url);

    res = curl_easy_perform(*curl); //primero esto

    if (res != CURLE_OK)
    {
        fprintf(stderr, "***Error en la solicitud: %s\n***", curl_easy_strerror(res));
        return ERROR_SOLICITUD;
    }

    return TODO_OK;
}

int obtenerRespuestaPalabra(CURL** curl)
{
    long http_code;
    curl_easy_getinfo(*curl, CURLINFO_RESPONSE_CODE, &http_code);
    //printf("\nCodigo de estado HTTP: %ld\n", http_code);
    return http_code;
}

void liberarCurl(CURL** curl)
{
    if(*curl == NULL)
        return;
    curl_easy_cleanup(*curl);    // Limpiar y cerrar el manejo de curl
    curl_global_cleanup();      // Finalizar el manejo global de curl
}
