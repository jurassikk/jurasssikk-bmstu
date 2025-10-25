#!/bin/bash
ps
count=$(ps | wc -l)
echo "Количество работающих процессов: $count"
read -p "Нажмите Enter для выхода"
