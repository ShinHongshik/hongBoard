#include "hw.h"

volatile const firm_ver_t firm_ver __attribute__((section(".version"))) = 
{
  .magic_number = VERSION_MAGIC_NUMBER,
  .version_str  = _DEF_FIRMWATRE_VERSION,
  .name_str     = _DEF_BOARD_NAME,
};

bool hwInit(void)
{
  bspInit();
  ledInit();
  cliInit();
  resetInit();
  i2cInit();

  flashInit();
  uartInit();

  return true;
}