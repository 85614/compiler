#include "ExprNode.h"
#include "TypeNode.h"


 void OP1ExprNode::init(){
        switch (this->op)
        {
            case op_e::Negative:
                // 负号
                if (first->getType() != BasicTypeNode::INT) {
                    cout << "负号运算的作用对象类型不为int" << endl;
                    first->getType()->print(0);
                    exit(1);
                }
                this->type = BasicTypeNode::INT;
                this->isConst = first->isConstExpr();
                this->isLeft = false;
                break;
            case op_e::Not:
                // 非
                if (first->getType() != BasicTypeNode::INT) {
                    cout << "负号运算的作用对象类型不为int" << endl;
                    first->getType()->print(0);
                    exit(1);
                }
                this->type = BasicTypeNode::INT;
                this->isConst = first->isConstExpr();
                this->isLeft = false;
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
                else if(first->getType()->get_type_e() == type_e::ArrayType) {
                    this->type = ((PointerTypeNode*)first->getType())->basicType;
                    this->isConst = false;
                    this->isLeft = true;
                }
                break;   
            default:
                cout << "未识别的一目运算符" << getInfo(op) << endl;
                exit(1);
        }
    }

void OP2ExprNode::init() {
    DEBUG2("init begin");
    switch (this->op)
    {
        case op_e::Assignop:
            DEBUG2("= begin");
            // return "Assignop \"=\" ";
            if (!first->isLeftValue()) {
                cout << "赋值运算的左边不是左值" << endl; 
                error();
            } else if (!first->getType()->assignable(second->getType())) {
                cout << "复制运算类型不兼容" << endl;
                error();
            }else {
                this->type = first->getType();
                this->isConst = false;
                this->isLeft = true;
            }
            DEBUG2("= end");
            break;
        case op_e::Relop:
            // return "Relop";
            break;
        case op_e::Plus:
            // return "Plus \"+\" ";
            break;
        case op_e::Minus:
            // return "Minus \"-\" ";
            break;
        case op_e::Times:
            // return "Times \"*\" ";
            break;
        case op_e::Div:
            // return "Div \"/\" ";
            break;
        case op_e::Mod:
            // return "Mod \"%\" ";
            break;
        case op_e::Power:
            // return "Power \"^\" ";
            break;
        case op_e::And:
            // return "And \"&&\" ";
            break;
        case op_e::Or:
            // return "Or \"||\" ";
            break;
        case op_e::Negative:
            // return "Negative \"-\" ";
            break;
        case op_e::Not:
            // return "Not \"!\" ";
            break;
        case op_e::SignalAnd:
            // return "SingalAnd \"&\" ";
            break;
        case op_e::GetValue:
            // return "GetValue";
            break;
        case op_e::GetArrayValue:
            // return " GetArrayValue \"[]\" ";
            break;
        case op_e::GetMember:
            // return "GetMember \".\" ";
            break;
        case op_e::AssignArray:
            // return "AssignArray \"[]\" ";
            break;
        case op_e::AssignMember:
            // return "AssignMember \".\" ";
            break;
        default:
            // return "something wrong";
            break;
    }
    DEBUG2("init end");
    }

void ConstExprNode::init() {
    init(BasicTypeNode::INT, true, false);
}