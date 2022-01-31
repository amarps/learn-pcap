default:
	gcc find_network_device.c -o find_network_device.o -lpcap
	gcc get_device_info.c -o get_device_info.o -lpcap
	gcc live_capture.c -o live_capture.o -lpcap
	gcc processing_packet.c -o processing_packet.o -lpcap
