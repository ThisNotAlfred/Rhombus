enum AST {
    SOURCE,
    DEST,
    LOAD,
    STORE,
    SHR, // SHIFT RIGHT
    SHL, // SHIFT LEFT
    ADD,
    SUB, // subtract
    XOR,
    OR,
    AND,
    JMPE, // jump equal
    JMPS, // jump smaller
    JMPB, // jump bigger
    COMPARE,
    PRINT,
    SCAN,
    NOP,
};