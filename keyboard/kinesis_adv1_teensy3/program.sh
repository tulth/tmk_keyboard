#!/bin/bash
set -e
#teensy-loader-cli --mcu=mk20dx256 -v -s -w $@
teensy-loader-cli --mcu=mk20dx256 -v -s -w kinesis_adv1_teensy3.hex
