def find_max(numbers):
    return max(numbers)

n = int(input("Введите количество элементов: "))
numbers = []

for i in range(n):
    numbers.append(int(input(f"Элемент {i+1}: ")))

print("Максимум:", find_max(numbers))

