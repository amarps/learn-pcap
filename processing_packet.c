#include <arpa/inet.h>
#include <pcap/pcap.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <pcap.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>

void my_packet_handler(
  u_char *args,
  const struct pcap_pkthdr *header,
  const u_char *packet
);

void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header);

int main() {
  char *device;
  char error_buffer[PCAP_ERRBUF_SIZE];
  pcap_t *handle;
  int timeout_limit = 10000; /* In miliseconds*/

  device = pcap_lookupdev(error_buffer);
  if (device == NULL) {
	printf("Error finding device: %s\n", error_buffer);
	return 1;
  }

  /* Open device for live capture */
  handle = pcap_open_live(
    device,
	BUFSIZ,
	0,
	timeout_limit,
	error_buffer
  );
  if (handle == NULL) {
	fprintf(stderr, "Could not open device %s: %s\n", device, error_buffer);
	return 2;
  }

  pcap_loop(handle, 0, my_packet_handler, NULL);

  return 0;
}

void my_packet_handler(
  u_char *args,
  const struct pcap_pkthdr *packet_header,
  const u_char *packet_body) {
  print_packet_info(packet_body, *packet_header);
}

void print_packet_info(const u_char *packet, struct pcap_pkthdr packet_header) {
  printf("Packet capture length: %d\n", packet_header.caplen);
  printf("packet total length %d\n", packet_header.len);
  for (int i = 0; i < packet_header.len; i++) {
	if(isprint(packet[i])) {
	  fprintf(stdout, "%c", packet[i]);
	} else {
	  fprintf(stdout, "%02X", packet[i]);
	}
  }
  fprintf(stdout, "\n");
}
