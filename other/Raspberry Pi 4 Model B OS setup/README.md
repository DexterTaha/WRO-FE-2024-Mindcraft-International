= Setting Up Your Raspberry Pi

== Getting Started with Your Raspberry Pi

image::https://img.youtube.com/vi/CQtliTJ41ZE/0.jpg[youtube, link="https://www.youtube.com/watch?v=CQtliTJ41ZE"]

To get started with your Raspberry Pi, you'll need the following:

* a xref:raspberry-pi.adoc#power-supply[power supply]
* boot media (e.g., a xref:getting-started.adoc#recommended-sd-cards[microSD card with ample storage and speed])

You can set up your Raspberry Pi as an interactive computer with a desktop or as a _headless_ computer accessible only over the network. To set up headlessly, preconfigure a hostname, user account, network connection, and SSH when installing the operating system.

For a direct setup, you’ll need:

* Display
* Cable to connect your Raspberry Pi to your display
* Keyboard
* Mouse

== Power Supply

Here’s the required USB-PD power mode for various Raspberry Pi models:

[%header,cols="1,1,1"]
|===
|Model
|Recommended Power Supply (voltage/current)
|Raspberry Pi Power Supply Link

|Raspberry Pi 5
|5V/5A, 5V/3A limits peripherals to 600mA
|https://www.raspberrypi.com/products/27w-power-supply/[27W USB-C power supply]

|Raspberry Pi 4 Model B
|5V/3A
|https://www.raspberrypi.com/products/type-c-power-supply/[15W USB-C power supply]

|Raspberry Pi 3 (all models)
|5V/2.5A
|https://www.raspberrypi.com/products/micro-usb-power-supply/[12.5W Micro USB power supply]

|Raspberry Pi 2 (all models)
|5V/2.5A
|https://www.raspberrypi.com/products/micro-usb-power-supply/[12.5W Micro USB power supply]

|Raspberry Pi 1 (all models)
|5V/2.5A
|https://www.raspberrypi.com/products/micro-usb-power-supply/[12.5W Micro USB power supply]

|Raspberry Pi Zero (all models)
|5V/2.5A
|https://www.raspberrypi.com/products/micro-usb-power-supply/[12.5W Micro USB power supply]
|===

image::images/peripherals/cable-power.png[alt="Plugging a power supply into a Raspberry Pi"]

Plug the power supply into the port marked "POWER IN," "PWR IN," or "PWR". Be careful to use the correct port, as some models have output USB ports similar to the power port.

== Boot Media

Raspberry Pi models require external storage, typically a microSD card. Only recent models support booting from USB or network storage.

image::images/peripherals/sd-card.png[alt="Inserting a microSD card into a Raspberry Pi"]

Recommended SD cards:

* Minimum 32GB for Raspberry Pi OS installations
* Minimum 16GB for Raspberry Pi OS Lite installations
* Up to 2TB (MBR limit)

Older models and specific ones like Raspberry Pi Zero support only up to 256GB boot partitions.

== Keyboard and Mouse

You can use any USB port for connecting a wired keyboard and mouse or a USB Bluetooth receiver.

image:images/peripherals/cable-key.png[alt="Plugging a keyboard into a Raspberry Pi"]
image:images/peripherals/cable-mouse.png[alt="Plugging a mouse into a Raspberry Pi"]

== Display Connectivity

[%header,cols="1,1"]
|===
|Model
|Display Outputs

|Raspberry Pi 5
|2× micro HDMI

|Raspberry Pi 4 (all models)
|2× micro HDMI, audio and composite out via TRRS jack

|Raspberry Pi 3 (all models)
|HDMI, audio and composite out via TRRS jack

|Raspberry Pi 2 (all models)
|HDMI, audio and composite out via TRRS jack

|Raspberry Pi 1 Model B+ / Model A+
|HDMI, audio and composite out via TRRS jack

|Raspberry Pi Zero (all models)
|mini HDMI
|===

Use `HDMI0` for the primary display if your model has multiple HDMI ports. 

== Audio Support

All Raspberry Pi models with HDMI, micro HDMI, or mini HDMI support audio over HDMI. Models with Bluetooth also support Bluetooth audio, and models with a 3.5mm auxiliary jack (TRRS) support audio output (amplification may be needed).

== Networking

Models with Wi-Fi and Bluetooth:

* Raspberry Pi 5
* Raspberry Pi 4
* Raspberry Pi 3B+ / 3
* Raspberry Pi Zero W / Zero 2 W

For models without Ethernet, use a USB-to-Ethernet adapter.

image::images/peripherals/cable-net.png[alt="Plugging an Ethernet cable into a Raspberry Pi"]

