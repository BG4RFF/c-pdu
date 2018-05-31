#include "ul_gsm_pdu.h"

void Decoding(void)
{
  pdu_struct packet;
  char inBuff[1024]; 
  //...fill buffer with PDU data
  
  //input data to filling pdu_struct 
  pdu_in_decode((uint8_t*)&inBuff[0], 
                        strlen(&inBuff[0]),
                        &packet);
            
  // check type SMS
  if(packet.sender.type == PDU_TYPE_INTERNATIONAL)
  {
    pdu_phone_unpack(&packet.sender.data[0], 
                    packet.sender.bytes, 
                    (uint8_t*)Str->number, 
                    packet.sender.type);
  }
  
  // check type alphadet
  if(packet.sender.type == PDU_TYPE_ALPHADET)
  {
    pdu_in_decode_text(&packet.sender.data[0],  
                      packet.sender.bytes,
                      PDU_DCS_7,
                      (uint8_t*)Str->number);
  }
  
  // decoding
  char Result[281];
  
  memset(&Result[0], 0, sizeof(Result));
  
  //fill result buffer
  pdu_in_decode_text(packet.msg.data,  
                     packet.msg.len,
                     (packet.tp_dcs == 0x00 ? PDU_DCS_7:PDU_DCS_UCS2),
                     (uint8_t*)&Result[0]);
          
  uint16_t len_msg = packet.msg.len;
          
  // correct symbol
  if(packet.tp_dcs == 0x00)
    len_msg = pdu_corr_sym_unpack_dcs7(&Temp[0], packet.msg.len);
}
