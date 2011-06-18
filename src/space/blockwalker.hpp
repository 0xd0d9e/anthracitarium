//encoding utf-8
//author dodge
#ifndef __BlockWalker__
#define __BlockWalker__

#include "block.hpp"
#include "blockindex.hpp"
#include "chunkwalker.hpp"
#include "spacenode.hpp"

namespace Space
{

class BlockWalker : public ChunkWalker
{
public:
    BlockIndex blockIndex() const { return blockIndex_; }

    void setBlockIndex( const BlockIndex & index );
    bool nextChunkBlock();
    SpaceNode<Block> blockNode;

    static void test();

private:
    BlockIndex blockIndex_;

};


}//namespace Space

#endif//__BlockWalker__
