ARGF.read.chomp.split.map do |num|
  as_little_endian = num.to_i.to_s(2).rjust(64, '0').chars.each_slice(8).to_a.reverse.map(&:join).join(' ')
  puts "#{num.rjust(10)}: #{as_little_endian}"
end
