def is_prime(a)
    # Проверяет, является ли число простым.
    return false if a < 2
  
    (2..Math.sqrt(a).to_i).each do |i|
        return false if a % i == 0
    end
  
    true
end
  
def calculate_nth_num(a)
    # Ищет N-й член последовательности.
    deviation = 1
    left_val = a
    right_val = a
  
    loop do
        if is_prime(left_val)
            return a - left_val
        elsif is_prime(right_val)
            return a - right_val
        end
        left_val = a - deviation  # ищем простое число слева от N
        right_val = a + deviation # ищем простое число справа от N
        deviation += 1
        end
    end
  
# Основная программа
print "Введите свое N: "
n = gets.to_i
  
nth = calculate_nth_num(n)
puts "Найден N-й член ряда: #{nth}"