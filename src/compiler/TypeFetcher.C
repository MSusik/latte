/*** BNFC-Generated Visitor Design Pattern TypeFetcher. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "TypeFetcher.H"



void TypeFetcher::visitProgram(Program* t) {} //abstract class
void TypeFetcher::visitTopDef(TopDef* t) {} //abstract class
void TypeFetcher::visitArg(Arg* t) {} //abstract class
void TypeFetcher::visitClassInstr(ClassInstr* t) {} //abstract class
void TypeFetcher::visitBlock(Block* t) {} //abstract class
void TypeFetcher::visitStmt(Stmt* t) {} //abstract class
void TypeFetcher::visitItem(Item* t) {} //abstract class
void TypeFetcher::visitLatteIdent(LatteIdent* t) {} //abstract class
void TypeFetcher::visitType(Type* t) {} //abstract class
void TypeFetcher::visitExpr(Expr* t) {} //abstract class
void TypeFetcher::visitAddOp(AddOp* t) {} //abstract class
void TypeFetcher::visitMulOp(MulOp* t) {} //abstract class
void TypeFetcher::visitRelOp(RelOp* t) {} //abstract class


vector<string> TypeFetcher::getFunctionArgsTypes(Ident function_name, const vector<FnDef *> &functions) {

    vector<string> result;
    auto it = this->predefined_functions.find(function_name);
    if(it != predefined_functions.end())
    {
        return it->second.second;
    }

    for(auto it=this->functions.begin(); it != this->functions.end(); ++it)
    {
        if((*it)->ident_ == function_name)
        {
            ListArg *la = (*it)->listarg_;
            for(auto it = la->begin(); it != la->end(); ++it)
            {
                Ar* ar = (Ar*)(*it);
                result.push_back(ar->type_->getType());
            }

        }
    }
    return result;
}

bool TypeFetcher::is_function_predefined(Ident function_name)
{
    return this->predefined_functions.find(function_name) != this->predefined_functions.end();
}

string TypeFetcher::getFunctionType(Ident function_name, int line)
{

    auto it = this->predefined_functions.find(function_name);
    if(it != predefined_functions.end())
    {
        return it->second.first;
    }


    for(auto it=this->functions.begin(); it != this->functions.end(); ++it)
    {
        if((*it)->ident_ == function_name)
        {
            // this is the function we are looking for
            return (*it)->type_->getType();
        }
    }
    // No such function
    this->errors->addError(line, "Function not defined: " + function_name);
    return "";
}

string TypeFetcher::getType(Expr* ex, vector<FnDef *> functions, const Environment& env, ErrorState *errors){
    this->functions = functions;
    this->env = env;
    this->errors = errors;
    ex->accept(this);
    return this->type;
}


void TypeFetcher::checkStatement(Stmt *sm, vector<FnDef *> functions, const Environment &env, ErrorState *errors) {
    this->functions = functions;
    this->env = env;
    this->errors = errors;
    sm->accept(this);
}


void TypeFetcher::visitProg(Prog *prog)
{
    /* Code For Prog Goes Here */

    prog->listtopdef_->accept(this);

}

void TypeFetcher::visitFnDef(FnDef *fndef)
{
    /* Code For FnDef Goes Here */

    fndef->type_->accept(this);
    visitIdent(fndef->ident_);
    fndef->listarg_->accept(this);
    fndef->block_->accept(this);

}

void TypeFetcher::visitClassDefNoInher(ClassDefNoInher *classdefnoinher)
{
    /* Code For ClassDefNoInher Goes Here */

    visitIdent(classdefnoinher->ident_);
    classdefnoinher->listclassinstr_->accept(this);

}

void TypeFetcher::visitClassDefInher(ClassDefInher *classdefinher)
{
    /* Code For ClassDefInher Goes Here */

    visitIdent(classdefinher->ident_1);
    visitIdent(classdefinher->ident_2);
    classdefinher->listclassinstr_->accept(this);

}

void TypeFetcher::visitAr(Ar *ar)
{
    /* Code For Ar Goes Here */

    ar->type_->accept(this);
    visitIdent(ar->ident_);

}

void TypeFetcher::visitMethodDef(MethodDef *methoddef)
{
    /* Code For MethodDef Goes Here */

    methoddef->type_->accept(this);
    visitIdent(methoddef->ident_);
    methoddef->listarg_->accept(this);
    methoddef->block_->accept(this);

}

void TypeFetcher::visitFieldDef(FieldDef *fielddef)
{
    /* Code For FieldDef Goes Here */

    fielddef->type_->accept(this);
    visitIdent(fielddef->ident_);

}

void TypeFetcher::visitBlk(Blk *blk)
{
    /* Code For Blk Goes Here */

    blk->liststmt_->accept(this);

}

void TypeFetcher::visitEmpty(Empty *empty)
{
    /* Code For Empty Goes Here */


}

void TypeFetcher::visitBStmt(BStmt *bstmt)
{
    /* Code For BStmt Goes Here */

    bstmt->block_->accept(this);

}

void TypeFetcher::visitDecl(Decl *decl)
{
    /* Code For Decl Goes Here */

    decl->type_->accept(this);
    decl->listitem_->accept(this);

}

void TypeFetcher::visitAss(Ass *ass)
{
    /* Code For Ass Goes Here */

    ass->listlatteident_->accept(this);
    ass->expr_->accept(this);

}

void TypeFetcher::visitAssArr(AssArr *assarr)
{
    /* Code For AssArr Goes Here */

    assarr->listlatteident_->accept(this);
    assarr->type_->accept(this);
    assarr->expr_->accept(this);

}

void TypeFetcher::visitAssObj(AssObj *assobj)
{
    /* Code For AssObj Goes Here */

    assobj->listlatteident_->accept(this);
    assobj->type_->accept(this);

}

void TypeFetcher::visitIncr(Incr *incr)
{
    /* Code For Incr Goes Here */
    auto p = env.get_type(incr->listlatteident_->at(0)->getIdent());
    if(p == nullptr){
        this->errors->addError(incr->line_number, "Variable not definied");
        return;
    }
    else if(p->getType() != "int") {
        this->errors->addError(incr->line_number, "Can't increment a non integer");
    }


    incr->listlatteident_->accept(this);

}

void TypeFetcher::visitDecr(Decr *decr)
{
    /* Code For Decr Goes Here */
    auto p = env.get_type(decr->listlatteident_->at(0)->getIdent());
    if(p == nullptr){
        this->errors->addError(decr->line_number, "Variable not definied");
        return;
    }
    else if(p->getType() != "int") {
        this->errors->addError(decr->line_number, "Can't decrement a non integer");
    }
    decr->listlatteident_->accept(this);

}

void TypeFetcher::visitRet(Ret *ret)
{
    /* Code For Ret Goes Here */

    ret->expr_->accept(this);

}

void TypeFetcher::visitVRet(VRet *vret)
{
    /* Code For VRet Goes Here */


}

void TypeFetcher::visitCond(Cond *cond)
{
    /* Code For Cond Goes Here */

    cond->expr_->accept(this);
    cond->stmt_->accept(this);

}

void TypeFetcher::visitCondElse(CondElse *condelse)
{
    /* Code For CondElse Goes Here */

    condelse->expr_->accept(this);
    condelse->stmt_1->accept(this);
    condelse->stmt_2->accept(this);

}

void TypeFetcher::visitWhile(While *while_)
{
    /* Code For While Goes Here */

    while_->expr_->accept(this);
    while_->stmt_->accept(this);

}

void TypeFetcher::visitForeach(Foreach *foreach)
{
    /* Code For Foreach Goes Here */

    foreach->type_->accept(this);
    visitIdent(foreach->ident_);
    foreach->listlatteident_->accept(this);
    foreach->stmt_->accept(this);

}

void TypeFetcher::visitSExp(SExp *sexp)
{
    /* Code For SExp Goes Here */

    sexp->expr_->accept(this);

}

void TypeFetcher::visitNoInit(NoInit *noinit)
{
    /* Code For NoInit Goes Here */

    visitIdent(noinit->ident_);

}

void TypeFetcher::visitInit(Init *init)
{
    /* Code For Init Goes Here */

    visitIdent(init->ident_);
    init->expr_->accept(this);

}

void TypeFetcher::visitInitArray(InitArray *initarray)
{
    /* Code For InitArray Goes Here */

    visitIdent(initarray->ident_);
    initarray->type_->accept(this);
    initarray->expr_->accept(this);

}

void TypeFetcher::visitInitObj(InitObj *initobj)
{
    /* Code For InitObj Goes Here */

    visitIdent(initobj->ident_);
    initobj->type_->accept(this);

}

void TypeFetcher::visitSingleIdent(SingleIdent *singleident)
{
    /* Code For SingleIdent Goes Here */

    visitIdent(singleident->ident_);

}

void TypeFetcher::visitArrayIdent(ArrayIdent *arrayident)
{
    /* Code For ArrayIdent Goes Here */

    visitIdent(arrayident->ident_);
    arrayident->expr_->accept(this);

}

void TypeFetcher::visitSelfIdent(SelfIdent *selfident)
{
    /* Code For SelfIdent Goes Here */


}

void TypeFetcher::visitClass(Class *class_)
{
    /* Code For Class Goes Here */

    visitIdent(class_->ident_);

}

void TypeFetcher::visitInt(Int *int_)
{
    /* Code For Int Goes Here */


}

void TypeFetcher::visitStr(Str *str)
{
    /* Code For Str Goes Here */


}

void TypeFetcher::visitBool(Bool *bool_)
{
    /* Code For Bool Goes Here */


}

void TypeFetcher::visitVoid(Void *void_)
{
    /* Code For Void Goes Here */


}

void TypeFetcher::visitArrayType(ArrayType *arraytype)
{
    /* Code For ArrayType Goes Here */

    arraytype->type_->accept(this);

}

void TypeFetcher::visitEVar(EVar *evar)
{
    /* Code For EVar Goes Here */
    Ident id = evar->listlatteident_->at(0)->getIdent();

    Type *type = this->env.get_type(id);
    if(type == nullptr){
        this->errors->addError(evar->line_number, "Undefined variable: " + id);
    }
    this->type = type->getType();
    // TODO evar->listlatteident_->accept(this);

}

void TypeFetcher::visitELitInt(ELitInt *elitint)
{
    /* Code For ELitInt Goes Here */
    this->type = "int";
    //visitInteger(elitint->integer_);

}

void TypeFetcher::visitELitFalse(ELitFalse *elitfalse)
{
    /* Code For ELitFalse Goes Here */
    this->type = "boolean";

}

void TypeFetcher::visitELitNull(ELitNull *elitnull)
{
    /* Code For ELitNull Goes Here */
    // TODO this->type = "void";

}

void TypeFetcher::visitELitTrue(ELitTrue *elittrue)
{
    /* Code For ELitTrue Goes Here */
    this->type = "boolean";

}

void TypeFetcher::visitEApp(EApp *eapp)
{
    /* Code For EApp Goes Here */

    this->type = this->getFunctionType(eapp->ident_, eapp->line_number);
    //visitIdent(eapp->ident_);
    //eapp->listexpr_->accept(this);

}

void TypeFetcher::visitEInstanceApp(EInstanceApp *einstanceapp)
{
    /* Code For EInstanceApp Goes Here */
    // TODO
    einstanceapp->listlatteident_->accept(this);
    einstanceapp->listexpr_->accept(this);

}

void TypeFetcher::visitEString(EString *estring)
{
    /* Code For EString Goes Here */
    this->type = "string";
    //visitString(estring->string_);

}

void TypeFetcher::visitNeg(Neg *neg)
{
    /* Code For Neg Goes Here */
    // Doesn't change type
    neg->expr_->accept(this);
    if(this->type != "int")
    {
        this->errors->addError(neg->line_number, "Can't negate non-integer");
    }
}

void TypeFetcher::visitNot(Not *not_)
{
    /* Code For Not Goes Here */

    not_->expr_->accept(this);
    if(this->type != "boolean")
    {
        this->errors->addError(not_->line_number, "Can't use not on non-boolean");
    }

}

void TypeFetcher::visitECast(ECast *ecast)
{
    /* Code For ECast Goes Here */
    // TODO
    visitIdent(ecast->ident_);
    ecast->expr_->accept(this);

}

void TypeFetcher::visitEMul(EMul *emul)
{
    /* Code For EMul Goes Here */

    emul->expr_1->accept(this);
    if(this->type != "int")
    {
        this->errors->addError(emul->line_number, "You can do maths only on integers!");
    }
    emul->mulop_->accept(this);
    emul->expr_2->accept(this);
    if(this->type != "int")
    {
        this->errors->addError(emul->line_number, "You can do maths only on integers!");
    }
    this->type = "int";
}

void TypeFetcher::visitEAdd(EAdd *eadd)
{
    /* Code For EAdd Goes Here */

    eadd->expr_1->accept(this);
    string type1 = this->type;

    if(!(type1 == "int" || (type1 == "string" && eadd->addop_->isPlus())))
    {
        this->errors->addError(eadd->line_number, "Wrong type!");
    }
    eadd->addop_->accept(this);
    eadd->expr_2->accept(this);
    eadd->expr_2->accept(this);
    if(this->type != type1)
    {
        this->errors->addError(eadd->line_number, "Wrong type!");
    }
    this->type = type1;
}

void TypeFetcher::visitERel(ERel *erel)
{
    /* Code For ERel Goes Here */

    erel->expr_1->accept(this);
    string type1 = this->type;
    if(type1 != "int" && !erel->relop_->noOrder())
    {
        this->errors->addError(erel->line_number, "You can't compare non integers");
    }
    erel->relop_->accept(this);
    erel->expr_2->accept(this);
    if(this->type != type1){
        this->errors->addError(erel->line_number, "You can't compare different types");
    }
    this->type = "boolean";
}

void TypeFetcher::visitEAnd(EAnd *eand)
{
    /* Code For EAnd Goes Here */

    eand->expr_1->accept(this);
    if(this->type != "boolean"){
        this->errors->addError(eand->line_number, "You can't use and on non-booleans");
    }
    eand->expr_2->accept(this);
    if(this->type != "boolean"){
        this->errors->addError(eand->line_number, "You can't use and on non-booleans");
    }
    this->type = "boolean";

}

void TypeFetcher::visitEOr(EOr *eor)
{
    /* Code For EOr Goes Here */

    eor->expr_1->accept(this);
    if(this->type != "boolean"){
        this->errors->addError(eor->line_number, "You can't use and on non-booleans");
    }
    eor->expr_2->accept(this);
    if(this->type != "boolean"){
        this->errors->addError(eor->line_number, "You can't use and on non-booleans");
    }
    this->type = "boolean";

}

void TypeFetcher::visitPlus(Plus *plus)
{
    /* Code For Plus Goes Here */


}

void TypeFetcher::visitMinus(Minus *minus)
{
    /* Code For Minus Goes Here */


}

void TypeFetcher::visitTimes(Times *times)
{
    /* Code For Times Goes Here */


}

void TypeFetcher::visitDiv(Div *div)
{
    /* Code For Div Goes Here */


}

void TypeFetcher::visitMod(Mod *mod)
{
    /* Code For Mod Goes Here */


}

void TypeFetcher::visitLTH(LTH *lth)
{
    /* Code For LTH Goes Here */


}

void TypeFetcher::visitLE(LE *le)
{
    /* Code For LE Goes Here */


}

void TypeFetcher::visitGTH(GTH *gth)
{
    /* Code For GTH Goes Here */


}

void TypeFetcher::visitGE(GE *ge)
{
    /* Code For GE Goes Here */


}

void TypeFetcher::visitEQU(EQU *equ)
{
    /* Code For EQU Goes Here */


}

void TypeFetcher::visitNE(NE *ne)
{
    /* Code For NE Goes Here */


}


void TypeFetcher::visitListTopDef(ListTopDef* listtopdef)
{
    for (ListTopDef::iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void TypeFetcher::visitListArg(ListArg* listarg)
{
    for (ListArg::iterator i = listarg->begin() ; i != listarg->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void TypeFetcher::visitListClassInstr(ListClassInstr* listclassinstr)
{
    for (ListClassInstr::iterator i = listclassinstr->begin() ; i != listclassinstr->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void TypeFetcher::visitListStmt(ListStmt* liststmt)
{
    for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void TypeFetcher::visitListItem(ListItem* listitem)
{
    for (ListItem::iterator i = listitem->begin() ; i != listitem->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void TypeFetcher::visitListLatteIdent(ListLatteIdent* listlatteident)
{
    for (ListLatteIdent::iterator i = listlatteident->begin() ; i != listlatteident->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void TypeFetcher::visitListExpr(ListExpr* listexpr)
{
    for (ListExpr::iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
    {
        (*i)->accept(this);
    }
}


void TypeFetcher::visitInteger(Integer x)
{
    /* Code for Integer Goes Here */
}

void TypeFetcher::visitChar(Char x)
{
    /* Code for Char Goes Here */
}

void TypeFetcher::visitDouble(Double x)
{
    /* Code for Double Goes Here */
}

void TypeFetcher::visitString(String x)
{
    /* Code for String Goes Here */
}

void TypeFetcher::visitIdent(Ident x)
{
    /* Code for Ident Goes Here */
}


TypeFetcher::TypeFetcher() {
    vector<string> printIntArgs = {"int"};
    vector<string> printStringArgs = {"string"};
    vector<string> empty;

    predefined_functions.insert(make_pair("printInt", make_pair("void", printIntArgs)));
    predefined_functions.insert(make_pair("printString", make_pair("void", printStringArgs)));
    predefined_functions.insert(make_pair("error", make_pair("void", empty)));
    predefined_functions.insert(make_pair("readInt", make_pair("int", empty)));
    predefined_functions.insert(make_pair("readString", make_pair("string", empty)));
}
