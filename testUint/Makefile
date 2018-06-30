#First you must set environment.
#source /opt/fsl-imx-fb/4.1.15-1.0.0/environment-setup-cortexa7hf-vfp-neon-poky-linux-gnueabi
all:
	$(CC) test_uart.c -otest_uart
	$(CC) test_key.c -otest_key
	$(CC) test_watchdog.c -otest_watchdog
	$(CC) test_zigbee.c -otest_zigbee
clean:
	rm test_uart test_key test_watchdog -fr
