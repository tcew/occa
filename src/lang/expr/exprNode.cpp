#include <occa/lang/expr/exprNode.hpp>

namespace occa {
  namespace lang {
    namespace exprNodeType {
      const udim_t empty             = (((uint64_t) 1) << 0);
      const udim_t primitive         = (((uint64_t) 1) << 1);
      const udim_t char_             = (((uint64_t) 1) << 2);
      const udim_t string            = (((uint64_t) 1) << 3);
      const udim_t identifier        = (((uint64_t) 1) << 4);
      const udim_t type              = (((uint64_t) 1) << 5);
      const udim_t vartype           = (((uint64_t) 1) << 6);
      const udim_t variable          = (((uint64_t) 1) << 7);
      const udim_t function          = (((uint64_t) 1) << 8);

      const udim_t value             = (primitive |
                                        type      |
                                        vartype   |
                                        variable  |
                                        function);

      const udim_t rawOp             = (((uint64_t) 1) << 9);
      const udim_t leftUnary         = (((uint64_t) 1) << 10);
      const udim_t rightUnary        = (((uint64_t) 1) << 11);
      const udim_t binary            = (((uint64_t) 1) << 12);
      const udim_t ternary           = (((uint64_t) 1) << 13);
      const udim_t op                = (leftUnary  |
                                        rightUnary |
                                        binary     |
                                        ternary);

      const udim_t pair              = (((uint64_t) 1) << 14);

      const udim_t subscript         = (((uint64_t) 1) << 15);
      const udim_t call              = (((uint64_t) 1) << 16);

      const udim_t sizeof_           = (((uint64_t) 1) << 17);
      const udim_t sizeof_pack_      = (((uint64_t) 1) << 18);
      const udim_t new_              = (((uint64_t) 1) << 19);
      const udim_t delete_           = (((uint64_t) 1) << 20);
      const udim_t throw_            = (((uint64_t) 1) << 21);

      const udim_t typeid_           = (((uint64_t) 1) << 22);
      const udim_t noexcept_         = (((uint64_t) 1) << 23);
      const udim_t alignof_          = (((uint64_t) 1) << 24);

      const udim_t const_cast_       = (((uint64_t) 1) << 25);
      const udim_t dynamic_cast_     = (((uint64_t) 1) << 26);
      const udim_t static_cast_      = (((uint64_t) 1) << 27);
      const udim_t reinterpret_cast_ = (((uint64_t) 1) << 28);

      const udim_t funcCast          = (((uint64_t) 1) << 29);
      const udim_t parenCast         = (((uint64_t) 1) << 30);
      const udim_t constCast         = (((uint64_t) 1) << 31);
      const udim_t staticCast        = (((uint64_t) 1) << 32);
      const udim_t reinterpretCast   = (((uint64_t) 1) << 33);
      const udim_t dynamicCast       = (((uint64_t) 1) << 34);

      const udim_t parentheses       = (((uint64_t) 1) << 35);
      const udim_t tuple             = (((uint64_t) 1) << 36);
      const udim_t cudaCall          = (((uint64_t) 1) << 37);
    }

    exprNode::exprNode(token_t *token_) :
      token(token_t::clone(token_)) {}

    exprNode::~exprNode() {
      delete token;
    }

    exprNode* exprNode::clone(exprNode *expr) {
      if (!expr) {
        return NULL;
      }
      return expr->clone();
    }

    bool exprNode::canEvaluate() const {
      return false;
    }

    primitive exprNode::evaluate() const {
      return primitive();
    }

    exprNode* exprNode::startNode() {
      return this;
    }

    exprNode* exprNode::endNode() {
      return this;
    }

    bool exprNode::hasAttribute(const std::string &attr) const {
      return false;
    }

    variable_t* exprNode::getVariable() {
      return NULL;
    }

    exprNode* exprNode::wrapInParentheses() {
      return clone();
    }

    std::string exprNode::toString() const {
      std::stringstream ss;
      printer pout(ss);
      pout << (*this);
      return ss.str();
    }

    void exprNode::printWarning(const std::string &message) const {
      token->printWarning(message);
    }

    void exprNode::printError(const std::string &message) const {
      token->printError(message);
    }

    void exprNode::debugPrint() const {
      debugPrint("");
      std::cerr << '\n';
    }

    void exprNode::childDebugPrint(const std::string &prefix) const {
      debugPrint(prefix + "|   ");
    }

    std::ostream& operator << (std::ostream &out,
                               const exprNode &node) {
      printer pout(out);
      node.print(pout);
      return out;
    }

    printer& operator << (printer &pout,
                          const exprNode &node) {
      node.print(pout);
      return pout;
    }

    void cloneExprNodeVector(exprNodeVector &dest,
                             const exprNodeVector &src) {
      const int nodes = (int) src.size();
      dest.clear();
      dest.reserve(nodes);
      for (int i = 0; i < nodes; ++i) {
        dest.push_back(src[i]->clone());
      }
    }

    void freeExprNodeVector(exprNodeVector &vec) {
      const int nodes = (int) vec.size();
      for (int i = 0; i < nodes; ++i) {
        delete vec[i];
      }
      vec.clear();
    }
  }
}