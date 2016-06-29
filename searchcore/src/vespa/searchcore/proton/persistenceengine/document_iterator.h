// Copyright 2016 Yahoo Inc. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#pragma once

#include <vespa/persistence/spi/bucket.h>
#include <vespa/persistence/spi/selection.h>
#include <vespa/persistence/spi/result.h>
#include "i_document_retriever.h"
#include <vespa/searchlib/common/idocumentmetastore.h>
#include <vespa/searchcore/proton/common/cachedselect.h>
#include <vespa/searchcore/proton/common/selectcontext.h>
#include <vespa/persistence/spi/read_consistency.h>

namespace proton {

class DocumentIterator
{
private:
    using ReadConsistency = storage::spi::ReadConsistency;
    const storage::spi::Bucket            _bucket;;
    const storage::spi::Selection         _selection;
    const storage::spi::IncludedVersions  _versions;
    const document::FieldSet::UP          _fields;
    const ssize_t                         _defaultSerializedSize;
    const ReadConsistency                 _readConsistency;
    const bool                            _metaOnly;
    const bool                            _ignoreMaxBytes;
    bool                                  _fetchedData;
    std::vector<IDocumentRetriever::SP>   _sources;
    size_t                                _nextItem;
    storage::spi::IterateResult::List     _list;


    bool useDocumentSelection() const;
    bool checkMeta(const search::DocumentMetaData &meta) const;
    bool checkDoc(const document::Document &doc) const;
    bool checkDoc(const SelectContext &sc) const;
    void fetchCompleteSource(const IDocumentRetriever & source, storage::spi::IterateResult::List & list);

public:
    DocumentIterator(const storage::spi::Bucket &bucket,
                     const document::FieldSet& fields,
                     const storage::spi::Selection &selection,
                     storage::spi::IncludedVersions versions,
                     ssize_t defaultSerializedSize,
                     bool ignoreMaxBytes,
                     ReadConsistency readConsistency=ReadConsistency::STRONG);
    void add(const IDocumentRetriever::SP &retriever);
    storage::spi::IterateResult iterate(size_t maxBytes);
};

} // namespace proton

