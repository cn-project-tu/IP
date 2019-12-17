int NetIpRecv(NetIpPkt * pIpPkt)      /**process all incoming packets**/
{
    unit16_t checksum;
    if(pIpPkt->ipHdr.ver_hlen != IP_VER_HLEN)    /**check IP header length and version **/
    {
        return(Error in network);
    }

    checksum = pIpPkt->ipHdr.checksum;   /**Move the IP header checksum out of the header**/
    pIpPkt->ipHdr.checksum = 0;
    
    if(checksum != NetIpChecksum((unit16_t *)pIpPkt,IP_HEADER_LEN))   /** Compute checksum and compare with the received value **/
    {
        return(Network Error);
    }
    switch(pIpPkt->ipHdr.protocol)    /** Route the packet to the appropriate layer 3 protocol **/
    {
        case PROTO_UDP:     /** Exports the required logic in order to handle UDP-based communication **/
        return(NetUdpRcv((NetUdpPkt *) pIpPkt,ntohs(pIpPkt->ipHdr.length)-IP_HEADER_LEN));

        case PROTO_TCP:
        return (NetTcpRcv((NetTcpPkt *) pIpPkt, ntohs(pIpPkt->ipHdr.length)-IP_HEADER_LEN));

        default:
        return (Network Error);    /** Unsupported protocol **/
    }
}    


