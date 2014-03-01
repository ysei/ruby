#pragma once
#include <vector>
#include <unordered_map>
#include "rbjit/common.h"
#include "rbjit/rubytypes.h"

RBJIT_NAMESPACE_BEGIN

class Variable;
class Opcode;
class BlockHeader;
class OpcodeFactory;

////////////////////////////////////////////////////////////
// IdTable
//
// Helper class to treat the node nd_tbl

class IdTable {
public:

  IdTable(ID* tbl)
    : size_(tbl ? (size_t)*tbl++ : 0), table_(tbl)
    {}

  size_t size() const { return size_; }
  ID id(size_t i) const { return table_[i]; }

private:

  size_t size_;
  ID* table_;
};

////////////////////////////////////////////////////////////
// CfgBuilder

class CfgBuilder {
public:

  CfgBuilder() : cfg_(0) {}

  ControlFlowGraph* buildMethod(const RNode* rootNode);

private:

  Variable* getNamedVariable(OpcodeFactory* factory, ID name);

  void buildProcedureBody(OpcodeFactory* factory, const RNode* node, bool useResult);
  Variable* buildNode(OpcodeFactory* factory, const RNode* node, bool useResult);
  Variable* buildAssignment(OpcodeFactory* factory, const RNode* node, bool useResult);
  Variable* buildLocalVariable(OpcodeFactory* factory, const RNode* node, bool useResult);
  Variable* buildImmediate(OpcodeFactory* factory, const RNode* node, bool useResult);
  Variable* buildTrue(OpcodeFactory* factory, const RNode* node, bool useResult);
  Variable* buildFalse(OpcodeFactory* factory, const RNode* node, bool useResult);
  Variable* buildNil(OpcodeFactory* factory, const RNode* node, bool useResult);
  Variable* buildIf(OpcodeFactory* factory, const RNode* node, bool useResult);
  Variable* buildCall(OpcodeFactory* factory, const RNode* node, bool useResult);

  ControlFlowGraph* cfg_;

  std::unordered_map<ID, Variable*> namedVariables_;

/*
  struct ExitPoint {
    OpcodeFactory* cond_;
    OpcodeFactory* block_;
    OpcodeFactory* exit_;
    Variable* result_;

    ExitPoint(OpcodeFactory* cond, OpcodeFactory* block, OpcodeFactory* exit, Variable* result)
      : cond_(cond), block_(block), exit_(exit), result_(result)
    {}
  };

  std::vector<ExitPoint> exits_;
  std::vector<OpcodeFactory*> rescueBlocks_;
  std::vector<const AstNode*> ensureNodes_;
  std::vector<OpcodeFactory*> retryBlocks_;
  std::vector<BlockHeader*> idomUnknown_;

  std::vector<BlockHeader*> lastSingleEntries_;
  BlockHeader* lastSingleEntry_;
  BlockHeader* exitIdom_;
  BlockHeader* condIdom_;
  OpcodeFactory exitBlock_;

  int* dfsOrder_;
  */
};

RBJIT_NAMESPACE_END
