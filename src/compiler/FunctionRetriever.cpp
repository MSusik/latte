//
// Created by msusik on 01.01.16.
//

#include "FunctionRetriever.h"

FunctionRetriever::FunctionRetriever(Prog *prog) {
    prog->listtopdef_->accept(this);
}

vector<FnDef *> FunctionRetriever::getFunctions() {
    return this->functions;
}

void FunctionRetriever::visitFnDef(FnDef *p) {
    this->functions.push_back(p);
}




void FunctionRetriever::visitProgram(Program* t) {} //abstract class
void FunctionRetriever::visitTopDef(TopDef* t) {} //abstract class
void FunctionRetriever::visitArg(Arg* t) {} //abstract class
void FunctionRetriever::visitClassInstr(ClassInstr* t) {} //abstract class
void FunctionRetriever::visitBlock(Block* t) {} //abstract class
void FunctionRetriever::visitStmt(Stmt* t) {} //abstract class
void FunctionRetriever::visitItem(Item* t) {} //abstract class
void FunctionRetriever::visitLatteIdent(LatteIdent* t) {} //abstract class
void FunctionRetriever::visitType(Type* t) {} //abstract class
void FunctionRetriever::visitExpr(Expr* t) {} //abstract class
void FunctionRetriever::visitAddOp(AddOp* t) {} //abstract class
void FunctionRetriever::visitMulOp(MulOp* t) {} //abstract class
void FunctionRetriever::visitRelOp(RelOp* t) {} //abstract class

void FunctionRetriever::visitProg(Prog *prog)
{
    /* Code For Prog Goes Here */

    prog->listtopdef_->accept(this);

}

void FunctionRetriever::visitClassDefNoInher(ClassDefNoInher *classdefnoinher)
{
    /* Code For ClassDefNoInher Goes Here */

    visitIdent(classdefnoinher->ident_);
    classdefnoinher->listclassinstr_->accept(this);

}

void FunctionRetriever::visitClassDefInher(ClassDefInher *classdefinher)
{
    /* Code For ClassDefInher Goes Here */

    visitIdent(classdefinher->ident_1);
    visitIdent(classdefinher->ident_2);
    classdefinher->listclassinstr_->accept(this);

}

void FunctionRetriever::visitAr(Ar *ar)
{
    /* Code For Ar Goes Here */
    ar->type_->accept(this);
    visitIdent(ar->ident_);

}

void FunctionRetriever::visitMethodDef(MethodDef *methoddef)
{
    /* Code For MethodDef Goes Here */

    methoddef->type_->accept(this);
    visitIdent(methoddef->ident_);
    methoddef->listarg_->accept(this);
    methoddef->block_->accept(this);

}

void FunctionRetriever::visitFieldDef(FieldDef *fielddef)
{
    /* Code For FieldDef Goes Here */

    fielddef->type_->accept(this);
    visitIdent(fielddef->ident_);

}

void FunctionRetriever::visitBlk(Blk *blk)
{
    /* Code For Blk Goes Here */

    blk->liststmt_->accept(this);

}

void FunctionRetriever::visitEmpty(Empty *empty)
{
    /* Code For Empty Goes Here */


}

void FunctionRetriever::visitBStmt(BStmt *bstmt)
{
    /* Code For BStmt Goes Here */

    bstmt->block_->accept(this);

}

void FunctionRetriever::visitDecl(Decl *decl)
{
    /* Code For Decl Goes Here */

    decl->type_->accept(this);
    decl->listitem_->accept(this);

}

void FunctionRetriever::visitAss(Ass *ass)
{
    /* Code For Ass Goes Here */

    ass->listlatteident_->accept(this);
    ass->expr_->accept(this);

}

void FunctionRetriever::visitAssArr(AssArr *assarr)
{
    /* Code For AssArr Goes Here */

    assarr->listlatteident_->accept(this);
    assarr->type_->accept(this);
    assarr->expr_->accept(this);

}

void FunctionRetriever::visitAssObj(AssObj *assobj)
{
    /* Code For AssObj Goes Here */

    assobj->listlatteident_->accept(this);
    assobj->type_->accept(this);

}

void FunctionRetriever::visitIncr(Incr *incr)
{
    /* Code For Incr Goes Here */

    incr->listlatteident_->accept(this);

}

void FunctionRetriever::visitDecr(Decr *decr)
{
    /* Code For Decr Goes Here */

    decr->listlatteident_->accept(this);

}

void FunctionRetriever::visitRet(Ret *ret)
{
    /* Code For Ret Goes Here */

    ret->expr_->accept(this);

}

void FunctionRetriever::visitVRet(VRet *vret)
{
    /* Code For VRet Goes Here */


}

void FunctionRetriever::visitCond(Cond *cond)
{
    /* Code For Cond Goes Here */

    cond->expr_->accept(this);
    cond->stmt_->accept(this);

}

void FunctionRetriever::visitCondElse(CondElse *condelse)
{
    /* Code For CondElse Goes Here */

    condelse->expr_->accept(this);
    condelse->stmt_1->accept(this);
    condelse->stmt_2->accept(this);

}

void FunctionRetriever::visitWhile(While *while_)
{
    /* Code For While Goes Here */

    while_->expr_->accept(this);
    while_->stmt_->accept(this);

}

void FunctionRetriever::visitForeach(Foreach *foreach)
{
    /* Code For Foreach Goes Here */

    foreach->type_->accept(this);
    visitIdent(foreach->ident_);
    foreach->listlatteident_->accept(this);
    foreach->stmt_->accept(this);

}

void FunctionRetriever::visitSExp(SExp *sexp)
{
    /* Code For SExp Goes Here */

    sexp->expr_->accept(this);

}

void FunctionRetriever::visitNoInit(NoInit *noinit)
{
    /* Code For NoInit Goes Here */

    visitIdent(noinit->ident_);

}

void FunctionRetriever::visitInit(Init *init)
{
    /* Code For Init Goes Here */

    visitIdent(init->ident_);
    init->expr_->accept(this);

}

void FunctionRetriever::visitInitArray(InitArray *initarray)
{
    /* Code For InitArray Goes Here */

    visitIdent(initarray->ident_);
    initarray->type_->accept(this);
    initarray->expr_->accept(this);

}

void FunctionRetriever::visitInitObj(InitObj *initobj)
{
    /* Code For InitObj Goes Here */

    visitIdent(initobj->ident_);
    initobj->type_->accept(this);

}

void FunctionRetriever::visitSingleIdent(SingleIdent *singleident)
{
    /* Code For SingleIdent Goes Here */

    visitIdent(singleident->ident_);

}

void FunctionRetriever::visitArrayIdent(ArrayIdent *arrayident)
{
    /* Code For ArrayIdent Goes Here */

    visitIdent(arrayident->ident_);
    arrayident->expr_->accept(this);

}

void FunctionRetriever::visitSelfIdent(SelfIdent *selfident)
{
    /* Code For SelfIdent Goes Here */


}

void FunctionRetriever::visitClass(Class *class_)
{
    /* Code For Class Goes Here */

    visitIdent(class_->ident_);

}

void FunctionRetriever::visitInt(Int *int_)
{
    /* Code For Int Goes Here */


}

void FunctionRetriever::visitStr(Str *str)
{
    /* Code For Str Goes Here */


}

void FunctionRetriever::visitBool(Bool *bool_)
{
    /* Code For Bool Goes Here */


}

void FunctionRetriever::visitVoid(Void *void_)
{
    /* Code For Void Goes Here */


}

void FunctionRetriever::visitArrayType(ArrayType *arraytype)
{
    /* Code For ArrayType Goes Here */

    arraytype->type_->accept(this);

}

void FunctionRetriever::visitEVar(EVar *evar)
{
    /* Code For EVar Goes Here */

    evar->listlatteident_->accept(this);

}

void FunctionRetriever::visitELitInt(ELitInt *elitint)
{
    /* Code For ELitInt Goes Here */

    visitInteger(elitint->integer_);

}

void FunctionRetriever::visitELitFalse(ELitFalse *elitfalse)
{
    /* Code For ELitFalse Goes Here */


}

void FunctionRetriever::visitELitNull(ELitNull *elitnull)
{
    /* Code For ELitNull Goes Here */


}

void FunctionRetriever::visitELitTrue(ELitTrue *elittrue)
{
    /* Code For ELitTrue Goes Here */


}

void FunctionRetriever::visitEApp(EApp *eapp)
{
    /* Code For EApp Goes Here */

    visitIdent(eapp->ident_);
    eapp->listexpr_->accept(this);

}

void FunctionRetriever::visitEInstanceApp(EInstanceApp *einstanceapp)
{
    /* Code For EInstanceApp Goes Here */

    einstanceapp->listlatteident_->accept(this);
    einstanceapp->listexpr_->accept(this);

}

void FunctionRetriever::visitEString(EString *estring)
{
    /* Code For EString Goes Here */

    visitString(estring->string_);

}

void FunctionRetriever::visitNeg(Neg *neg)
{
    /* Code For Neg Goes Here */

    neg->expr_->accept(this);

}

void FunctionRetriever::visitNot(Not *not_)
{
    /* Code For Not Goes Here */

    not_->expr_->accept(this);

}

void FunctionRetriever::visitECast(ECast *ecast)
{
    /* Code For ECast Goes Here */

    visitIdent(ecast->ident_);
    ecast->expr_->accept(this);

}

void FunctionRetriever::visitEMul(EMul *emul)
{
    /* Code For EMul Goes Here */

    emul->expr_1->accept(this);
    emul->mulop_->accept(this);
    emul->expr_2->accept(this);

}

void FunctionRetriever::visitEAdd(EAdd *eadd)
{
    /* Code For EAdd Goes Here */

    eadd->expr_1->accept(this);
    eadd->addop_->accept(this);
    eadd->expr_2->accept(this);

}

void FunctionRetriever::visitERel(ERel *erel)
{
    /* Code For ERel Goes Here */

    erel->expr_1->accept(this);
    erel->relop_->accept(this);
    erel->expr_2->accept(this);

}

void FunctionRetriever::visitEAnd(EAnd *eand)
{
    /* Code For EAnd Goes Here */

    eand->expr_1->accept(this);
    eand->expr_2->accept(this);

}

void FunctionRetriever::visitEOr(EOr *eor)
{
    /* Code For EOr Goes Here */

    eor->expr_1->accept(this);
    eor->expr_2->accept(this);

}

void FunctionRetriever::visitPlus(Plus *plus)
{
    /* Code For Plus Goes Here */


}

void FunctionRetriever::visitMinus(Minus *minus)
{
    /* Code For Minus Goes Here */


}

void FunctionRetriever::visitTimes(Times *times)
{
    /* Code For Times Goes Here */


}

void FunctionRetriever::visitDiv(Div *div)
{
    /* Code For Div Goes Here */


}

void FunctionRetriever::visitMod(Mod *mod)
{
    /* Code For Mod Goes Here */


}

void FunctionRetriever::visitLTH(LTH *lth)
{
    /* Code For LTH Goes Here */


}

void FunctionRetriever::visitLE(LE *le)
{
    /* Code For LE Goes Here */


}

void FunctionRetriever::visitGTH(GTH *gth)
{
    /* Code For GTH Goes Here */


}

void FunctionRetriever::visitGE(GE *ge)
{
    /* Code For GE Goes Here */


}

void FunctionRetriever::visitEQU(EQU *equ)
{
    /* Code For EQU Goes Here */


}

void FunctionRetriever::visitNE(NE *ne)
{
    /* Code For NE Goes Here */


}


void FunctionRetriever::visitListTopDef(ListTopDef* listtopdef)
{
    for (ListTopDef::iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void FunctionRetriever::visitListArg(ListArg* listarg)
{
    for (ListArg::iterator i = listarg->begin() ; i != listarg->end() ; ++i)
    {
        //arguments_names.insert((*i)->)
        (*i)->accept(this);
    }
}

void FunctionRetriever::visitListClassInstr(ListClassInstr* listclassinstr)
{
    for (ListClassInstr::iterator i = listclassinstr->begin() ; i != listclassinstr->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void FunctionRetriever::visitListStmt(ListStmt* liststmt)
{
    for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void FunctionRetriever::visitListItem(ListItem* listitem)
{
    for (ListItem::iterator i = listitem->begin() ; i != listitem->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void FunctionRetriever::visitListLatteIdent(ListLatteIdent* listlatteident)
{
    for (ListLatteIdent::iterator i = listlatteident->begin() ; i != listlatteident->end() ; ++i)
    {
        (*i)->accept(this);
    }
}

void FunctionRetriever::visitListExpr(ListExpr* listexpr)
{
    for (ListExpr::iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
    {
        (*i)->accept(this);
    }
}


void FunctionRetriever::visitInteger(Integer x)
{
    /* Code for Integer Goes Here */
}

void FunctionRetriever::visitChar(Char x)
{
    /* Code for Char Goes Here */
}

void FunctionRetriever::visitDouble(Double x)
{
    /* Code for Double Goes Here */
}

void FunctionRetriever::visitString(String x)
{
    /* Code for String Goes Here */
}

void FunctionRetriever::visitIdent(Ident x)
{
    /* Code for Ident Goes Here */
}
