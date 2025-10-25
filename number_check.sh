#!/bin/bash
echo -n "Введите число: "
read num
if [ $((num % 2)) -eq 0 ]; then
echo "Число четное"
else
echo "Число нечетное"
fi
read -p "Нажмите Enter для выхода"
