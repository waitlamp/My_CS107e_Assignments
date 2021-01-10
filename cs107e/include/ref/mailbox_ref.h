#pragma once
#include "mailbox.h"
void ref_mailbox_write(unsigned int channel, unsigned int addr);
unsigned int ref_mailbox_read(unsigned int channel);
