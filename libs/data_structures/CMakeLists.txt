add_library(data_structures
        bitset/bitset.c
        bitset/bitset.h
        unordered_array_set/unordered_array_set.c
        unordered_array_set/unordered_array_set.h
        ordered_array_set/ordered_array_set.c
        ordered_array_set/ordered_array_set.h
        vector/vector.c
        vector/vector.h
        vector/vectorVoid.c
        vector/vectorVoid.h
        matrix/matrix.c
        matrix/matrix.h
)

target_link_libraries(data_structures algorithms)