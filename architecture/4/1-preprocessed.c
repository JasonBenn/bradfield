# 1 "0-program.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 330 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "0-program.c" 2
# 1 "./0-program-2.c" 1
int sub2(int i) {
  return i -2;
}
# 2 "0-program.c" 2

int main(int argc, char *argv[]) {
  return sub2(atoi(argv[1]));
}
