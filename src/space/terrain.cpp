//encoding utf-8
//author dodge
#include <assert.h>

#include <QRect>

#include "abstractchunkdataprovider.hpp"
#include "block.hpp"
#include "blockindex.hpp"
#include "chunk.hpp"
#include "chunkindex.hpp"
#include "terrain.hpp"

namespace Space
{

Terrain::Terrain()
    : chunkDataProvider_(0)
{
}


Chunk * Terrain::chunk( const ChunkIndex & index ) const
{
    return chunks_.value( index, 0 );
}

Block * Terrain::block( const BlockIndex & index ) const
{
    ChunkIndex ci = index.toChunkIndex(chunkSize_);
    if ( Chunk * c = chunk(ci) )
    {
        return c->block( index.plainIndex(chunkSize_) );
    }
    return 0;
}

const Size & Terrain::chunkSize() const
{
    return chunkSize_;
}

const QRect & Terrain::chunksRect() const
{
    return chunksRect_;
}

void Terrain::setVisibleRect( const QRect & rect )
{
//     qDebug("> Prepare terrain content");
//     QMap<ChunkIndex,Chunk*>::iterator current,
//                                        next = chunks_.begin();
//     for ( ; current != chunks_.end();  )
//     {
//         current = next;
//         ++next;
//         const ChunkIndex & index = current.key();
//         if ( !rect.contains( QPoint( index.p[0], index.p[1] ) ) )
//         {
//             qDebug() << "  Remove chunk at" << index;
//             delete current.value();
//             chunks_.erase(current);
//             qDebug() << "    ok";
//         }
//     }
    chunksRect_ = rect;
    QMap<ChunkIndex,Chunk*>::iterator current = chunks_.begin();
    QList<ChunkIndex> deadlyShadows;
    for ( ; current != chunks_.end(); ++current )
    {
        const ChunkIndex & index = current.key();
        if ( !rect.contains( QPoint( index.p[0], index.p[1] ) ) )
        {
            deadlyShadows.push_back(index);
        }
    }
    ChunkIndex index;
    while ( deadlyShadows.count() )
    {
        index = deadlyShadows.takeFirst();
        assert(chunks_[index]);
        delete chunks_[index];
        chunks_.remove(index);
    }
//     int count = 0;
    for ( qint32 y = rect.top(); y != rect.y() + rect.height(); ++y )
    {
        for ( qint32 x = rect.left(); x != rect.x() + rect.width(); ++x )
        {
            ensureChunk( ChunkIndex( x, y, 0 ) );
//             ++count;
        }
    }
//     assert( count == ( rect.width() * rect.height() ) );
}

// static
void Terrain::test()
{
    printf("* Terrain base func test\n");
    Terrain terrain;
    Size chunkSize( 16, 16, 128 );
    terrain.setChunkSize(chunkSize);
    ChunkIndex chunkIndex( 0, 0, 0 );
    printf( "  Not exists chunk access      %s\n", !terrain.chunk(chunkIndex) ? "ok" : "fail" );
    printf( "  Create chunk                 %s\n", terrain.ensureChunk(chunkIndex) ? "ok" : "fail" );
    Chunk * chunk = terrain.chunk(chunkIndex);
    printf( "  Exists chunk access          %s\n", chunk ? "ok" : "fail" );
    int checksum = 1;
    if (chunk)
    {
        checksum = 0;
        Block * block;
        for ( quint32 i = 0; i < chunk->size(); ++i )
        {
            block = chunk->block(i);
            assert(block);
            checksum += block->type;
        }
    }
    printf( "  Chunk checksum:              %s\n", !checksum ? "ok" : "fail" );
    if (chunk)
    {
        qint32 i = 0;
        const Block * block;
        for ( quint32 z = 0; z < chunkSize.p[2]; ++z )
        {
            for ( quint32 y = 0; y < chunkSize.p[1]; ++y )
            {
                for ( quint32 x = 0; x < chunkSize.p[0]; ++x )
                {
                    block = terrain.block( BlockIndex( x, y, z ) );
                    assert(block);
                    assert( block == chunk->block(i) );
                    ++ i;
                }
            }
        }
    }
    printf( "  Block align and access:      ok\n" );

    terrain.setVisibleRect( QRect( -5, -5, 10, 10 ) );
    printf( "  Chunk rect creation:         %s\n", ( terrain.chunks_.count() == 100 ) ? "ok" : "fail" );

}

void Terrain::setChunkSize( const Size & chunkSize )
{
    chunkSize_ = chunkSize;
}

Chunk * Terrain::ensureChunk( const ChunkIndex & index )
{
    Chunk *& chunk = chunks_[index  ];
    if (!chunk)
    {
//         qDebug() << "> Create chunk at" << index;
        chunk = new Chunk(chunkSize_);
        if (chunkDataProvider_)
        {
//             qDebug() << "> Load data" << index;
            chunkDataProvider_->load( this, chunk, index );
        }
    }
    return chunk;
}

}//namespace Space
