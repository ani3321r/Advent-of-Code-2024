#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <cmath>
#include <sstream>

using namespace std;

struct Program {
    int registers[3] = {0, 0, 0};
    vector<int> opcodes;
    int ip = 0;
    vector<string> stout;
};

int combo(const Program& program, int operand) {
    if (operand >= 0 && operand <= 3) {
        return operand;
    }
    switch (operand) {
        case 4: return program.registers[0];
        case 5: return program.registers[1];
        case 6: return program.registers[2];
        default: return 0;
    }
}

void parseInput(const string& text, Program& program) {
    size_t pos = 0, end;

    pos = text.find("Register A: ") + 12;
    end = text.find('\n', pos);
    program.registers[0] = stoi(text.substr(pos, end - pos));

    pos = text.find("Register B: ", end) + 12;
    end = text.find('\n', pos);
    program.registers[1] = stoi(text.substr(pos, end - pos));

    pos = text.find("Register C: ", end) + 12;
    end = text.find('\n', pos);
    program.registers[2] = stoi(text.substr(pos, end - pos));

    pos = text.find("Program: ") + 9;
    end = text.find('\n', pos);
    string opcodeStr = text.substr(pos, end - pos);

    size_t opcodePos = 0;
    while ((opcodePos = opcodeStr.find(',')) != string::npos) {
        program.opcodes.push_back(stoi(opcodeStr.substr(0, opcodePos)));
        opcodeStr.erase(0, opcodePos + 1);
    }
    if (!opcodeStr.empty()) {
        program.opcodes.push_back(stoi(opcodeStr));
    }
}

void adv(Program& program, int operand) {
    program.registers[0] /= (1 << combo(program, operand));
    program.ip += 2;
}

void bxl(Program& program, int operand) {
    program.registers[1] ^= operand;
    program.ip += 2;
}

void bst(Program& program, int operand) {
    program.registers[1] = combo(program, operand) % 8;
    program.ip += 2;
}

void jnz(Program& program, int operand) {
    if (program.registers[0] == 0) {
        program.ip += 2;
    } else {
        program.ip = operand;
    }
}

void bxc(Program& program, int) {
    program.registers[1] ^= program.registers[2];
    program.ip += 2;
}

void out(Program& program, int operand) {
    int value = combo(program, operand) % 8;
    program.stout.push_back(to_string(value));
    program.ip += 2;
}

void bdv(Program& program, int operand) {
    program.registers[1] = program.registers[0] / (1 << combo(program, operand));
    program.ip += 2;
}

void cdv(Program& program, int operand) {
    program.registers[2] = program.registers[0] / (1 << combo(program, operand));
    program.ip += 2;
}

void (*ops[])(Program&, int) = {
    adv, bxl, bst, jnz, bxc, out, bdv, cdv
};

inline bool fetchInstruction(const Program& program, int& op, int& v) {
    if (program.ip >= program.opcodes.size()) {
        return false;
    }
    op = program.opcodes[program.ip];
    v = program.opcodes[program.ip + 1];
    return true;
}

void exec(Program& program) {
    int op, v;
    while (fetchInstruction(program, op, v)) {
        ops[op](program, v);
    }
}

void printOutput(const vector<string>& stout) {
    for (const auto& val : stout) {
        cout << val << ",";
    }
    cout << endl;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    stringstream buffer;
    buffer << cin.rdbuf();
    string text = buffer.str();

    Program program;
    parseInput(text, program);

    exec(program);

    printOutput(program.stout);

    return 0;
}