/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkColorFilter_Matrix_DEFINED
#define SkColorFilter_Matrix_DEFINED

#include "include/core/SkColorFilter.h"
#include "include/core/SkFlattenable.h"

class SkColorFilter_Matrix : public SkColorFilter {
public:
    enum class Domain : uint8_t { kRGBA, kHSLA };

    explicit SkColorFilter_Matrix(const float array[20], Domain);

    uint32_t getFlags() const override;

#if SK_SUPPORT_GPU
    std::unique_ptr<GrFragmentProcessor> asFragmentProcessor(GrRecordingContext*,
                                                             const GrColorInfo&) const override;
#endif

    static void RegisterFlattenables();

private:
    void flatten(SkWriteBuffer&) const override;
    bool onAsAColorMatrix(float matrix[20]) const override;

    SK_FLATTENABLE_HOOKS(SkColorFilter_Matrix)

    bool onAppendStages(const SkStageRec& rec, bool shaderIsOpaque) const override;
    bool program(skvm::Builder*,
                 SkColorSpace* dstCS,
                 skvm::Arg uniforms, size_t offset,
                 skvm::I32* r, skvm::I32* g, skvm::I32* b, skvm::I32* a) const override;
    void uniforms(SkColorSpace* dstCS, std::vector<uint32_t>*) const override;

    float       fMatrix[20];
    uint16_t    fFlags;
    Domain      fDomain;

    typedef SkColorFilter INHERITED;
};

#endif
