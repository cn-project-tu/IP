//hi mandeep
struct tcp_header
{
 uint16_t source_port;  //source port(16)
 unit16_t dest_port;  //Destination port(16)
 unit32_t sequ_number;  //dequence number(32)
 unit32_t ack_number; //acknowledgement number(32)
 unit8_t header_len;  //(4)header length-(4)reserved bit
 //unit3_t res; //reserved bit
 unit8_t flag_bit ;//2 bit reserved URG,ACK,PSH,RSH,SYN,FIN each are of 1 bit
 unit16_t window_size; //receiver advertise window size(16)
 unit16_t checksum;  //checksum(16) to be computed
 unit16_t urgent_pointer;//points to urgent data byte(16) if URG flag_bit set to 1

/*it may be possible option file be required */

 //unit32_t options;//option field may not be 32 so to compromise the remaining
                   //bits we can use padding
};


// we have to find what is data length
#define TCP_DATA_LEN  



//Tcp Packet
struct tcp_packet{
  struct tcp_header header;
  unit8_t data[TCP_DATA_LEN];
}
