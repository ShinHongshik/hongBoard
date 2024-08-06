#include "can_driver.h"
#include "EthernetManager.hpp"

static uint32_t canDriverAvailable(void *args);
static bool canDriverFlush(void *args);
static uint8_t canDriverRead(void *args);
static uint32_t canDriverWrite(void *args, uint8_t *p_data, uint32_t length);



static qbuffer_t* sendBufferPtr;
static qbuffer_t* recvBufferPtr;
static cmd_can_driver_t cmd_can_driver;

cmd_can_driver_t *canDriverGetPtr(void)
{
  auto socket = EthernetManager::GetInstance()->GetSocket();
  
  if ( socket )
  {
   sendBufferPtr = socket->GetSendBuffer();
   recvBufferPtr = socket->GetRecvBuffer();
  }

  cmd_can_driver.available  = canDriverAvailable;
  cmd_can_driver.flush      = canDriverFlush;
  cmd_can_driver.read       = canDriverRead;
  cmd_can_driver.write      = canDriverWrite;

  return &cmd_can_driver;
}

uint32_t canDriverAvailable(void *args)
{
  if(recvBufferPtr)
    return qbufferAvailable(recvBufferPtr);
  else 
    return 0;
}

bool canDriverFlush(void *args)
{
  if ( recvBufferPtr ) {
    qbufferFlush(recvBufferPtr);
  } 
  return true;
}

uint8_t canDriverRead(void *args)
{
  uint8_t ret;

  if ( recvBufferPtr ) {
    qbufferRead(recvBufferPtr, &ret , 1); 
  }

  return ret; 
}

uint32_t canDriverWrite(void *args, uint8_t *p_data, uint32_t length)
{
  int ret = 0;
  if ( sendBufferPtr == nullptr ) return 0;

  if ( EthernetManager::GetInstance()->IsAssignedIP()) {
    if ( qbufferWrite(sendBufferPtr, p_data, length) == true ){
      ret = length;
    }
  }
  if ( ret < 0 ) ret = 0;

  return ret;
}