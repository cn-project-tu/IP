//hi mandeep
struc tcp_header
{
 uint16_t source_port;  //source port
 unit16_t dest_port;  //Destination port
 unit32_t sequ_number;  //dequence number
 unit32_t ack_number; //acknowledgement number
 unit4_t data_off;  //data offset
 unit3_t res; //reserved bit
 unit1_t ns;  //flag-explicit congestion notification signaling
 unit1_t cwr;
 unit1_t ece;
 unit1_t urg;
 unit1_t ack;
 unit1_t psh;
 unit1_t rst;
 unit1_t syn;
 unit1_t fin;
 unit16_t window_size;
 unit16_t checksum;
 unit16_t urgent_pointer;
 unit32_t options;//option field may not be 32 so to compromise the remaining
                   //bits we can use padding
};
