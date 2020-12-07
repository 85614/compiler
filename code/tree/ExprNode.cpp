#include "ExprNode.h"
#include "TypeNode.h"


 void OP1ExprNode::init(){
        switch (this->op)
        {
            case op_e::Not:
                if (first->getType()->get_type_e() == type_e::PointerType 
                    || first->getType()->get_type_e() == type_e::ArrayType) {
                    this->type = BasicTypeNode::INT;
                    this->isConst = first->isConstExpr();
                    this->isLeft = false;
                    break;
                }
            case op_e::Negative:
                // 负号
                if (first->getType()->isSame(BasicTypeNode::INT)) {
                    this->type = BasicTypeNode::INT;
                    this->isConst = first->isConstExpr();
                    this->isLeft = false; 
                    break;   
                }
                if (op == op_e::Negative) {
                    cout << "必须包含算数类型" << endl;
                    first->getType()->print(0);
                    exit(1);
                }
                else {
                    cout << "取非运算必须包含int类型、指针类型和数组类型" << endl;
                    first->getType()->print(0);
                    exit(1);
                }
                break;
            case op_e::SignalAnd:
                // 取地址
                if (!first->isLeftValue()) {
                    cout << "对右值取地址" << endl;
                    exit(1);
                }
                this->type = new PointerTypeNode(first->getType());
                this->isConst = false;
                this->isLeft = false;
                break;
            case op_e::GetValue:
                // 解引用
                if (first->getType()->get_type_e() == type_e::ArrayType) {
                    this->type = ((ArrayTypeNode*)first->getType())->basicType;
                    this->isConst = false;
                    this->isLeft = true;
                }
                else if(first->getType()->get_type_e() == type_e::PointerType) {
                    this->type = ((PointerTypeNode*)first->getType())->basicType;
                    this->isConst = false;
                    this->isLeft = true;
                } else {
                    cout << "只能对数组类型和指针类型解引用" << endl;
                    exit(1);
                }
                break;   
            default:
                cout << "未识别的一目运算符" << getInfo(op) << endl;
                exit(1);
        }
    }

void OP2ExprNode::init() {
    switch (this->op)
    {
        case op_e::Assignop:
            // return "Assignop \"=\" ";
            if (!first->isLeftValue()) {
                cout << "赋值运算的左边不是左值" << endl; 
                error();
            } else if (!first->getType()->assignable(second->getType())) {
                cout << "赋值运算类型不兼容" << endl;
                first->print(0);
                second->print(0);
                error();
            }else {
                this->type = first->getType();
                this->isConst = false;
                this->isLeft = true;
            }
            break;
        case op_e::Relop:
            {
                TypeNode *assignable = nullptr;
                if (first->getType()->assignable(second->getType()))
                    assignable = first->getType();
                else if(second->getType()->assignable(first->getType()))
                    assignable = second->getType();
                if (assignable && 
                    (assignable->isSame(BasicTypeNode::INT) ||
                    assignable->get_type_e() == type_e::PointerType))
                    init(assignable, false, false);
                else {
                    cout << "无法进行比较运算" <<endl;
                    exit(1);
                }
            }   
            break;
        case op_e::Plus:
        case op_e::Minus:
            {
                // a + b 
                // a - b
                TypeNode *intType, *otherType;
                if (first->getType()->isSame(BasicTypeNode::INT)){
                    intType = first->getType();
                    otherType = second->getType();
                } else if (second->getType()->isSame(BasicTypeNode::INT)){
                    intType = second->getType();
                    otherType = first->getType();
                }
                else {
                    cout << "只有int类型可以和其他类型进行加减" << endl;
                    exit(1);
                }
                if (otherType->get_type_e() == type_e::ArrayType) {
                    auto arrayT = (ArrayTypeNode*)otherType;
                    otherType = new PointerTypeNode(arrayT->basicType);
                }
                else if (otherType->get_type_e() == type_e::PointerType) {
                    // 保持不变
                }
                else if (otherType->isSame(BasicTypeNode::INT)) {
                    // 保持不变
                } else {
                    cout << "只有数组类型，指针类型和int类型可以加减" << endl;
                    exit(1);
                }
                init(otherType, false, false);
            }   
            break;
        case op_e::Times:
        case op_e::Div:
        case op_e::Mod:
        case op_e::Power:
        case op_e::And:
        case op_e::Or:
            if (first->getType()->isSame(BasicTypeNode::INT) && 
                second->getType()->isSame(BasicTypeNode::INT)){
                init(BasicTypeNode::INT, false, false);
            }
            else {
                cout << "只有int 类型可以乘、除、取模、乘方、与、或运算" << endl;
                exit(1);
            }
            break;
        case op_e::GetArrayValue:
            {

        
                TypeNode *resultT = nullptr;
                if (first->getType()->get_type_e() == type_e::PointerType) 
                    resultT = ((PointerTypeNode*)first->getType())->basicType;
                else if (first->getType()->get_type_e() == type_e::ArrayType) 
                    resultT = ((ArrayTypeNode*)first->getType())->basicType;
                else {
                    cout << "只有指针类型和数组类型可以使用[]" << endl;
                    exit(1);
                }
                init(resultT, false, true);
            }
            break;
        default:
            // return "something wrong";
            break;
    }
}

void ConstExprNode::init() {
    init(BasicTypeNode::INT, true, false);
}

void MemberExprNode::init(){
        // return "GetMember \".\" ";
        if (first->getType()->get_type_e() == type_e::BasicType) {
            auto basicT = (BasicTypeNode*) first->getType();
            if (basicT->get_basic_type_e() == basic_type_e::STRUCT){
                auto structT = (StructTypeNode*) basicT;
                if (!structT->defined) {
                    cout << "不允许使用不完整的类型，用于取成员运算符" << endl;
                    exit(1);
                }
                for (auto &member: structT->members) {
                    if (member.second->ID == second->ID) {
                        init(member.first, false, true);
                        return;
                    }
                }
                cout << "类型没有该成员" << endl;
                exit(1);
            }
        }
        cout << "对非结构体类型使用取成员运算 " << endl;
        exit(1);
}


void  FunCallExprNode::init(){

    auto t = name->getType();
    if (t->get_type_e() == type_e::FuncType) {
        auto funT = (FuncTypeNode*) t;
        if (this->args.size() != funT->args.size()){
            cout << "参数个数不对, excepted" << funT->args.size() << 
                ", but get " << this->args.size() << endl;
            exit(1);
        }
        auto _Size = this->args.size();
        for (int i = 0; i< _Size; ++i) {
            if (!funT->args[i]->assignable(this->args[i]->getType())) {
                cout << "参数类型不兼容" <<endl;
                exit(1);
            }
        }
        init(funT->re, false, false);
    }
    else {
        cout << name->ID << " 不是函数" << endl;
    }
}