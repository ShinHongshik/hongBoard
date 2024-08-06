

#include "cmd_can.h"
#ifdef _USE_HW_CLI
  #include "cli.h"
#endif

#define CMD_CAN_STX0             0x02
#define CMD_CAN_STX1             0xFD


// typedef enum
// {
//   CMD_CAN_STATE_WAIT_STX0,
//   CMD_CAN_STATE_WAIT_STX1,
//   CMD_CAN_STATE_WAIT_TYPE,
//   CMD_CAN_STATE_WAIT_CMD_L,
//   CMD_CAN_STATE_WAIT_CMD_H,
//   CMD_CAN_STATE_WAIT_ERR_L,
//   CMD_CAN_STATE_WAIT_ERR_H,
//   CMD_CAN_STATE_WAIT_LENGTH_L,
//   CMD_CAN_STATE_WAIT_LENGTH_H,
//   CMD_CAN_STATE_WAIT_DATA,
//   CMD_CAN_STATE_WAIT_CHECKSUM
//   // CMD_CAN_STATE_WAIT_CRC,
//   // CMD_CAN_STATE_WAIT_ETX
// } CmdCanState_t;

#define CMD_CAN_STATE_WAIT_STX0         0
#define CMD_CAN_STATE_WAIT_STX1         1
#define CMD_CAN_STATE_WAIT_TYPE         2
#define CMD_CAN_STATE_WAIT_CMD_L        3
#define CMD_CAN_STATE_WAIT_CMD_H        4
#define CMD_CAN_STATE_WAIT_ERR_L        5
#define CMD_CAN_STATE_WAIT_ERR_H        6
#define CMD_CAN_STATE_WAIT_LENGTH_L     7
#define CMD_CAN_STATE_WAIT_LENGTH_H     8
#define CMD_CAN_STATE_WAIT_DATA         9
#define CMD_CAN_STATE_WAIT_CHECKSUM     10



void cmdCanInit(cmd_can_t *p_cmd , cmd_can_driver_t *p_driver)
{
  p_cmd->is_open    = false;
  p_cmd->p_driver   = p_driver;
  // p_cmd->state      = CMD_CAN_STATE_WAIT_STX;
  p_cmd->state      = CMD_CAN_STATE_WAIT_STX0;

  // p_cmd->packet.data    = &p_cmd->rx_packet.buffer[CMD_CAN_STATE_WAIT_DATA];
  // p_cmd->rx_packet.data = &p_cmd->rx_packet.buffer[CMD_CAN_STATE_WAIT_DATA];
  // p_cmd->tx_packet.data = &p_cmd->tx_packet.buffer[CMD_CAN_STATE_WAIT_DATA];
  p_cmd->packet.data    = &p_cmd->packet.buffer[CMD_CAN_STATE_WAIT_DATA];

  p_cmd->is_init = true;
}

bool cmdCanOpen(cmd_can_t *p_cmd)
{
  cmd_can_driver_t *p_drver = p_cmd->p_driver;

  if ( p_drver == NULL)
    return false;

  // if ( p_drver->open(p_drver->args) == true)
  // {
  //   p_cmd->is_open = true;
  // }
  // else 
  // {
  //   p_cmd->is_open = false;
  // }
  p_cmd->is_open = true;

  p_cmd->state = CMD_CAN_STATE_WAIT_STX0;
  p_cmd->pre_time = millis();

  return true;
}

bool cmdCanClose(cmd_can_t* p_cmd)
{
  bool ret;
  cmd_can_driver_t *p_driver = p_cmd->p_driver;

  if(p_driver == NULL)
    return false;

  ret = p_driver->close(p_driver->args);
  p_cmd->is_open = false;
  return ret;
}

// bool cmdCanIsBusy(cmd_can_t *p_cmd)
// {
//   return p_cmd->p_driver->available();
// }

bool cmdCanReceivePacket(cmd_can_t *p_cmd)
{
 bool ret = false;
  uint8_t rx_data;
  cmd_can_driver_t *p_driver = p_cmd->p_driver;

  if (p_cmd->is_open != true) return false;

  while(ret != true && p_driver->available(p_driver->args) > 0)
  {
    rx_data = p_driver->read(p_driver->args);

    if (millis()-p_cmd->pre_time >= 100)
    {
      p_cmd->state = CMD_CAN_STATE_WAIT_STX0;
    }
    p_cmd->pre_time = millis();

    switch(p_cmd->state)
    {
      case CMD_CAN_STATE_WAIT_STX0:
        if (rx_data == CMD_CAN_STX0)
        {
          p_cmd->packet.check_sum = 0;
          p_cmd->state = CMD_CAN_STATE_WAIT_STX1;
          p_cmd->packet.check_sum += rx_data;
        }
        break;

      case CMD_CAN_STATE_WAIT_STX1:
        if (rx_data == CMD_CAN_STX1)
        {
          p_cmd->state = CMD_CAN_STATE_WAIT_TYPE;
          p_cmd->packet.check_sum += rx_data;
        }
        else
        {
          p_cmd->state = CMD_CAN_STATE_WAIT_STX0;
        }
        break;

      case CMD_CAN_STATE_WAIT_TYPE:
        p_cmd->packet.type = (CmdCanType_t)rx_data;
        p_cmd->packet.check_sum += rx_data;
        p_cmd->state = CMD_CAN_STATE_WAIT_CMD_L;
        break;

      case CMD_CAN_STATE_WAIT_CMD_L:
        p_cmd->packet.cmd = rx_data;
        p_cmd->packet.check_sum += rx_data;
        p_cmd->state = CMD_CAN_STATE_WAIT_CMD_H;
        break;

      case CMD_CAN_STATE_WAIT_CMD_H:
        p_cmd->packet.cmd |= (rx_data << 8);
        p_cmd->packet.check_sum += rx_data;
        p_cmd->state = CMD_CAN_STATE_WAIT_ERR_L;
        break;

      case CMD_CAN_STATE_WAIT_ERR_L:
        p_cmd->packet.err_code = rx_data;
        p_cmd->packet.check_sum += rx_data;
        p_cmd->state = CMD_CAN_STATE_WAIT_ERR_H;
        break;

      case CMD_CAN_STATE_WAIT_ERR_H:
        p_cmd->packet.err_code |= (rx_data << 8);
        p_cmd->packet.check_sum += rx_data;
        p_cmd->state = CMD_CAN_STATE_WAIT_LENGTH_L;
        break;

      case CMD_CAN_STATE_WAIT_LENGTH_L:
        p_cmd->packet.length = rx_data;
        p_cmd->packet.check_sum += rx_data;
        p_cmd->state = CMD_CAN_STATE_WAIT_LENGTH_H;
        break;

      case CMD_CAN_STATE_WAIT_LENGTH_H:
        p_cmd->packet.length |= (rx_data << 8);
        p_cmd->packet.check_sum += rx_data;

        if (p_cmd->packet.length > 0)
        {
          if (p_cmd->packet.length <= CMD_CAN_MAX_DATA_LENGTH)
          {
            p_cmd->index = 0;
            p_cmd->state = CMD_CAN_STATE_WAIT_DATA;
          }
          else
          {
            p_cmd->packet.err_code = ERR_CMD_MAX_LENGTH;
            p_cmd->state = CMD_CAN_STATE_WAIT_STX0;
            ret = true;
          }
        }
        else
        {
          p_cmd->state = CMD_CAN_STATE_WAIT_CHECKSUM;
        }
        break;

      case CMD_CAN_STATE_WAIT_DATA:
        p_cmd->packet.data[p_cmd->index] = rx_data;
        p_cmd->packet.check_sum += rx_data;
        p_cmd->index++;
        if (p_cmd->index == p_cmd->packet.length)
        {
          p_cmd->state = CMD_CAN_STATE_WAIT_CHECKSUM;
        }
        break;

      case CMD_CAN_STATE_WAIT_CHECKSUM:
        p_cmd->packet.check_sum_recv = rx_data;
        p_cmd->packet.check_sum = (~p_cmd->packet.check_sum) + 1;
        if (p_cmd->packet.check_sum != p_cmd->packet.check_sum_recv)
        {
          p_cmd->packet.err_code = ERR_CMD_CHECKSUM;
        }
        ret = true;
        p_cmd->state = CMD_CAN_STATE_WAIT_STX0;
        break;
    }
  }

  return ret;
}



// bool cmdCanSend(cmd_can_t *p_cmd, CmdCanType_t type, CmdCanCmd_t cmd, uint8_t *p_data, uint32_t length)
bool cmdCanSend(cmd_can_t *p_cmd, CmdCanType_t type, uint16_t cmd, uint16_t err_code, uint8_t *p_data, uint32_t length)
{
  uint32_t index;
  cmd_can_driver_t *p_driver = p_cmd->p_driver;
  uint32_t data_len;
  uint32_t wr_len;

  if (p_cmd->is_open != true) return false;

  data_len = length;

  index = 0;
  p_cmd->packet.buffer[index++] = CMD_CAN_STX0;
  p_cmd->packet.buffer[index++] = CMD_CAN_STX1;
  p_cmd->packet.buffer[index++] = type;
  p_cmd->packet.buffer[index++] = (cmd >> 0) & 0xFF;
  p_cmd->packet.buffer[index++] = (cmd >> 8) & 0xFF;
  p_cmd->packet.buffer[index++] = (err_code >> 0 ) & 0xFF;
  p_cmd->packet.buffer[index++] = (err_code >> 8 ) & 0xFF;;
  p_cmd->packet.buffer[index++] = (data_len >> 0 ) & 0xFF;
  p_cmd->packet.buffer[index++] = (data_len >> 8 ) & 0xFF;

  for (int i=0; i<data_len; i++)
  {
    p_cmd->packet.buffer[index++] = p_data[i];
  }

  uint8_t check_sum = 0;
  for (int i=0; i<index; i++)
  {
    check_sum += p_cmd->packet.buffer[i];
  }
  check_sum = (~check_sum) + 1;
  p_cmd->packet.buffer[index++] = check_sum;

  wr_len = p_driver->write(p_driver->args, p_cmd->packet.buffer, index);

  if (wr_len == index)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool cmdCanSendType(cmd_can_t *p_cmd, CmdCanType_t type, uint8_t *p_data, uint32_t length)
{
  bool ret;

  ret = cmdCanSend(p_cmd, type, 0, 0, p_data, length);
  return ret;
}

bool cmdCanSendCmd(cmd_can_t *p_cmd, uint16_t cmd, uint8_t *p_data, uint32_t length)
{
  bool ret;

  ret = cmdCanSend(p_cmd, PKT_TYPE_CMD, cmd, 0, p_data, length);
  return ret;
}

bool cmdCanSendResp(cmd_can_t *p_cmd, uint16_t cmd, uint16_t err_code, uint8_t *p_data, uint32_t length)
{
  bool ret;

  ret = cmdCanSend(p_cmd, PKT_TYPE_RESP, cmd, err_code, p_data, length);
  return ret;
}

bool cmdCanSendCmdRxResp(cmd_can_t *p_cmd, uint16_t cmd, uint8_t *p_data, uint32_t length, uint32_t timeout)
{
  bool  ret = false;
  uint32_t time_pre;


  cmdCanSendCmd(p_cmd, cmd, p_data, length);

  time_pre = millis();

  while(1)
  {
    if (cmdCanReceivePacket(p_cmd) == true)
    {
      ret = true;
      break;
    }

    if (millis()-time_pre >= timeout)
    {
      p_cmd->packet.err_code = ERR_CMD_RX_TIMEOUT;
      ret = true;
      break;
    }
  }

  return ret;
}