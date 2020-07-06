/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

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

#ifndef TENSORFLOW_COMPILER_MLIR_HLO_INCLUDE_MLIR_HLO_DIALECT_MHLO_IR_CHLO_OPS_H_
#define TENSORFLOW_COMPILER_MLIR_HLO_INCLUDE_MLIR_HLO_DIALECT_MHLO_IR_CHLO_OPS_H_

#include "third_party/llvm/llvm-project/llvm/include/llvm/ADT/StringRef.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/Dialect.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/DialectImplementation.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/MLIRContext.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/OpDefinition.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/Operation.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/StandardTypes.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/IR/Types.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/Interfaces/InferTypeOpInterface.h"
#include "third_party/llvm/llvm-project/mlir/include/mlir/Interfaces/SideEffectInterfaces.h"

namespace mlir {
namespace xla_chlo {

class XlaHloClientDialect : public Dialect {
 public:
  explicit XlaHloClientDialect(MLIRContext *context);
  static StringRef getDialectNamespace() { return "xla_chlo"; }
};

#define GET_OP_CLASSES
#include "third_party/tensorflow/compiler/mlir/hlo/include/mlir-hlo/Dialect/mhlo/IR/chlo_ops.h.inc"

}  // namespace xla_chlo
}  // namespace mlir

#endif  // TENSORFLOW_COMPILER_MLIR_HLO_INCLUDE_MLIR_HLO_DIALECT_MHLO_IR_CHLO_OPS_H_
