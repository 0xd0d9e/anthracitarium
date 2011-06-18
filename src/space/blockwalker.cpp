//encoding utf-8
//author dodge
#include <assert.h>

#include "blockwalker.hpp"
#include "terrain.hpp"

namespace Space
{

void BlockWalker::setBlockIndex( const BlockIndex & index )
{
    assert( terrain() );
    setChunkIndex( index.toChunkIndex( terrain()->chunkSize() ) );
    blockIndex_ = index - chunkIndex() * terrain()->chunkSize();
//         qDebug() << "Chunk index" << chunkIndex().p[0] << chunkIndex().p[1] << chunkIndex().p[2];
//         qDebug() << "Local index" << blockIndex_.p[0] << blockIndex_.p[1] << blockIndex_.p[2];
//         qDebug() << "Global index" << index.p[0] << index.p[1] << index.p[2];
    blockNode.current = block(blockIndex_);
    blockNode.left = block( blockIndex_.left() );
    blockNode.right = block( blockIndex_.right() );
    blockNode.front = block( blockIndex_.front() );
    blockNode.back = block( blockIndex_.back() );
    blockNode.top = block( blockIndex_.top() );
    blockNode.bottom = block( blockIndex_.bottom() );
}

bool BlockWalker::nextChunkBlock()
{
    if ( Terrain * terrain = TerrainWalker::terrain() )
    {
        const Size & chunkSize = terrain->chunkSize();
        ++blockIndex_.p[0];
        if ( blockIndex_.p[0] >= static_cast<qint32>(chunkSize.p[0]) )
        {
            blockIndex_.p[0] = 0;
            ++blockIndex_.p[1];
            if ( blockIndex_.p[1] >= static_cast<qint32>(chunkSize.p[1]) )
            {
                blockIndex_.p[1] = 0;
                ++blockIndex_.p[2];
                if ( blockIndex_.p[2] >= static_cast<qint32>(chunkSize.p[2]) )
                {
                    return false;
                }
            }
        }
        blockNode.current = block(blockIndex_);
        blockNode.left = block( blockIndex_.left() );
        blockNode.right = block( blockIndex_.right() );
        blockNode.front = block( blockIndex_.front() );
        blockNode.back = block( blockIndex_.back() );
        blockNode.top = block( blockIndex_.top() );
        blockNode.bottom = block( blockIndex_.bottom() );
        return true;
    }
    return false;
}

// static
void BlockWalker::test()
{
    printf("* BlockWalker base func test\n");
    Terrain terrain;
    Size chunkSize( 100, 100, 100 );

    terrain.setChunkSize(chunkSize);
    BlockIndex blockIndex( 0, 0, 0 );
    ChunkIndex chunkIndex( blockIndex.toChunkIndex(chunkSize) );
    terrain.setVisibleRect( QRect( -1, -1, 2, 2 ) );

    BlockWalker blockWalker;
    blockWalker.setTerrain(&terrain);
    blockWalker.setBlockIndex(blockIndex);

    printf( "  Start block access           %s\n", blockWalker.blockNode.current ? "ok" : "fail" );

    Chunk * chunk = terrain.chunk(chunkIndex);
    assert(chunk);

    for ( quint32 i = 0; i < chunk->size(); ++i )
    {
        assert( chunk->block(i) );
        chunk->block(i)->type = i;
    }

    quint32 i = 0;
    if (blockWalker.blockNode.current) do
    {
//             qDebug() << blockWalker.blockIndex();
        assert(blockWalker.blockNode.current);
        assert( chunk->block(i) );
//             qDebug() << i << chunk->block(i)->type;
        assert( chunk->block(i) == blockWalker.blockNode.current );
        ++i;
    }
    while ( blockWalker.nextChunkBlock() );
//         qDebug() << chunk->size() << i << terrain.chunkSize.square();
    printf( "  Block access                 %s\n", ( chunk->size() == i ) ? "ok" : "fail" );

}

}//namespace Space
