.text
addiu $t1,$s1,66000 # t1 = s1 + 42
.data # do the next hting in the data segment
.ascii "hello" # decode and write bytes
.text
addiu $v0,$zero,5 # move 5 into v0

# zero - always zero. helpful for moving values, zeroing memory (i.e., add 0 to 0, put in a register)
# at - reserved by assembler, bc some commands are two instructions.
# v0, v1 - conventional function return value register. everyone knows where to look when i come back from funcs. two bc errors are nice to store too.
# a ("argument") registers - so funcs know where to look
# t ("temporary") - local vars, stomp on em all you want
# s ("stack") - like t registers, but these become a stack frame if you need more space (on you to do the work, tho)
# t8, t9 - same as temp registers from earlier
# k0, k1 - reserved by kernel, don't use
# gp - global? pointer. to of data segment (pointer to global data)
# sp - stack pointer. top of stack
# fp - frame pointer. top of frame within stack (so you know where to put stack pointer when you pop from stack)
# ra - return address. convention, you could theoretically use any address to 
# pc - instruction pointer ("program counter"). starts at start of text segment
# hi, lo - meta registers. holds overflow from other registers. division puts answer and remainder into these registers, too. ephemeral
