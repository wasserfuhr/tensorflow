/* Copyright 2015 Google Inc. All Rights Reserved.

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

// Helper routines for encoding/decoding tensor contents.
#ifndef TENSORFLOW_PLATFORM_TENSOR_CODING_H_
#define TENSORFLOW_PLATFORM_TENSOR_CODING_H_

#include <string>
#include "tensorflow/core/lib/core/refcount.h"
#include "tensorflow/core/lib/core/stringpiece.h"
#include "tensorflow/core/platform/platform.h"
#include "tensorflow/core/platform/port.h"

#ifdef PLATFORM_GOOGLE
#include "tensorflow/core/platform/google/cord_coding.h"
#endif

namespace tensorflow {
namespace port {

// Store src contents in *out.  If backing memory for src is shared with *out,
// will ref obj during the call and will arrange to unref obj when no
// longer needed.
void AssignRefCounted(StringPiece src, core::RefCounted* obj, string* out);

// Copy contents of src to dst[0,src.size()-1].
inline void CopyToArray(const string& src, char* dst) {
  memcpy(dst, src.data(), src.size());
}

// Store encoding of strings[0..n-1] in *out.
void EncodeStringList(const string* strings, int64 n, string* out);

// Decode n strings from src and store in strings[0..n-1].
// Returns true if successful, false on parse error.
bool DecodeStringList(const string& src, string* strings, int64 n);

// Assigns base[0..bytes-1] to *s
void CopyFromArray(string* s, const char* base, size_t bytes);

}  // namespace port
}  // namespace tensorflow

#endif  // TENSORFLOW_PLATFORM_TENSOR_CODING_H_
