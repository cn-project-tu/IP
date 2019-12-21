int NetIpSnd(NetIpPkt * pIpPkt, uint16_t len) 
{ //Function to send ip packets

    uint16_t ident; 

    //Assign a unique ID to the outgoing packet. 
     
    // Enter critical section here. 
    ident = gNextPacketID++; 
    // Leave critical section here. 

    //Fill in the remaining IP header fields.(Some fields were pre-filled by the UDP layer.) 
    pIpPkt->ipHdr.ver_hlen = IP_VER_HLEN; 
    pIpPkt->ipHdr.service = 0x00; 
    pIpPkt->ipHdr.length = htons(len); 
    pIpPkt->ipHdr.ident = htons(ident); 
    pIpPkt->ipHdr.fragment = 0x00; 
    pIpPkt->ipHdr.timetolive = 0x10; 

    //Compute and fill in the IP header checksum. 
    pIpPkt->ipHdr.checksum = NetIpChecksum((INT16U *) pIpPkt, IP_HEADER_LEN); 

    //Forward the IP packet to the network interface driver.  
    return (NetPhySnd(htons(PROTO_IP), (uint8_t *) pIpPkt, len)); 

}
