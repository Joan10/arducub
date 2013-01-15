#include "basic3d.h"

t_obj cub =
{
    {
        -10,-10, 10, //vertex v0
         10,-10, 10, //vertex v1
         10,-10,-10, //vertex v2
        -10,-10,-10, //vertex v3
        -10, 10, 10, //vertex v4
         10, 10, 10, //vertex v5
         10, 10,-10, //vertex v6
        -10, 10,-10  //vertex v7
    },
    {
        0, 1, 4, //polygon v0,v1,v4
        1, 5, 4, //polygon v1,v5,v4
        1, 2, 5, //polygon v1,v2,v5
        2, 6, 5, //polygon v2,v6,v5
        2, 3, 6, //polygon v2,v3,v6
        3, 7, 6, //polygon v3,v7,v6
        3, 0, 7, //polygon v3,v0,v7
        0, 4, 7, //polygon v0,v4,v7
        4, 5, 7, //polygon v4,v5,v7
        5, 6, 7, //polygon v5,v6,v7
        3, 2, 0, //polygon v3,v2,v0
        2, 1, 0, //polygon v2,v1,v0
    }
};

