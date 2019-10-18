//hi mandeep
struct tcp_header
{
 uint16_t source_port;  //source port
 unit16_t dest_port;  //Destination port
 unit32_t sequ_number;  //dequence number
 unit32_t ack_number; //acknowledgement number
 unit8_t dataoff_res;  //(1)data offset-(2)reserved bit
 //unit3_t res; //reserved bit
 unit8_t flag_bit ;
 unit16_t window_size;//receiver advertise window
 unit16_t checksum;//to be computed
 unit16_t urgent_pointer;//points to urgent data byte if URG flag_bit set to 1
 unit32_t options;//option field may not be 32 so to compromise the remaining
                   //bits we can use padding
};
