#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "../Absyn.H"


class Skeleton : public Visitor
{
public:
  void visitProgram(Program* p);
  void visitTopDef(TopDef* p);
  void visitArg(Arg* p);
  void visitClassInstr(ClassInstr* p);
  void visitBlock(Block* p);
  void visitStmt(Stmt* p);
  void visitItem(Item* p);
  void visitLatteIdent(LatteIdent* p);
  void visitType(Type* p);
  void visitExpr(Expr* p);
  void visitAddOp(AddOp* p);
  void visitMulOp(MulOp* p);
  void visitRelOp(RelOp* p);
  void visitProg(Prog* p);
  void visitFnDef(FnDef* p);
  void visitClassDefNoInher(ClassDefNoInher* p);
  void visitClassDefInher(ClassDefInher* p);
  void visitAr(Ar* p);
  void visitMethodDef(MethodDef* p);
  void visitFieldDef(FieldDef* p);
  void visitBlk(Blk* p);
  void visitEmpty(Empty* p);
  void visitBStmt(BStmt* p);
  void visitDecl(Decl* p);
  void visitNoInit(NoInit* p);
  void visitInit(Init* p);
  void visitInitArray(InitArray* p);
  void visitInitObj(InitObj* p);
  void visitSingleIdent(SingleIdent* p);
  void visitArrayIdent(ArrayIdent* p);
  void visitSelfIdent(SelfIdent* p);
  void visitAss(Ass* p);
  void visitAssArr(AssArr* p);
  void visitAssObj(AssObj* p);
  void visitIncr(Incr* p);
  void visitDecr(Decr* p);
  void visitRet(Ret* p);
  void visitVRet(VRet* p);
  void visitCond(Cond* p);
  void visitCondElse(CondElse* p);
  void visitWhile(While* p);
  void visitForeach(Foreach* p);
  void visitSExp(SExp* p);
  void visitClass(Class* p);
  void visitInt(Int* p);
  void visitStr(Str* p);
  void visitBool(Bool* p);
  void visitVoid(Void* p);
  void visitArrayType(ArrayType* p);
  void visitEVar(EVar* p);
  void visitELitInt(ELitInt* p);
  void visitELitFalse(ELitFalse* p);
  void visitELitNull(ELitNull* p);
  void visitELitTrue(ELitTrue* p);
  void visitEApp(EApp* p);
  void visitEInstanceApp(EInstanceApp* p);
  void visitEString(EString* p);
  void visitNeg(Neg* p);
  void visitNot(Not* p);
  void visitECast(ECast* p);
  void visitEMul(EMul* p);
  void visitEAdd(EAdd* p);
  void visitERel(ERel* p);
  void visitEAnd(EAnd* p);
  void visitEOr(EOr* p);
  void visitPlus(Plus* p);
  void visitMinus(Minus* p);
  void visitTimes(Times* p);
  void visitDiv(Div* p);
  void visitMod(Mod* p);
  void visitLTH(LTH* p);
  void visitLE(LE* p);
  void visitGTH(GTH* p);
  void visitGE(GE* p);
  void visitEQU(EQU* p);
  void visitNE(NE* p);
  void visitListTopDef(ListTopDef* p);
  void visitListArg(ListArg* p);
  void visitListClassInstr(ListClassInstr* p);
  void visitListStmt(ListStmt* p);
  void visitListItem(ListItem* p);
  void visitListLatteIdent(ListLatteIdent* p);
  void visitListExpr(ListExpr* p);

  void visitInteger(Integer x);
  void visitChar(Char x);
  void visitDouble(Double x);
  void visitString(String x);
  void visitIdent(Ident x);

};


#endif
