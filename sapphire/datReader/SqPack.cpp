#include "SqPack.h"

namespace xiv {
   namespace dat {

      struct SqPackHeader 
      {
         char magic[0x8]; 
         uint32_t zero; 
         uint32_t size; 
         uint32_t version; 
         uint32_t type;
      };

      struct SqPackIndexHeader
      {
         uint32_t size;
         uint32_t type;
      };
   }
}
namespace xiv {
   namespace utils {
      namespace bparse {
         template <> inline void reorder<xiv::dat::SqPackHeader>( xiv::dat::SqPackHeader& i_struct )
         {
            for( int i = 0; i < 0x8; ++i ) 
            {
               xiv::utils::bparse::reorder( i_struct.magic[i] );
            }
            xiv::utils::bparse::reorder( i_struct.zero );
            xiv::utils::bparse::reorder( i_struct.size ); 
            xiv::utils::bparse::reorder( i_struct.version ); 
            xiv::utils::bparse::reorder( i_struct.type );
         }

         template <> inline void reorder<xiv::dat::SqPackIndexHeader>( xiv::dat::SqPackIndexHeader& i_struct ) 
         { 
            xiv::utils::bparse::reorder( i_struct.size );
            xiv::utils::bparse::reorder( i_struct.type );
         }
      }
   }
};

using xiv::utils::bparse::extract;

namespace xiv
{
   namespace dat
   {

      SqPack::SqPack( const boost::filesystem::path& i_path ) :
         // Open the file
         _handle( i_path.string(), std::ios_base::in | std::ios_base::binary )
      {
         //XIV_DEBUG(xiv_dat_logger, "Initializing SqPack with path: " << i_path);

         // Extract the header
         extract<SqPackHeader>( _handle );

         // Skip until the IndexHeader the extract it
         _handle.seekg( 0x400 );
         extract<SqPackIndexHeader>( _handle );
      }

      SqPack::~SqPack()
      {
      }

      void SqPack::is_block_valid( uint32_t i_offset, uint32_t i_size, const SqPackBlockHash& i_block_hash )
      {
         // TODO
      }

   }
}
