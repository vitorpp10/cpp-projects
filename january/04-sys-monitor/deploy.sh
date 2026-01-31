#!/bin/bash

make clean
make

sudo mv sys_monitor /usr/local/bin/sys_monitor

sudo chmod +x /usr/local/bin/sys_monitor

echo "Sucesso! Agora você pode digitar 'sys_monitor' em qualquer terminal."
