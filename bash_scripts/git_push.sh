#!/bin/bash
cd /home/pi/github/shiny_app
#git status
git commit -m "update meteo.csv" meteo.csv
git push
exit
