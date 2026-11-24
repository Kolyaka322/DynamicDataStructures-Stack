#include <iostream>
#include <string>

struct StackNode {
    char bracket;
    size_t position;
    StackNode* next;

    StackNode(char b, size_t pos, StackNode* n)
        : bracket(b), position(pos), next(n) {
    }
};

class BracketStack {
private:
    StackNode* topNode;

public:
    BracketStack() : topNode(nullptr) {}

    ~BracketStack() {
        clear();
    }

    void push(char bracket, size_t pos) {
        topNode = new StackNode(bracket, pos, topNode);
    }

    bool pop(char& outBracket, size_t& outPos) {
        if (topNode == nullptr) {
            return false;
        }
        StackNode* temp = topNode;
        outBracket = temp->bracket;
        outPos = temp->position;
        topNode = topNode->next;
        delete temp;
        return true;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    size_t topPosition() const {
        return topNode ? topNode->position : 0;
    }

    void clear() {
        while (topNode != nullptr) {
            StackNode* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
};

bool isOpening(char ch) {
    return ch == '(' || ch == '[' || ch == '{';
}

bool isClosing(char ch) {
    return ch == ')' || ch == ']' || ch == '}';
}

bool isMatchingPair(char openB, char closeB) {
    return (openB == '(' && closeB == ')') ||
        (openB == '[' && closeB == ']') ||
        (openB == '{' && closeB == '}');
}

void checkBrackets(const std::string& input) {
    size_t endPos = input.find(';');
    std::string expr = (endPos != std::string::npos) ? input.substr(0, endPos) : input;

    BracketStack stack;

    for (size_t i = 0; i < expr.size(); ++i) {
        char ch = expr[i];

        if (isOpening(ch)) {
            stack.push(ch, i);
        }
        else if (isClosing(ch)) {
            char openBracket;
            size_t openPos;
            if (!stack.pop(openBracket, openPos) || !isMatchingPair(openBracket, ch)) {
                std::cout << "Помилка у рядку!\n";
                std::cout << "До місця помилки: " << expr.substr(0, i + 1) << "\n";
                return;
            }
        }
    }

    if (!stack.isEmpty()) {
        size_t unclosedPos = stack.topPosition();
        std::cout << "Помилка у рядку (незакрита дужка)!\n";
        std::cout << "До місця помилки: " << expr.substr(0, unclosedPos + 1) << "\n";
        return;
    }

    std::cout << "Рядок коректний: усі дужки розставлені правильно.\n";
}

int main() {
    system("chcp 1251>null");
    std::string line;
    std::cout << "Введіть рядок (ознака кінця ';'):\n";
    std::getline(std::cin, line);

    checkBrackets(line);

    return 0;
}
