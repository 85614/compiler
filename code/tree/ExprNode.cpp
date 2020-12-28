#include "ExprNode.h"
#include "TypeNode.h"
ValPtr *ConstExprNode::calValue(std::ostream &os, bool getAddr)
{
    return new ValPtr(new ConstValue(this->value, 0));
}
ValPtr *VarExprNode ::calValue(std::ostream &os, bool getAddr)
{

    int off = this->id->realID->off;
    ValPtr *addr;
    if (off)
        addr = new ValPtr(new ConstValue("ebp", this->id->realID->off));
    else
        addr = new ValPtr(new ConstValue(this->id->ID, 0));
    if (getAddr)
        return addr;
    else if (isRef(getType()))
    {
        addr->_IsRef = true;
        return addr;
    }
    else
        return newMemberValPtr(os, addr);
}

ValPtr *FunCallExprNode::calValue(std::ostream &os, bool getAddr)
{
    std::vector<ValPtr *> vs;
    storeReg(0);

    for (auto *arg : args)
    {
        vs.push_back(arg->calValue(os));
    }
    holdReg(0);
    for (auto it = vs.rbegin(); it != vs.rend(); ++it)
    {
        if ((*it)->isMemory() || (*it)->isState() || (*it)->hasOff())
            (*it)->load(os);
    }
    // os << "    ; hold 0 \n";

    for (auto it = vs.rbegin(); it != vs.rend(); ++it)
    {
        stack_esp -= 4;
        if ((*it)->isMemory() || (*it)->isState())
            (*it)->load(os);
        os << "    push " << (*it)->str() << "\n";
        delete *it;
    }
    unholdReg(0);
    // os << "    ; unhold 0 \n";
    os << "    call " << this->name->ID << "\n";
    if (getAddr)
        my_error("函数返回值不可能是左值");

    auto ans = new ValPtr(nullptr);
    ans->_Ptr = new RegValue(ans, 0);
    return ans;
}

ValPtr *OP1ExprNode::calValue(std::ostream &os, bool getAddr)
{

    switch (this->op)
    {
    case op_e::Not:
        // 计算bool
        {
            auto v = first->calValue(os);
            v->load(os);
            v->judge(os);
            delete v;
            v = new ValPtr(new StateValue("je", "jne"));
            return v;
        }
    case op_e::Negative:
        // 负号
        {
            auto v = first->calValue(os);
            v->load(os);
            os << "    neg " << v->str() << "\n";
            return v;
        }
        break;
    case op_e::SignalAnd:
        // 取地址
        {
            auto v = first->calValue(os, true);
            return v;
        }
        break;
    case op_e::GetValue:
        // 解引用
        {
            auto v = first->calValue(os);
            if (isRef(getType()))
            {
                // 结果是数组或结构体
                // 所以v是数组或结构体的指针
                if (!getAddr)
                    v->_IsRef = true;
                return v;
            }
            // my_error("un check 注释");
            // auto v = first->calValue(os);
            if (getAddr)
                return v;
            else if (isRef(getType()))
            {
                v->_IsRef = true;
                return v;
            }
            auto ans = new ValPtr(nullptr);
            ans->_Ptr = new MemValue(os, v);
            return ans;
        }
        break;
    default:
        cout << "未识别的一目运算符" << getInfo(op) << endl;
        exit(1);
    }
    return nullptr;
}
ValPtr *MemberExprNode::calValue(std::ostream &os, bool getAddr)
{
    if (!isStruct(first->getType()))
        my_error("对非结构体类型，取成员");
    auto structT = (StructTypeNode *)first->getType();
    int off = -1;
    for (auto &&member : structT->members)
    {
        if (member.second->ID == second->ID)
        {
            off = member.second->realID->off;
            break;
        }
    }
    if (off == -1)
        my_error("没有这个成员");
    auto v = first->calValue(os, true); //自动取地址，不能设为true
    if (off)
    {
        v->load(os);
        os << "    add " << v->str() << ", " << toHex(off) << "\n";
    }
    if (getAddr)
        return v;
    else if (isRef(getType()))
    {
        v->_IsRef = true;
        return v;
    }
    else
        return newMemberValPtr(os, v);
}

int getZhiShu(size_t x)
{
    int ans = 0;
    while (x > 1)
    {
        x >>= 1;
        ++ans;
    }
    return ans;
}

ValPtr *OP2ExprNode::calValue(std::ostream &os, bool getAddr)
{
    switch (this->op)
    {
    case op_e::Assignop:
    {
        // 赋值表达式
        // 计算右边的值 或 地址（for结构体）
        // 计算左边的地址
        // 若为值，直接mov
        // 否则 获取大小
        // 多次mov

        auto right = second->calValue(os);
        auto left = first->calValue(os, true);

        if (isRef(getType()))
        {
            if (left->isMemory() || left->isState())
                left->load(os);
            if (right->isMemory() || right->isState())
            {
                holdReg(left);
                right->load(os);
                unholdReg(left);
            }
            holdReg(left);
            holdReg(right);
            auto tmp = newRegValPtr();
            unholdReg(left);
            unholdReg(right);
            // 结果是结构体，(数组不可能)
            int _Size = getType()->size;
            for (int i = 0; i < _Size; i += 4)
            {
                os << "    mov " << tmp->str() << ", [" << right->str(i) << "]\n";
                os << "    mov [" << left->str(i) << "], " << tmp->str() << endl;
            }
            delete tmp;
            delete right;
            if (!getAddr)
                left->_IsRef = true;
            return left;
        }
        // ------以下是非结构体的做法------
        right->load(os); // 右边必须是一个寄存器
        if (left->isMemory() || left->isState())
        {
            holdReg(right);
            left->load(os);
            unholdReg(right);
        }
        os << "    mov [" << left->str() << "], " << right->str() << endl;

        if (getAddr)
        {
            delete right;
            return left;
        }
        else
        {
            delete left;
            return right;
        }

        // 返回值或地址（for结构体）
    }
    case op_e::Relop:
    {
        // 比较
        // 计算左边的值
        // 计算右边的值
        // 保证至少一个寄存器
        // 输出 cmp
        auto v1 = first->calValue(os);
        auto v2 = second->calValue(os);
        v1->load(os);
        os << "    cmp " << v1->str() << ", " << v2->str() << "\n";
        delete v1;
        delete v2;
        if (opStr == ">")
            return new ValPtr(new StateValue("jg", "jle"));
        else if (opStr == "<")
            return new ValPtr(new StateValue("jl", "jge"));
        else if (opStr == ">=")
            return new ValPtr(new StateValue("jge", "jl"));
        else if (opStr == "<=")
            return new ValPtr(new StateValue("jle", "jg"));
        else if (opStr == "==")
            return new ValPtr(new StateValue("je", "jne"));
        else if (opStr == "!=")
            return new ValPtr(new StateValue("jne", "je"));
        else
            my_error("未知的比较运算符");
    }
    break;
    case op_e::Plus:
    case op_e::Minus:
    {
        auto v1 = first->calValue(os);
        auto v2 = second->calValue(os);
        bool hasSwap = false;
        holdReg(v2);
        v1->load(os);
        unholdReg(v2);
        int eleSize1 = tryGetBaseTypeSize(first->getType());
        int eleSize2 = tryGetBaseTypeSize(second->getType());
        if (eleSize1 != eleSize2)
        {
            // 只有一个是指针或数组
            if (eleSize2)
                os << "    sal " << v1->str() << ", " << toHex(getZhiShu(eleSize2)) << "\n";
            else
            {
                holdReg(v1);
                v2->load(os);
                unholdReg(v1);
                os << "    sal " << v2->str() << ", " << toHex(getZhiShu(eleSize1)) << "\n";
            }
        }
        if (v2->hasOff())
        {
            holdReg(v1);
            v2->load(os);
            unholdReg(v1);
        }

        os << (this->op == op_e::Plus ? "    add " : "    sub ");
        os << v1->str() << ", " << v2->str() << " ; ";
        os << (this->op == op_e::Plus ? "+\n" : "-\n");
        delete v2;
        if (hasSameBasic(first->getType(), second->getType()))
        {
            // 如果是指针-指针
            int eleSize = getBaseTypeSize(first->getType());
            v1->load(os);
            os << "    sar " << v1->str() << ", " << toHex(getZhiShu(eleSize)) << "\n";
        }
        return v1;
        // a + b
        // a - b
        // 计算左边的值
        // 计算右边的值
        // 可能是数组
        // 所以要判断类型
        // 保证至少有一个寄存器
        // 输出 add/sub
        // 返回一个寄存器Value
    }
    break;
    case op_e::Times:
    {
        auto v1 = first->calValue(os);
        auto v2 = second->calValue(os);
        v1->load(os);
        v2->load(os);
        os << "    imul " << v1->str() << ", " << v2->str() << "\n";
        delete v2;
        return v1;
    }
    case op_e::Div:
    case op_e::Mod:
    {
        auto v1 = first->calValue(os);
        auto v2 = second->calValue(os);
        v1->load(os, 0);
        storeReg(3);
        holdReg(3);
        v2->load(os);
        os << "    cdq\n    idiv ";
        os << v2->str() << "\n";
        unholdReg(3);
        delete v2;
        if (op == op_e::Div)
            return v1;
        else
        {
            delete v1;
            return &((new ValPtr(0))->newRegValue(3));
        }
        break;
    }

    case op_e::Power:
    {
        auto v1 = first->calValue(os);
        auto v2 = second->calValue(os);
        ValPtr *tmp = nullptr;
        if (v1->isConst())
            tmp = new ValPtr(new ConstValue(v1->str(), 0));
        storeReg(3);
        holdReg(3);
        v1->load(os);
        holdReg(v1);
        v2->load(os);
        holdReg(v2);
        if (!tmp)
        {
            tmp = newRegValPtr();
            os << "    mov " << tmp->str() << ", " << v1->str() << "\n";
        }
        unholdReg(v1);
        unholdReg(v2);
        unholdReg(3);
        int lable = nextlable();
        os << "    mov " << v1->str() << ", 1\n";
        os << "pow_go_on_" << lable << ":\n";
        os << "    cmp " << v2->str() << ", 0\n";
        os << "    jle pow_over_" << lable << "\n";
        os << "    imul " << v1->str() << ", " << tmp->str() << "\n";
        os << "    sub " << v2->str() << ", 1\n";
        os << "    jmp pow_go_on_" << lable << "\n";
        os << "pow_over_" << lable << ":\n";
        delete v2;
        delete tmp;
        return v1;
    }
    break;
    case op_e::And:
    case op_e::Or:
    {

        auto v1 = first->calValue(os);
        int label1 = nextlable();
        int label2 = nextlable();
        v1->GoTo(os, label1, op == op_e::Or);
        delete v1;
        auto v2 = second->calValue(os);
        v2->GoTo(os, label1, op == op_e::Or);
        delete v2;
        auto vp = &(new ValPtr(0))->newRegValue();
        os << "    mov " << vp->str() << ", " << (op != op_e::Or) << "\n";
        os << "    jmp goto" << label2 << "\n";
        os << "goto" << label1 << ":\n";
        os << "    mov " << vp->str() << ", " << (op == op_e::Or) << "\n";
        os << "goto" << label2 << ":\n";

        return vp;
        break;
    }
    // 计算左边的bool值
    // 以 && 为例
    // 生成一个标签false
    // 左边的值生成为假时的跳转到标签false的语句
    // 计算右边的bool值
    // 右边的值生成为假时的跳转到标签false的语句
    // 输出 mov eax, 1
    // 输出标签false
    // 输出 mov eax, 0
    break;
    case op_e::GetArrayValue:
    {

        int size = getBaseTypeSize(first->getType());
        auto v2 = second->calValue(os);
        auto tmp = newRegValPtr();
        os << "    mov " << tmp->str() << ", " << toHex(size) << "\n";
        storeReg(3);
        holdReg(3);
        os << "    imul " << tmp->str() << ", " << v2->str() << "\n";
        delete v2;
        unholdReg(3);

        auto v1 = first->calValue(os);
        if (v1->hasOff())
        {
            holdReg(tmp);
            v1->load(os);
            unholdReg(tmp);
        }
        os << "    add " << tmp->str() << ", " << v1->str() << "\n";
        delete v1;
        if (getAddr)
            return tmp;
        else if (isRef(getType()))
        {
            tmp->_IsRef = true;
            return tmp;
        }
        else
            return newMemberValPtr(os, tmp);
    }

    break;
    default:
        // return "something wrong";
        break;
    }
    return nullptr;
}

void OP1ExprNode::init()
{
    switch (this->op)
    {
    case op_e::Not:
        if (first->getType()->get_type_e() == type_e::PointerType || first->getType()->get_type_e() == type_e::ArrayType)
        {
            this->type = BasicTypeNode::INT;
            this->isConst = first->isConstExpr();
            this->isLeft = false;
            break;
        }
    case op_e::Negative:
        // 负号
        if (first->getType()->isSame(BasicTypeNode::INT))
        {
            this->type = BasicTypeNode::INT;
            this->isConst = first->isConstExpr();
            this->isLeft = false;
            break;
        }
        if (op == op_e::Negative)
        {
            cout << "必须包含算数类型" << endl;
            first->getType()->print(0);
            exit(1);
        }
        else
        {
            cout << "取非运算必须包含int类型、指针类型和数组类型" << endl;
            first->getType()->print(0);
            exit(1);
        }
        break;
    case op_e::SignalAnd:
        // 取地址
        if (!first->isLeftValue())
        {
            cout << "对右值取地址" << endl;
            exit(1);
        }
        this->type = new PointerTypeNode(first->getType());
        this->isConst = false;
        this->isLeft = false;
        break;
    case op_e::GetValue:
        // 解引用
        if (first->getType()->get_type_e() == type_e::ArrayType)
        {
            this->type = ((ArrayTypeNode *)first->getType())->basicType;
            this->isConst = false;
            this->isLeft = true;
        }
        else if (first->getType()->get_type_e() == type_e::PointerType)
        {
            this->type = ((PointerTypeNode *)first->getType())->basicType;
            this->isConst = false;
            this->isLeft = true;
        }
        else
        {
            DEBUG2(getInfo(first->getType()->get_type_e()));
            cout << "只能对数组类型和指针类型解引用" << endl;
            exit(1);
        }
        break;
    default:
        cout << "未识别的一目运算符" << getInfo(op) << endl;
        exit(1);
    }
}

void OP2ExprNode::init()
{
    switch (this->op)
    {
    case op_e::Assignop:
        // return "Assignop \"=\" ";
        if (!first->isLeftValue())
        {
            cout << "赋值运算的左边不是左值" << endl;
            error();
        }
        else if (!first->getType()->assignable(second->getType()))
        {
            cout << "赋值运算类型不兼容" << endl;
            first->print(0);
            second->print(0);
            error();
        }
        else
        {
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
        else if (second->getType()->assignable(first->getType()))
            assignable = second->getType();
        if (assignable &&
            (assignable->isSame(BasicTypeNode::INT) ||
             assignable->get_type_e() == type_e::PointerType ||
             assignable->get_type_e() == type_e::ArrayType))
            init(assignable, false, false);
        else
        {
            cout << "无法进行比较运算" << endl;
            exit(1);
        }
    }
    break;
    case op_e::Minus:
        if (hasSameBasic(first->getType(), second->getType()))
        {
            init(BasicTypeNode::INT, false, false);
            return;
        }
    case op_e::Plus:
    {
        // a + b
        // a - b
        TypeNode *intType, *otherType;
        if (first->getType()->isSame(BasicTypeNode::INT))
        {
            intType = first->getType();
            otherType = second->getType();
        }
        else if (second->getType()->isSame(BasicTypeNode::INT))
        {
            intType = second->getType();
            otherType = first->getType();
        }
        else
        {
            cout << "只有int类型可以和其他类型进行加减" << endl;
            exit(1);
        }
        if (otherType->get_type_e() == type_e::ArrayType)
        {
            auto arrayT = (ArrayTypeNode *)otherType;
            otherType = new PointerTypeNode(arrayT->basicType);
        }
        else if (otherType->get_type_e() == type_e::PointerType)
        {
            // 保持不变
        }
        else if (otherType->isSame(BasicTypeNode::INT))
        {
            // 保持不变
        }
        else
        {
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

        if (first->getType()->isSame(BasicTypeNode::INT) &&
            second->getType()->isSame(BasicTypeNode::INT))
        {
            init(BasicTypeNode::INT, false, false);
        }
        else
        {
            cout << "只有int 类型可以乘、除、取模、乘方、" << endl;
            exit(1);
        }
        break;
    case op_e::And:
    case op_e::Or:
        if (first->getType()->toBool() && second->getType()->toBool())
        {
            init(BasicTypeNode::INT, false, false);
        }
        else
        {
            cout << "不能进行与、或运算" << endl;
        }
        break;
    case op_e::GetArrayValue:
    {

        TypeNode *resultT = nullptr;
        if (first->getType()->get_type_e() == type_e::PointerType)
            resultT = ((PointerTypeNode *)first->getType())->basicType;
        else if (first->getType()->get_type_e() == type_e::ArrayType)
            resultT = ((ArrayTypeNode *)first->getType())->basicType;
        else
        {
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

void ConstExprNode::init()
{
    init(BasicTypeNode::INT, true, false);
}

void MemberExprNode::init()
{
    // return "GetMember \".\" ";
    if (first->getType()->get_type_e() == type_e::BasicType)
    {
        auto basicT = (BasicTypeNode *)first->getType();
        if (basicT->get_basic_type_e() == basic_type_e::STRUCT)
        {
            auto structT = (StructTypeNode *)basicT;
            if (!structT->defined)
            {
                cout << "不允许使用不完整的类型，用于取成员运算符" << endl;
                exit(1);
            }
            for (auto &member : structT->members)
            {
                if (member.second->ID == second->ID)
                {
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

void FunCallExprNode::init()
{

    auto t = name->getType();
    if (t->get_type_e() == type_e::FuncType)
    {
        auto funT = (FuncTypeNode *)t;
        if (this->args.size() != funT->args.size())
        {
            cout << "参数个数不对, excepted" << funT->args.size() << ", but get " << this->args.size() << endl;
            exit(1);
        }
        auto _Size = this->args.size();
        for (int i = 0; i < _Size; ++i)
        {
            if (!funT->args[i]->assignable(this->args[i]->getType()))
            {
                cout << "参数类型不兼容" << endl;
                exit(1);
            }
        }
        init(funT->re, false, false);
    }
    else
    {
        cout << name->ID << " 不是函数" << endl;
    }
}