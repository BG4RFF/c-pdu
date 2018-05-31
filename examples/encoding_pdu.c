#include "ul_gsm_pdu.h"

void Encoding(void)
{
  char Number[10] = {'1','2','3','4','5','6','7','8','9',0};
  char Str[11] = {'h','e','l','l','o',' ','w','o','r','d',0};
  uint8_t OutBuff[281];
  pdu_struct packet;
          
  memset(&OutBuff[0], 0, sizeof(OutBuff));
        
  pdu_out_encode_simple(&packet, &OutBuff[0], &Number[0], &Str[0], 0);
}
