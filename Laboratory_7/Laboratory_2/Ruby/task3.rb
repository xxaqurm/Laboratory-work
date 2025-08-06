def is_number(a)
    # Проверяет, что это число, а не цифра.
    a / 10 != 0
end
  
def cnt_odd_digits(a)
    # Считает количество нечетных цифр в числе.
    res = 0
    a = a.abs
  
    while a > 0
        res += (a % 2)
        a /= 10
    end
    res
end
  
puts "Введите количество чисел: "
n = gets.to_i
  
n.times do |i|
    puts "Введите #{i + 1} число: "
    num = gets.to_i
  
    cnt_odd = 0
    if is_number(num)
        cnt_odd = cnt_odd_digits(num)
    else
        puts "#{num} - это цифра!"
    end
  
    puts "Количество нечетных цифр: #{cnt_odd}"
end
  