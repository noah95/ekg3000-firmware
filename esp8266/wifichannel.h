/*
   EKG3000 - Copyright (C) 2016 FHNW Project 3 Team 2
 */

/**
 * @file       wifichannel.h
 * @brief      handels the differenc TCP/UDP channels of the esp module
 * @details    Source: https://github.com/vpcola/MikroChibiOS
 * @author     Noah Huetter (noahhuetter@gmail.com)
 * @date       1 December 2016
 * 
 *
 * @addtogroup WIFICHANNEL
 * @{
 */

#ifndef __WIFICHANNEL_H__
#define __WIFICHANNEL_H__

/**
 * Author : Cola Vergil
 * Email  : vpcola@gmail.com
 * Date : Thu Feb 12 2015
 **/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#include "hal.h"
#include "ch.h"
#include "esp8266.h"

/**
 *  Since ESP8266 can accomodate only 4
 * different connections. We manage only
 * a static list of 4 ring buffers each
 * for receive and send
 **/
#define MAX_CONNECTIONS 1

enum wifiModes {
      WIFI_MODE_STA = 1,
      WIFI_MODE_AP,
      WIFI_MODE_APSTA
};

#define IPADDR_MAX_SIZ 100
typedef struct {
   int id; 
   int type;
   int status;
   bool ispassive; // affects how we read from the channel
   char ipaddress[IPADDR_MAX_SIZ]; // can be a string
   uint16_t port;
   char localaddress[IPADDR_MAX_SIZ];
   uint16_t localport;  // Used for binding localport to socket
   bool isservergenerated;
   input_queue_t * iqueue;
   int usecount;
} esp_channel_t;

typedef enum {
    CHANNEL_UNUSED = 0,
    CHANNEL_CONNECTED = 1,
    CHANNEL_DISCONNECTED = 2
} esp_channel_status;

enum {
  CMD_SEND,
  CMD_SENDTO,
  CMD_RECVFROM
};

typedef struct {
  int cmd;
  int channel;
  int numbytes;
} esp_channel_cmd;

esp_channel_t * getChannel(int d);

int wifiInit(void);
bool wifiHasIP(void);


//int wifiInit(int mode, SerialDriver * usart, SerialDriver * dbg);
int wifiConnectAP(const char * ssid, const char * password);

// Channel open returns an unused, empty channel
int channelOpen(int conntype);

// Send and receive
//int channelPrint(int channel, const char * format, ...);
bool channelSendLine(int channel, const char * msg);
int channelSend(int channel, const void * msg, int msglen);
int channelSendTo(int channel, const char * msg, int msglen, const char * ipaddress, uint16_t port);
int channelRead(int channel, char * buff, int msglen);
int channelReadLine(int channel, char * buff, int buflen);
int channelGet(int channel);

// Connect the channel to tcp or udp connection
int channelConnect(int channel, const char * ipddress, uint16_t port);
bool channelIsConnected(int channel);
// Start a server connection on the channel
int channelServer(int channel, int type, uint16_t port);

// Closes the channel
int channelClose(int channel);

void channelStatus(BaseSequentialStream *chp);
bool channelSetCipmux (void);

#ifdef __cplusplus
}
#endif

#endif


/** @} */