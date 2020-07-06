/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

// This file defines the operations used in the XLA dialect.

#ifndef TENSORFLOW_COMPILER_MLIR_HLO_INCLUDE_MLIR_HLO_DIALECT_MHLO_IR_HLO_OPS_H_
#define TENSORFLOW_COMPILER_MLIR_HLO_INCLUDE_MLIR_HLO_DIALECT_MHLO_IR_HLO_OPS_H_

#include "third_party/llvm/llvm-project/llvm/include/llvm/ADT/StringRef.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/Attributes.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/Dialect.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/DialectImplementation.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/Location.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/MLIRContext.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/OpDefinition.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/Operation.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/StandardTypes.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/Types.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/Interfaces/InferTypeOpInterface.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/Interfaces/SideEffectInterfaces.h"
#include "third_party/tensorflow/compiler/mlir/hlo/include/mlir-hlo/Dialect/mhlo/IR/infer_fusibility_op_interface.h"

namespace mlir {
class OpBuilder;

#include "third_party/tensorflow/compiler/mlir/hlo/include/mlir-hlo/Dialect/mhlo/IR/hlo_structs.h.inc"

namespace xla_hlo {

class XlaHloDialect : public Dialect {
 public:
  explicit XlaHloDialect(MLIRContext *context);
  static StringRef getDialectNamespace() { return "xla_hlo"; }

  // Registered hook to materialize a constant operation from a given attribute
  // value with the desired resultant type.
  Operation *materializeConstant(OpBuilder &builder, Attribute value, Type type,
                                 Location loc) override;

  // Parses a type registered to this dialect.
  Type parseType(DialectAsmParser &parser) const override;

  // Prints a type registered to this dialect.
  void printType(Type type, DialectAsmPrinter &os) const override;
};

namespace HLOTypes {
enum Kind {
  Token = Type::FIRST_XLA_HLO_TYPE,
};
}  // namespace HLOTypes

class TokenType : public Type::TypeBase<TokenType, Type, TypeStorage> {
 public:
  using Base::Base;

  static TokenType get(MLIRContext *context) {
    return Base::get(context, HLOTypes::Token);
  }

  // Support method to enable LLVM-style type casting.
  static bool kindof(unsigned kind) { return kind == HLOTypes::Token; }
};

// Shape derivation function that computes the shape of the result based on
// the first argument. For a 2-dimensional input tensor, this produces IR of
// the form
//
//  %0 = dim %arg0, 0 : memref<?x?xf32>
//  %1 = index_cast %0 : index to i64
//  %2 = dim %arg0, 1 : memref<?x?xf32>
//  %3 = index_cast %2 : index to i64
//  %4 = "xla_hlo.scalars_to_dimension_tensor"(%1, %3)
//    : (i64, i64) -> tensor<2xi64>
//
// and returns %4 as the shape value.
LogicalResult deriveShapeFromFirstOperand(
    OpBuilder *builder, Operation *op,
    SmallVectorImpl<Value> *reifiedReturnShapes);

#define GET_OP_CLASSES
#include "third_party/tensorflow/compiler/mlir/hlo/include/mlir-hlo/Dialect/mhlo/IR/hlo_ops.h.inc"

}  // end namespace xla_hlo
}  // end namespace mlir

#endif  //  TENSORFLOW_COMPILER_MLIR_HLO_INCLUDE_MLIR_HLO_DIALECT_MHLO_IR_HLO_OPS_H_
