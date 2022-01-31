/* Compile with: gcc finc_device.c - lpcap */
#include <pcap/pcap.h>
#include <stdio.h>
#include <pcap.h>

int main() {
  char *device; /* Name of devie (e.g eth0 wlan0) */
  char error_buffer[PCAP_ERRBUF_SIZE]; /* Size defined in pcap.h */ 
  
  /* Find a device */
  device = pcap_lookupdev(error_buffer);
  if (device == NULL) {
	printf("Error finding device: %s\n", error_buffer);
	return 1;
  }

  printf("Network device found: %s\n", device);
  return 0;
}
