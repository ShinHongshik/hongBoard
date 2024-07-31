#include "ap.h"
#include "EthernetManager.hpp"

static void cliThread(void *args);


static bool is_init = false;
void EthernetLoopBack(void);
#if 0

#include "wizchip_conf.h"
#include "w5x00_spi.h"

// #include "port_common.h"


#include "dhcp.h"
#include "sntp.h"
#include "timer.h"

#include "tftp.h"

/**
 * ----------------------------------------------------------------------------------------------------
 * Macros
 * ----------------------------------------------------------------------------------------------------
 */
/* Clock */
#define PLL_SYS_KHZ (133 * 1000)

/* Buffer */
#define ETHERNET_BUF_MAX_SIZE (1024 * 2)

/* Socket */
#define SOCKET_SNTP 0

/* Timeout */
#define RECV_TIMEOUT (1000 * 10) // 10 seconds

/* Timezone */
#define TIMEZONE 40 // Korea

/* Network */
static wiz_NetInfo g_net_info =
{
  .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
  .ip = {192, 168, 0, 88},                     // IP address
  .sn = {255, 255, 255, 0},                    // Subnet Mask
  // .gw = {192, 168, 0, 1},                     // Gateway
  .gw = {192, 168, 0, 1},                     // Gateway
  .dns = {8, 8, 8, 8},                         // DNS server
  .dhcp = NETINFO_STATIC                       // DHCP enable/disable
};
/* Buffer */
#define ETHERNET_BUF_MAX_SIZE (1024 * 2)

/* Socket */

#define SOCKET_DHCP 0
#define SOCKET_DNS 1
#define SOCKET_TFTP 0

/* Retry count */
#define DHCP_RETRY_COUNT 5
#define DNS_RETRY_COUNT 5
/* SNTP */
static uint8_t g_sntp_buf[ETHERNET_BUF_MAX_SIZE] = {
    0,
};
static uint8_t g_sntp_server_ip[4] = {216, 239, 35, 0}; // time.google.com
static uint8_t g_ethernet_buf[ETHERNET_BUF_MAX_SIZE] = {
    0,
}; // common buffer

static uint8_t tftp_server[4] = {192,168,0,22};


/* Timer */
static volatile uint32_t g_msec_cnt = 0;

/* DHCP */
static void wizchip_dhcp_init(void)
{
    printf(" DHCP client running\n");

    DHCP_init(SOCKET_DHCP, g_ethernet_buf);

    // reg_dhcp_cbfunc(wizchip_dhcp_assign, wizchip_dhcp_assign, wizchip_dhcp_conflict);
}




static uint8_t g_socket_rcv_buf[MAX_MTU_SIZE];
/**
 * ----------------------------------------------------------------------------------------------------
 * Functions
 * ----------------------------------------------------------------------------------------------------
 */
/* Clock */
// static void set_clock_khz(void);

/* Timer  */
static void repeating_timer_callback(void);
// static time_t millis(void);

#endif
void apInit(void)
{
  cliOpen(_DEF_UART1, 115200);
  uartOpen(_DEF_UART2, 115200);


#if ( FREERTOS_USE == 1 )
  xTaskCreate(cliThread, "cliThread", _HW_DEF_RTOS_THREAD_MEM_CLI , NULL , _HW_DEF_RTOS_THREAD_PRI_CLI , NULL );
#endif

#ifdef _USE_HW_CLI
  // cliAdd("test", cliTest);
#endif
}
uint8_t g_tftpInitEnable = 1;
void apMain(void)
{
  static volatile uint8_t cnttttt = 0;
  while(true)
  {
    cliMain();    
    if ( g_tftpInitEnable )
    {
      cnttttt++;
      if ( cnttttt  > 200 )
      {
        // tftp_timeout_handler();
        cnttttt = 0;
      }
    }
    delay(5);
  }
}

static void cliThread(void *args)
{
#if 0
  uint32_t start_ms = 0;
  uint8_t retval = 0;
  static datetime time;
  uint32_t tftp_server_s;
  uint8_t* filename = (uint8_t*)"CatTerm 3.0.exe";
  int once =1;
  int ret;
  delay(3500);
  ledOn(0);
  // set_clock_khz();
  wizchip_spi_initialize();
  wizchip_cris_initialize();
  
  wizchip_reset();
  wizchip_initialize();
  wizchip_check();
  // wizchip_1ms_timer_initialize(repeating_timer_callback);

  // if ( g_net_info.dhcp == NETINFO_DHCP )
  // {
  //   wizchip_dhcp_init();
  // }
  // else 
  // {
  network_initialize(g_net_info);
  // cliPrintf("network_initialize ok\r\n");
  // }

  // SNTP_init(SOCKET_SNTP, g_sntp_server_ip, TIMEZONE, g_sntp_buf);

  TFTP_init(SOCKET_TFTP, g_socket_rcv_buf);
  // TFTP_init(0, g_socket_rcv_buf);
  // cliPrintf("sock init ok\r\n");
  // tftp_server_s = ( tftp_server[0] << 24) | (tftp_server[1] << 16) | (tftp_server[2] << 8) | tftp_server[3];
  // TFTP_read_request(tftp_server_s,  filename);

  // cliPrintf("TFTP_read_request\r\n");

  /* Get network information */
  print_network_information(g_net_info);

  start_ms = millis();


  tftp_server_s = ( tftp_server[0] << 24) | (tftp_server[1] << 16) | (tftp_server[2] << 8) | tftp_server[3];
  TFTP_read_request(tftp_server_s,  filename);
  
#endif
  uint32_t pre_time = 0 ;
  uint8_t t1= 0;

  EthernetManager::InitInstance(MAC_ADDRESS, DHCP_ENABLED);
  EthernetManager::GetInstance()->AddSocket(std::make_shared<EventSocket>(SOCKET_PORT_DEFAULT, SocketMode::UDP_PEER));

  is_init = true;

  while(true)
  {
    #if 0
    // SNTP_run(&time);
    // while(1) {
    if ( once == 1 )
    {
      while(1)
      {
        // set_server_ip(tftp_server_s);
        
        ret = TFTP_run();
        if ( ret != TFTP_PROGRESS )
        {
          if ( ret == TFTP_SUCCESS)
          {
            once = 0;
            cliPrintf("****************************************** ret =%d \r\n", ret);
            break;
          }
        }
        delay(5);
      }
    }
    #endif
    EthernetManager::GetInstance()->Run();
    if (millis() - pre_time >= 500) {
      AP_LOGGER_PRINT("running EthernetManager\r\n");
      pre_time = millis();
      ledToggle(0);
    }

    delay(100);

    if (EthernetManager::GetInstance()->IsAssignedIP()) {
        EthernetLoopBack();
        if (!t1 )
        {
          cliPrintf("IP %d.%d.%d.%d\r\n", EthernetManager::GetInstance()->GetIPAddress()[0],
                  EthernetManager::GetInstance()->GetIPAddress()[1], EthernetManager::GetInstance()->GetIPAddress()[2],
                  EthernetManager::GetInstance()->GetIPAddress()[3]);
          t1 = 1;
        }
    }

  }
}

void EthernetLoopBack(void) {
  if (EthernetManager::GetInstance()->IsAssignedIP()) {
    auto socket = EthernetManager::GetInstance()->GetSocket();
    if (socket) {
      qbuffer_t* sendBufferPtr = socket->GetSendBuffer();
      qbuffer_t* recvBufferPtr = socket->GetRecvBuffer();

      uint32_t recvSize = qbufferAvailable(recvBufferPtr);
      if (recvSize > 0) {
        uint8_t tempBuffer[recvSize];
        qbufferRead(recvBufferPtr, tempBuffer, recvSize);
        cliPrintf("recv %d bytes\r\n", recvSize);

        if (qbufferWrite(sendBufferPtr, tempBuffer, recvSize) == false) {
          cliPrintf("send buffer full\r\n");
        }
      }
    }
  }
}



volatile unsigned long tickHookCnt;

void vApplicationTickHook(void)
{
  tickHookCnt++;
}


/* Timer */
#if 0 
static void repeating_timer_callback(void)
{
    g_msec_cnt++;
}
#endif

