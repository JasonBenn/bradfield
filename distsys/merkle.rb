require 'digest'

blocks = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']

# Pass 1: create an array with leaf nodes in even indexes
# TODO: drop last nil index
tree = blocks.zip(Array.new(blocks.length)).flatten

tree = tree.map.with_index do |elem, i|
  if i && i % 2 == 0
    elem
  else
    range = 2 ^ count_trailing_ones(i)
    " "
  end
end


def count_trailing_ones(number)
  binary_string = "%b" % number
  trailing_ones = binary_string.match(/(1*)$/)[-1]
  trailing_ones.length
end

def print_tree(tree)
  tree.each_with_index do |elem, i|
    print i.to_s + ":\t"
    print "  " * count_trailing_ones(elem.bytes.last)
    puts elem
  end
end

print_tree(tree)

