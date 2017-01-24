const INST = {
  halt: 0x00,
  loadConst: 0x01,
  print: 0x02,
  add: 0x03,
  eq: 0x04,
  branchTrue: 0x05,
  dup: 0x06,
  inc: 0x07,
  jump: 0x08
}

function eval(w) {

  w.stack = [];
  w.localEnv = {};
  w.ip = w.entry || 0;
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
      case (INST['branchTrue']):
        var byte1 = w.code[w.ip++];
        var byte2 = w.code[w.ip++];
        const address = (byte1 << 8) | byte2;
        if (w.stack.pop()) {
          w.ip = address
        }
        break;
      case (INST['dup']):
        w.stack.push(w.stack[w.stack.length -1]);
        break;
      case (INST['inc']):
        w.stack[w.stack.length -1]++
        break;
      case (INST['jump']):
        var byte1 = w.code[w.ip++];
        var byte2 = w.code[w.ip++];
        const address2 = (byte1 << 8) | byte2;
        w.ip = address2
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

// eval({
//   "code": [
//     1, 0, 0, // LOAD_CONST 0  // 3
//     1, 0, 1, // LOAD_CONST 1  // 5
//     4,       // EQ
//     2,       // PRINT // FALSE
//     1, 0, 2, // LOAD_CONST 2  // 9
//     1, 0, 3, // LOAD_CONST 3  // 9
//     4,       // EQ
//     2,       // PRINT // TRUE
//   ],
//   "consts": [3, 5, 9, 9]
// })

// eval({
//   "code": [
//     1, 0, 0, // LOAD_CONST 0   // ("HELLO WORLD")
//     2,       // PRINT
//   ],
//   "consts": ["hello world"]
// })

eval({
  "code": [
    0,       // Halt
    1, 0, 0, // LOAD_CONST 0  // 1
    6,       // DUP
    6,       // DUP
    2,       // PRINT
    1, 0, 1, // LOAD_CONST 1  // 10
    4,       // EQ
    5, 0, 0, // Branch if true to HALT
    7,       // INC
    8, 0, 4  // Jump unconditionaly address 4
  ],
  "consts": [1, 10],
  "entry": 1
})
