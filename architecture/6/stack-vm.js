const INST = {
  halt: 0x00,
  loadConst: 0x01,
  print: 0x02,
  add: 0x03,
  eq: 0x04
}

function eval(w) {

  w.stack = [];
  w.localEnv = {};
  w.ip = 0;
  w.ins = w.code[w.ip];

  while (w.ins !== INST['halt'] && w.ip < w.code.length) {
    w.ip++;
    switch (w.ins) {
      case (INST['loadConst']):
        var byte1 = w.code[w.ip++];
        var byte2 = w.code[w.ip++];
        const idx = (byte1 << 8) | byte2;
        w.stack.push(w.consts[idx])
        break;
      case (INST['print']):
        console.log(w.stack.pop());
        break;
      case (INST['add']):
        w.stack.push(w.stack.pop() + w.stack.pop());
        break;
      case (INST['eq']):
        w.stack.push(w.stack.pop() === w.stack.pop());
        break;
      case (INST['b']):
        console.log('b');
        break;
      case (INST['c']):
        console.log('c');
        break;
      default:
        throw "unrecognized instruction";
    }
    w.ins = w.code[w.ip];
  }
}

// eval({
//   "code": [
//     1, 0, 0, // LOAD_CONST 0  // 3
//     1, 0, 1, // LOAD_CONST 1  // 5
//     3,       // ADD
//     2,       // PRINT
//   ],
//   "consts": [3, 5]
// })

eval({
  "code": [
    1, 0, 0, // LOAD_CONST 0  // 3
    1, 0, 1, // LOAD_CONST 1  // 5
    4,       // EQ
    2,       // PRINT // FALSE
    1, 0, 2, // LOAD_CONST 2  // 9
    1, 0, 3, // LOAD_CONST 3  // 9
    4,       // EQ
    2,       // PRINT // TRUE
  ],
  "consts": [3, 5, 9, 9]
})

// eval({
//   "code": [
//     1, 0, 0, // LOAD_CONST 0   // ("HELLO WORLD")
//     2,       // PRINT
//   ],
//   "consts": ["hello world"]
// })
