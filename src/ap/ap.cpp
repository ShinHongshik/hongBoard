#include "ap.h"

static void cliThread(void *args);


#include "wizchip_conf.h"
#include "w5x00_spi.h"

// #include "port_common.h"

#include "dhcp.h"
#include "sntp.h"
#include "timer.h"


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
  .gw = {192, 168, 0, 1},                     // Gateway
  .dns = {8, 8, 8, 8},                         // DNS server
  .dhcp = NETINFO_STATIC                       // DHCP enable/disable
};
/* Buffer */
#define ETHERNET_BUF_MAX_SIZE (1024 * 2)

/* Socket */
#define SOCKET_DHCP 0
#define SOCKET_DNS 1

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
/* Timer */
static volatile uint32_t g_msec_cnt = 0;

/* DHCP */
static void wizchip_dhcp_init(void)
{
    printf(" DHCP client running\n");

    DHCP_init(SOCKET_DHCP, g_ethernet_buf);

    // reg_dhcp_cbfunc(wizchip_dhcp_assign, wizchip_dhcp_assign, wizchip_dhcp_conflict);
}
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

void apMain(void)
{
  while(true)
  {
    cliMain();    
    delay(5);
  }
}

static void cliThread(void *args)
{
  uint32_t start_ms = 0;
  uint8_t retval = 0;
  static datetime time;
#if 1
  delay(5000);
  ledOn(0);
  // set_clock_khz();
  wizchip_spi_initialize();
  wizchip_cris_initialize();

  wizchip_reset();
  wizchip_initialize();
  wizchip_check();
  // wizchip_1ms_timer_initialize(repeating_timer_callback);
  if ( g_net_info.dhcp == NETINFO_DHCP )
  {
    wizchip_dhcp_init();
  }
  else 
  {
    network_initialize(g_net_info);
  }

  SNTP_init(SOCKET_SNTP, g_sntp_server_ip, TIMEZONE, g_sntp_buf);

  /* Get network information */
  print_network_information(g_net_info);

  start_ms = millis();
#endif

  while(true)
  {
    SNTP_run(&time);
    ledToggle(0);
    cliPrintf(" %d-%d-%d, %d:%d:%d\r\n", time.yy, time.mo, time.dd, time.hh, time.mm, time.ss);
    delay(100);
  }
}

volatile unsigned long tickHookCnt;

void vApplicationTickHook(void)
{
  tickHookCnt++;
}


/* Timer */
static void repeating_timer_callback(void)
{
    g_msec_cnt++;
}

