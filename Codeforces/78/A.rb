int,frac = gets.split('.')
if int[-1] == '9'
    puts "GOTO Vasilisa."
elsif frac[0].to_i < 5
    puts int
else
    puts int.to_i+1
end
