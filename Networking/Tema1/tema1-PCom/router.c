#include "queue.h"
#include "skel.h"

int checkBroadcast(uint8_t* dhost) {
	int ret = 1;

	for(int i = 0; i < 6; i++) {
		if (dhost[i] != 0xFF) {
			ret = 0;
		}
	}

	return ret;
}

int checkMac(uint8_t* ha1, uint8_t* ha2) {
	int ret = 1;

	for(int i = 0; i < 6; i++) {
		if (ha1[i] != ha2[i]) {
			ret = 0;
		}
	}

	return ret;
}

// Introducem un nou entry in cache
void insertCache(struct arp_entry *arpCache, int* size, struct arp_header* arpHeader)
{
	int i = *size;

    arpCache[i].ip = (arpHeader->spa);
    for (int j = 0; j < 6; j++)
        arpCache[i].mac[j] = arpHeader->sha[j];

 
    (*size)++;
}


// Cautam entry-ul din cache ce contine ip-ul dorit
// in caz ca acesta nu este gasit, intoarcem -1.
int searchCache(struct arp_entry *arpCache, int size, uint32_t ipaddr)
{
    
    for (int i = 0; i < size; i++) {
		if (arpCache[i].ip == ipaddr) {
			return i;
		}
    }
    
    return -1;
}

// Functie de comparare pentru qsort (tabela de routare)
int compare(const void* a, const void* b) {
	
	//Tabela trebuie soratata in functie de prefix, dupa care in fucntie de masca
	if((*(struct route_table_entry*)a).prefix != (*(struct route_table_entry*)b).prefix) {
		return (*(struct route_table_entry*)a).prefix - (*(struct route_table_entry*)b).prefix;
	} else {
		return (*(struct route_table_entry*)a).mask - (*(struct route_table_entry*)b).mask;
	}

}

// Functie pentru cautarea binara recursiva.
int binarySearch(int left, int right, uint32_t dest_ip, struct route_table_entry* rtable) {

	if(left <= right){

		int mid = (left+right)/2;
		if(rtable[mid].prefix == (rtable[mid].mask & dest_ip)) {
			return mid;
		} else if (rtable[mid].prefix > (rtable[mid].mask & dest_ip)){
			binarySearch(left, mid-1, dest_ip, rtable);
		} else {
			binarySearch(mid+1, right, dest_ip, rtable);
		}
	}

	return -1;
}
// Intoarce un pointer pentru best matching route.
struct route_table_entry *get_best_route(struct route_table_entry* rtable, uint32_t dest_ip, int rtable_len) {

	// Folosesc cautare binara pe o tabela sortata
	struct route_table_entry* entry = NULL;
	
	int i = binarySearch(0, rtable_len, dest_ip, rtable);
	for (int j = i; j < rtable_len; j++){
		if((dest_ip & rtable[j].mask) == rtable[j].prefix){
			if(entry == NULL || (entry->mask < rtable[j].mask)) {
				entry = &rtable[j];
			}
		}
	}

	return entry;
}

void generateArp(struct arp_header* arp_hdr, uint32_t spa, uint32_t tpa, uint8_t* tha, uint8_t* sha, uint16_t op) {
	arp_hdr->htype = htons(1);
	arp_hdr->ptype = htons(2048);
	arp_hdr->hlen = 6;
	arp_hdr->plen = 4;
	arp_hdr->op = op;
	
	arp_hdr->spa = spa;
	arp_hdr->tpa = tpa;

	memcpy(arp_hdr->tha, tha, 6);
	memcpy(arp_hdr->sha, sha, 6);
}

void generateEthHeader(struct ether_header *ethHeader, int interface, uint8_t* dhost, uint16_t type) {
	get_interface_mac(interface, ethHeader->ether_shost);
	memcpy(ethHeader->ether_dhost, dhost, 6);
	ethHeader->ether_type = type;
}

void sendArpPacket(struct ether_header* ethHeader, struct arp_header* arp_hdr, int interface) {
	packet p;
	memset(p.payload, 0, MAX_LEN);
	memcpy(p.payload, ethHeader, sizeof(struct ether_header));
	memcpy(p.payload + sizeof(struct ether_header), arp_hdr, sizeof(struct arp_header));
	p.len = sizeof(struct ether_header) + sizeof(struct arp_header);
	p.interface = interface;

	// Trimitem pachetul
	send_packet(&p);
}

void generateIpv4(struct iphdr* iph, uint32_t daddr, uint32_t saddr) {

	iph->version = 4;
	iph->ihl = 5;
	iph->tos = 0;
	iph->tot_len = htons(sizeof(struct iphdr) + sizeof(struct icmphdr));
	iph->id = htons(1);
	iph->frag_off = 0; 
	iph->ttl = 64; 
	iph->protocol = 1;
	

	iph->check = 0;
	iph->check = ip_checksum((void*)iph, sizeof(struct iphdr));

	iph->saddr = saddr;
	iph->daddr = daddr;
}

void generateIcmp(struct icmphdr* icmp_hdr, uint8_t type, int isEcho, uint16_t id, uint16_t sequence) {
	
	icmp_hdr->code = 0;
	icmp_hdr->type = type;

	if(isEcho) {
		icmp_hdr->un.echo.id = id;
		icmp_hdr->un.echo.sequence = sequence;
	}

	icmp_hdr->checksum = 0;
	icmp_hdr->checksum = icmp_checksum((uint16_t*) icmp_hdr, sizeof(struct icmphdr));
}

void sendIcmp(struct ether_header* eth_hdr, struct iphdr* ip_hdr, struct icmphdr* icmp_hdr, int interface, void* payload){
	packet p;
	
	memset(p.payload, 0, MAX_LEN);
	memcpy(p.payload, eth_hdr, sizeof(struct ether_header));
	memcpy(p.payload + sizeof(struct ether_header), ip_hdr, sizeof(struct iphdr));
	memcpy(p.payload + sizeof(struct ether_header) + sizeof(struct iphdr), icmp_hdr, sizeof(struct icmphdr));
	memcpy(p.payload + sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct icmphdr), payload, 64);
	
	p.len = sizeof(struct ether_header) + sizeof(struct iphdr) + sizeof(struct icmphdr) + 64;
	p.interface = interface;

	send_packet(&p);
}

int main(int argc, char *argv[])
{
	packet m;
	int rc;

	struct arp_entry* arpCache = malloc(sizeof(struct arp_entry) * 6); // cache pentru ARP
	int cacheSize = 0;

	queue q = queue_create(); // coada
	
	// tabela de rutare
	struct route_table_entry* rtable = malloc(sizeof(struct route_table_entry) * 100000);
	int rtable_len = read_rtable(argv[1], rtable);
	// Pentru ca folosesc cautare binara, tabela trebuie sortata
	qsort(rtable, rtable_len, sizeof(struct route_table_entry), compare);

	// Do not modify this line
	init(argc - 2, argv + 2);

	while (1) {
		rc = get_packet(&m);
		DIE(rc < 0, "get_packet");
		/* TODO */


		struct ether_header *eth_hdr = (struct ether_header *) m.payload; // Parsare pachet

		struct iphdr *iph;
		struct arp_header *arp_hdr; 

		uint8_t* mac = malloc(6);
		get_interface_mac(m.interface, mac);
		if (!(checkMac(eth_hdr->ether_dhost, mac) || checkBroadcast(eth_hdr->ether_dhost))) { 
			continue; // drop pachet
		}

		if (ntohs(eth_hdr->ether_type) == 0x0806) { // Check for ARP
		
			arp_hdr = (struct arp_header*)(m.payload + sizeof(struct ether_header));
						
			if(ntohs(arp_hdr->op) == 1) {// ARP Request

				// Creez ethHeader
				struct ether_header *ethHeader = (struct ether_header*) malloc(sizeof(struct ether_header));
				generateEthHeader(ethHeader, m.interface, eth_hdr->ether_shost, eth_hdr->ether_type);

				// Creez arp_header, trimit REPLY, (op = 2)
				struct arp_header* arpHeader = (struct arp_header*) malloc(sizeof(struct arp_header));
				generateArp(arpHeader, arp_hdr->tpa, arp_hdr->spa, ethHeader->ether_dhost, ethHeader->ether_shost, htons(2));
		
				// Trimitem pachetul
				sendArpPacket(ethHeader, arpHeader, m.interface);

				free(ethHeader);
				free(arpHeader);
				continue;
			}

			if(ntohs(arp_hdr->op) == 2) { // ARP Reply

				insertCache(arpCache, &cacheSize , arp_hdr); // Introducem in cache
				
				if(!(queue_empty(q))) { // Lucram pe queue
					packet *p = (packet*)queue_deq(q);
		
					struct ether_header *ethHeader = (struct ether_header*) p->payload;
					generateEthHeader(ethHeader, p->interface, arp_hdr->sha, ethHeader->ether_type);
					send_packet(p);
				}
			}
			continue;
		}

		
		if (ntohs(eth_hdr->ether_type) == 0x0800) { // Check for IPv4

			iph = (struct iphdr*)( m.payload + sizeof(struct ether_header));

			if(iph->daddr == inet_addr(get_interface_ip(m.interface))) {
				// Primesc ICMP trebuie sa fie te tip echo request, type 8
				// generez header
				struct icmphdr* icmp_hdr = (struct icmphdr*) (m.payload + sizeof(struct iphdr) + sizeof(struct ether_header));
				if (icmp_hdr->type == 8) { // Trebuie sa trimitem un Echo reply (type 0)

					struct ether_header* eHeader = (struct ether_header*) malloc(sizeof(struct ether_header));
					struct iphdr* ipHeader = (struct iphdr*) malloc(sizeof(struct iphdr));
					struct icmphdr* icmpHeader = (struct icmphdr*) malloc(sizeof(struct icmphdr));

					generateEthHeader(eHeader, m.interface, eth_hdr->ether_shost, htons(0x0800));
					generateIpv4(ipHeader, iph->saddr, iph->daddr);
					generateIcmp(icmpHeader, 0, 1, icmp_hdr->un.echo.id, icmp_hdr->un.echo.sequence);
				
					sendIcmp(eHeader, ipHeader, icmpHeader, m.interface, m.payload);
					// Trebuie sa generam de asemenea un antet ether si un antet ipv4. Acestea se vor intampla in 
					// functiile de mai sus, unde se va trimite si pachetul.

					free(eHeader);
					free(ipHeader);
					free(icmpHeader);
				}

				continue;
			}

			if (ip_checksum((void*)iph, sizeof(struct iphdr)) != 0) { // Checksum
				continue;
			}

			if (iph->ttl <= 1) { // check ttl
				// ICMP timeout send
				
				struct ether_header* eHeader = (struct ether_header*) malloc(sizeof(struct ether_header));
				struct iphdr* ipHeader = (struct iphdr*) malloc(sizeof(struct iphdr));
				struct icmphdr* icmp_hdr = (struct icmphdr*) malloc(sizeof(struct icmphdr));

				memcpy(eHeader->ether_dhost, eth_hdr->ether_shost, 6);
				memcpy(eHeader->ether_shost, eth_hdr->ether_dhost ,6);
				eHeader->ether_type = htons(0x0800);

				generateIpv4(ipHeader, iph->saddr, iph->daddr);
				generateIcmp(icmp_hdr, 11, 0, 0, 0);

				sendIcmp(eHeader, ipHeader, icmp_hdr, m.interface, m.payload);

				free(eHeader);
				free(ipHeader);
				free(icmp_hdr);

				continue; 
			}
		
			iph->ttl--;

			struct route_table_entry *route = get_best_route(rtable, (iph->daddr), rtable_len);
			if (route == NULL) { // Nu am gasit nimic in tabela, aruncam pachetul
				// ICMP dest unreachable
				struct ether_header* eHeader = (struct ether_header*) malloc(sizeof(struct ether_header));
				struct iphdr* ipHeader = (struct iphdr*) malloc(sizeof(struct iphdr));
				struct icmphdr* icmp_hdr = (struct icmphdr*) malloc(sizeof(struct icmphdr));

				memcpy(eHeader->ether_dhost, eth_hdr->ether_shost, 6);
				memcpy(eHeader->ether_shost, eth_hdr->ether_dhost ,6);
				eHeader->ether_type = htons(0x0800);

				generateIpv4(ipHeader, iph->saddr, iph->daddr);
				generateIcmp(icmp_hdr, 3, 0, 0, 0);

				sendIcmp(eHeader, ipHeader, icmp_hdr, m.interface, m.payload);

				free(eHeader);
				free(ipHeader);
				free(icmp_hdr);

				continue;
			}
			
			// Recalculam checksum
			iph->check = 0; // Checksum must be set to 0 beforehand
			iph->check = ip_checksum((void*)iph, sizeof(struct iphdr));

			// Caut in arp cache adresa
			int index = searchCache(arpCache, cacheSize, route->next_hop); 

			if(index != -1) { // Am gasit adresa in cache, antetul trebuie rescirs si trimis

				generateEthHeader(eth_hdr, route->interface, arpCache[index].mac, eth_hdr->ether_type); 

				m.interface = route->interface;
				send_packet(&m);
				continue;
			}
			
			m.interface = route->interface;
			// Nu am gasit in cache, adaug pachetul original in coada

			packet* toQueue = (packet*) malloc(sizeof(packet));
			memcpy(toQueue, &m, sizeof(m));
			queue_enq(q, toQueue);


			// Trebuie sa generez un ARP Request
			arp_hdr = (struct arp_header*) malloc(sizeof(struct arp_header));

			// Generez antetul ethernet
			struct ether_header *ethHeader = (struct ether_header *) malloc(sizeof(struct ether_header));

			for(int i = 0; i < 6; i++){
				ethHeader->ether_dhost[i] = 0xFF;
			}
		
			generateEthHeader(ethHeader, route->interface, ethHeader->ether_dhost, htons(0x806));
			
			// Generez antentul ARP, REQUEST op = 1
			generateArp(arp_hdr, (inet_addr(get_interface_ip(route->interface))), route->next_hop,
						ethHeader->ether_dhost, ethHeader->ether_shost, htons(1));

			// Trimitem pachetul
			sendArpPacket(ethHeader, arp_hdr, route->interface);

			free(ethHeader);
			free(arp_hdr);
		}
	}
}
