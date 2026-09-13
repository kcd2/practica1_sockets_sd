
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char *argv[])
{
    char *servidor_ip;
    char *servidor_puerto;
    char *id_estacion;
    char *ubicacion;
    char mensaje[1024];
    char respuesta[1024];
    
    struct sockaddr_in direccion;
    int s;
    int n, enviados, recibidos;

   
    if (argc != 5)
    {
        fprintf(stderr, "Error. Faltan parametros de conexion y registro.\n");
        fprintf(stderr, "Sintaxis: %s <ip> <puerto> <id_estacion> <ubicacion>\n", argv[0]);
        fprintf(stderr, "Ejemplo : %s 127.0.0.1 9999 WS-04 \"River Park\"\n", argv[0]);
        return 1;
    }

    
    servidor_ip = argv[1];
    servidor_puerto = argv[2];
    id_estacion = argv[3];
    ubicacion = argv[4];

    
    snprintf(mensaje, sizeof(mensaje), "REGISTRO#%s#%s\n", id_estacion, ubicacion);

    printf("Intentando registrar [%s - %s] en %s:%s...\n", id_estacion, ubicacion, servidor_ip, servidor_puerto);

    /**** Paso 1: Abrir el socket ****/
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        fprintf(stderr, "Error. No se puede abrir el socket\n");
        return 1;
    }
    printf("Socket abierto\n");

    /**** Conectar al servidor ****/
    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = inet_addr(servidor_ip);
    direccion.sin_port = htons(atoi(servidor_puerto));
    
    if (connect(s, (struct sockaddr *)&direccion, sizeof (direccion)) == -1)
    {
        fprintf(stderr, "Error. No se puede conectar al servidor\n");
        close(s);
        return 1;
    }
    printf("Conexion establecida\n");

    /**** Enviar mensaje ****/
    n = strlen(mensaje);
    enviados = write(s, mensaje, n);
    if (enviados == -1 || enviados < n)
    {
        fprintf(stderr, "Error enviando la trama de registro\n");
        close(s);
        return 1;
    }
    printf("Trama enviada: %s", mensaje);

    /****  Recibir respuesta ****/
    n = sizeof(respuesta) - 1;
    recibidos = read(s, respuesta, n);
    
    /* Correccion de bug de plantilla (tenia "recibidos == 1", corregido a "== -1") */
    if (recibidos == -1)
    {
        fprintf(stderr, "Error recibiendo respuesta\n");
        close(s);
        return 1;
    }
    respuesta[recibidos] = '\0';
    printf("Respuesta de WM_Central: %s\n", respuesta);

    /**** Cerrar el socket ****/
    close(s);
    printf("Socket cerrado. Registro finalizado\n");

    return 0;
}
/*Limpié todos los retornos de carro '\r\n' de los printf/fprintf dejandolos en '\n' */