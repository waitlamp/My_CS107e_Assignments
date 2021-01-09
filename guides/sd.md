---
title: "Guide: Working with SD Cards"
toc: true
---

*Written by Pat Hanrahan*

![micro card with adapter](../images/sd.kingston.jpg)
{: .float-right}
Your parts kit contains a microSDHC card. A secure digital (SD) card
stores data in non-volatile memory. The HC in SDHC stands for high
capacity. A micro-SD is shown here with its adapter "jacket" . The Raspberry Pi card reader slot accepts an un-jacketed micro-SD card. When the Pi boots, it looks for a program file named `kernel.img` on its micro-SD card. To change the program executed at boot, you change that file. 

The process of loading a program onto the SD card looks like this:

1. Prepare the card with the proper files. 
    - Mount the card on your laptop and copy the necessary files onto it. 
    - Eject the card from your laptop.
2. Use card on Raspberry Pi.
    - Insert card into slot on Pi. 
    - Reset Pi.
    - When the Pi boots, it runs the program on the card.

To change the program, repeat the process to copy an updated version of the files onto the card. 

In the long run, it is much more convenient to prep the card with a [bootloader](/guides/bootloader) and then send an updated program to the Pi over a serial connection.

## Mount SD card on laptop
To edit the files on the card, mount it on your laptop. If your laptop does not have a built-in SD card reader slot, you will need an external USB reader (we have a few to loan in lab). If your card reader expects a full-size card, use a jacket adapter around the micro card.

![insert sd card into slot](../images/sd.mac.jpg)

When you insert an SD card into the reader, the volume should mount automatically. The new volume will show up in the macOS Finder or Windows File Explorer along with other mounted file systems.

## Copy files onto card
The necessary files are stored in the `$CS107E/firmware` directory . There are 4 files.

```console
$ cd $CS107E/firmware
$ ls
blink-actled.bin   bootcode.bin     bootloader.bin  start.elf
```

`bootcode.bin` and `start.elf` are the start files necessary for the GPU. The Pi boot sequence next looks for a file called `kernel.img`, the program to run. Normally `kernel.img` is the linux kernel. In this course, we will replace the linux kernel with our own program.

Our firmware folder has two program files, `blink-actled.bin` and
`bootloader.bin`.  The program `blink-actled.bin`
blinks the on-board activity (ACT) LED.  Copying `blink-actled.bin`
to `kernel.img` on the sd card is a good way to test whether your Pi is working

After you've verified the blink program, use `bootloader.bin` as the `kernel.img` on the card so that Pi will start the bootloader that can receive uploaded programs. 

You can copy the files using `cp` in a shell or via the macOS Finder or Windows File Explorer. After copying the firmware files onto your SD card, safely eject it.

## Insert card into Raspberry Pi
Insert the card into the slot on the underside of the Raspberry Pi circuit board labelled "Micro SD Card". There is a small spring that holds the card in place. As you push the card in, you will feel the mechanism grab onto the card and secure it in place.

![micro SD inserted on Pi](../images/sd.pi.jpg)
{: .mx-auto}

When you reset the Pi, it will now run the program `kernel.img` on the  card.

## Removing the card from the Pi
To eject the card from the Pi's card slot, __push__ the card in and allow it to spring back out.

>**Do not force the mechanism!** Gently push the card in and allow it to spring back out. If you forcibly pull the card out, you can break the mechanism and potentially destroy your Pi.
{: .callout-danger-invert}

## Troubleshooting

1.  The SD cards we are using are formatted with a FAT32 filesystem. If this
    file system is corrupted, you will need to reformat the file system.
    Consult the internet for how to do this.
2.  The Raspberry Pi can become wedged if `kernel.img` has bugs or
    becomes corrupted. You can always recover to a known state by copying the
    original firmware to the SD card.

