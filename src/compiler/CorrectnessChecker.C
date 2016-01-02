/*** BNFC-Generated Visitor Design Pattern TypeChecker. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include <iostream>
#include "CorrectnessChecker.H"
#include "../Absyn.H"

void CorrectnessChecker::visitProgram(Program* t) {} //abstract class
void CorrectnessChecker::visitTopDef(TopDef* t) {} //abstract class
void CorrectnessChecker::visitArg(Arg* t) {} //abstract class
void CorrectnessChecker::visitClassInstr(ClassInstr* t) {} //abstract class
void CorrectnessChecker::visitBlock(Block* t) {} //abstract class
void CorrectnessChecker::visitStmt(Stmt* t) {} //abstract class
void CorrectnessChecker::visitItem(Item* t) {} //abstract class
void CorrectnessChecker::visitLatteIdent(LatteIdent* t) {} //abstract class
void CorrectnessChecker::visitType(Type* t) {} //abstract class
void CorrectnessChecker::visitExpr(Expr* t) {} //abstract class
void CorrectnessChecker::visitAddOp(AddOp* t) {} //abstract class
void CorrectnessChecker::visitMulOp(MulOp* t) {} //abstract class
void CorrectnessChecker::visitRelOp(RelOp* t) {} //abstract class

void CorrectnessChecker::visitProg(Prog *prog)
{
    /* Code For Prog Goes Here */

    prog->listtopdef_->accept(this);

}

bool CorrectnessChecker::checkBlock(Blk* blk)
{
    bool ret_ = false;
    for (auto it = blk->liststmt_->begin(); it != blk->liststmt_->end(); ++it) {

        if((*it)->isRet() || (*it)->isVRet())
        {
            ret_ = true;
            break;
        }
        CondElse *ce = (*it)->returnCondElse();
        if (ce != nullptr){
            ret_ = this->checkIfElse(ce);
            if(ret_)
                break;
        }
        Cond *cd = (*it)->returnCond();
        if (cd != nullptr){
            ret_ = this->CheckIf(cd);
            if(ret_)
                break;
        }
    }
    return ret_;
}

bool CorrectnessChecker::checkPart(Stmt* stmt_1)
{
    BStmt* bl = stmt_1->getBlock();
    if(bl){
        return this->checkBlock((Blk*)bl->block_);
    }

    CondElse *ce = stmt_1->returnCondElse();
    if (ce != nullptr){
        return this->checkIfElse(ce);
    }
    Cond *cd = stmt_1->returnCond();
    if (cd != nullptr){
        return this->CheckIf(cd);
    }

    return stmt_1->isRet() || stmt_1->isVRet();

}


bool CorrectnessChecker::CheckIf(Cond *pCond) {
    if(pCond->expr_->true_())
    {
        return this->checkPart(pCond->stmt_);
    }
    return false;
}


bool CorrectnessChecker::checkIfElse(CondElse *ce)
{
    if(ce->expr_->false_())
    {
        return this->checkPart(ce->stmt_2);
    } else if(ce->expr_->true_())
    {
        return this->checkPart(ce->stmt_1);
    }
    return this->checkPart(ce->stmt_1) && this->checkPart(ce->stmt_2);

}

void CorrectnessChecker::visitFnDef(FnDef *fndef)
{
    this->return_ = false;
    /* Code For FnDef Goes Here */
    envs.emplace(); // should this be empty?
    fndef->type_->accept(this);
    visitIdent(fndef->ident_);
    fndef->listarg_->accept(this);

    this->current_function_type = fndef->type_->getType();
    fndef->block_->accept(this);
    // function has to return specific type
    Blk* blk = (Blk*)fndef->block_;
    this->return_ = this->checkBlock(blk);

    if(!this->return_ && current_function_type != "void")
        error.addError(fndef->line_number, "Function doesn't return");

}

void CorrectnessChecker::visitClassDefNoInher(ClassDefNoInher *classdefnoinher)
{
    /* Code For ClassDefNoInher Goes Here */

    visitIdent(classdefnoinher->ident_);
    classdefnoinher->listclassinstr_->accept(this);

}

void CorrectnessChecker::visitClassDefInher(ClassDefInher *classdefinher)
{
    /* Code For ClassDefInher Goes Here */

    visitIdent(classdefinher->ident_1);
    visitIdent(classdefinher->ident_2);
    classdefinher->listclassinstr_->accept(this);

}

void CorrectnessChecker::visitAr(Ar *ar)
{
    /* Code For Ar Goes Here */
    if(ar->type_->getType() == "void"){
        error.addError(ar->line_number, "void used as an argument type in function definition");
    }
    ar->type_->accept(this);
    visitIdent(ar->ident_);

}

void CorrectnessChecker::visitMethodDef(MethodDef *methoddef)
{
    /* Code For MethodDef Goes Here */

    methoddef->type_->accept(this);
    visitIdent(methoddef->ident_);
    methoddef->listarg_->accept(this);
    methoddef->block_->accept(this);

}

void CorrectnessChecker::visitFieldDef(FieldDef *fielddef)
{
    /* Code For FieldDef Goes Here */

    fielddef->type_->accept(this);
    visitIdent(fielddef->ident_);

}

void CorrectnessChecker::visitBlk(Blk *blk)
{
    if(!top)
    {
        envs.emplace(envs.top().get_previous());
    }
    top = false;
    /* Code For Blk Goes Here */
    blk->liststmt_->accept(this);
    envs.pop();
}

void CorrectnessChecker::visitEmpty(Empty *empty)
{
    /* Code For Empty Goes Here */


}

void CorrectnessChecker::visitBStmt(BStmt *bstmt)
{
    /* Code For BStmt Goes Here */

    bstmt->block_->accept(this);

}

void CorrectnessChecker::visitDecl(Decl *decl)
{

    if(decl->type_->getType() == "void")
    {
        error.addError(decl->line_number, "Can't declare a void variable!");
    }
    /* Code For Decl Goes Here */
    for(auto it=decl->listitem_->begin(); it != decl->listitem_->end(); ++it)
    {
        Ident ident = (*it)->getIdent();
        if(this->envs.top().is_variable_declared_here(ident))
        {
            this->error.addError((*it)->line_number, "Variable declared twice!: " + ident);
        }
        else
        {
            this->envs.top().add_variable(ident, decl->type_);
        }
    }
    decl->type_->accept(this);
    decl->listitem_->accept(this);

}

void CorrectnessChecker::visitAss(Ass *ass)
{
    /* Code For Ass Goes Here */
    Ident assigned_to = ass->listlatteident_->at(0)->getIdent();
    Type *tta = envs.top().get_type(assigned_to);
    if(tta == nullptr){
        this->error.addError(ass->line_number, "Undefined variable: " +  assigned_to);
        return;
    }
    string type_assigned_to = tta->getType();
    string expr_type = typeFetcher.getType(ass->expr_, functions, envs.top(), &error);
    if(type_assigned_to != expr_type)
    {
        this->error.addError(ass->line_number, "Wrong type assigned to: " +  assigned_to);
    }
    ass->listlatteident_->accept(this);
    ass->expr_->accept(this);

}

void CorrectnessChecker::visitAssArr(AssArr *assarr)
{
    /* Code For AssArr Goes Here */

    assarr->listlatteident_->accept(this);
    assarr->type_->accept(this);
    assarr->expr_->accept(this);

}

void CorrectnessChecker::visitAssObj(AssObj *assobj)
{
    /* Code For AssObj Goes Here */

    assobj->listlatteident_->accept(this);
    assobj->type_->accept(this);

}

void CorrectnessChecker::visitIncr(Incr *incr)
{
    /* Code For Incr Goes Here */
    incr->listlatteident_->accept(this);

}

void CorrectnessChecker::visitDecr(Decr *decr)
{
    /* Code For Decr Goes Here */
    decr->listlatteident_->accept(this);

}

void CorrectnessChecker::visitRet(Ret *ret)
{
    /* Code For Ret Goes Here */
    string expr_type = typeFetcher.getType(ret->expr_, functions, envs.top(), &error);
    if(expr_type != current_function_type){
        error.addError(ret->line_number, "Wrong type returned. Expected " + current_function_type);
    } else if(current_function_type == "void"){
        error.addError(ret->line_number, "Can't return void.");
    }
    ret->expr_->accept(this);

}

void CorrectnessChecker::visitVRet(VRet *vret)
{
    /* Code For VRet Goes Here */
    if(current_function_type != "void"){
        error.addError(vret->line_number, "Returned nothing, but expected " + current_function_type);
    }

}

void CorrectnessChecker::visitCond(Cond *cond)
{

    /* Code For Cond Goes Here */
    string expr_type = typeFetcher.getType(cond->expr_, functions, envs.top(), &error);
    if(expr_type != "boolean")
    {
        error.addError(cond->line_number, "If condition should receive a boolean. Received " + expr_type);
    }
    cond->expr_->accept(this);
    envs.emplace(envs.top().get_previous());
    cond->stmt_->accept(this);
    envs.pop();

}

void CorrectnessChecker::visitCondElse(CondElse *condelse)
{
    /* Code For CondElse Goes Here */
    string expr_type = typeFetcher.getType(condelse->expr_, functions, envs.top(), &error);
    if(expr_type != "boolean")
    {
        error.addError(condelse->line_number, "If condition should receive a boolean. Received " + expr_type);
    }
    condelse->expr_->accept(this);
    envs.emplace(envs.top().get_previous());
    condelse->stmt_1->accept(this);
    envs.pop();
    envs.emplace(envs.top().get_previous());
    condelse->stmt_2->accept(this);
    envs.pop();

}

void CorrectnessChecker::visitWhile(While *while_)
{
    /* Code For While Goes Here */
    string expr_type = typeFetcher.getType(while_->expr_, functions, envs.top(), &error);
    if(expr_type != "boolean")
    {
        error.addError(while_->line_number, "While condition should receive a boolean. Received " + expr_type);
    }
    while_->expr_->accept(this);
    envs.emplace(envs.top().get_previous());
    while_->stmt_->accept(this);
    envs.pop();

}

void CorrectnessChecker::visitForeach(Foreach *foreach)
{
    /* Code For Foreach Goes Here */

    foreach->type_->accept(this);
    visitIdent(foreach->ident_);
    foreach->listlatteident_->accept(this);
    foreach->stmt_->accept(this);

}

void CorrectnessChecker::visitSExp(SExp *sexp)
{
    /* Code For SExp Goes Here */
    sexp->expr_->accept(this);

}

void CorrectnessChecker::visitNoInit(NoInit *noinit)
{
    /* Code For NoInit Goes Here */

    visitIdent(noinit->ident_);

}

void CorrectnessChecker::visitInit(Init *init)
{
    /* Code For Init Goes Here */
    string expr_type = this->typeFetcher.getType(init->expr_, this->functions, this->envs.top(), &(this->error));
    string var_type = this->envs.top().get_type(init->ident_)->getType();
    if(var_type != expr_type)
    {
        this->error.addError(init->line_number, "Wrong type assigned to declaration of " + init->ident_);
    }
    visitIdent(init->ident_);
    init->expr_->accept(this);

}

void CorrectnessChecker::visitInitArray(InitArray *initarray)
{
    /* Code For InitArray Goes Here */
    // TODO
    visitIdent(initarray->ident_);
    initarray->type_->accept(this);
    initarray->expr_->accept(this);

}

void CorrectnessChecker::visitInitObj(InitObj *initobj)
{
    /* Code For InitObj Goes Here */
    // TODO
    visitIdent(initobj->ident_);
    initobj->type_->accept(this);

}

void CorrectnessChecker::visitSingleIdent(SingleIdent *singleident)
{
    /* Code For SingleIdent Goes Here */

    visitIdent(singleident->ident_);

}

void CorrectnessChecker::visitArrayIdent(ArrayIdent *arrayident)
{
    /* Code For ArrayIdent Goes Here */

    visitIdent(arrayident->ident_);
    arrayident->expr_->accept(this);

}

void CorrectnessChecker::visitSelfIdent(SelfIdent *selfident)
{
    /* Code For SelfIdent Goes Here */


}

void CorrectnessChecker::visitClass(Class *class_)
{
    /* Code For Class Goes Here */

    visitIdent(class_->ident_);

}

void CorrectnessChecker::visitInt(Int *int_)
{
    /* Code For Int Goes Here */


}

void CorrectnessChecker::visitStr(Str *str)
{
    /* Code For Str Goes Here */


}

void CorrectnessChecker::visitBool(Bool *bool_)
{
    /* Code For Bool Goes Here */


}

void CorrectnessChecker::visitVoid(Void *void_)
{
    /* Code For Void Goes Here */


}

void CorrectnessChecker::visitArrayType(ArrayType *arraytype)
{
    /* Code For ArrayType Goes Here */

    arraytype->type_->accept(this);

}

void CorrectnessChecker::visitEVar(EVar *evar)
{
    /* Code For EVar Goes Here */

    evar->listlatteident_->accept(this);

}

void CorrectnessChecker::visitELitInt(ELitInt *elitint)
{
    /* Code For ELitInt Goes Here */

    visitInteger(elitint->integer_);

}

void CorrectnessChecker::visitELitFalse(ELitFalse *elitfalse)
{
    /* Code For ELitFalse Goes Here */


}

void CorrectnessChecker::visitELitNull(ELitNull *elitnull)
{
    /* Code For ELitNull Goes Here */


}

void CorrectnessChecker::visitELitTrue(ELitTrue *elittrue)
{
    /* Code For ELitTrue Goes Here */


}

void CorrectnessChecker::visitEApp(EApp *eapp)
{
    /* Code For EApp Goes Here */
    vector<string> definition_types = typeFetcher.getFunctionArgsTypes(eapp->ident_, functions);
    int i;
    for(i = 0; i < definition_types.size() && i < eapp->listexpr_->size(); ++i)
    {
        string position_type = typeFetcher.getType(eapp->listexpr_->at(i),functions, envs.top(), &error);
        if(position_type != definition_types[i]) {
            error.addError(eapp->line_number, "Type mismatch in function call. Argument " + to_string(i) +
                                              " expected to be " + definition_types[i]);
        }
    }
    if(i < definition_types.size())
    {
        error.addError(eapp->line_number, "Missing parameters in function call");
    }
    if(i < eapp->listexpr_->size())
    {
        error.addError(eapp->line_number, "Too many parameters in function call");
    }

    visitIdent(eapp->ident_);
    eapp->listexpr_->accept(this);

}

void CorrectnessChecker::visitEInstanceApp(EInstanceApp *einstanceapp)
{
    /* Code For EInstanceApp Goes Here */

    einstanceapp->listlatteident_->accept(this);
    einstanceapp->listexpr_->accept(this);

}

void CorrectnessChecker::visitEString(EString *estring)
{
    /* Code For EString Goes Here */

    visitString(estring->string_);

}

void CorrectnessChecker::visitNeg(Neg *neg)
{
    /* Code For Neg Goes Here */
    neg->expr_->accept(this);

}

void CorrectnessChecker::visitNot(Not *not_)
{
    /* Code For Not Goes Here */
    not_->expr_->accept(this);

}

void CorrectnessChecker::visitECast(ECast *ecast)
{
    /* Code For ECast Goes Here */

    visitIdent(ecast->ident_);
    ecast->expr_->accept(this);

}

void CorrectnessChecker::visitEMul(EMul *emul)
{
    /* Code For EMul Goes Here */
    emul->expr_1->accept(this);
    emul->mulop_->accept(this);
    emul->expr_2->accept(this);

}

void CorrectnessChecker::visitEAdd(EAdd *eadd)
{
    /* Code For EAdd Goes Here */
    eadd->expr_1->accept(this);
    eadd->addop_->accept(this);
    eadd->expr_2->accept(this);

}

void CorrectnessChecker::visitERel(ERel *erel)
{
    /* Code For ERel Goes Here */

    erel->expr_1->accept(this);
    erel->relop_->accept(this);
    erel->expr_2->accept(this);

}

void CorrectnessChecker::visitEAnd(EAnd *eand)
{
    /* Code For EAnd Goes Here */

    eand->expr_1->accept(this);
    eand->expr_2->accept(this);

}

void CorrectnessChecker::visitEOr(EOr *eor)
{
    /* Code For EOr Goes Here */

    eor->expr_1->accept(this);
    eor->expr_2->accept(this);

}

void CorrectnessChecker::visitPlus(Plus *plus)
{
    /* Code For Plus Goes Here */


}

void CorrectnessChecker::visitMinus(Minus *minus)
{
    /* Code For Minus Goes Here */


}

void CorrectnessChecker::visitTimes(Times *times)
{
    /* Code For Times Goes Here */


}

void CorrectnessChecker::visitDiv(Div *div)
{
    /* Code For Div Goes Here */


}

void CorrectnessChecker::visitMod(Mod *mod)
{
    /* Code For Mod Goes Here */


}

void CorrectnessChecker::visitLTH(LTH *lth)
{
    /* Code For LTH Goes Here */


}

void CorrectnessChecker::visitLE(LE *le)
{
    /* Code For LE Goes Here */


}

void CorrectnessChecker::visitGTH(GTH *gth)
{
    /* Code For GTH Goes Here */


}

void CorrectnessChecker::visitGE(GE *ge)
{
    /* Code For GE Goes Here */


}

void CorrectnessChecker::visitEQU(EQU *equ)
{
    /* Code For EQU Goes Here */


}

void CorrectnessChecker::visitNE(NE *ne)
{
    /* Code For NE Goes Here */


}


void CorrectnessChecker::visitListTopDef(ListTopDef* listtopdef)
{
    for (ListTopDef::iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void CorrectnessChecker::visitListArg(ListArg* listarg)
{
    set<string> arguments_names;
    for (ListArg::iterator i = listarg->begin() ; i != listarg->end() ; ++i)
    {
        Ar *arg = (Ar*)(*i);
        this->envs.top().add_variable(arg->ident_, arg->type_);
        if(!arguments_names.insert(arg->ident_).second){
            this->error.addError(arg->line_number,"Function received the same argument twice: " + arg->ident_);
        };
        (*i)->accept(this);
    }
}

void CorrectnessChecker::visitListClassInstr(ListClassInstr* listclassinstr)
{
    for (ListClassInstr::iterator i = listclassinstr->begin() ; i != listclassinstr->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void CorrectnessChecker::visitListStmt(ListStmt* liststmt)
{

    for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
    {
        ListLatteIdent *deref = (*i)->simple();

        if(deref != nullptr){
            // Incr or decr
            typeFetcher.checkStatement(*i, functions, envs.top(), &error);
        } else {
            Expr *expr = (*i)->expr();
            if(expr != nullptr){
                typeFetcher.getType(expr, functions, envs.top(), &error);
            }
        }
        (*i)->accept(this);
    }
}

void CorrectnessChecker::visitListItem(ListItem* listitem)
{
    for (ListItem::iterator i = listitem->begin() ; i != listitem->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void CorrectnessChecker::visitListLatteIdent(ListLatteIdent* listlatteident)
{
    /* Code For Ass Goes Here */
    Ident ident = listlatteident->at(0)->getIdent();

    if(ident != "")
    {
        if(this->envs.top().is_variable_declared(ident)) {
            listlatteident->at(0)->accept(this);
        } else
        {
            this->error.addError(listlatteident->at(0)->line_number, "Usage of undeclared variable: " + ident);
        }
    } else
    {
        return; //self
    }

    /*for (ListLatteIdent::iterator i = listlatteident->begin() ; i != listlatteident->end() ; ++i)
    {
        (*i)->accept(this);
    }*/
}

void CorrectnessChecker::visitListExpr(ListExpr* listexpr)
{
    for (ListExpr::iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
    {
        (*i)->accept(this);
    }
}


void CorrectnessChecker::visitInteger(Integer x)
{
    /* Code for Integer Goes Here */
}

void CorrectnessChecker::visitChar(Char x)
{
    /* Code for Char Goes Here */
}

void CorrectnessChecker::visitDouble(Double x)
{
    /* Code for Double Goes Here */
}

void CorrectnessChecker::visitString(String x)
{
    /* Code for String Goes Here */
}

void CorrectnessChecker::visitIdent(Ident x)
{
    /* Code for Ident Goes Here */
}


CorrectnessChecker::CorrectnessChecker(vector<FnDef*> functions) : functions(functions)
{}

void CorrectnessChecker::check_types() {
    set<string> function_names;
    bool main_ = false;

    for(auto el: this->functions){
        if(el->ident_ == "main"){
            main_ = true;
            if(el->listarg_->size()){
                error.addError(el->line_number, "Main function got arguments");
            }
            if(el->type_->getType() != "int"){
                error.addError(el->line_number, "Main function should return an integer");
            }
        }
        if(function_names.find(el->ident_) != function_names.end()){
            error.addError(el->line_number, "Redefinition of a function: " + el->ident_);
        } else if(typeFetcher.is_function_predefined(el->ident_)){
            error.addError(el->line_number, "Redefinition of a predefined function " + el->ident_);
        }
        this->visitFnDef(el);
        function_names.insert(el->ident_);
    }

    if(!main_)
    {
        error.addError(0, "No main function!");
    }
}

