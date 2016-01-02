//
// Created by msusik on 02.01.16.
//

/*** BNFC-Generated Visitor Design Pattern Compiler. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include <fstream>
#include <iostream>
#include "Compiler.h"



void Compiler::visitProgram(Program* t) {} //abstract class
void Compiler::visitTopDef(TopDef* t) {} //abstract class
void Compiler::visitArg(Arg* t) {} //abstract class
void Compiler::visitClassInstr(ClassInstr* t) {} //abstract class
void Compiler::visitBlock(Block* t) {} //abstract class
void Compiler::visitStmt(Stmt* t) {} //abstract class
void Compiler::visitItem(Item* t) {} //abstract class
void Compiler::visitLatteIdent(LatteIdent* t) {} //abstract class
void Compiler::visitType(Type* t) {} //abstract class
void Compiler::visitExpr(Expr* t) {} //abstract class
void Compiler::visitAddOp(AddOp* t) {} //abstract class
void Compiler::visitMulOp(MulOp* t) {} //abstract class
void Compiler::visitRelOp(RelOp* t) {} //abstract class

void Compiler::visitProg(Prog *prog)
{
    /* Code For Prog Goes Here */

    prog->listtopdef_->accept(this);

}

void Compiler::addFunctionPrologue()
{
    this->program << "\tpushq %rbp\n";
    this->program << "\tmovq %rsp, %rbp\n";
}

void Compiler::addFunctionEpilogue()
{
    this->program << "\tleave\n";
}

void Compiler::visitFnDef(FnDef *fndef)
{
    /* Code For FnDef Goes Here */

    cout << "Generating function: " << fndef->ident_ << endl;
    flush(cout);

    this->program << fndef->ident_ << ":" << endl;
    this->addFunctionPrologue();
    this->envs.addEnv(false);
    /*this->env.prepare();
    this->env.new_fun();*/
    fndef->type_->accept(this);
    visitIdent(fndef->ident_);
    fndef->listarg_->accept(this);
    fndef->block_->accept(this);
    this->envs.removeEnv();

    //return

}

void Compiler::visitClassDefNoInher(ClassDefNoInher *classdefnoinher)
{
    /* Code For ClassDefNoInher Goes Here */

    visitIdent(classdefnoinher->ident_);
    classdefnoinher->listclassinstr_->accept(this);

}

void Compiler::visitClassDefInher(ClassDefInher *classdefinher)
{
    /* Code For ClassDefInher Goes Here */

    visitIdent(classdefinher->ident_1);
    visitIdent(classdefinher->ident_2);
    classdefinher->listclassinstr_->accept(this);

}

void Compiler::visitAr(Ar *ar)
{
    /* Code For Ar Goes Here */

    envs.top().addArgumentToVariables(ar->ident_, false);
    ar->type_->accept(this);
    //visitIdent(ar->ident_);

}

void Compiler::visitMethodDef(MethodDef *methoddef)
{
    /* Code For MethodDef Goes Here */

    methoddef->type_->accept(this);
    visitIdent(methoddef->ident_);
    methoddef->listarg_->accept(this);
    methoddef->block_->accept(this);

}

void Compiler::visitFieldDef(FieldDef *fielddef)
{
    /* Code For FieldDef Goes Here */

    fielddef->type_->accept(this);
    visitIdent(fielddef->ident_);

}

void Compiler::visitBlk(Blk *blk)
{
    /* Code For Blk Goes Here */

    blk->liststmt_->accept(this);

}

void Compiler::visitEmpty(Empty *empty)
{
    /* Code For Empty Goes Here */


}

void Compiler::visitBStmt(BStmt *bstmt)
{
    /* Code For BStmt Goes Here */

    bstmt->block_->accept(this);

}

void Compiler::visitDecl(Decl *decl)
{
    /* Code For Decl Goes Here */

    decl->type_->accept(this);
    decl->listitem_->accept(this);

}

void Compiler::visitAss(Ass *ass)
{
    /* Code For Ass Goes Here */

    string var_ = envs.top().getVariable(ass->listlatteident_->at(0)->getIdent());
    ass->expr_->accept(this); // na górze wartość

    string r1 = envs.top().freeTemp();
    if(r1 != var_)
        this->program << "\tmovl " << r1 << ", " << var_ << endl;
}

void Compiler::visitAssArr(AssArr *assarr)
{
    /* Code For AssArr Goes Here */

    assarr->listlatteident_->accept(this);
    assarr->type_->accept(this);
    assarr->expr_->accept(this);

}

void Compiler::visitAssObj(AssObj *assobj)
{
    /* Code For AssObj Goes Here */

    assobj->listlatteident_->accept(this);
    assobj->type_->accept(this);

}

void Compiler::visitIncr(Incr *incr)
{
    /* Code For Incr Goes Here */

    incr->listlatteident_->accept(this);

}

void Compiler::visitDecr(Decr *decr)
{
    /* Code For Decr Goes Here */

    decr->listlatteident_->accept(this);

}

void Compiler::visitRet(Ret *ret)
{
    /* Code For Ret Goes Here */

    ret->expr_->accept(this);

    // TO DO type
    string retReg = envs.top().freeTemp();
    if(retReg != "%eax")
        this->program << "\tmovl " << retReg << ", %eax\n";
    this->addFunctionEpilogue();
    this->program << "\tret\n";
}

void Compiler::visitVRet(VRet *vret)
{
    /* Code For VRet Goes Here */
    this->addFunctionEpilogue();
    this->program << "\tret\n";
}

void Compiler::visitCond(Cond *cond)
{
    /* Code For Cond Goes Here */

    cond->expr_->accept(this);
    cond->stmt_->accept(this);

}

void Compiler::visitCondElse(CondElse *condelse)
{
    /* Code For CondElse Goes Here */

    string afterLabel = this->envs.getNextLabel();
    string yesLabel = this->envs.getNextLabel();

    condelse->expr_->accept(this);
    this->program << "\t" << jump << " " << yesLabel << endl;

    condelse->stmt_2->accept(this);
    this->program << "\tjmp " << afterLabel << endl;
    this->program << yesLabel << ":\n";
    condelse->stmt_1->accept(this);

    this->program << afterLabel << ":\n";

}

void Compiler::visitWhile(While *while_)
{
    /* Code For While Goes Here */
    string blockLabel = this->envs.getNextLabel();
    string conditionLabel = this->envs.getNextLabel();

    this->program << "\tjmp " << conditionLabel << endl;
    this->program << blockLabel << ":" << endl;

    this->envs.addEnv(true);
    while_->stmt_->accept(this);
    this->envs.removeEnv();

    this->program << conditionLabel << ":" << endl;

    while_->expr_->accept(this);
    this->program << "\t" << jump << " " << blockLabel << endl;

}

void Compiler::visitForeach(Foreach *foreach)
{
    /* Code For Foreach Goes Here */

    foreach->type_->accept(this);
    visitIdent(foreach->ident_);
    foreach->listlatteident_->accept(this);
    foreach->stmt_->accept(this);

}

void Compiler::visitSExp(SExp *sexp)
{
    /* Code For SExp Goes Here */

    sexp->expr_->accept(this);
    this->envs.top().freeTemp(); //not used
}

void Compiler::visitNoInit(NoInit *noinit)
{
    /* Code For NoInit Goes Here */

    this->envs.top().addVariable(noinit->ident_, false);
    visitIdent(noinit->ident_);

}

void Compiler::visitInit(Init *init)
{
    /* Code For Init Goes Here */

    visitIdent(init->ident_);
    init->expr_->accept(this);

}

void Compiler::visitInitArray(InitArray *initarray)
{
    /* Code For InitArray Goes Here */

    visitIdent(initarray->ident_);
    initarray->type_->accept(this);
    initarray->expr_->accept(this);

}

void Compiler::visitInitObj(InitObj *initobj)
{
    /* Code For InitObj Goes Here */

    visitIdent(initobj->ident_);
    initobj->type_->accept(this);

}

void Compiler::visitSingleIdent(SingleIdent *singleident)
{
    /* Code For SingleIdent Goes Here */

    visitIdent(singleident->ident_);

}

void Compiler::visitArrayIdent(ArrayIdent *arrayident)
{
    /* Code For ArrayIdent Goes Here */

    visitIdent(arrayident->ident_);
    arrayident->expr_->accept(this);

}

void Compiler::visitSelfIdent(SelfIdent *selfident)
{
    /* Code For SelfIdent Goes Here */


}

void Compiler::visitClass(Class *class_)
{
    /* Code For Class Goes Here */

    visitIdent(class_->ident_);

}

void Compiler::visitInt(Int *int_)
{
    /* Code For Int Goes Here */


}

void Compiler::visitStr(Str *str)
{
    /* Code For Str Goes Here */


}

void Compiler::visitBool(Bool *bool_)
{
    /* Code For Bool Goes Here */


}

void Compiler::visitVoid(Void *void_)
{
    /* Code For Void Goes Here */


}

void Compiler::visitArrayType(ArrayType *arraytype)
{
    /* Code For ArrayType Goes Here */
    arraytype->type_->accept(this);

}

void Compiler::visitEVar(EVar *evar)
{
    /* Code For EVar Goes Here */
    this->envs.top().registers.temps.push_back("V" + this->envs.top().getVariable(evar->listlatteident_->at(0)->getIdent()));
    //evar->listlatteident_->accept(this); CO TO JEST?

}

void Compiler::visitELitInt(ELitInt *elitint)
{
    /* Code For ELitInt Goes Here */

    visitInteger(elitint->integer_);

}

void Compiler::visitELitFalse(ELitFalse *elitfalse)
{
    /* Code For ELitFalse Goes Here */


}

void Compiler::visitELitNull(ELitNull *elitnull)
{
    /* Code For ELitNull Goes Here */


}

void Compiler::visitELitTrue(ELitTrue *elittrue)
{
    /* Code For ELitTrue Goes Here */


}

void Compiler::visitEApp(EApp *eapp)
{
    /* Code For EApp Goes Here */
    visitIdent(eapp->ident_);

    this->envs.top().registers.clearArgs(&program);
    eapp->listexpr_->accept(this);

    this->program << "\tcall " << eapp->ident_ << endl;
    this->envs.top().registers.freeArguments();
    this->envs.top().registers.temps.push_back("%eax");

    this->envs.top().registers.restoreArgs(&program);


}

void Compiler::visitEInstanceApp(EInstanceApp *einstanceapp)
{
    /* Code For EInstanceApp Goes Here */

    einstanceapp->listlatteident_->accept(this);
    einstanceapp->listexpr_->accept(this);

}

void Compiler::visitEString(EString *estring)
{
    /* Code For EString Goes Here */

    visitString(estring->string_);

}

void Compiler::visitNeg(Neg *neg)
{
    /* Code For Neg Goes Here */

    neg->expr_->accept(this);

}

void Compiler::visitNot(Not *not_)
{
    /* Code For Not Goes Here */

    not_->expr_->accept(this);

}

void Compiler::visitECast(ECast *ecast)
{
    /* Code For ECast Goes Here */

    visitIdent(ecast->ident_);
    ecast->expr_->accept(this);

}

void Compiler::visitEMul(EMul *emul)
{
    /* Code For EMul Goes Here */

    emul->expr_1->accept(this);
    emul->expr_2->accept(this);

    emul->mulop_->accept(this);

}

void Compiler::visitEAdd(EAdd *eadd)
{
    /* Code For EAdd Goes Here */

    eadd->expr_1->accept(this);
    eadd->expr_2->accept(this);

    eadd->addop_->accept(this);
}

void Compiler::visitERel(ERel *erel)
{
    /* Code For ERel Goes Here */

    erel->expr_1->accept(this);
    erel->expr_2->accept(this);

    erel->relop_->accept(this);
}

void Compiler::visitEAnd(EAnd *eand)
{
    /* Code For EAnd Goes Here */

    eand->expr_1->accept(this);
    eand->expr_2->accept(this);

}

void Compiler::visitEOr(EOr *eor)
{
    /* Code For EOr Goes Here */

    eor->expr_1->accept(this);
    eor->expr_2->accept(this);

}

void Compiler::visitPlus(Plus *plus)
{
    /* Code For Plus Goes Here */
    // TODO Strings
    string r2 = envs.top().freeTemp(); // drugi
    string r1 = envs.top().freeTemp(); // pierwszy
    string r3 = envs.top().getTemp(false);

    if(r1 != r3)
        this->program << "\tmovl " << r1 << ", " << r3 << endl;
    this->program << "\taddl " << r2 << ", " << r3 << endl;

    // this->envs.top().registers.temps.push(r2);

}

void Compiler::visitMinus(Minus *minus)
{
    /* Code For Minus Goes Here */
    string r2 = envs.top().freeTemp(); // drugi
    string r1 = envs.top().freeTemp(); // pierwszy

    string r3 = envs.top().getTemp(false);

    if(r1 != r3)
        this->program << "\tmovl " << r1 << ", " << r3 << endl;
    this->program << "\tsubl " << r2 << ", " << r3 << endl;

    // this->envs.top().registers.temps.push(envs.top().freeTemp());

}

void Compiler::visitTimes(Times *times)
{
    /* Code For Times Goes Here */

    string r2 = envs.top().freeTemp(); // drugi
    string r1 = envs.top().freeTemp(); // pierwszy

    this->program << "\tpushq %rax\t;mnozenie\n";
    this->program << "\tpushq %rdx\n";
    if(r2 != "%eax")
        this->program << "\tmovl " << r2 << ", %eax\n";
    this->program << "\tmull " << r1 << endl;
    string free_ = this->envs.top().getTemp(false);

    this->program << "\tmovl %eax, " << free_ <<endl;
    this->program << "\tpopq %rdx\n";
    this->program << "\tpopq %rax\n";


}

void Compiler::visitDiv(Div *div)
{
    /* Code For Div Goes Here */


}

void Compiler::visitMod(Mod *mod)
{
    /* Code For Mod Goes Here */


}

void Compiler::visitLTH(LTH *lth)
{

    /* Code For LTH Goes Here */
    string r2 = envs.top().freeTemp(); // drugi
    string r1 = envs.top().freeTemp(); // pierwszy

    this->program << "\tcmpl " << r1 << ", " << r2 << endl;

    this->jump = "jge";
}

void Compiler::visitLE(LE *le)
{
    /* Code For LE Goes Here */
    string r2 = envs.top().freeTemp(); // drugi
    string r1 = envs.top().freeTemp(); // pierwszy

    this->program << "\tcmpl " << r1 << ", " << r2 << endl;

    this->jump = "jg";
}

void Compiler::visitGTH(GTH *gth)
{
    /* Code For GTH Goes Here */
    // n > 0 na szczycie 0

    string r2 = envs.top().freeTemp(); // drugi
    string r1 = envs.top().freeTemp(); // pierwszy

    this->program << "\tcmpl " << r2 << ", " << r1 << endl;

    this->jump = "jg";

}

void Compiler::visitGE(GE *ge)
{
    /* Code For GE Goes Here */

    string r2 = envs.top().freeTemp(); // drugi
    string r1 = envs.top().freeTemp(); // pierwszy

    this->program << "\tcmpl " << r2 << ", " << r1 << endl;

    this->jump = "jge";

}

void Compiler::visitEQU(EQU *equ)
{
    /* Code For EQU Goes Here */
    string r2 = envs.top().freeTemp(); // drugi
    string r1 = envs.top().freeTemp(); // pierwszy

    this->program << "\ttest " << r2 << ", " << r1 << endl;

    this->jump = "je";

}

void Compiler::visitNE(NE *ne)
{
    /* Code For NE Goes Here */
    string r2 = envs.top().freeTemp(); // drugi
    string r1 = envs.top().freeTemp(); // pierwszy

    this->program << "\ttest " << r2 << ", " << r1 << endl;

    this->jump = "jne";

}


void Compiler::visitListTopDef(ListTopDef* listtopdef)
{
    for (ListTopDef::iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void Compiler::visitListArg(ListArg* listarg)
{

    for (ListArg::iterator i = listarg->begin() ; i != listarg->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void Compiler::visitListClassInstr(ListClassInstr* listclassinstr)
{
    for (ListClassInstr::iterator i = listclassinstr->begin() ; i != listclassinstr->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void Compiler::visitListStmt(ListStmt* liststmt)
{
    for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void Compiler::visitListItem(ListItem* listitem)
{
    for (ListItem::iterator i = listitem->begin() ; i != listitem->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void Compiler::visitListLatteIdent(ListLatteIdent* listlatteident)
{
    Ident i = listlatteident->at(0)->getIdent();


    string reg_name1 = this->envs.top().getTemp(false);
    string reg_name2 = this->envs.top().getVariable(i);
    if(reg_name1 != reg_name2)
        this->program << "\tmovl " << reg_name2 << ", " << reg_name1 << endl;

    for (ListLatteIdent::iterator i = listlatteident->begin() ; i != listlatteident->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void Compiler::visitListExpr(ListExpr* listexpr)
{
    for (ListExpr::iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
    {
        (*i)->accept(this);
        this->envs.top().putArg(&program);
    }
}


void Compiler::visitInteger(Integer x)
{
    /* Code for Integer Goes Here */
    this->envs.top().registers.temps.push_back("$" + to_string(x));
}

void Compiler::visitChar(Char x)
{
    /* Code for Char Goes Here */
}

void Compiler::visitDouble(Double x)
{
    /* Code for Double Goes Here */
}

void Compiler::visitString(String x)
{
    /* Code for String Goes Here */
}

void Compiler::visitIdent(Ident x)
{
    /* Code for Ident Goes Here */
}


Compiler::Compiler(std::vector<FnDef *> functions, std::string assembly_file) : assembly_file(assembly_file) {

    int main_index = 0;
    for(auto it = 0; it != functions.end() - functions.begin(); ++it)
    {
        if(functions[it]->ident_ == "main") {
            this->functions.push_back(functions[it]);
            main_index = it;
        }
    }
    for(auto it = 0; it != functions.end() - functions.begin(); ++it) {
        if(it != main_index){
            this->functions.push_back(functions[it]);
        }
    }
    this->program <<"\t.globl main\n";

    cout << "Generating program" << endl;

    for(auto it=functions.begin(); it != functions.end(); ++it){
        visitFnDef(*it);
    }

}

void Compiler::generate() {
    std::ofstream outFile;
    outFile.open(this->assembly_file);
    outFile << this->program.rdbuf();
    outFile.close();
}

