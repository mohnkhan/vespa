// Copyright 2016 Yahoo Inc. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#pragma once

#include "datastorebase.h"
#include "entryref.h"
#include "handle.h"

namespace search {
namespace datastore {

/**
 * Allocator used to allocate entries of a specific type in an underlying data store.
 */
template <typename EntryT, typename RefT>
class Allocator
{
public:
    using ConstArrayRef = vespalib::ConstArrayRef<EntryT>;
    using HandleType = Handle<EntryT>;

protected:
    DataStoreBase &_store;
    uint32_t _typeId;

public:
    Allocator(DataStoreBase &store, uint32_t typeId);

    template <typename ... Args>
    HandleType alloc(Args && ... args);

    HandleType allocArray(ConstArrayRef array);
    HandleType allocArray(size_t size);
};

}
}