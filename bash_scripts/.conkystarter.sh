#!/bin/bash
sleep 60
conky -d -c .conkyrc &&
conky -d -c .conkyrc_2 &&
conky -d -c .conkyrc_3 &&
conky -d -c .conkyrc_4 
exit
