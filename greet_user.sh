#!/bin/bash
if [ -z "$1" ]; then
echo "Пожалуйста, укажите ваше имя"
else
name="$*"
echo "Привет, $name!"
fi
read -p "Нажмите Enter для выхода"
