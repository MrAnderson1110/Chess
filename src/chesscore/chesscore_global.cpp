#include "chesscore_global.h"

namespace CORE_GLOBAL {

void unite(AvailableMoves &dest, const AvailableMoves &source)
{
    for(AvailableMoves::const_iterator it = source.cbegin(); it != source.cend(); ++it)
        dest[it.key()] << it.value();
}

}
