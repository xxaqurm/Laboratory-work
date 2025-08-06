def print_bottles(bottle, count)
    # Выводит бутылки на экран.
    count.times do |i|
        puts if i % 3 == 0
        print "#{bottle} "
    end
end
  
  def drink_simulation(n, m)
    # Показывает все шаги питья.
    full = n
    empty = 0
    total_drunk = 0
    iterations = 0
  
    full_bottle = "●"
    empty_bottle = "○"
  
    # Выведем дано
    print "Дано"
    print_bottles(full_bottle, full)
    puts "\n"
  
    loop do
        # Шаг 1: выпить все полные бутылки
        if full > 0
            total_drunk += full
            empty += full
            full = 0
            iterations += 1
    
            # Выведем все выпитые бутылки
            print "#{iterations} шаг"
            print_bottles(empty_bottle, empty)
            puts "\n"
    
            break if empty < m  # условие завершения
    
            # Шаг 2: обмен пустых бутылок на полные
            full = empty / m
            empty = empty % m
            iterations += 1
    
            # Выведем бутылки после обмена
            print "#{iterations} шаг"
            print_bottles(full_bottle, full)
            print_bottles(empty_bottle, empty)
            puts "\n"
        end
    end
  
    return total_drunk, iterations
end
  
# Основная часть программы
puts "Введите количество полных бутылок и количество бутылок, которых достаточно для обмена: "
n, m = gets.split.map(&:to_i)
  
puts "Input: #{n} #{m} \n"
  
total, iters = drink_simulation(n, m)
  
puts "Output (total, iters): #{total} #{iters}"
  