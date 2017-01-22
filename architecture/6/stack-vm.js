const INST = {
  halt: 0x00,
  loadConst: 0x01,
  print: 0x02
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
        w.stack.push(w.consts[(byte1 << 8) | byte2])
        break;
      case (INST['print']):
        console.log(w.stack.pop());
        break;
    }
    w.ins = w.code[w.ip];
  }
}

eval({
  "code": [1, 0, 0, 2],
  "consts": ["hello world"]
})
