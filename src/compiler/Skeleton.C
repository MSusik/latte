/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"



void Skeleton::visitProgram(Program* t) {} //abstract class
void Skeleton::visitTopDef(TopDef* t) {} //abstract class
void Skeleton::visitArg(Arg* t) {} //abstract class
void Skeleton::visitClassInstr(ClassInstr* t) {} //abstract class
void Skeleton::visitBlock(Block* t) {} //abstract class
void Skeleton::visitStmt(Stmt* t) {} //abstract class
void Skeleton::visitItem(Item* t) {} //abstract class
void Skeleton::visitLatteIdent(LatteIdent* t) {} //abstract class
void Skeleton::visitType(Type* t) {} //abstract class
void Skeleton::visitExpr(Expr* t) {} //abstract class
void Skeleton::visitAddOp(AddOp* t) {} //abstract class
void Skeleton::visitMulOp(MulOp* t) {} //abstract class
void Skeleton::visitRelOp(RelOp* t) {} //abstract class

void Skeleton::visitProg(Prog *prog)
{
  /* Code For Prog Goes Here */

  prog->listtopdef_->accept(this);

}

void Skeleton::visitFnDef(FnDef *fndef)
{
  /* Code For FnDef Goes Here */

  fndef->type_->accept(this);
  visitIdent(fndef->ident_);
  fndef->listarg_->accept(this);
  fndef->block_->accept(this);

}

void Skeleton::visitClassDefNoInher(ClassDefNoInher *classdefnoinher)
{
  /* Code For ClassDefNoInher Goes Here */

  visitIdent(classdefnoinher->ident_);
  classdefnoinher->listclassinstr_->accept(this);

}

void Skeleton::visitClassDefInher(ClassDefInher *classdefinher)
{
  /* Code For ClassDefInher Goes Here */

  visitIdent(classdefinher->ident_1);
  visitIdent(classdefinher->ident_2);
  classdefinher->listclassinstr_->accept(this);

}

void Skeleton::visitAr(Ar *ar)
{
  /* Code For Ar Goes Here */

  ar->type_->accept(this);
  visitIdent(ar->ident_);

}

void Skeleton::visitMethodDef(MethodDef *methoddef)
{
  /* Code For MethodDef Goes Here */

  methoddef->type_->accept(this);
  visitIdent(methoddef->ident_);
  methoddef->listarg_->accept(this);
  methoddef->block_->accept(this);

}

void Skeleton::visitFieldDef(FieldDef *fielddef)
{
  /* Code For FieldDef Goes Here */

  fielddef->type_->accept(this);
  visitIdent(fielddef->ident_);

}

void Skeleton::visitBlk(Blk *blk)
{
  /* Code For Blk Goes Here */

  blk->liststmt_->accept(this);

}

void Skeleton::visitEmpty(Empty *empty)
{
  /* Code For Empty Goes Here */


}

void Skeleton::visitBStmt(BStmt *bstmt)
{
  /* Code For BStmt Goes Here */

  bstmt->block_->accept(this);

}

void Skeleton::visitDecl(Decl *decl)
{
  /* Code For Decl Goes Here */

  decl->type_->accept(this);
  decl->listitem_->accept(this);

}

void Skeleton::visitAss(Ass *ass)
{
  /* Code For Ass Goes Here */

  ass->listlatteident_->accept(this);
  ass->expr_->accept(this);

}

void Skeleton::visitAssArr(AssArr *assarr)
{
  /* Code For AssArr Goes Here */

  assarr->listlatteident_->accept(this);
  assarr->type_->accept(this);
  assarr->expr_->accept(this);

}

void Skeleton::visitAssObj(AssObj *assobj)
{
  /* Code For AssObj Goes Here */

  assobj->listlatteident_->accept(this);
  assobj->type_->accept(this);

}

void Skeleton::visitIncr(Incr *incr)
{
  /* Code For Incr Goes Here */

  incr->listlatteident_->accept(this);

}

void Skeleton::visitDecr(Decr *decr)
{
  /* Code For Decr Goes Here */

  decr->listlatteident_->accept(this);

}

void Skeleton::visitRet(Ret *ret)
{
  /* Code For Ret Goes Here */

  ret->expr_->accept(this);

}

void Skeleton::visitVRet(VRet *vret)
{
  /* Code For VRet Goes Here */


}

void Skeleton::visitCond(Cond *cond)
{
  /* Code For Cond Goes Here */

  cond->expr_->accept(this);
  cond->stmt_->accept(this);

}

void Skeleton::visitCondElse(CondElse *condelse)
{
  /* Code For CondElse Goes Here */

  condelse->expr_->accept(this);
  condelse->stmt_1->accept(this);
  condelse->stmt_2->accept(this);

}

void Skeleton::visitWhile(While *while_)
{
  /* Code For While Goes Here */

  while_->expr_->accept(this);
  while_->stmt_->accept(this);

}

void Skeleton::visitForeach(Foreach *foreach)
{
  /* Code For Foreach Goes Here */

  foreach->type_->accept(this);
  visitIdent(foreach->ident_);
  foreach->listlatteident_->accept(this);
  foreach->stmt_->accept(this);

}

void Skeleton::visitSExp(SExp *sexp)
{
  /* Code For SExp Goes Here */

  sexp->expr_->accept(this);

}

void Skeleton::visitNoInit(NoInit *noinit)
{
  /* Code For NoInit Goes Here */

  visitIdent(noinit->ident_);

}

void Skeleton::visitInit(Init *init)
{
  /* Code For Init Goes Here */

  visitIdent(init->ident_);
  init->expr_->accept(this);

}

void Skeleton::visitInitArray(InitArray *initarray)
{
  /* Code For InitArray Goes Here */

  visitIdent(initarray->ident_);
  initarray->type_->accept(this);
  initarray->expr_->accept(this);

}

void Skeleton::visitInitObj(InitObj *initobj)
{
  /* Code For InitObj Goes Here */

  visitIdent(initobj->ident_);
  initobj->type_->accept(this);

}

void Skeleton::visitSingleIdent(SingleIdent *singleident)
{
  /* Code For SingleIdent Goes Here */

  visitIdent(singleident->ident_);

}

void Skeleton::visitArrayIdent(ArrayIdent *arrayident)
{
  /* Code For ArrayIdent Goes Here */

  visitIdent(arrayident->ident_);
  arrayident->expr_->accept(this);

}

void Skeleton::visitSelfIdent(SelfIdent *selfident)
{
  /* Code For SelfIdent Goes Here */


}

void Skeleton::visitClass(Class *class_)
{
  /* Code For Class Goes Here */

  visitIdent(class_->ident_);

}

void Skeleton::visitInt(Int *int_)
{
  /* Code For Int Goes Here */


}

void Skeleton::visitStr(Str *str)
{
  /* Code For Str Goes Here */


}

void Skeleton::visitBool(Bool *bool_)
{
  /* Code For Bool Goes Here */


}

void Skeleton::visitVoid(Void *void_)
{
  /* Code For Void Goes Here */


}

void Skeleton::visitArrayType(ArrayType *arraytype)
{
  /* Code For ArrayType Goes Here */

  arraytype->type_->accept(this);

}

void Skeleton::visitEVar(EVar *evar)
{
  /* Code For EVar Goes Here */

  evar->listlatteident_->accept(this);

}

void Skeleton::visitELitInt(ELitInt *elitint)
{
  /* Code For ELitInt Goes Here */

  visitInteger(elitint->integer_);

}

void Skeleton::visitELitFalse(ELitFalse *elitfalse)
{
  /* Code For ELitFalse Goes Here */


}

void Skeleton::visitELitNull(ELitNull *elitnull)
{
  /* Code For ELitNull Goes Here */


}

void Skeleton::visitELitTrue(ELitTrue *elittrue)
{
  /* Code For ELitTrue Goes Here */


}

void Skeleton::visitEApp(EApp *eapp)
{
  /* Code For EApp Goes Here */

  visitIdent(eapp->ident_);
  eapp->listexpr_->accept(this);

}

void Skeleton::visitEInstanceApp(EInstanceApp *einstanceapp)
{
  /* Code For EInstanceApp Goes Here */

  einstanceapp->listlatteident_->accept(this);
  einstanceapp->listexpr_->accept(this);

}

void Skeleton::visitEString(EString *estring)
{
  /* Code For EString Goes Here */

  visitString(estring->string_);

}

void Skeleton::visitNeg(Neg *neg)
{
  /* Code For Neg Goes Here */

  neg->expr_->accept(this);

}

void Skeleton::visitNot(Not *not_)
{
  /* Code For Not Goes Here */

  not_->expr_->accept(this);

}

void Skeleton::visitECast(ECast *ecast)
{
  /* Code For ECast Goes Here */

  visitIdent(ecast->ident_);
  ecast->expr_->accept(this);

}

void Skeleton::visitEMul(EMul *emul)
{
  /* Code For EMul Goes Here */

  emul->expr_1->accept(this);
  emul->mulop_->accept(this);
  emul->expr_2->accept(this);

}

void Skeleton::visitEAdd(EAdd *eadd)
{
  /* Code For EAdd Goes Here */

  eadd->expr_1->accept(this);
  eadd->addop_->accept(this);
  eadd->expr_2->accept(this);

}

void Skeleton::visitERel(ERel *erel)
{
  /* Code For ERel Goes Here */

  erel->expr_1->accept(this);
  erel->relop_->accept(this);
  erel->expr_2->accept(this);

}

void Skeleton::visitEAnd(EAnd *eand)
{
  /* Code For EAnd Goes Here */

  eand->expr_1->accept(this);
  eand->expr_2->accept(this);

}

void Skeleton::visitEOr(EOr *eor)
{
  /* Code For EOr Goes Here */

  eor->expr_1->accept(this);
  eor->expr_2->accept(this);

}

void Skeleton::visitPlus(Plus *plus)
{
  /* Code For Plus Goes Here */


}

void Skeleton::visitMinus(Minus *minus)
{
  /* Code For Minus Goes Here */


}

void Skeleton::visitTimes(Times *times)
{
  /* Code For Times Goes Here */


}

void Skeleton::visitDiv(Div *div)
{
  /* Code For Div Goes Here */


}

void Skeleton::visitMod(Mod *mod)
{
  /* Code For Mod Goes Here */


}

void Skeleton::visitLTH(LTH *lth)
{
  /* Code For LTH Goes Here */


}

void Skeleton::visitLE(LE *le)
{
  /* Code For LE Goes Here */


}

void Skeleton::visitGTH(GTH *gth)
{
  /* Code For GTH Goes Here */


}

void Skeleton::visitGE(GE *ge)
{
  /* Code For GE Goes Here */


}

void Skeleton::visitEQU(EQU *equ)
{
  /* Code For EQU Goes Here */


}

void Skeleton::visitNE(NE *ne)
{
  /* Code For NE Goes Here */


}


void Skeleton::visitListTopDef(ListTopDef* listtopdef)
{
  for (ListTopDef::iterator i = listtopdef->begin() ; i != listtopdef->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListArg(ListArg* listarg)
{
  for (ListArg::iterator i = listarg->begin() ; i != listarg->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListClassInstr(ListClassInstr* listclassinstr)
{
  for (ListClassInstr::iterator i = listclassinstr->begin() ; i != listclassinstr->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListStmt(ListStmt* liststmt)
{
  for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListItem(ListItem* listitem)
{
  for (ListItem::iterator i = listitem->begin() ; i != listitem->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListLatteIdent(ListLatteIdent* listlatteident)
{
  for (ListLatteIdent::iterator i = listlatteident->begin() ; i != listlatteident->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListExpr(ListExpr* listexpr)
{
  for (ListExpr::iterator i = listexpr->begin() ; i != listexpr->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void Skeleton::visitInteger(Integer x)
{
  /* Code for Integer Goes Here */
}

void Skeleton::visitChar(Char x)
{
  /* Code for Char Goes Here */
}

void Skeleton::visitDouble(Double x)
{
  /* Code for Double Goes Here */
}

void Skeleton::visitString(String x)
{
  /* Code for String Goes Here */
}

void Skeleton::visitIdent(Ident x)
{
  /* Code for Ident Goes Here */
}



